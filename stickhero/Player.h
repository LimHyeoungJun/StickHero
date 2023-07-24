#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Player :public SpriteGo
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

	bool sound = true;

	float Ypos;
	float landpos;

	sf::SoundBuffer walk;
	sf::Sound soundwalk;
	sf::SoundBuffer falling;
	sf::Sound soundfalling;


public:
	AnimationController animation; 

	Player(const std::string& textureId="", const std::string& n="");
	virtual ~Player() override { Release(); }

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
	void SetLandPos(float l);
};

