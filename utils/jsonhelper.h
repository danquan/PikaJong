#ifndef JSONHELPER_H
#define JSONHELPER_H

#include <nlohmann/json.h>

using namespace nlohmann;

struct JsonHelper {
private:
    JsonHelper() {}
public:

    /**
     * Get instance of JsonHelper
     * @return instance of JsonHelper
     */
    static JsonHelper getInstance() {
        static JsonHelper instance;
        return instance;
    }

    /**
     * Load json file from path
     * @param path path to json file
     * @return json object
     */
    json loadJson(std::string path);
};

#endif