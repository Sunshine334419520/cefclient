//
// Created by Sunshine on 2018/6/11.
//

#ifndef CEF_RESOURCE_UTIL_H
#define CEF_RESOURCE_UTIL_H

#include <string>

namespace simple {


// Returns the directory containing resource files.
bool GetResourceDir(std::string& dir);

bool ReadFileToString(const char* path, std::string& resouce_data);

// Retrieve a resource as a string.
bool LoadBinaryResource(const char *resource_name, std::string &resource_data);

}

#endif //CEF_RESOURCE_UTIL_H
