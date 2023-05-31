#pragma once
#ifndef __PATH_H__
#define __PATH_H__

#include "pathdata.h"
#include <stack>
#include <vector>
#define ROW 1000  
#define COL 1000
#define MAX_ARRAY_NUM 2000
namespace gpath
{
    static double Fvalue;
    static ts_cell g_grid[COL][ROW];

    class tc_path
    {
    public:
        pa_point global_start;
        pa_point global_goal;
        papa_point cost_node;
        std::stack<pa_point> global_path;
        int nPathNodeNum = 0;
        // ts_PathCoord global_path_cor[MAX_ARRAY_NUM] = {0};
        ts_PathCoord global_path_cor[MAX_ARRAY_NUM];
        // std::vector<ts_PathCoord> global_path_cor;
        double dValuePlus = 0.0;

        tc_path()
        {
            for(int i = 0; i < MAX_ARRAY_NUM; ++i)
            {
                this->global_path_cor[i].x = 0;
                this->global_path_cor[i].y = 0;
                this->global_path_cor[i].z = 0;
                this->global_path_cor[i].theta = 0;
            }
            // global_path_cor.resize(MAX_ARRAY_NUM);
        };
        void setStartandGoal(int _nsx, int _nsy, int _ngx, int _ngy)
        {
            this->global_start = std::make_pair(_nsx, _nsy);
            this->global_goal = std::make_pair(_ngx, _ngy);
        }
        void setGlobalPath(int _nCol, int _nRow)
        {
            this->global_path.push(std::make_pair(_nCol, _nRow));
            // std::cout << "in class tc_path :" << this->global_path.top().first << std::endl;
            // std::cout << "in class tc_path :" << this->global_path.top().second << std::endl;
        }
        pa_point getPathPoint()
        {
            return this->global_path.top();
        }
        void delPathPoint()
        {
            this->global_path.pop();
        }
        int getnPathNodeNum()
        {
            this->nPathNodeNum = this->global_path.size();
            return this->nPathNodeNum;
        }
    };

    void fnvInitCell(ts_cell _grid[][ROW]);
    void fnvSetObstacle(int Begin_x, int End_x, int Begin_y, int End_y, double H, double W, int MARK, int isempty, ts_cell _grid[][ROW], ts_pose markpose);
    void fnvInitObstacle(ts_cell _grid[][ROW]);
    void fnInitGridMap(ts_cell _grid[][ROW]);
    void fnvInitStart(ts_cell _grid[][ROW], pa_point m_Start, pa_point m_Goal);
    bool fnisValid(int m_nCol, int m_nRow);
    bool fnisEmpty(ts_cell _grid[][ROW], int m_nCol, int m_nRow);
    bool fnisEmptyWithHeight(ts_cell _grid[][ROW], int m_nCol, int m_nRow, double Hight);
    bool fnisGoal(int m_nCol, int m_nRow, pa_point m_Goal);
    void fncellCheck(ts_cell _grid[][ROW], pa_point m_Start, pa_point m_Goal);
    void fncellCheckWithHeight(ts_cell _grid[][ROW], pa_point m_Start, pa_point m_Goal, double Hight);
    double fncalculateHValue(int m_nCol, int m_nRow, pa_point m_Goal);
    double fncalculateH_HValue(int m_nCol, int m_nRow, pa_point m_Goal, double Height);
    double fncalculateAValue(int m_nCol, int m_nRow, pa_point m_Goal, double Height, double Width);

    void fntracePath(ts_cell _grid[][ROW], pa_point m_Goal);
    void api_AStarSearchWithHeight(ts_cell _grid[][ROW], pa_point m_Start, pa_point m_Goal);
    int api_PathPlaning(int _sx, int _sy, int _gx, int _gy);
    tc_path &api_PathPlaningReturn(int _sx, int _sy, int _gx, int _gy);
    void gfnvSaveData();
}

#endif //__PATH_H__