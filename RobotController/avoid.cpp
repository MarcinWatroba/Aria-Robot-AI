#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include <ariaUtil.h>

#include "avoid.h"
// Implementation

// Constructor
Avoid::Avoid() : ArAction("Avoid")
{
	avoiding = false;
	deltaHeading = 0;
	time.setToNow();
}

// Body of action
ArActionDesired * Avoid::fire(ArActionDesired d)
{
 desiredState.reset(); // reset the desired state (must be done)

 leftSonar = myRobot->getClosestSonarRange(-20, 100);
 rightSonar = myRobot->getClosestSonarRange(-100, 20);

 //avoid obstacle to the left of robot that's less than 250mm away, make sure robot was not turning in other direction before starting to turn in this direction
 //otherwise the robot would keep turning left and right infinitely in some circumstances, for example corners
 if(leftSonar < 250 && turningLeft == false)
 {

	 time.setToNow();
	 avoiding = true;
	 turningRight = true;
	 desiredState.setVel(0);
	 desiredState.setDeltaHeading(deltaHeading - 30);
	 myRobot->resetTripOdometer();
	 //std::cout
		// << std::endl << "Avoiding:" << std::endl
		// << "Closest object on right: " << rightSonar << " Closest object on left: " << leftSonar << std::endl
		// << "Speed: " << myRobot->getVel() << " Heading: " << myRobot->getTh() << std::endl
		// << "Location: X: " << myRobot->getX() << " Y: " << myRobot->getY() << std::endl <<
		// std::endl;
 }
 //avoid obstacle to ther ight of the robot that is less than 250mm away
 else if(rightSonar < 250 && turningRight == false)
 {
	 time.setToNow();
	 turningLeft = true;
	 avoiding = true;
	 desiredState.setVel(0);
	 desiredState.setDeltaHeading(deltaHeading + 30);
	 myRobot->resetTripOdometer();
	 //std::cout
		// << std::endl << "Avoiding:" << std::endl
		// << "Closest object on right: " << rightSonar << " Closest object on left: " << leftSonar << std::endl
		// << "Speed: " << myRobot->getVel() << " Heading: " << myRobot->getTh() << std::endl
		// << "Location: X: " << myRobot->getX() << " Y: " << myRobot->getY() << std::endl <<
		// std::endl;

 }
 else 
 {
	 avoiding = false;
 }
 //make sure robot resets these booleans after the turn has been completed
 if (avoiding == false ) {
	 turningLeft = false;
	 turningRight = false;

 }

 return &desiredState; // give the desired state to the robot for actioning
}
