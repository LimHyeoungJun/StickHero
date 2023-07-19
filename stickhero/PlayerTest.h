#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class SceneGame;

class PlayerTest :public SpriteGo
{

protected:
	
	sf::Vector2f direction;

	bool isrun = false;
	bool animationStart = false;
	float sticklength;
	sf::Vector2f oriPos;
	bool isdie = false;
	bool isfulling = false;
	float gravity = 1000.f; 
	bool reset = false;
	bool playerArrival = false;
	bool isgo = false;

	PlayerType player;
	bool choose = true;

	float Ypos;

public:
	AnimationController animation; 

	PlayerTest(const std::string& textureId="", const std::string& n="");
	virtual ~PlayerTest() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	void SetRun(bool n);
	void SetStartAnimation(bool n);
	void Setdistance(float d);
	void PlayerDie(bool n);

	void PlayerArrival(bool p);
	bool IsGo() { return isgo; };
	sf::Vector2f Scales();
};

