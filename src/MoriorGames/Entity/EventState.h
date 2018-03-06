#ifndef MORIOR_GAMES_ENTIty_EVENT_STATE_H
#define MORIOR_GAMES_ENTIty_EVENT_STATE_H

class EventState
{
public:
    EventState();
    void clear();
    bool isUp() const;
    void setUp(bool up);
    bool isDown() const;
    void setDown(bool down);
    bool isLeft() const;
    void setLeft(bool left);
    bool isRight() const;
    void setRight(bool right);

private:
    bool up, down, left, right;

};

#endif
