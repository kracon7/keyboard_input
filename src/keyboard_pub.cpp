#include <ros/ros.h>
#include <ros/console.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <termios.h>
#include <stdio.h>

ros::Publisher keyboard_pub;
using namespace std;

std_msgs::Int32 getch()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);           // save old settings
  newt = oldt;
  newt.c_lflag &= ~(ICANON);                 // disable buffering      
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings
  std_msgs::Int32 C;
  int c = getchar();  // read character (non-blocking)
  C.data = c;
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
  return C;
}

int
main(int argc, char** argv)
{

  ros::init(argc, argv, "keyboard_pub");
  ros::NodeHandle n;

  // keyboard_pub = n.advertise<std_msgs::Int32>("arduino_blue/keyboard_pub", 1);

  keyboard_pub = n.advertise<std_msgs::Int32>("keyboard_pub", 1);

  while (ros::ok())
  {
    std_msgs::Int32 c = getch();   // call your non-blocking input function
    keyboard_pub.publish(c);
    //if (c == 'a')
      //keyboard_pub.publish(c)
   // else if (c == 'b')
      //send message 'B'

  }
}
