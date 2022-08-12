#ifndef GPXSTATS_GPXPARAMETER_H
#define GPXSTATS_GPXPARAMETER_H

struct GPXParameter
{
    double lats, lons, eles, temps;
    std::time_t times;
};

#endif //GPXSTATS_GPXPARAMETER_H
