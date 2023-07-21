#include "stdafx.h"
#include "Land.h"

Land::Land() :ShapeGameObj(ShapeType::Rectangle)
{

}

void Land::SetSize(float width, float height)
{
	((sf::RectangleShape*)shape)->setSize({ width, height });
	this->size = { width,height };
}

void Land::SetPosition(float x, float y)
{
	((sf::RectangleShape*)shape)->setPosition(x, y);
	this->position = { x, y };
}

sf::FloatRect Land::GetGlobalBounds()
{
	return shape->getGlobalBounds();
}
