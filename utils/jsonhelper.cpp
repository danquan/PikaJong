#include <utils/jsonhelper.h>
#include <fstream>

json JsonHelper::loadJson(std::string path) {
    std::ifstream configFile(path.c_str());
    
    if (!configFile.is_open())
    {
        printf("Could not open json file at %s\n", path.c_str());
        return NULL;
    }

    json config;
    configFile >> config;
    configFile.close();

    printf("Json file loaded sucessfully from %s\n", path.c_str());
    return config;
}