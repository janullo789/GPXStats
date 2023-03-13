# GPXStats
Program for analyzing and management .gpx files.

## Features

- menu allowing to select a file
- display of activity distance
- display of activity time
- display of activity elevation
- display of average temperature during activity
- crop the beginning/end of the activity

## Screenshots
![image](https://user-images.githubusercontent.com/100961127/224851611-3e59612b-0523-480e-a4d3-5d78d0a859eb.png)
![image](https://user-images.githubusercontent.com/100961127/224851670-2cc45977-b652-4f6f-a360-82aa463e47cf.png)
![image](https://user-images.githubusercontent.com/100961127/224851706-ef00b301-91df-4ef6-a480-f6c83e8dd456.png)

## Tech Stack

**C++** using libraries such as *vector, iomanip, dirent.h, tinyxml2.h, ctime, cassert, cmath, string* and *iostream*.

The program was written in accordance with the assumptions of object-oriented programming.

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
