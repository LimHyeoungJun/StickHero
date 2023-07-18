#include "stdafx.h"
#include "Hitbox.h"

Hitbox::Hitbox()
	:ShapeGameObj(ShapeType::Rectangle)
{
}

void Hitbox::SetSize(sf::Vector2f size)
{
	((sf::RectangleShape*)shape)->setSize(size);
}

void Hitbox::SetPosition(sf::Vector2f position)
{
	((sf::RectangleShape*)shape)->setPosition(position);
}

sf::FloatRect Hitbox::GetGlobalBounds() 
{
	return shape->getGlobalBounds(); 
}
