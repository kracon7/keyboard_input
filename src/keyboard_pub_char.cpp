#include <ros/ros.h>
#include <ros/console.h>
#include <std_msgs/String.h>
#include <std_msgs/Char.h>
#include <termios.h>
#include <stdio.h>

ros::Publisher keyboard_pub;
using namespace std;

char getch()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);           // save old settings
  newt = oldt;
  newt.c_lflag &= ~(ICANON);                 // disable buffering      
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings
  std_msgs::Char C;
  char c = getchar();  // read character (non-blocking)
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
  return c;
}

int main(int argc, char** argv)
{

  ros::init(argc, argv, "keyboard_pub");
  ros::NodeHandle n;

  keyboard_pub = n.advertise<std_msgs::Char>("keyboard_pub", 1);

  char c = ' ';

  while (ros::ok())
  {
    std_msgs::Char C;
    c = getch();   // call your non-blocking input function
    C.data = c;
    keyboard_pub.publish(C);
    //if (c == 'a')
      //keyboard_pub.publish(c)
   // else if (c == 'b')
      //send message 'B'

  }
}
