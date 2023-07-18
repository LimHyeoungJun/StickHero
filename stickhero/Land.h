#pragma once
#include "ShapeGameObj.h"
class Land : public ShapeGameObj
{
public:
	Land();
	void SetSize(float width, float height);
	void SetPosition(float x, float y);

	sf::FloatRect GetGlobalBounds();
};

