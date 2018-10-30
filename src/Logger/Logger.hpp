#pragma once

//#include <iostream>
//#include <fstream>
//#include <string>
//#include <map>


//Not yet used, ill do it later
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
    char out_type;
    std::fstream output;
    std::string(*formatter)(std::string, ...);

    void print(std::string);

public:
    Logger(std::string);
    Logger(std::string, Output);
    Logger(std::string, std::string(*)(std::string, ...));
    ~Logger();

    void stdout_true();
    void stdout_false();

    void log(std::string str, ...);

    Logger& operator<<(std::string str);

};

Logger* get_logger(std::string str);

//turns all loggers to print to std::out
void all_out();

/**
 * Logger's should rarely be used in local context because 
 * fstream is so big
 * Better that be created once 
 */ 

extern Logger* Debug;
extern Logger* Error;
extern Logger* InternalLog;
extern Logger* InternalLog;
extern Logger* UserErrors;


#define F_L __FILE__ + ":" + __LINE__

#define SPDLOG_STR_H(x) #x
#define SPDLOG_STR_HELPER(x) SPDLOG_STR_H(x)
#define __LOG(str) "[ " __FILE__     \
":" SPDLOG_STR_HELPER(__LINE__) " ] " str

#define DEBUG_MSG(str)   \
    Debug->log(__LOG(str))

#define INFO_MSG(str) \
    InternalLog->log(__LOG(str))

#define LOG(str) INFO_MSG(str)

#define ERROR_MSG(str) \
    Error->log(__LOG(str))

#define USER_ERROR(str) \
    UserErrors->log(__LOG(str))

