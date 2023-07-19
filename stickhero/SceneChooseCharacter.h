#pragma once
#include "Scene.h"

class SceneChooseCharacter : public Scene
{
	friend Singleton<SceneChooseCharacter>;

protected:

	std::map<std::string, bool> mouseOverStates;

	bool choose = false;
public:
	//PlayerType player;
	SceneChooseCharacter();
	virtual ~SceneChooseCharacter() override;

	virtual void Enter() override;
	void Reset();
	virtual void Exit() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	/*void SetPlayer(int player);
	PlayerType GetPlayer();*/
};



