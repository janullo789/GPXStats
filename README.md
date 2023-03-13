# GPXStats
Program for analyzing and management .gpx files.

## Tech Stack

**C++** using libraries such as *vector, iomanip, dirent.h, tinyxml2.h, ctime, cassert, cmath, string* and *iostream*.

The program was written in accordance with the assumptions of object-oriented programming 

## Installation

1. Clone the repository:
```
git clone https://github.com/janullo789/GPXStats.git
```
2. Go to the new folder:
```
cd GPXStats
```
3. Install libraries and complation of files
```
g++ -I/tinyxml2/include -L/tinyxml2/lib main.cpp GPXData.cpp GPXList.cpp -ltinyxml2 -o gpxstats
```
4. Paste your **.gpx files** into the folder */GPXStats* or use example files (those are already included)
5. Run gpxstats.exe
```
gpxstats.exe
```
