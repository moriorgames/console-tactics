#ifndef MORIOR_GAMES_ENTITY_HERO_H
#define MORIOR_GAMES_ENTITY_HERO_H

#include <string>

namespace MoriorGames {

class Hero
{
private:
    int id;
    std::string name;

public:
    int getId() const;
    void setId(int id);
    const std::string &getName() const;
    void setName(const std::string &name);
};

}

#endif
