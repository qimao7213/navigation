#include <show/matplotlib_show.h>
#include <matplotlib/matplotlibcpp.h>
#include <glog/logging.h>
#include <fstream>
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace plt = matplotlibcpp;
vector<string> color ={"r", "b", "g", "y", "c", "k", "m"};

// void show(std::vector<PathsD> & polys, bool show_, string save_path)
// {
//     // cout<<"to show"<<endl;
//     // cout<<"polys size "<<polys.size()<<endl;
//     if (polys.empty())
//     {
//         LOG(WARNING)<<"polys is empty";
//     }
//     vector<vector<vector<float>>> xx, yy;
//     LOG(INFO)<<"polys size "<<polys.size();
//     for (size_t i = 0; i < polys.size(); i++)//每个多边形
//     {
//         vector<vector<float>> x, y;//多边形
//         x.resize(polys.at(i).size());//多边形内轮廓个数
//         y.resize(polys.at(i).size());
//         // cout<<x.size()<<endl;
//         for (int j = 0; j < polys.at(i).size(); j++)//每个轮廓
//         {
//             // cout<<"..."<<endl;
//             for (auto & pp : polys.at(i).at(j))
//             {
//                 x.at(j).emplace_back(pp.x);
//                 y.at(j).emplace_back(pp.y);
//             }
//             // cout<<"??"<<j<<endl;
//             // cout<<*x.at(j).begin()<<endl;
//             // cout<<x.at(j).size()<<endl;
//             x.at(j).emplace_back(*(x.at(j).begin()));
//             y.at(j).emplace_back(*(y.at(j).begin()));
//         }
//         xx.emplace_back(x);
//         yy.emplace_back(y);
//     }
//     plt::figure();
//     plt::clf();
//     // cout<<"plot"<<endl;
//     for (int i = 0; i < xx.size(); i++)
//     {
//         string c = color.at(i%color.size());
//         for (int j = 0; j < xx.at(i).size(); j++)
//         {
//             plt::plot(xx.at(i).at(j), yy.at(i).at(j), c);
//             for (size_t k = 0; k < xx.at(i).at(j).size(); k++)
//             {
//                 LOG(INFO)<<xx.at(i).at(j).at(k)<<" "<<yy.at(i).at(j).at(k);
//             }
//         }
//     }
//     if (!save_path.empty())
//     {
//         LOG(INFO)<<"save png";
//         plt::savefig(save_path + ".png");
//     }
//     if (show_)
//     {
//         plt::show();
//     }
//     plt::close();
// }

// void show(PathsD & poly, bool show_, string save_path)
// {
//     vector<PathsD> p_s;
//     p_s.emplace_back(poly);
//     show(p_s, show_, save_path);
// }

// void show(vector<polytopic> ps, bool show, string save_path)
// {
//     if (ps.empty())
//     {
//         LOG(WARNING)<<"input polytopic is empty";
//     }
//     vector<vector<vector<float>>> x, y;
//     for (auto & p : ps)
//     {
//         vector<vector<float>> xx, yy;
//         xx.resize(p.getInners().size() + 1);
//         yy.resize(p.getInners().size() + 1);
//         // xx.resize(p.getPolygon().inners().size() + 1);
//         // yy.resize(p.getPolygon().inners().size() + 1);
//         for (auto & pp3 : p.getOuter())
//         {
//             xx.at(0).emplace_back(pp3.x());
//             yy.at(0).emplace_back(pp3.y());
//         }
//         xx.at(0).emplace_back(*xx.at(0).begin());
//         yy.at(0).emplace_back(*yy.at(0).begin());
//         int inner_index = 1;
//         for (auto & inner : p.getInners())
//         {
//             for (auto & pp3 : inner)
//             {
//                 xx.at(inner_index).emplace_back(pp3.x());
//                 yy.at(inner_index).emplace_back(pp3.y());
//             }
//             xx.at(inner_index).emplace_back(*xx.at(inner_index).begin());
//             yy.at(inner_index).emplace_back(*yy.at(inner_index).begin());
//             inner_index++;
//         }
//         x.emplace_back(xx);
//         y.emplace_back(yy);
//     }
//     plt::figure();
//     plt::clf();
//     for (int i = 0; i < x.size(); i++)
//     {
//         string c = color.at(i%color.size());
//         for (int j = 0; j < x.at(i).size(); j++)
//         {
//             plt::plot(x.at(i).at(j), y.at(i).at(j), c);
//         }
//     }
//     if (!save_path.empty())
//     {
//         plt::save(save_path + ".png");
//     }
//     if (show)
//     {
//         plt::show();
//     }
//     plt::close();
// }

