#include <iostream>
#include <stdlib.h>
#include <Aria.h>

#include "wander.h"
// Implementation

// Constructor
Wander::Wander() : ArAction("Wander")
{
	turning = false;
	deltaHeading = 0;
	time.setToNow();
	distanceChosen = false;
	randomTurn = 0;

}

// Body of action
ArActionDesired * Wander::fire(ArActionDesired d)
{
	desiredState.reset(); // reset the desired state (must be done)

	//get readings of left and right sonars
	leftSonar = myRobot->getClosestSonarRange(-20, 100);
	rightSonar = myRobot->getClosestSonarRange(-100, 20);

	//if distance to an object is more than 1500mm
	if (leftSonar > 1500 && rightSonar > 1500)
	{
		//std::cout
		//	<< std::endl << "Wandering:" << std::endl
		//	<< "Closest object on right: " << rightSonar << " Closest object on left: " << leftSonar << std::endl
		//	<< "Speed: " << myRobot->getVel() << " Heading: " << myRobot->getTh() << std::endl
		//	<< "Location: X: " << myRobot->getX() << " Y: " << myRobot->getY() << std::endl <<
		//	std::endl;
		//std::cout << "Distance travelled since last turn: " << myRobot->getTripOdometerDistance() << std::endl;
		//std::cout << "Last angle of turn: " << randomTurn << std::endl;
		//if random distance hasn't been generated already, generate a new random distance
		if (distanceChosen == false)
		{
			randomDistance = rand() % 1000 + 500;
			distanceChosen = true;


		}
		//turn the robot if the distance that robot has travelled after the last turn is higher than the random distance chosen
		if (myRobot->getTripOdometerDistance() > randomDistance)
		{
			//generate a random angle of turn between -140 and 140 degrees
			if (turning == false)
			{
				time.setToNow();
				randomTurn = rand() % 280 - 140;

			}
			//let the robot know it is already turning so that it will not generate a new angle of turn again
			turning = true;
			desiredState.setVel(0);
			//turn by the generated angle at the spot
			desiredState.setDeltaHeading(randomTurn);
			//it takes robot 1 second to make a turn, after one second reset everything
			if (time.mSecSince() > 999)
			{
				time.setToNow();
				turning = false;
				myRobot->resetTripOdometer();
				distanceChosen = false;
			}
		}


		//if not turning set speed to 200mm/s
		if (turning == false)
		{
			desiredState.setVel(200);
		}
	}
	//make sure that turning is false after exiting this behaviour
	if (leftSonar < 1500 && rightSonar < 1500)
	{
		turning = false;
	}

	return &desiredState; // give the desired state to the robot for actioning
}
