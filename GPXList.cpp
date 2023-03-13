//
// Created by Dell on 13.02.2023.
//

#include "GPXList.h"

GPXList::GPXList(std::string path)
{
    this->path = path;
    try {
        filesGPX = listGPX();
        if (filesGPX.empty()) {
            throw std::runtime_error("No one .gpx file in this path!");
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

std::vector<std::string> GPXList::listGPX()
{
    DIR *dir;
    struct dirent *ent;
    std::vector<std::string> filesGPX;

    dir = opendir(path.c_str());
    if (dir != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            std::string fileName = ent->d_name;
            std::string fileExtension = fileName.substr(fileName.find_last_of(".") + 1);
            if (fileExtension == "gpx")
            {
                filesGPX.push_back(fileName);
            }
        }
        closedir(dir);
    } else
    {
        std::cerr << "Cannot open catalog " << path << std::endl;
    }
    return filesGPX;
}

void GPXList::showList()
{
    int i = 1;
    for(std::string file : filesGPX)
    {
        std::cout << i << "." << file << std::endl;
        i++;
    }
}

std::string GPXList::menu()
{
    int choice;
    do
    {
        std::cout << "Choose a file (enter the option number or press 0 to skip):" << std::endl;
        showList();
        std::cin >> choice;
    } while (choice < 1 || choice > filesGPX.size());

    return filesGPX[choice - 1];
}