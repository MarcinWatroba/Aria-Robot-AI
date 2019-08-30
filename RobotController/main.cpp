#include <iostream>

#include "Aria.h"
#include "avoid.h"
#include "wander.h"
#include "follow.h"
#include "scatterMap.h"

extern "C"
{
#include "glut.h"
}

using namespace std;

ArTime timer;
//RANSAC ransac;
Wander wander;
Follow follow;
Avoid avoid;
scatterMap drawMap;
float scatterUpdateTime;

void drawPoint(int n)
{
	//draw point every 1.5 seconds if distance is less than 2000mm, scale the positions to fit the window
	if (drawMap.getDistance() < 2000)
	{
		vertex2D datum;
		datum.x = (drawMap.getXPoint() / 50) + 400;
		datum.y = 600 - ((drawMap.getYPoint() / 50) + 300);
		drawMap.data.push_back(datum);
		glutPostRedisplay();
	}
	glutTimerFunc(scatterUpdateTime, drawPoint, 0);
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glPointSize(4);
	float size = 50;
	// Draw data
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	vector<vertex2D>::iterator i;
	for (i = drawMap.data.begin(); i != drawMap.data.end(); ++i)
	{

		glVertex2d(i->x, i->y);
	}
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	//initialize glut  window and callbacks
  srand(time(NULL));
  scatterUpdateTime = 1500;
  timer.setToNow();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Scattergram Map");
  glutDisplayFunc(render);
  glutTimerFunc(scatterUpdateTime, drawPoint, 0);
  glMatrixMode(GL_PROJECTION);
  glOrtho(0, 800, 0, 600, -10, 10); // Orthographic projection (x,y,z) ranges								// Background is white 
  glClearColor(1.0, 1.0, 1.0, 1.0);
						   //glutKeyboardFunc(key); // Use the key function for key board events
						  


  //initialize aria
  Aria::init();
  ArArgumentParser argParser(&argc, argv);
  argParser.loadDefaultArguments();
  ArRobot robot;
  ArRobotConnector robotConnector(&argParser, &robot);
  ArLaserConnector laserConnector(&argParser, &robot, &robotConnector);


  // Always try to connect to the first laser:
  argParser.addDefaultArgument("-connectLaser");

  if(!robotConnector.connectRobot())
  {
    ArLog::log(ArLog::Terse, "Could not connect to the robot.");
    if(argParser.checkHelpAndWarnUnparsed())
    {
        // -help not given, just exit.
        Aria::logOptions();
        Aria::exit(1);
    }
  }


  // Trigger argument parsing
  if (!Aria::parseArgs() || !argParser.checkHelpAndWarnUnparsed())
  {
    Aria::logOptions();
    Aria::exit(1);
  }

  ArKeyHandler keyHandler;
  Aria::setKeyHandler(&keyHandler);
  robot.attachKeyHandler(&keyHandler);

  puts("Press  Escape to exit.");
  
  ArSonarDevice sonar;
  robot.addRangeDevice(&sonar);

  robot.runAsync(true);

  
  // try to connect to laser. if fail, warn but continue, using sonar only
  if(!laserConnector.connectLasers())
  {
    ArLog::log(ArLog::Normal, "Warning: unable to connect to requested lasers, will wander using robot sonar only.");
  }



  // turn on the motors
  robot.enableMotors();
 

  // robot's behaviours
  ArActionStallRecover recover;
  ArActionBumpers bumpers;
  robot.addAction(&drawMap, 100);
  robot.addAction(&recover, 90);
  robot.addAction(&bumpers, 80);
  robot.addAction(&avoid, 60);
  robot.addAction(&follow, 40);
  robot.addAction(&wander, 20);


  glutMainLoop();


  
  // wait for robot task loop to end before exiting the program
  robot.waitForRunExit();

  Aria::exit(0);
  return EXIT_SUCCESS;

}
