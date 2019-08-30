#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "scatterMap.h"

scatterMap::scatterMap() : ArAction("Draw Map")
{
	radius = 250;
	distance = 0;

}
ArActionDesired * scatterMap::fire(ArActionDesired d)
{
	robotX = myRobot->getX();
	robotY = myRobot->getY();
	robotTh = myRobot->getTh(); 

	distance = myRobot->getClosestSonarRange(-91, 91);
	//every 1.5 second if closest obstacle distance is less than 2000mm away
	if (time.mSecSince() > 1500 && distance < 2000)
	{
		sonarNum = myRobot->getClosestSonarNumber(-91, 91);
		//get angle of the sonar closest to an obstacle
		switch (sonarNum)
		{
		case 15: sonarAngle = 90; break;
		case 0: sonarAngle = 90; break;
		case 1: sonarAngle = 50; break;
		case 2: sonarAngle = 30; break;
		case 3: sonarAngle = 10; break;
		case 4: sonarAngle = -10; break;
		case 5: sonarAngle = -30; break;
		case 6: sonarAngle = -50; break;
		case 7: sonarAngle = -90; break;
		case 8: sonarAngle = -90; break;
		}

		sonarAngle = degToRad(sonarAngle);	//need to calculate in radians
		//get local x and y of the wall
		wallX = cos(sonarAngle) * (distance + radius);
		wallY = sin(sonarAngle) * (distance + radius);

		robotTh = degToRad(robotTh);
		//get global x and y of the wall
		global[0] = (wallX * cos(robotTh)) + (wallY * -(sin(robotTh)));
		global[1] = (wallX * sin(robotTh)) + (wallY * cos(robotTh));
		global[0] += robotX;
		global[1] += robotY;
		//reset timer
		time.setToNow();
		std::cout << "New Obstacle detected: " << std::endl
			<< "Robot local pos: " << "x: " << robotX << "y: " << robotY << std::endl
			<< "Robot local heading: " << robotTh * (180 / 3.14) << std::endl
			<< "Distance to obstacle: " << distance << std::endl
			<< "Angle to obstacle:" << sonarAngle * (180 / 3.14) << std::endl
			<< "Obstacle position: " << "x: " << global[0] << "y: " << global[1] << std::endl << std::endl;

	}
	return &desiredState; // give the desired state to the robot for actioning
}


double scatterMap::degToRad(double angle)
{
	angle = angle * 3.14 / 180;
	return angle;
}

double scatterMap::getXPoint()
{
	return global[0];
}

double scatterMap::getYPoint()
{
	return global[1];
}

double scatterMap::getDistance()
{
	return distance;
}