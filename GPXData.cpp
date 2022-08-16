#include <iostream>
#include <cassert>
#include <tinyxml2.h>
#include <iomanip>
#include <cmath>

#include "GPXData.h"

std::time_t stringToTimeDate(const std::string& dateTime);
long double toRadians(long double degree);
double calcDistance(double firstLat, double secondLat, double firstLon, double secondLon);

GPXData::GPXData(const char* titleGPX)
{
    this->titleGPX = titleGPX;
    readData();
}

void GPXData::readData()
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

    gpx = docGPX.FirstChildElement("gpx");
    assert(gpx);
    trk = gpx->FirstChildElement("trk");
    assert(trk);
    trkseg = trk->FirstChildElement("trkseg");
    assert(trkseg);

    for (tinyxml2::XMLElement *trkpt = trkseg->FirstChildElement("trkpt"); trkpt; trkpt = trkpt->NextSiblingElement("trkpt"))
    {
        GPXParameter insertParm{};
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

void GPXData::cropData(const double km)
{
    tinyxml2::XMLNode *gpx = nullptr;
    tinyxml2::XMLNode *trk = nullptr;
    tinyxml2::XMLNode *trkseg = nullptr;

    tinyxml2::XMLDocument docGPX;
    docGPX.LoadFile(titleGPX);
    tinyxml2::XMLNode* root = docGPX.FirstChild();
    if(root == nullptr)
        std::cout << "Cannot open file" << std::endl;

    gpx = docGPX.FirstChildElement("gpx");
    assert(gpx);
    trk = gpx->FirstChildElement("trk");
    assert(trk);
    trkseg = trk->FirstChildElement("trkseg");
    assert(trkseg);

    int nrOfPoint = getDistanceItr(km);
    int i = 0;

    tinyxml2::XMLElement* trkpt = trkseg->FirstChildElement("trkpt");
    while (trkpt != nullptr) {
        tinyxml2::XMLElement* next = trkpt->NextSiblingElement("trkpt");
        if (nrOfPoint < i) {
            trkpt->Parent()->DeleteChild(trkpt);
        }
        trkpt = next;
        ++i;
    }

    std::string titleCropFile = ((std::string)titleGPX).substr(0,((std::string)titleGPX).find_last_of('.')) + "_Cropped.gpx";

    docGPX.SaveFile(titleCropFile.c_str());
}

double GPXData::getDistance()
{
    double distance = 0;

    for(unsigned i = 1; i < parm.size() - 1; i++)
    {
        distance += calcDistance(parm[i - 1].lats, parm[i].lats, parm[i - 1].lons, parm[i].lons);
    }
    return distance;
}

int GPXData::getDistanceItr(const double kmToCrop)
{
    double distance = 0;

    for(int i = 1; i < parm.size() - 1; i++)
    {
        distance += calcDistance(parm[i - 1].lats, parm[i].lats, parm[i - 1].lons, parm[i].lons);

        if(distance - 0.05 < kmToCrop && distance + 0.05 > kmToCrop)
            return i;
    }
    return -1;
}

double calcDistance(double firstLat, double secondLat, double firstLon, double secondLon)
{
    long double lat1 = toRadians(firstLat);
    long double lon1 = toRadians(firstLon);
    long double lat2 = toRadians(secondLat);
    long double lon2 = toRadians(secondLon);

    long double xDist = lon2 - lon1;
    long double yDist = lat2 - lat1;

    long double ans = pow(sin(yDist / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(xDist / 2), 2);

    ans = 2 * asin(sqrt(ans));

    long double R = 6371;
    ans = ans * R;

    return ans;
}

long double toRadians(const long double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
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

double GPXData::getTime()
{
    return difftime(parm[parm.size() - 1].times, parm[0].times);
}

std::string GPXData::getTimeFormat(double time)
{
    int hours = 0, minutes = 0, seconds = 0;
    int counter = (int)time;
    while(counter >= 0)
    {
        if(time >= 60*60)
        {
            time -= 60*60;
            hours++;
        }
        else if(time >= 60)
        {
            time -= 60;
            minutes++;
        }
        else
        {
            seconds = time;
            counter = 0;
        }

        counter--;
    }

    return std::to_string(hours) + " hours, " + std::to_string(minutes) + " minutes, " + std::to_string(seconds) + " seconds.";
}

double GPXData::getAvgTemp()
{
    int sum = 0;
    for (auto & i : parm)
    {
        sum += i.temps;
    }
    return sum / parm.size();
}

std::time_t stringToTimeDate(const std::string& dateTime)
{
    const std::string dateTimeFormat{"%Y-%m-%dT%H:%M:%SZ"};
    std::stringstream ss{dateTime};
    std::tm dt;

    ss >> std::get_time(&dt, dateTimeFormat.c_str());

    return std::mktime(&dt);
}

