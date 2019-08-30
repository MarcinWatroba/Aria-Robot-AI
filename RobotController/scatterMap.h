#pragma once

#include <vector>

using namespace std;

struct vertex2D
{
	int x;
	int y;
};

class scatterMap : public ArAction // Class action inherits from ArAction
{
public:
	scatterMap(); // Constructor
	virtual ~scatterMap() {}  // Destructor
	virtual ArActionDesired * fire(ArActionDesired d); // Body of the action
	ArActionDesired desiredState; // Holds state of the robot that we wish to action
	double getXPoint();	//get x point of the detected obstacle
	double getYPoint();	//get y point of the detected obstacle
	double getDistance();	//get distance to the detected obstacle
	vector<vertex2D> data;	//vector containing all the detected obstacle points

protected:

	double degToRad(double angle);	//converts degree to radians for calculations
	ArTime time;	//timer
	int sonarNum;	//ID of the sonar returning closest distance to an obstacle
	double sonarAngle;	//angle to the obstacle
	int radius;	//robot radius
	double distance;	//distance to the obstacle

	double wallX;	//wall local x pos
	double wallY;	//wall local y pos
	double global[2];	//wall global pos
	double robotX, robotY, robotTh; // Robots position and heading
};