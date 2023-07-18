#include "stdafx.h"
#include "Stick.h"

Stick::Stick()
	:ShapeGameObj(ShapeType::Rectangle)
{

}

void Stick::SetSize(float width, float height)
{
	((sf::RectangleShape*)shape)->setSize({width, height }); 
}

void Stick::SetRotaition(float r)
{
	((sf::RectangleShape*)shape)->setRotation(r);
}
