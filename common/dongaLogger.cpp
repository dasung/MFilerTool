#include "dongaLogger.h"
#include <cstdio>
#include <cstdarg>

void _dongaLogDebug(const char *zFormat, ...)
{
    // Buffer to store the formatted string
    char zDesc[1000];

    // Initialize the va_list
    va_list ap;
    va_start(ap, zFormat);

    // Format the string and store it in the buffer
    vsnprintf(zDesc, sizeof(zDesc), zFormat, ap);

    // Clean up the va_list
    va_end(ap);

    // Example: Writing to a log file
    FILE *logFile = fopen("log.txt", "a"); // Open the log file in append mode
    if (logFile != nullptr)
    {
        fprintf(logFile, "%s\n", zDesc);
        fclose(logFile);
    }
}