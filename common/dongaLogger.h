#ifndef DONGA_LOGGER_H
#define DONGA_LOGGER_H

void _dongaLogDebug(const char *zFormat, ...);

// set this to 0 to disable logging
#define LOG_ENABLED 1

// wrapper for _dongaLogDebug
#define DLogDebug(...) { if(LOG_ENABLED) { _dongaLogDebug(__VA_ARGS__); } }

#endif // DONGA_LOGGER_H