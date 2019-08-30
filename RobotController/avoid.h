// Signatures
#include <ctime>

class Avoid: public ArAction // Class action inherits from ArAction
{
 public:
   Avoid(); // Constructor
   virtual ~Avoid() {}  // Destructor
   virtual ArActionDesired * fire(ArActionDesired d); // Body of the action
   ArActionDesired desiredState; // Holds state of the robot that we wish to action

 protected:
	 ArTime time;

   double deltaHeading; // Change in heading
   double leftSonar;
   double rightSonar;
   bool turningLeft;
   bool turningRight;
   bool avoiding;

};
