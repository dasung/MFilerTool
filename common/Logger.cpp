#include "Logger.h"
#include <cstdio>
#include <cstdarg>

std::unique_ptr<Logger> Logger::logger_ = nullptr;
std::mutex Logger::mutex_;


void _logDebug(const char *zFormat, ...)
{
    char zDesc[1000];

    // initialize the va_list
    va_list ap;
    va_start(ap, zFormat);

    // format the string and store it in the buffer
    vsnprintf(zDesc, sizeof(zDesc), zFormat, ap);

    // clean up the va_list
    va_end(ap);

    Logger::getInstance()->writeFile(zDesc);
}


void Logger::writeFile(const char *buferStr)
{
    FILE *logFile = fopen(LOG_FILE_NAME, "a"); // Open the log file in append mode
    if (logFile != nullptr)
    {
        fprintf(logFile, "%s\n", buferStr);
        fclose(logFile);
    }
}

Logger* Logger::getInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);
	if(logger_ == nullptr)
	{
		logger_.reset(new Logger());  // reset() used to make sure always deletes previous pointer in case.

        FILE* logFile = fopen(LOG_FILE_NAME, "r");
        if (logFile)
        {
            fclose(logFile);
            std::remove(LOG_FILE_NAME); // delete previous log file
        }
	}

	return logger_.get();
}