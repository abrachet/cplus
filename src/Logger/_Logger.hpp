#pragma once //not necessary

#include <iostream>
#include <fstream>
#include <string>
#include <map>

enum Output {
    NONE = -1,
    FILE_ONLY = 0,
    NO_FILE = 1,
    STDERR = 2,  // ie 3 is no file and stderr
    STDOUT = 4   //    5 is no file and stdout
                 //    7 is no file, stderr and stdout
                 //    6 is file, stderr, and stdout
};

class Logger {
protected:
    char out_type;
    std::fstream output;
    std::string(*formatter)(std::string, ...);

    virtual void print(std::string, va_list);

public:
    Logger() = delete;
    Logger(std::string);
    Logger(std::string, Output);
    Logger(std::string, std::string(*)(std::string, ...));
    Logger(std::string, Output, std::string(*)(std::string, ...));
    virtual ~Logger();

    void stdout_true();
    void stdout_false();

    void log(std::string str, ...);
    

    void operator<<(std::string str);

};

class UserFacingLogger : public Logger {
    std::string public_name;
    std::string(*public_formatter)(std::string, ...);

    //override
    void print(std::string, va_list);

public:

    UserFacingLogger() = delete;
    UserFacingLogger(std::string, std::string);
    UserFacingLogger(std::string, std::string, Output);
    UserFacingLogger(std::string, std::string, std::string(*public_formatter)(std::string, ...));
    UserFacingLogger(std::string, Output, std::string(*)(std::string, ...));

    
};




Logger* get_logger(std::string str);

//turns all loggers to print to std::out
void all_out();