/**
 * laser-roomba.cc
 * 
 * Sample code for a robot that has two front bumpers and a laser scanner.
 * Suitable for use with the roomba.
 *
 * Written by: Simon Parsons
 * Date:       11th October 2011
 *  
 **/


#include <iostream>
//#include <libplayerc++/playerc++.h>
//using namespace PlayerCc;  

/**
 * Function headers
 *
 **/

void printLaserData(LaserProxy& sp);
void printRobotData(BumperProxy& bp);

/**
 * main()
 *
 **/

int main(int argc, char *argv[])
{  


  // Variables
  int counter = 0;
  int i=10;
  int largest=0;
  double speed;            // How fast do we want the robot to go forwards?
  double turnrate;         // How fast do we want the robot to turn?
  player_laser_data laser; // For handling laser data
  double rangeFront;
  double rangeLeft;
  double rangeRight;

  // Set up proxies. These are the names we will use to connect to 
  // the interface to the robot.
  PlayerClient    robot("localhost");  
  BumperProxy     bp(&robot,0);  
  Position2dProxy pp(&robot,0);
  LaserProxy      sp(&robot, 0);

  // Allow the program to take charge of the motors (take care now)
  pp.SetMotorEnable(true);

  // Main control loop
  while(true) 
    {
      // Update information from the robot.
      robot.Read();

      // Print information about the laser. Check the counter first to stop
      // problems on startup
      //if(counter > 2){
			//	printLaserData(sp);
      //}

      // Print data on the robot to the terminal
      //printRobotData(bp);
      
      //std::cout << " 72";
      rangeFront = sp.GetRange(170);
      rangeLeft = sp.GetRange(350);
      rangeRight = sp.GetRange(10);
      largest = 10;
      //std::cout<<" 77";
      for ( i=10; i<=350 ; i=i+10) {
      	//std::cout<<i;
      	if ( sp.GetRange(i) > sp.GetRange(largest) ) 
      		largest = i;
      }
      
      //std::cout << "\nLargest: (" << largest << "): " << sp.GetRange(largest);
      
      speed = 0.2;
			turnrate = RTOD(sp.GetBearing(largest)*3);
      
      /*
      
      // If either bumper is pressed, stop. Otherwise just go forwards
      
     	if(bp[0] || bp[1]){
				speed= -2;
				turnrate= 0;
      } 
      else {
				if ( rangeFront < 1 && rangeLeft < 1.5 && rangeRight < 1.5 ) {
					speed= 0;
					turnrate= .1;
					std::cout << "\n\n\t :)\n\n\n";
				} else {
						
				}
      }  
      
      */   
      
      
      
      

      // What are we doing?
      std::cout << "Speed: " << speed << std::endl;      
      std::cout << "Turn rate: " << turnrate << std::endl << std::endl;

      // Send the commands to the robot
      pp.SetSpeed(speed, turnrate);  
      // Count how many times we do this
      counter++;
    }
  
} // end of main()


void printLaserData(LaserProxy& sp)
{

  double maxRange, minLeft, minRight, range,range1 ,range2,range3,range300, bearing;
  int points;

  // This illustrates the things the proxy provides. These should be self-explanatory
  // if you look at the print statements, except possible GetRange(5) and GetBearing(5).
  // These allow you to access one particular reading. You might want to use this
  // to look through all the values in a given arc to find the closest object.

  maxRange  = sp.GetMaxRange();
  minLeft   = sp.MinLeft();
  minRight  = sp.MinRight();
  points    = sp.GetCount();
  range1    = sp.GetRange(5);
  bearing   = sp.GetBearing(5);

  std::cout << "Laser says..." << std::endl;
  std::cout << "Maximum distance I can see: " << maxRange << std::endl;
  std::cout << "Number of readings I return: " << points << std::endl;
  std::cout << "Closest thing on left: " << minLeft << std::endl;
  std::cout << "Closest thing on right: " << minRight << std::endl;
  std::cout << "Range of a single point 5: " << range1 << std::endl;
  std::cout << "Bearing of a single point: " << bearing << std::endl;

  return;
} // End of printLaserData()

/**
 *  printRobotData
 *
 * Print out data on the state of the bumpers and the current location
 * of the robot.
 *
 **/

void printRobotData(BumperProxy& bp)
{

  // Print out what the bumpers tell us:
  std::cout << "Left  bumper: " << bp[0] << std::endl;
  std::cout << "Right bumper: " << bp[1] << std::endl;

  // Might want to add odometry data here also, but then you'd have
  // to pass the position proxy to the function.

} // End of printRobotData()