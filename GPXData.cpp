#include <iostream>
#include <cassert>
#include <tinyxml2.h>
#include <iomanip>
#include <cmath>

#include "GPXData.h"

std::time_t stringToTimeDate(const std::string& dataTime);
long double toRadians(const long double degree);

GPXData::GPXData(char* nameFile)
{
    readData(nameFile);
}

void GPXData::readData(char* titleGPX)
{
    tinyxml2::XMLNode *gpx = nullptr;
    tinyxml2::XMLNode *trk = nullptr;
    tinyxml2::XMLNode *trkseg = nullptr;
    tinyxml2::XMLError result;

    tinyxml2::XMLDocument docGPX;
    docGPX.LoadFile(titleGPX);
    tinyxml2::XMLNode* root = docGPX.FirstChild();
    if(root == nullptr)
        std::cout << "Cannot open file" << std::endl;

    //docGPX.Print(); // TESTOWE

    gpx = docGPX.FirstChildElement("gpx");
    assert(gpx);
    trk = gpx->FirstChildElement("trk");
    assert(trk);
    trkseg = trk->FirstChildElement("trkseg");
    assert(trkseg);

    for (tinyxml2::XMLElement *trkpt = trkseg->FirstChildElement("trkpt"); trkpt; trkpt = trkpt->NextSiblingElement("trkpt"))
    {
        GPXParameter insertParm;
        result = trkpt->QueryDoubleAttribute("lat", &insertParm.lats);
        assert(result == tinyxml2::XML_SUCCESS);
        result = trkpt->QueryDoubleAttribute("lon", &insertParm.lons);
        assert(result == tinyxml2::XML_SUCCESS);

        tinyxml2::XMLElement *ele = trkpt->FirstChildElement("ele");
        assert(ele);

        result = ele->QueryDoubleText(&insertParm.eles);
        assert(result == tinyxml2::XML_SUCCESS);

        tinyxml2::XMLElement *timeDate = trkpt->FirstChildElement("time");
        assert(timeDate);

        insertParm.times = stringToTimeDate((std::string)timeDate->GetText());

        tinyxml2::XMLElement *extensions = trkpt->FirstChildElement("extensions");
        assert(extensions);

        tinyxml2::XMLElement *gpxtpxTPE = extensions->FirstChildElement("gpxtpx:TrackPointExtension");
        assert(gpxtpxTPE);

        tinyxml2::XMLElement *temp = gpxtpxTPE->FirstChildElement("gpxtpx:atemp");
        assert(temp);

        result = temp->QueryDoubleText(&insertParm.temps);
        assert(result == tinyxml2::XML_SUCCESS);

        parm.push_back(insertParm);
    }
}

long double GPXData::getDistance()
{
    long double distance = 0;

    for(unsigned i = 1; i < parm.size() - 1; i++)
    {
        long double lat1 = toRadians(parm[i - 1].lats);
        long double lon1 = toRadians(parm[i - 1].lons);
        long double lat2 = toRadians(parm[i].lats);
        long double lon2 = toRadians(parm[i].lons);

        long double xDist = lon2 - lon1;
        long double yDist = lat2 - lat1;

        long double ans = pow(sin(yDist / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(xDist / 2), 2);

        ans = 2 * asin(sqrt(ans));

        long double R = 6371;
        ans = ans * R;

        distance += ans;
    }
    return distance;
}

double GPXData::getTime()
{
    return difftime(parm[parm.size() - 1].times, parm[0].times);
}

double GPXData::getElevation()
{
    double elevation = 0;

    for(unsigned i = 1; i < parm.size() - 1; i++)
    {
        if(parm[i - 1].eles < parm[i].eles)
            elevation += (parm[i].eles - parm[i - 1].eles);
    }

    return elevation;
}

long double toRadians(const long double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

std::time_t stringToTimeDate(const std::string& dateTime)
{
    const std::string dateTimeFormat{"%Y-%m-%dT%H:%M:%SZ"};
    std::stringstream ss{dateTime};
    std::tm dt;

    ss >> std::get_time(&dt, dateTimeFormat.c_str());

    return std::mktime(&dt);
}

