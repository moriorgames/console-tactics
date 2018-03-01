#ifndef MORIOR_GAMES_SERVICES_LOGGER_H
#define MORIOR_GAMES_SERVICES_LOGGER_H

#include <ctime>
#include <string>
#include <fstream>

class Logger
{
public:
    Logger();
    void log(const std::string &message);

private:
    std::string file;

    void init();
};

#endif
