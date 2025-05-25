#ifndef UTIL_H
#define UTIL_H

#include <string>

namespace ose4g
{
    bool validateTime(const std::string&);
    int getSeconds(const std::string& s);
    std::string secondsToTimeString(int totalSeconds);
    void showWhile(std::function<void()> func);
}

#endif