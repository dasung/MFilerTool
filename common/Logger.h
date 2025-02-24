#pragma once

#include <mutex>
#include <memory>

class Logger
{
public:

    void writeFile(const char *zFormat);
	static Logger* getInstance();

    ~Logger() = default;   // when unique_ptr needs destroyed, destructor should be accible public


    // avoids to copy or copy assignment objects
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // optional: avoids implicit move to another objects
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

private:

    // privent object creation
    Logger() = default;

	static std::unique_ptr<Logger> logger_;
    static std::mutex mutex_;

};


void _logDebug(const char *zFormat, ...);

// set this to 0 to disable logging
#define LOG_ENABLED 1

#define LOG_FILE_NAME "devDebug.log"

// wrapper for _logDebug
#define LogDebug(...) { if(LOG_ENABLED) { _logDebug(__VA_ARGS__); } }

// to return the current function name only
#define __SEE_FUNCTION__ __FUNCTION__
