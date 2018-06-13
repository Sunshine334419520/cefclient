//
// Created by Sunshine on 2018/6/11.
//

#include "tests/cefsimple/browser/resource_util.h"

namespace simple {


bool ReadFileToString(const char *path, std::string &resouce_data) {
    FILE *file = fopen(path, "rb");

    if (!file)
        return false;

    char buf[1 << 16];
    size_t len = 0;
    while ((len = fread(buf, 1, sizeof(buf), file)) > 0) {
        resouce_data.append(buf, len);
    }

    fclose(file);
    return true;
}

bool LoadBinaryResource(const char *resource_name,
                        std::string &resource_data) {
    std::string current_path;

    if (!GetResourceDir(current_path))
        return false;


    current_path.append("/");
    current_path.append(resource_name);

    return ReadFileToString(current_path.c_str(), resource_data);
}

}


