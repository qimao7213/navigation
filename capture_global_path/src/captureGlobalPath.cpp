#include <iostream>
#include <sstream>
#include <fstream>
#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <capture_global_path/capture_global_path.h>

std::string outputfile = "/home/qimao/catkin_ws/src/hdl_localization_mapping/hdl_localization/data/globalPath.txt";
std::string filepath = "/home/qimao/catkin_ws/src/capture_global_path/data/globalPath1cm.txt";
ros::Subscriber globalPathSub;
ros::Publisher globalPathPub;
nav_msgs::Path globalPath;
bool isCaputer = false;
void topicCallback(const nav_msgs::Path::ConstPtr &globalPath)
{
    // std::ofstream fout(outputfile);
    // if(!fout)
    // {
    //     ROS_ERROR("outputfile error!");
    // }
    // fout << "# seq: " << globalPath->header.seq << std::endl;
    // fout << "# timestamp: " << std::to_string(globalPath->header.stamp.toSec()) << std::endl;
    // fout << "# frame_id: " << globalPath->header.frame_id << std::endl;
    // fout << "# x, y, z, x, y, z, w" << std::endl;
    // for(int i = 0; i < globalPath->poses.size(); ++i)
    // {
    //     fout << globalPath->poses[i].pose.position.x << " " ;
    //     fout << globalPath->poses[i].pose.position.y << " " ;
    //     fout << globalPath->poses[i].pose.position.z << " " ;
    //     fout << globalPath->poses[i].pose.orientation.x << " " ;
    //     fout << globalPath->poses[i].pose.orientation.y << " " ;
    //     fout << globalPath->poses[i].pose.orientation.z << " " ;
    //     fout << globalPath->poses[i].pose.orientation.w << " " ;
    //     fout << std::endl;
    // }
    // fout.close();
    if(globalPath->poses.size() > 0)
    {
        ROS_INFO("------------Got Global Path-------------");
    }
}


bool serviceCallback(capture_global_path::capture_global_path::Request &req, 
                capture_global_path::capture_global_path::Response &res)
{
    //收到之后，就启动接收
    // isCaputer = true;
    ROS_INFO("receive command from client. ");
    globalPath.header.stamp = ros::Time::now();
    // res.success = true;
    res.result = "Now starting capture global path.....";
    res.GlobalPath = globalPath;
    return 1;
}


int main(int argc, char** argv)
{
    ros::init (argc, argv, "publish_pointcloud");  
	ros::NodeHandle nh;  
    ROS_INFO("the service to caputure global path is perpared!");

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


    // ros::ServiceServer globaPathCapture = nh.advertiseService("/capture_global_path", 
    //                     [&](capture_global_path::capture_global_path::Request &req, capture_global_path::capture_global_path::Response &res)
    //                     {
    //                         callbackService(req, res, globalPathSub, globalPathPub);
    //                     });
    ros::ServiceServer globaPathCapture = nh.advertiseService("/capture_global_path", serviceCallback);
    ros::Rate loop_rate(30);
    while(ros::ok())
    {
        ros::spinOnce();
        // if(isCaputer)
        // {
        //     break;
        // }
        loop_rate.sleep();
    }     
    // while(ros::ok() && isCaputer)
    // {
    //     // globalPathPub = nh.advertise<nav_msgs::Path> ("/FootStep/GlobalPath", 10); 
    //     //这里要加入发布数据的，还有就是，多次调用捕获数据的。
    //     globalPathSub = nh.subscribe<nav_msgs::Path> ("/move_base/GlobalPlanner/plan", 10, topicCallback); 
    //     ros::spin();
    // }
    return 0;
}
