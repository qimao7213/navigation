#include <iostream>
#include <sstream>
#include <fstream>
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>

std::string filepath = "/home/qimao/catkin_ws/src/capture_global_path/data/globalPath1cm.txt";
int main(int argc, char** argv)
{
    ros::init (argc, argv, "publishGlobalPath");  
	ros::NodeHandle nh;  
    ros::Publisher pub_global_path = nh.advertise<nav_msgs::Path> ("/move_base/GlobalPlanner/plan", 10);
     
    nav_msgs::Path globalPath;
    globalPath.header.frame_id = "3dmap";

    std::ifstream fGlobalPath;
    fGlobalPath.open(filepath);
    if(!fGlobalPath)
    {
        std::cout << "A wrong file path at: " <<  filepath.c_str() << std::endl;
    }
    int numPoint = 0;
    while(!fGlobalPath.eof())
    {
        std::string s;
        getline(fGlobalPath,s);
        // cout << s.c_str() << endl;
        if(!s.empty())
        {
            std::stringstream ss;
            ss << s;
            std::string sss;
            ss >> sss;
            if(sss == "#")
            {
                continue;
            }
            if(numPoint == 40)
            {
                int b = 0;
            }
            geometry_msgs::PoseStamped onePoint;
            onePoint.pose.position.x = (double)atof(sss.c_str());
            ss >> sss;
            onePoint.pose.position.y = (double)atof(sss.c_str());
            onePoint.pose.position.z = 0.0;
            globalPath.poses.emplace_back(onePoint);
            numPoint ++;
        }
    }
    ROS_INFO("generate a global path with :%i points ", globalPath.poses.size());

    ros::Rate loop_rate(30);
    while(ros::ok())
    {
        globalPath.header.stamp = ros::Time::now();
        pub_global_path.publish(globalPath);
        loop_rate.sleep();
    }
    return 0;
}
