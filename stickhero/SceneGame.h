#pragma once
#include "Scene.h"
#include "SoundGo.h"

class Player;
class SpriteGo;
class UiButton;
class Land;
class Stick;
class Hitbox;


class SceneGame : public Scene
{
protected:
	Player* player;
	Stick* stick;
	Hitbox* hitbox;

	SpriteGo* bg[2];
	SpriteGo* cloud[3];
	Land* land[2];
	Land* landBs[2];
	sf::FloatRect landBound[2];
	sf::FloatRect landBsBound[2];

	sf::Vector2f landpos[2];
	sf::Vector2f cloudpos[2];
	sf::Vector2f bgpos[2];

	float sticklength;
	float speed = 1000.f;
	float totalRotation = 0.f;
	float time = 1.7f;
	float playerYpos;
	float savestick;

	bool stickfall = false;
	bool ischeck = false;
	bool ismove = false;

	bool playerdie = false;
	bool scorecount = true;
	bool landfirst = true;

	bool islandbound[2] = { false };

	bool sound = true;
	bool stickcollapse = false;

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
	sf::SoundBuffer bonus;
	sf::Sound soundbounus;

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

