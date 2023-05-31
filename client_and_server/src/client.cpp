#include "ros/ros.h"
#include "commen_msg/FootSteps.h"
#include "commen_msg/planning_request.h"

#include <iostream>
#include <tcpip/tcpip_port.h>
#include <glog/logging.h>
using namespace std;
int main(int argc, char *argv[])
{
    ros::init(argc,argv,"client");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<commen_msg::planning_request>("planning_service");
    ros::service::waitForService("planning_service");

    commen_msg::planning_request planning;
    tcpip_port port;
    port.initial();
    port.accept_client();
    // 规划的输入，来自控制端
    while (1)
    {
        if(port.recvData())
        {
            port.analysisBuf();
            // planning.request.walk_case = port.com_data.flag;
            planning.request.walk_case.emplace_back(port.com_data.flag[0]);
            planning.request.walk_case.emplace_back(port.com_data.flag[1]);

            planning.request.direct = port.com_data.direct;
            for (size_t i = 0; i < 6; i++)
            {
                planning.request.left_arm_joints.emplace_back(port.com_data.left_arm_joints[i]);
                planning.request.right_arm_joints.emplace_back(port.com_data.right_arm_joints[i]);
                planning.request.left_leg_joints.emplace_back(port.com_data.left_leg_joints[i]);
                planning.request.right_leg_joints.emplace_back(port.com_data.right_leg_joints[i]);
            }
            cout<<"reques data copy finish"<<endl;
            
            bool flag = client.call(planning);
            if (flag)
            {
                ROS_INFO("request sucess");
                for (auto & result_step : planning.response.result_steps)
                {
                    cout<<result_step.is_left<<" "<<result_step.x<<" "<<result_step.y<<" "<<result_step.z<<" "<<result_step.roll<<" "<<result_step.pitch<<" "<<result_step.yaw<<endl;
                }
                // CHECK(planning.response.result_steps.size() <= 16);
                /**
                 * 这里规定了最大传输的步数
                 * 
                */
                CHECK(planning.response.result_steps.size() <= 30);
                vector<LEECHAO::FootStep> steps;
                for (auto & result_step : planning.response.result_steps)
                {
                    LEECHAO::FootStep step;
                    step.is_left = result_step.is_left;
                    step.x = result_step.x;
                    step.y = result_step.y;
                    step.z = result_step.z;
                    // step.roll = result_step.roll;
                    // step.pitch = result_step.pitch;
                    step.yaw = result_step.yaw;
                    steps.emplace_back(step);
                }
                port.sendSteps(steps);
            }
            else
            {
                ROS_ERROR("client failed");
                port.close_client();
                port.closetcpip();
                return 1;
            }
        }
    }
    port.close_client();
    port.closetcpip();
    return 0;
}