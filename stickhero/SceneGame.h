#pragma once
#include "Scene.h"


class PlayerTest;

class SceneGame : public Scene
{
protected:
	//Player2* player;
	PlayerTest* player;
	//Stick* stick;
	sf::RectangleShape shape;
	//sf::RectangleShape stick;
	float sticklength;
	float speed = 1000.f;
	float totalRotation = 0.f;
	bool stickmove = false;
	bool landSequence = true;
	bool ischeck = false;
	bool ismove = false;
	bool isflip = true;
	bool going = false;
	sf::Vector2f playermaxpos;
	bool playerdie = false;

	sf::Font* font;
	sf::Text text;
	sf::Text best;
	sf::Texture* backg;
	int score = 0;
	bool scorecount = true;

	//bool playerdie = false;
	int record;
	std::map<std::string, bool> mouseOverStates;

	float time = 1.7f;

	float playerYpos;
public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void ReStart(); 
	void SaveScore(int highscore);
	int LoadScore(); 
};

