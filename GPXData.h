#ifndef GPXSTATS_GPXDATA_H
#define GPXSTATS_GPXDATA_H

#include <iostream>
#include <vector>
#include <ctime>

#include "GPXParameter.h"

class GPXData
{
public:
    GPXData(char*);

    long double getDistance();
    double getTime();
    double getElevation();

private:
    std::vector<GPXParameter> parm;
    void readData(char* titleGPX);


};


#endif //GPXSTATS_GPXDATA_H
