#include <map>
#include <iostream>
#include <string>
#include "Logger.hpp"
#include <chrono>

extern Logger* __NULL_Logger__;

int main()
{
    DEBUG_MSG("main called");
    __NULL_Logger__->log("dont show up anywhere");
}