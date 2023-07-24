#pragma once
#include "Scene.h"
class SceneOption : public Scene
{
protected:
	std::map<std::string, bool> mouseOverStates;

	sf::RectangleShape shape;
	sf::RectangleShape shapepoint;

	bool first = true;
	//int volume = 50;

public:
	SceneOption();
	virtual ~SceneOption() override;

	virtual void Enter() override;
	void Reset();
	virtual void Exit() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};
