#pragma once
#include "Utils.h"

class GameObject
{
protected:
	sf::Vector2f position;
	sf::Vector2f size;
	std::string name;
	bool isActive = true;
	Origins origin = Origins::TL;

public:

	int sortLayer = 0;
	int sortOrder = 0;

	GameObject(const std::string& n = "");
	virtual ~GameObject();

	bool GetActive() const;
	void SetActive(bool active);

	const std::string& GetName();
	virtual void SetName(const std::string& n);

	const sf::Vector2f& GetPosition();
	const sf::Vector2f& GetSize();

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetSize(const sf::Vector2f& p);
	virtual void SetSize(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Init() = 0;	
	virtual void Release() {};

	virtual void Reset() = 0;	// √ ±‚»≠

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
};