// void show(vector<vector<polytopic>> & frames, bool show_, string save_path)
// {
//     if (frames.empty())
//     {
//         LOG(WARNING)<<"empty frames";
//     }
//     LOG(INFO)<<"ENTER SHOW FUNCTION";
//     LOG(INFO)<<"frame size "<<frames.size();
//     plt::figure();
//     plt::clf();
//     for (size_t i = 0; i < frames.size(); i++)
//     {
//         // 多个点组成轮廓
//         // 多个轮廓组成多边形
//         // 多个多边形组成frame
//         vector<vector<vector<float>>> x, y;    
//         // LOG(INFO)<<" ";
//         for (auto & p : frames.at(i))
//         {
//             vector<vector<float>> xx, yy;
//             xx.resize(p.getPolygon().inners().size() + 1);
//             yy.resize(p.getPolygon().inners().size() + 1);
//             for (auto & pp3 : p.getOuter())
//             {
//                 xx.at(0).emplace_back(pp3.x());
//                 yy.at(0).emplace_back(pp3.y());
//             }
//             xx.at(0).emplace_back(*xx.at(0).begin());
//             yy.at(0).emplace_back(*yy.at(0).begin());
//             int inner_index = 1;
//             for (auto & inner : p.getInners())
//             {
//                 for (auto & pp3 : inner)
//                 {
//                     xx.at(inner_index).emplace_back(pp3.x());
//                     yy.at(inner_index).emplace_back(pp3.y());
//                 }
//                 xx.at(inner_index).emplace_back(*xx.at(inner_index).begin());
//                 yy.at(inner_index).emplace_back(*yy.at(inner_index).begin());
//                 inner_index++;
//             }     
//             // LOG(INFO)<<xx.size()<<" "<<yy.size();
//             // LOG(INFO)<<p.getPolygon().outer().size();
//             // for (auto & pp3 : p.getPolygon().outer())
//             // {
//             //     LOG(INFO)<<pp3.x()<<" "<<pp3.y();
//             //     xx.at(0).emplace_back(pp3.x());
//             //     yy.at(0).emplace_back(pp3.y());
//             //     // xx.at(0).emplace_back(pp3.x());
//             // }
//             // int inner_index = 1;
//             // LOG(INFO)<<xx.at(0).size()<<" "<<yy.at(0).size();
//             // for (auto & inner : p.getPolygon().inners())
//             // {
//             //     for (auto & pp3 : inner)
//             //     {
//             //         xx.at(inner_index).emplace_back(pp3.x());
//             //         yy.at(inner_index).emplace_back(pp3.y());
//             //     }
//             //     inner_index++;
//             //     LOG(INFO)<<xx.at(inner_index).size()<<" "<<yy.at(inner_index).size();
//             // }
//             x.emplace_back(xx);
//             y.emplace_back(yy);
//         }
//         // LOG(INFO)<<x.size()<<" "<<y.size();
//         // LOG(INFO)<<"GET CONTOURS";      
//         string c = color.at(i%color.size());
//         for (int j = 0; j < x.size(); j++)
//         {
//             for (int k = 0; k < x.at(j).size(); k++)
//             {
//                 plt::plot(x.at(j).at(k), y.at(j).at(k), c);
//             }
//         }
//         // LOG(INFO)<<"PLOT";
//     }
//     if (!save_path.empty())
//     {
//         plt::save(save_path + ".png");
//     }
//     if (show_)
//     {
//         plt::show();
//     }
//     plt::close();
// }

// void show(vector<polygon> ps, bool show_, string save_path)
// {
//     if (ps.empty())
//     {
//         LOG(WARNING)<<"empty polygon";
//     } 
//     vector<vector<vector<float>>> x, y;
//     for (auto & p : ps)
//     {
//         vector<vector<float>> xx, yy;
//         xx.resize(p.inners().size() + 1);
//         yy.resize(p.inners().size() + 1);
//         for (auto & pp3 : p.outer())
//         {
//             xx.at(0).emplace_back(pp3.x());
//             yy.at(0).emplace_back(pp3.y());
//         }
//         int inner_index = 1;
//         for (auto & inner : p.inners())
//         {
//             for (auto & pp3 : inner)
//             {
//                 xx.at(inner_index).emplace_back(pp3.x());
//                 yy.at(inner_index).emplace_back(pp3.y());
//             }
//             inner_index++;
//         }
//         x.emplace_back(xx);
//         y.emplace_back(yy);
//     }
//     plt::figure();
//     plt::clf();
//     for (int i = 0; i < x.size(); i++)
//     {
//         string c = color.at(i%color.size());
//         for (int j = 0; j < x.at(i).size(); j++)
//         {
//             plt::plot(x.at(i).at(j), y.at(i).at(j), c);
//         }
//     }
//     if (!save_path.empty())
//     {
//         plt::save(save_path + ".png");
//     }
//     if (show_)
//     {
//         plt::show();
//     }
//     plt::close();
// }

