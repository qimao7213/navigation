#pragma once
#include "Pathplan/path.h"
#include "Pathplan/pathdata.h"

namespace gpathsmooth
{
    /* 圆心，半径，圆心角 */
    typedef struct CirclePara
    {
        double x;
        double y;
        double R;
        double Angle;
    } ts_circle;
    bool gfnnTurningChangFlag(gpath::tc_path *_path, int gi, int gap);
    bool gfnbIFTurning(int i, gpath::ts_PathCoord pathnode[]);
    void gfnvPathTransLine(gpath::tc_path *_path);
    void gfnvSaveDataTransLine(gpath::tc_path *_path);
    void gfnvSaveDataWithFile(gpath::tc_path *_path, char *filetest);
    void gfnGeneratePathFromTxt(gpath::tc_path *_path, const std::string filename);
    gpath::ts_PathCoord gaofnGPFramTrans(double dlx, double dly, double dltheta, double dllx, double dlly);
    gpath::ts_PathCoord gaofnGPFramTransV2(double dlx, double dly, double dltheta, double dllx, double dlly);
    int ReturnCaculatNDefualt(gpath::ts_PathCoord pathnode[], int initn, int loopN, double defualtfootL, int flag);
    ts_circle gfnvCircleCentrAndRand(double theta1, double x1, double y1, double theta2, double x2, double y2);
    void gfnvPathSmooth(gpath::tc_path *_path);
}