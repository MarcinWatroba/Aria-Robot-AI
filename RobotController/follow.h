// Signatures

class Follow : public ArAction // Class action inherits from ArAction
{
 public:
   Follow(); // Constructor
   virtual ~Follow() {}  // Destructor
   virtual ArActionDesired * fire(ArActionDesired d); // Body of the action
   ArActionDesired desiredState; // Holds state of the robot that we wish to action

 protected:
   int speed; // Speed of the robot in mm/s
   double deltaHeading; // Change in heading
   bool followingRight;	//true if following edge on the right
   bool followingLeft;	//true if following edge on the left
   // Reading
   double leftSonar;
   double rightSonar;
   int numOfErrors;	//num of errors for calculating rmse mean
   double sumOfErrors;	//sum of errors for calculating rmse mean
   // Control variables
   double rmse;
   double setPoint; // Set point of the controller
   double error; // Current error
   double lError; // Last error
   double errorDiff;	//difference between current and last error
   double output; // Final output signal
   double pGain; 
   double iGain;
   double dGain;
   double integral;
   double proportional;
   double derivative;
   double iErrorSum;	//sum of errors for integral
   double iMin;	//min error for integral
   double iMax;	//max error for integral

};