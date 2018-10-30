#include "_Logger.hpp"
#include <ctime>

static std::map<std::string, Logger*> _loggers;

#ifndef __NO_CPLUS_LOGGING
Logger* __NULL_Logger__ = new Logger("/dev/null", NONE);
Logger* Debug           = new Logger("Logs/debug.dbg");
Logger* Error           = new Logger("Logs/error.dbg");
Logger* InternalLog     = new Logger("Logs/log.dbg");
Logger* UserErrors      = new UserFacingLogger("Logs/user_error.dbg", "Error");
#endif

/*
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
    

    Logger& operator<<(std::string str);

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
*/

//just for now
static std::string default_formatter(std::string str, ...) 
{
    time_t now = time(0);
    std::string dt = ctime(&now);
    dt.pop_back();
    
    return dt + ": " + str + '\n'; 
}


/**
 * TODO:
 * make this function properly print out in accordance with 
 * Output enum options including the possible or options
 * 
 * enum Output {
    NONE = -1,
    FILE_ONLY = 0,
    NO_FILE = 1,
    STDERR = 2,  // ie 3 is no file and stderr
    STDOUT = 4   //    5 is no file and stdout
                 //    7 is no file, stderr and stdout
                 //    6 is file, stderr, and stdout
  };
 */     
void Logger::print(std::string str, va_list list)
{
    if (out_type == NONE) return;

    
    if ( !(1 & out_type)) {
        output << formatter(str, list);
        output.flush();
    }
    
    if (out_type == 5 || 
        out_type == 6 ||
        out_type == 7   )
        std::cout << formatter(str, list);
}


Logger::Logger(std::string filename, Output c)
: out_type(c), formatter(default_formatter)
{
    output.open(filename, std::fstream::out);
    _loggers[filename] = this;
}

Logger::Logger(std::string filename)
: out_type(FILE_ONLY), formatter(default_formatter)
{
    output.open(filename, std::fstream::out);
    _loggers[filename] = this;
}

Logger::Logger(std::string filename, std::string(*formatter)(std::string, ...))
: out_type(FILE_ONLY), formatter(formatter)
{
    output.open(filename, std::fstream::out);
    _loggers[filename] = this;
}

Logger::~Logger()
{
    //erases it self from the map
    for (const auto& it : _loggers)
        if (it.second == this) {
            _loggers.erase(it.first);
            return;
        }
}

void Logger::stdout_true() { out_type &= STDOUT; }
void Logger::stdout_false() { out_type ^= STDOUT; }

void Logger::log(std::string str, ...) { print(str, NULL); }

void Logger::operator<<(std::string str)
{
    this->log(str);
}

Logger* get_logger(std::string str) {
    //dont

    for (const auto& i : _loggers)
        if (i.first == str)
            return i.second;

    return get_logger("NULL_Logger");
}


UserFacingLogger::UserFacingLogger(std::string filename, std::string name)
: Logger(filename), public_name(name), public_formatter(default_formatter)
{}

UserFacingLogger::UserFacingLogger(std::string filename, std::string name, Output out_type)
: Logger(filename, out_type), public_name(name), public_formatter(default_formatter)
{}

UserFacingLogger::UserFacingLogger(std::string filename, std::string name, std::string(*public_formatter)(std::string, ...))
: Logger(filename), public_name(name), public_formatter(public_formatter)
{}


void UserFacingLogger::print(std::string str, va_list list)
{
    if (out_type == NONE) return;

    
    if ( !(1 & out_type)) {
        output << formatter(str, list);
        output.flush();
    }
    
    if (out_type == 5 || 
        out_type == 6 ||
        out_type == 7   )
        std::cout << public_formatter(str, list);
}