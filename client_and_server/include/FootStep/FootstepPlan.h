#pragma once
#include "Pathplan/path.h"
#include "Pathplan/pathdata.h"
#include "PathSmooth/PathSmooth.h"

#define Gdeg2rad (3.14 / 180)
#define Grad2deg (180 / 3.14)

void tfnGFoot1();
void tfnGFoot2();
namespace gfootstepplan
{
    class tc_BHRhard
    {
    public:
        double dmaxstep; //0.35
        double dmaxsteptheta; // degree 10
        double dstepwidth; //0.08
        tc_BHRhard(){};
        tc_BHRhard(const double _cdmaxstep, const double _cdmaxsteptheta, const double _dstepwidth) : dmaxstep(_cdmaxstep), dmaxsteptheta(_cdmaxsteptheta), dstepwidth(_dstepwidth){};
    };
    class tc_PathCapture
    {
    public:
        int GCAPTURE_PATH_NUM;
        gpath::ts_PathCoord capurepath[MAX_ARRAY_NUM];

        tc_PathCapture(){};
    };

    class tc_Footstep
    {
    private:
        /* data */
    public:
        gpath::ts_FootCoord gfoot[MAX_ARRAY_NUM];
        int footnum;

        tc_Footstep(){};
    };
    
    double gfndCaculateTurningTheta(gpath::tc_path *_path,int ginow, int gilast);
    void gfnvCapturePath(gpath::tc_path *_path, tc_BHRhard hardpara);
    tc_PathCapture &gfnvCapturePathV4(gpath::tc_path *_path, tc_BHRhard hardpara, double map_resolution);
    tc_PathCapture &gfnvCapturePathV3(gpath::tc_path *_path, tc_BHRhard hardpara, double map_resolution);
    tc_PathCapture &gfnvCapturePathV2(gpath::tc_path *_path, tc_BHRhard hardpara);
    double gfndPlantFootStepPlanner(gpath::tc_path *_path, gfootstepplan::tc_BHRhard hardpara);
    tc_Footstep &gfndPlantFootStepPlannerV2(tc_PathCapture *_cpath, gfootstepplan::tc_BHRhard hardpara);
    void gfnvSaveFoot(tc_Footstep *_foot, char *filetest);
    void gfnvSaveCPath(tc_PathCapture *_cpath, char *filetest);
}