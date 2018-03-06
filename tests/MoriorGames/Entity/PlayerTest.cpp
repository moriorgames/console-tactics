
#include <boost/test/unit_test.hpp>
#include "../../../src/MoriorGames/Entity/Player.h"

BOOST_AUTO_TEST_CASE(test_getters_and_setters_hero_entity)
{
    float x = .1f, y = .2f, angle = .3f;

    auto player = new Player(new Map);
    player->setX(x);
    player->setY(x);
    player->setAngle(angle);

    BOOST_CHECK(player->getX() == x);
    BOOST_CHECK(player->getY() == y);
    BOOST_CHECK(player->getAngle() == angle);
}
