#pragma once
#include "ShapeGameObj.h"
class Hitbox : public ShapeGameObj
{
public:
	Hitbox();
	void SetSize(sf::Vector2f size);
	void SetPosition(sf::Vector2f position);

	sf::FloatRect GetGlobalBounds();
};

