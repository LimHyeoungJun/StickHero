#pragma once
#include <SFML/Graphics.hpp> 
#include "Defines.h"
#include "GameObject.h"

class ShapeGameObj : public GameObject
{
protected:
	sf::Shape* shape;  
	ShapeType type; 
public:
	ShapeGameObj(ShapeType type);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override; //¾ê
	virtual void Draw(sf::RenderWindow& window) override;  //¾ê

	void SetOrigin(Origins origin);
	virtual void SetPosition(const sf::Vector2f& position) override;
	void SetFillColor(sf::Color color);

	virtual void Reset() override;

};

