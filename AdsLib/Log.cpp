#include "Log.h"
#include <algorithm>
#include <chrono>
#include <ctime>

#ifdef _WIN32
#define TIME_T_TO_STRING(DATE_TIME, TIME_T) do { \
    struct tm temp; \
    localtime_s(&temp, TIME_T); \
    std::strftime(DATE_TIME, sizeof(DATE_TIME), "%Y-%m-%dT%H:%M:%S ", &temp); \
    } while (0, 0);
#else
#define TIME_T_TO_STRING(DATE_TIME, TIME_T) std::strftime(DATE_TIME, sizeof(DATE_TIME), "%FT%T%z ", localtime(TIME_T));
#endif

static const char* CATEGORY[] = {
    "Info: ",
    "Warning: ",
    "Error: "
};

void Logger::Log(const size_t level, const std::string &msg)
{
    std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char dateTime[28];

    //TODO use std::put_time() when available
    TIME_T_TO_STRING(dateTime, &tt);
    std::cerr << dateTime << CATEGORY[std::min(level, sizeof(CATEGORY) / sizeof(CATEGORY[0]))] << msg << std::endl;
}