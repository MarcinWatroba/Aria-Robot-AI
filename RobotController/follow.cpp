#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include <fstream>
#include "follow.h"
//#include "scatterMap.h"
// Implementation

// Constructor
Follow::Follow() : ArAction("Follow Edge")
{
  speed = 200; // Set the robots speed to 200 mm/s
  deltaHeading = 0; // Straight line
  setPoint = 700; // 0.7 m
//  time.setToNow();
  pGain = 0.19; 
  iGain = 0.0001;
  dGain = -3.5;
  iMin = -800;
  iMax = 800;
  iErrorSum = 0;
  error = 0;
  proportional = 0;
  integral = 0;
  derivative = 0;
  rmse = 0;
  numOfErrors = 0;
  sumOfErrors = 0;

}

// Body of action
ArActionDesired * Follow::fire(ArActionDesired d)
{
 desiredState.reset(); // reset the desired state (must be done)

 // Get sonar readings
 leftSonar = myRobot->getClosestSonarRange(-20, 100);
 rightSonar = myRobot->getClosestSonarRange(-100, 20);

 //if distance is less than 1.5m
 if (leftSonar > 249 && rightSonar > 249)
 {
	 if (leftSonar < 1501 || rightSonar < 1501)
	 {
		 //if there's no obstacle to the left less than 1m away
		 if (leftSonar > 999)
		 {

			 followingLeft = false;
		 }
		 //if there's no obstacle to the right less than 1m away
		 if (rightSonar > 999)
		 {
			 followingRight = false;
		 }
		 // Find error when following edge to the left
		 if (leftSonar < 1000 && followingRight == false)
		 {
			 speed = 200;
			 error = leftSonar - setPoint;
			 followingLeft = true;
			 //std::cout << std::endl << "Following left wall:" << std::endl;
		 }
		 //find error when following edge to the right
		 else if (rightSonar < 1000 && followingLeft == false)
		 {
			 speed = 200;
			 followingRight = true;
			 error = setPoint - rightSonar;
			 //std::cout << std::endl << "Following right wall:" << std::endl;
		 }
		 //else not following any edge
		 else
		 {
			 //std::cout << std::endl << "Going straight:" << std::endl;
			 speed = 200;
			 error = 0;
			 lError = 0;
			 iErrorSum = 0;
			 errorDiff = 0;
		 }

		 //calculate integral with limits
		 iErrorSum += error;
		 if (iErrorSum > iMax)
		 {
			 iErrorSum = iMax;
		 }
		 else if (iErrorSum < iMin)
		 {
			 iErrorSum = iMin;
		 }
		 //calculate error difference for derivative
		 errorDiff = lError - error;
		 // calculate proportional, integral and derivative values
		 proportional = pGain * error;	//
		 integral = iGain * iErrorSum;
		 derivative = dGain * errorDiff;

		 /*Limit derivative to certain difference of an error, when an edge that robot is following ends, the difference of error might be really high.
		 For example when robot finds an edge 500mm to the left and then suddenly edge ends with next edge detected at 1500mm, the difference of an error is 1000.
		 This causes a very high derivative value which causes robot to turn instantly at a very high angle, setting a limit for derivative stops this problem*/
		 if (derivative > 25)
		 {
			 derivative = 25;
		 }
		 if (derivative < -25)
		 {
			 derivative = -25;
		 }

		 //calculating rmse, not sure if this is the correct way to calculate it though...
		 numOfErrors++;
		 sumOfErrors += error;
		 rmse = sqrt(pow(sumOfErrors, 2) / numOfErrors);

		 //output deltaheading based on PID feedback
		 output = proportional + integral + derivative;

		 //std::cout
			// << "Closest object on right: " << rightSonar << " Closest object on left: " << leftSonar << std::endl
			// << "Speed: " << myRobot->getVel() << " Heading: " << myRobot->getTh() << std::endl
			// << "Location: X: " << myRobot->getX() << " Y: " << myRobot->getY() << std::endl << "RMSE: " << rmse <<
			// std::endl;

		 //setting the last error value for next iteration
		 lError = error;
		 // Implement control action
		 deltaHeading = output;


		 desiredState.setVel(speed); // set the speed of the robot in the desired state
		 desiredState.setDeltaHeading(deltaHeading); // Set the heading change of the robot
	 }
 }
 return &desiredState; // give the desired state to the robot for actioning
}



