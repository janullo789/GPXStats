//
// Created by Dell on 13.02.2023.
//

#include "GPXList.h"

GPXList::GPXList(std::string path)
{
    this->path = path;
    listGPX();
}

std::vector<std::string> GPXList::listGPX()
{
    DIR *dir;
    struct dirent *ent;
    std::vector<std::string> filesGPX;

    dir = opendir(path.c_str());
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string fileName = ent->d_name;
            std::string fileExtension = fileName.substr(fileName.find_last_of(".") + 1);
            if (fileExtension == "gpx") {
                std::cout << fileName << std::endl;
            }
        }
        closedir(dir);
    } else {
        // Błąd otwierania folderu
        std::cerr << "Nie można otworzyć folderu: " << path << std::endl;
        return filesGPX;;
    }
    return filesGPX;

}