// void show(polygon p, bool show_, string save_path)
// {
//     vector<polygon> ps;
//     ps.emplace_back(p);
//     show(ps, show_, save_path);
// }

// void show_stamp(vector<vector<float>> topics_times, string save_path)
// {
//     int topics = topics_times.size();
//     plt::figure();
//     plt::clf();
//     for (int i = 0; i < topics; i++)
//     {
//         // string c = color.at(i%color.size());
//         vector<float> y(30, i*0.1);
//         // cout<<y.size()<<endl;
//         // plt::plot(topics_times.at(i), y, c);
//         // plt::scatter(topics_times.at(i), y, 1, c);
//         vector<float> x(topics_times.at(i).begin(), topics_times.at(i).begin() + 30);
//         plt::scatter(x,y,6);
//         // plt::plot();    
//     }
//     // plt::scatter()
//     plt::grid(true);
//     if (!save_path.empty())
//     {
//         plt::save(save_path + ".png");
//     }
//     plt::show();
//     plt::close();
// }

enum foot_corner_point {LF, RF, RE, LE};

/**
 * @brief 计算脚各角点的坐标，分别为左前，右前，右后，左后
 * @details 计算时，以脚踝在脚面上的垂直投影为坐标原点，坐标系向前为？
*/
Eigen::Vector3f compute_foot_corner_point(foot_corner_point which_corner, LEECHAO::FootStep step)
{
    Eigen::Vector3f center_V_corner = Eigen::Vector3f::UnitZ();
    // 左右脚是不是不一样
    if (step.is_left)
    {
        if (which_corner == LF)
        {
            center_V_corner(0) = 0.145;
            center_V_corner(1) = 0.105;
        }
        else if (which_corner == RF)
        {
            center_V_corner(0) = 0.145;
            center_V_corner(1) = - 0.065;
        }
        else if (which_corner == RE)
        {
            center_V_corner(0) = - 0.105;
            center_V_corner(1) = - 0.065;
        }
        else if (which_corner == LE)
        {
            center_V_corner(0) = - 0.105;
            center_V_corner(1) = 0.105;
        }        
    }
    else
    {
        if (which_corner == LF)
        {
            center_V_corner(0) = 0.145;
            center_V_corner(1) = 0.065;
        }
        else if (which_corner == RF)
        {
            center_V_corner(0) = 0.145;
            center_V_corner(1) = - 0.105;
        }
        else if (which_corner == RE)
        {
            center_V_corner(0) = - 0.105;
            center_V_corner(1) = - 0.105;
        }
        else if (which_corner == LE)
        {
            center_V_corner(0) = - 0.105;
            center_V_corner(1) = 0.065;
        } 
    }
    
    Eigen::AngleAxisf angle_z(step.yaw, Eigen::Vector3f::UnitZ());
    // Eigen::AngleAxisf angle_y(step.pitch, Eigen::Vector3f::UnitY());
    // Eigen::AngleAxisf angle_x(step.roll, Eigen::Vector3f::UnitX());
    
    Eigen::Matrix4f T = Eigen::Matrix4f::Identity();
    T.block<3,3>(0,0) = angle_z.toRotationMatrix();
    // T.block<3,3>(0,0) = angle_x.toRotationMatrix() * angle_y.toRotationMatrix() * angle_z.toRotationMatrix();
    T(0,3) = step.x;
    T(1,3) = step.y;
    T(2,3) = step.z;
    return T.block<3,3>(0,0)*center_V_corner + T.block<3,1>(0,3);
}

void show(vector<LEECHAO::FootStep> & footsteps)
{
    for (auto & step : footsteps)
    {
        vector<Eigen::Vector3f> points(4);
        for (size_t i = 0; i < 4; i++)
        {
            points.at(i) = compute_foot_corner_point(foot_corner_point(i), step);
        }
        vector<float> x, y;
        for (size_t i = 0; i < 4; i++)
        {
            x.emplace_back(points.at(i).x());
            y.emplace_back(points.at(i).y());
        }
        x.emplace_back(*(x.begin()));
        y.emplace_back(*(y.begin()));
        if (step.is_left)
        {
            plt::plot(x, y, color.at(0));
        }
        else
        {
            plt::plot(x, y, color.at(1));
        }
    }
    vector<float> left_x, left_y, right_x, right_y;
    for (auto & step : footsteps)
    {
        if (step.is_left)
        {
            left_x.emplace_back(step.x);
            left_y.emplace_back(step.y);
        }
        else
        {
            right_x.emplace_back(step.x);
            right_y.emplace_back(step.y);
        }
    }
    plt::scatter(left_x, left_y);
    plt::scatter(right_x, right_y);
    plt::show();
}







