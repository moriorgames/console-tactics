#ifndef MORIOR_GAMES_ENTIty_EVENT_STATE_H
#define MORIOR_GAMES_ENTIty_EVENT_STATE_H

class EventState
{
public:
    bool isUp() const;
    void setUp(bool up);
    bool isDown() const;
    void setDown(bool down);
    bool isLeft() const;
    void setLeft(bool left);
    bool isRight() const;
    void setRight(bool right);

private:
    bool up = false, down = false, left = false, right = false;

};

#endif
