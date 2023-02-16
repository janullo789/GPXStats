//
// Created by Dell on 13.02.2023.
//

#ifndef GPXSTATS_GPXLIST_H
#define GPXSTATS_GPXLIST_H


#include <iostream>
#include <string>
#include <dirent.h>
#include <vector>

class GPXList
{
public:
    GPXList(std::string);
    std::string menu();

private:
    std::string path;
    std::vector<std::string> filesGPX;
    std::vector<std::string> listGPX();
    void showList();
};


#endif //GPXSTATS_GPXLIST_H
