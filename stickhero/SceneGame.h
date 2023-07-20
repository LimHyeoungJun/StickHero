#pragma once
#include "Scene.h"


class PlayerTest;

class SceneGame : public Scene
{
protected:
	PlayerTest* player;

	sf::RectangleShape shape;

	float sticklength;
	float speed = 1000.f;
	float totalRotation = 0.f;
    float time = 1.7f;
	float playerYpos;

	bool wood = false;
	bool landSequence = true;
	bool ischeck = false;
	bool ismove = false;
	bool isflip = true;
	bool going = false;
	bool playerdie = false;
	bool scorecount = true;
	bool landfirst = true;
	sf::Vector2f playermaxpos;

	sf::Font* font;

	sf::Text text;
	sf::Text best;
	sf::Texture* backg;

	int score = 0;
	int record;

	std::map<std::string, bool> mouseOverStates;

	/*float land1pos;
	float land2pos;

	bool create;*/

public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void GamePlaying(float dt);

	void ReStart(); 

	void SaveScore(int highscore);
	int LoadScore();
 
	void CreatLand1();
	void CreatLand2();


	void ShowButton();
	
};

