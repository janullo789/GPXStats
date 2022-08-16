#ifndef GPXSTATS_GPXDATA_H
#define GPXSTATS_GPXDATA_H

#include <iostream>
#include <vector>
#include <ctime>

#include "GPXParameter.h"

class GPXData
{
public:
    GPXData(const char*);

    double getDistance();
    int getDistanceItr(double);
    double getElevation();
    double getTime();
    std::string getTimeFormat(double);
    double getAvgTemp();
    void cropData(double km);

private:
    const char* titleGPX;
    std::vector<GPXParameter> parm;
    void readData();


};


#endif //GPXSTATS_GPXDATA_H
