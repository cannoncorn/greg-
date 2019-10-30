#include "Attack.h"

void Attack::setInitPos()
{
    initPos = getPosition(); // sets initPos to the current location
}

void Attack::reset()
{
    setPosition(initPos); // sets the current location to initPos
}