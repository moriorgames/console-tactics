#include "Logger.h"

Logger::Logger()
{
    init();
}

void Logger::log(const std::string &message)
{
    std::ofstream log_file(file, std::ios_base::out | std::ios_base::app);
    log_file << message << std::endl;
}

void Logger::init()
{
    time_t rawTime;
    struct tm *timeInfo;
    char buffer[80];
    time(&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(buffer, sizeof(buffer), "%d-%m-%Y__%I_%M_%S", timeInfo);
    std::string fileTimesTamp(buffer);
    file = "logs/" + fileTimesTamp + ".log";
}
