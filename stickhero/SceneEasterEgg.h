#pragma once
#include "Scene.h"

class EggAnimation;

class SceneEasterEgg : public Scene
{
protected:
	EggAnimation* egg;
public:
	SceneEasterEgg();
	virtual ~SceneEasterEgg() override;

	virtual void Enter() override;
	void Reset();
	virtual void Exit() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

