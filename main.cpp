#include <iostream>
#include <iomanip>

#include "GPXData.h"

using namespace std;

bool mainMenu(GPXData &);
void cropMenu(GPXData &);

int main()
{
    char* nameOfFirstFile = "../../MTBCROSS_Sobk_w.gpx";

    GPXData file1(nameOfFirstFile);

    while(mainMenu(file1)){}

    return 0;
}

bool mainMenu(GPXData &file)
{
    char choice;
    cout << setw(50) << "GPXStats - analyze your activities!" << endl;
    cout << "1. Show distance" << endl;
    cout << "2. Show elevation" << endl;
    cout << "3. Show time" << endl;
    cout << "4. Show average temperature" << endl;
    cout << "5. Crop activity" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter the option number: ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {
        case '1':
            cout << file.getDistance() << endl;
            break;
        case '2':
            cout << file.getElevation() << endl;
            break;
        case '3':
            cout << file.getTimeFormat(file.getTime()) << endl;
            break;
        case '4':
            cout << file.getAvgTemp() << endl;
            break;
        case '5':
            cropMenu(file);
            break;
        case '0':
            return false;
        default:
            return true;
    }
    return true;
}

void cropMenu(GPXData &file)
{
    char choice;
    double km;
    cout << setw(50) << "- Crop your activity -" << endl;
    cout << "1. Crop last ... km" << endl;
    cout << "2. Leave only the first ... km" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter the option number: "; cin >> choice;
    cout << endl;

    switch (choice)
    {
        case '1':
            cout << "How many last km do you want to crop? "<< endl;
            cin >> km;
            file.cropData(file.getDistance()-km);
            break;
        case '2':
            cout << "How many the first km do you want to leave? " << endl;
            cin >> km;
            file.cropData(km);
            break;
        default:
            break;
    }
}