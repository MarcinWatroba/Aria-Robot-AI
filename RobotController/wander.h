// Signatures
#include <ctime>

class Wander : public ArAction // Class action inherits from ArAction
{
public:
	Wander(); // Constructor
	virtual ~Wander() {}  // Destructor
	virtual ArActionDesired * fire(ArActionDesired d); // Body of the action
	ArActionDesired desiredState; // Holds state of the robot that we wish to action

protected:
	ArTime time;

	double randomTurn;	//random degree of turn
	double deltaHeading; // Change in heading
	double leftSonar;
	double rightSonar;
	bool turning;
	bool distanceChosen;
	double randomDistance;	//random distance to travel before turn

};