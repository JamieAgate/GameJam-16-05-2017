#include "PowerUps.h"

PowerUp::PowerUp(AnimSprite* _PowerUp, char _name)
{
	sprite = _PowerUp;
	powerUpID = _name;
}

PowerUp::~PowerUp()
{

}