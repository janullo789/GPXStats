#include <iostream>

#include "GPXData.h"

using namespace std;

int main()
{
    char* nameOfFirstFile = "MTBCROSS_Sobk_w.gpx";

    GPXData file1(nameOfFirstFile);

    cout << file1.getDistance() << endl;
    cout << file1.getElevation() << endl;
    cout << file1.getTime() << endl;



    return 0;
}