#include "stdafx.h"
#include "ShapeGameObj.h"
#include "Utils.h"

ShapeGameObj::ShapeGameObj(ShapeType type)
	:GameObject("Shape"),type(type)
{
	switch (type)
	{
	case ShapeType::None:
		break;
	case ShapeType::Rectangle:
		shape = new sf::RectangleShape();
		break;
	}
}

void ShapeGameObj::Init()
{
}

void ShapeGameObj::Release()
{
	delete shape;
}
void ShapeGameObj::Update(float dt)
{
}
void ShapeGameObj::Draw(sf::RenderWindow& window)
{
	window.draw(*shape);
}

void ShapeGameObj::SetOrigin(Origins origin)
{
	Utils::SetOrigin(*shape, origin);
}

void ShapeGameObj::SetPosition(const sf::Vector2f& position)
{
	GameObject::SetPosition(position);
	shape->setPosition(position);
}

void ShapeGameObj::SetFillColor(sf::Color color)
{
	shape->setFillColor(color);
}

void ShapeGameObj::Reset()
{
}
