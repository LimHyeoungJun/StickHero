#pragma once
#include "Scene.h"

class Player;

class SceneGame : public Scene
{
protected:
	Player* player;

	sf::RectangleShape shape;

	float sticklength;
	float speed = 1000.f;
	float totalRotation = 0.f;
    float time = 1.7f;
	float playerYpos;

	bool wood = false;
	bool ischeck = false;
	bool ismove = false;

	bool playerdie = false;
	bool scorecount = true;
	bool landfirst = true;

	bool land1bound = false;
	bool land2bound = false;
	bool land3bound = false;

	bool sound = true;

	sf::Font* font;

	sf::Text text;
	sf::Text best;
	sf::Texture* backg;
	sf::Texture* backg2;

	int score = 0;
	int record;

	std::map<std::string, bool> mouseOverStates;

	sf::SoundBuffer stickup;
	sf::Sound soundstickup;
	sf::SoundBuffer slash;
	sf::Sound soundslash;
	sf::SoundBuffer collapse;
	sf::Sound soundcollapse;
	sf::SoundBuffer bgm;
	sf::Sound soundbgm;

public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

    void ShowButton();

	void GamePlaying(float dt);


	void ReStart(); 

	void SaveScore(int highscore);
	int LoadScore();
 
	
	
};

