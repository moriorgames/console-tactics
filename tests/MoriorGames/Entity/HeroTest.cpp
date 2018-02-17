
#include <boost/test/unit_test.hpp>
#include "../../../src/MoriorGames/Entity/Hero.h"

using MoriorGames::Hero;

BOOST_AUTO_TEST_CASE(test_getters_and_setters_hero_entity)
{
    int id = 1;
    std::string name = "Khal Drogo";

    auto hero = new Hero;
    hero->setId(id);
    hero->setName(name);

    BOOST_CHECK(hero->getId() == id);
    BOOST_CHECK(hero->getName() == name);
}
