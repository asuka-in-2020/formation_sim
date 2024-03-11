#include "ros/ros.h"
#include "Simulator.h"
// #include <string>
#define RATE 10.0f

int main(int argc, char **argv) {

    ros::init(argc, argv, "simulator");
    ros::NodeHandle nh;

    formation_sim::Simulator * p=formation_sim::Simulator::instance(RATE);
    ros::Rate loop_rate(RATE);

    while (ros::ok()) {
        p->doStep();
        ros::spinOnce(); 
        loop_rate.sleep(); // rate control
    }

    return 0;
}