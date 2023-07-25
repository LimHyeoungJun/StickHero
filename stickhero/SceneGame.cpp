#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "Framework.h"
#include "Stick.h"
#include "UiButton.h"
#include "Land.h"
#include "Hitbox.h"
#include <sstream>
#include "SpriteGo.h" 
#include "UiButton.h"
#include "SoundGo.h"
SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = ("script/SceneGameResourceList.csv");
	sticklength = 0.f;
	stickup.loadFromFile("sound/stickup.wav");
	soundstickup.setBuffer(stickup);
	slash.loadFromFile("sound/slash.wav");
	soundslash.setBuffer(slash);
	collapse.loadFromFile("sound/Collapse.wav");
	soundcollapse.setBuffer(collapse);
	bonus.loadFromFile("sound/bonus.wav");
	soundbounus.setBuffer(bonus);
};
void SceneGame::Init()
{
	Release();
	for (int i = 0; i < 2; ++i)
	{
		cloud[i] = (SpriteGo*)AddGo(new SpriteGo("graphics/cloud.png"));
		cloud[i]->SetOrigin(Origins::MC);
		cloud[i]->sortLayer = 1;
		cloud[i]->sprite.setScale(0.2f, 0.2f);
		cloud[i]->SetPosition(0.f +(i*700), -150.f + (i * 170));
	}
	UiButton* reButton = (UiButton*)AddGo(new UiButton("graphics/ReButton.png"));
	reButton->SetOrigin(Origins::MC);
	reButton->sortLayer = 100;
	reButton->SetPosition(640.f, 450.f);
	reButton->SetName("Restart");
	reButton->SetActive(false);
	UiButton* homeButton = (UiButton*)AddGo(new UiButton("graphics/HomeButton.png"));
	homeButton->SetOrigin(Origins::MC);
	homeButton->sortLayer = 100;
	homeButton->SetPosition(390.f, 450.f);
	homeButton->SetName("Home");
	homeButton->SetActive(false);
	UiButton* exitButton = (UiButton*)AddGo(new UiButton("graphics/ExitButton.png"));
	exitButton->SetOrigin(Origins::MC);
	exitButton->sortLayer = 100;
	exitButton->SetPosition(890.f, 450.f);
	exitButton->SetName("Exit");
	exitButton->SetActive(false);
	bg[0] = (SpriteGo*)AddGo(new SpriteGo("graphics/background.png"));
	bg[0]->SetOrigin(Origins::MC);
	bg[0]->SetPosition(0.f, 0.f);
	bg[1] = (SpriteGo*)AddGo(new SpriteGo("graphics/background.png"));
	bg[1]->SetPosition(1280.f, 0.f);
	bg[1]->SetOrigin(Origins::MC);
	player = (Player*)AddGo(new Player());
	player->sortLayer = 50;
	sticklength = 0.f;
	stick = (Stick*)AddGo(new Stick());
	stick->sortLayer = 1;
	stick->SetOrigin(Origins::BR);
	stick->SetPosition({ -340.f,257.f });
	stick->SetFillColor(sf::Color::Black);
	hitbox = (Hitbox*)AddGo(new Hitbox());
	hitbox->SetSize({ 0.1f, 10.f });
	hitbox->SetFillColor(sf::Color::Red);
	hitbox->sortLayer = -30;
	hitbox->SetOrigin(Origins::MC);
	record = LoadScore();
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneGame::Enter()
{
	bgm.loadFromFile("sound/bgm.wav");
	soundbgm.setBuffer(bgm);
	soundbgm.setVolume(Variables::volume);
	soundbgm.play();
	soundbgm.setLoop(true);
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });
	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	Scene::Enter();
	font = (RESOURCE_MGR.GetFont("font/NanumGothic.ttf"));
	text.setFont(*font);
	best.setFont(*font);
	if (landfirst)
	{
		land[0] = (Land*)AddGo(new Land());
		land[0]->SetSize(Utils::RandomRange(100.f, 200.f), 720.f);
		land[0]->SetPosition(Utils::RandomRange(100.f, 400.f), 257.f);
		land[0]->SetFillColor(sf::Color::Black);
		land[0]->sortLayer = 20;
		land[0]->SetOrigin(Origins::TR);
		landBs[0] = (Land*)AddGo(new Land());
		landBs[0]->SetSize(20.f, 20.f);
		landBs[0]->SetPosition(land[0]->GetPosition().x - (land[0]->GetSize().x * 0.5f), 257.f);
		landBs[0]->SetOrigin(Origins::TC);
		landBs[0]->SetFillColor(sf::Color::Red);
		landBs[0]->sortLayer = 21;
		land[1] = (Land*)AddGo(new Land());
		land[1]->SetSize(220.f, 720.f);
		land[1]->SetPosition(-340.f, 257.f);
		land[1]->sortLayer = 20;
		land[1]->SetOrigin(Origins::TR);
		land[1]->SetFillColor(sf::Color::Black);
		landBs[1] = (Land*)AddGo(new Land());
		landBs[1]->SetSize(20.f, 20.f);
		landBs[1]->SetPosition(land[1]->GetPosition().x - (land[1]->GetSize().x * 0.5f), 257.f);
		landBs[1]->SetOrigin(Origins::TC);
		landBs[1]->SetFillColor(sf::Color::Red);
		landBs[1]->sortLayer = 21;
		land[2] = (Land*)AddGo(new Land());
		land[2]->SetSize(Utils::RandomRange(100.f, 200.f), 720.f);
		land[2]->SetPosition(840.f, 257.f);
		land[2]->sortLayer = 20;
		land[2]->SetOrigin(Origins::TR);
		land[2]->SetFillColor(sf::Color::Black);
		landBs[2] = (Land*)AddGo(new Land());
		landBs[2]->SetSize(20.f, 20.f);
		landBs[2]->SetPosition(land[2]->GetPosition().x - (land[2]->GetSize().x * 0.5f), 257.f);
		landBs[2]->SetOrigin(Origins::TC);
		landBs[2]->SetFillColor(sf::Color::Red);
		landBs[2]->sortLayer = 21;
		landfirst = false;
	}
	playerYpos = player->GetPosition().y;
}
void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	GamePlaying(dt);
	soundcollapse.setVolume(Variables::volume);
	soundstickup.setVolume(Variables::volume);
	soundslash.setVolume(Variables::volume);
	soundbgm.setVolume(Variables::volume);
	soundbounus.setVolume(Variables::volume);
	for (int i = 0; i < 2; ++i)
	{
	    cloudpos[i] = cloud[i]->GetPosition();
		bgpos[i] = bg[i]->GetPosition();
	}
	if (ismove)
	{
		for (int i = 0; i < 2; ++i)
		{
			cloudpos[i].x -= dt * 30.f;
			bgpos[i].x -= dt * 10.f;
		}
	}
	else
	{
		cloudpos[0].x -= dt * 7.f;
		cloudpos[1].x -= dt * 10.f;
	}
	for (int i = 0; i < 2; ++i)
	{
		cloud[i]->SetPosition(cloudpos[i].x, cloudpos[i].y);
		bg[i]->SetPosition(bgpos[i].x, bgpos[i].y); 
	}
	if (cloudpos[0].x < -800)
	{
		cloud[0]->SetPosition(800.f, -150.f);
		cloud[0]->SetOrigin(Origins::MC);
	}
	if (cloudpos[1].x < -800)
	{
		cloud[1]->SetPosition(800.f, 70.f);
		cloud[1]->SetOrigin(Origins::MC);
	}
	for (int i = 0; i < 2; ++i)
	{
		if (bgpos[i].x <= -1280.f)
		{
			bg[i]->SetPosition(1280.f, 0.f);
			bg[i]->SetOrigin(Origins::MC);
		}
	}
	std::stringstream tscore;
	tscore << "Score: " << score;
	text.setCharacterSize(30);
	text.setPosition(600.f, 0.f);
	text.setString(tscore.str());
	std::stringstream bscore;
	bscore << "Best Score: " << record;
	best.setCharacterSize(30);
	best.setPosition(1050.f, 0.f);
	best.setString(bscore.str());
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
	else
	{
		if (player->GetPosition().y > 1000.f)
		{
			ShowButton();
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		ReStart();
		soundbgm.stop();
		SCENE_MGR.ChangeScene(SceneId::Title);
	}

	if (record <= score)
	{
		record = score;
		SaveScore(record);
	}

	if (sticklength > 10000.f)
	{
		SCENE_MGR.ChangeScene(SceneId::Easter);
	}
	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(text);
	window.draw(best);
}

void SceneGame::ReStart()
{
	UiButton* reButton = (UiButton*)FindGo("Restart");
	UiButton* homeButton = (UiButton*)FindGo("Home");
	UiButton* exitButton = (UiButton*)FindGo("Exit");
	totalRotation = 0.f;
	sticklength = 0.f;
	stick->SetPosition({ -340.f,257.f });
	stick->SetRotaition(0.f);
	stickfall = false;
	SCENE_MGR.ChangeScene(sceneId);
	player->SetRun(false);
	player->SetPosition(-450.f, playerYpos);
	ischeck = false;
	player->PlayerDie(false);
	playerdie = false;
	ismove = false;
	score = 0;
	reButton->SetActive(false);
	time = 1.7f;
	homeButton->SetActive(false);
	player->SetOrigin(Origins::BC);
	text.setCharacterSize(30);
	text.setPosition(600.f, 0.f);
	exitButton->SetActive(false);
	land[0]->SetSize(Utils::RandomRange(100.f, 200.f), 720.f);
	land[0]->SetPosition(Utils::RandomRange(-150.f, 400.f), 257.f);
	land[0]->SetOrigin(Origins::TR);
	land[1]->SetSize(220.f, 720.f);
	land[1]->SetPosition(-340.f, 257.f);
	land[1]->SetOrigin(Origins::TR);
	land[2]->SetSize(Utils::RandomRange(100.f, 200.f), 720.f);
	land[2]->SetPosition(840.f, 257.f);
	land[2]->SetOrigin(Origins::TR);
	stickcollapse = false;
}

void SceneGame::SaveScore(int highscore)
{
	std::ofstream file("highscore.txt");
	if (file.is_open())
	{
		file << highscore;
		file.close();
		std::cout << "save score" << std::endl;
	}
	else
	{
		std::cout << "failed" << std::endl;
	}
}

int SceneGame::LoadScore()
{
	int highscore = 0;
	std::ifstream file("highscore.txt");
	if (file.is_open())
	{
		file >> highscore;
		file.close();
		std::cout << "Load successfully" << std::endl;
	}
	else
	{
		std::cout << "failed" << std::endl;
	}
	return highscore;
}


void SceneGame::ShowButton()
{
	UiButton* reButton = (UiButton*)FindGo("Restart");
	UiButton* homeButton = (UiButton*)FindGo("Home");
	UiButton* exitButton = (UiButton*)FindGo("Exit");
	text.setCharacterSize(90);
	text.setPosition(450.f, 100.f);
	reButton->SetActive(true);
	reButton->OnEnter = [reButton]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/ReButton2.png");
		reButton->sprite.setTexture(*tex);
	};
	reButton->OnExit = [reButton]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/ReButton.png");
		reButton->sprite.setTexture(*tex);
	};
	reButton->OnClick = [this]()
	{
		ReStart();
	};
	homeButton->SetActive(true);
	homeButton->OnEnter = [homeButton]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/HomeButton2.png");
		homeButton->sprite.setTexture(*tex);
	};
	homeButton->OnExit = [homeButton]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/HomeButton.png");
		homeButton->sprite.setTexture(*tex);
	};
	homeButton->OnClick = [this]()
	{
		ReStart();
		soundbgm.stop();
		SCENE_MGR.ChangeScene(SceneId::Title);
	};
	exitButton->SetActive(true);
	exitButton->OnEnter = [exitButton]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/ExitButton2.png");
		exitButton->sprite.setTexture(*tex);
	};
	exitButton->OnExit = [exitButton]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/ExitButton.png");
		exitButton->sprite.setTexture(*tex);
	};
	exitButton->OnClick = [this]()
	{
		window.close();
	};
}

void SceneGame::GamePlaying(float dt)
{
	landBs[0]->SetPosition(land[0]->GetPosition().x - (land[0]->GetSize().x * 0.5f), 257.f);
	landBs[1]->SetPosition(land[1]->GetPosition().x - (land[1]->GetSize().x * 0.5f), 257.f);
	landBs[2]->SetPosition(land[2]->GetPosition().x - (land[2]->GetSize().x * 0.5f), 257.f);
	landBound[0] = land[0]->GetGlobalBounds();
	landBsBound[0] = landBs[0]->GetGlobalBounds();
	landBound[1] = land[1]->GetGlobalBounds();
	landBsBound[1] = landBs[1]->GetGlobalBounds();
	landBound[2] = land[2]->GetGlobalBounds();
	landBsBound[2] = landBs[2]->GetGlobalBounds();
	sf::FloatRect hitb = hitbox->GetGlobalBounds();
	if (INPUT_MGR.GetKey(sf::Keyboard::Space) && !stickcollapse)
	{
		sticklength += dt * speed;
		//std::cout << sticklength << std::endl;
	}
	stick->SetSize(7.f, sticklength);
	stick->SetOrigin(Origins::BR);
	hitbox->SetPosition({ -340.f + sticklength, 257.f });
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		soundstickup.play();
		soundstickup.setLoop(true);
	}
	if (INPUT_MGR.GetKeyUp(sf::Keyboard::Space))
	{
		stickfall = true;
		soundstickup.stop();
		soundslash.play();
		sound = true;
		stickcollapse = true;
	}
	if (stickfall)
	{
		float rotationSpeed = 200.f; // 회전 속도 
		float rotationLimit = 90.f; // 회전한 총 각도 제한 
		float rotation = rotationSpeed * dt; // 회전 각도 계산 
		if (totalRotation + rotation > rotationLimit)
		{
			rotation = rotationLimit - totalRotation; // 회전 총 각도 제한 
		}
		totalRotation += rotation; // 회전 총 각도 누적 
		stick->SetRotaition(totalRotation); // 회전 설정 
		if (totalRotation >= rotationLimit)
		{
			player->SetRun(true);
			ischeck = true;
			if (sound)
			{
				sound = false;
				soundcollapse.play();
			}
		}
	}
	if (ischeck)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (hitb.intersects(landBound[i]))
			{
				islandbound[i] = true;
			}
		}

		if (hitb.intersects(landBound[0]) || hitb.intersects(landBound[1]) || hitb.intersects(landBound[2]))  
		{
			player->Setdistance(sticklength);
			ischeck = false;
			player->PlayerArrival(true);
			if (scorecount)
			{
				if (hitb.intersects(landBsBound[0]) || hitb.intersects(landBsBound[1]) || hitb.intersects(landBsBound[2]))
				{
					soundbounus.play();
					score += 2;
				}
				else
				{
					score += 1;
				}
			}
			scorecount = false;
		}
		else
		{
			player->Setdistance(sticklength);
			ischeck = false;
			//player->SetOrigin(Origins::BL);
			player->PlayerDie(true);
			playerdie = true;
			player->PlayerArrival(false);
			soundbgm.stop();
		}
	}
	if (player->IsGo())
	{
		if (!playerdie)
		{
			ismove = true;
			for (int i = 0; i < 3; ++i)
			{
				landpos[i] = land[i]->GetPosition();

				if (islandbound[i])
				{
					land[i]->SetPosition(player->GetPosition().x + 110.f, 257.f);
					player->SetRun(false);
					//std::cout << land1->GetSize().x << std::endl;
				}
				else
				{
					landpos[i].x -= 700.f * dt;
					land[i]->SetPosition(landpos[i].x, 257.f);
					player->SetRun(false);
				}
			}
			for (int i = 0; i < 3; ++i)
			{
				if (landpos[i].x <= -640.f)
				{
					std::cout << "New land" << std::endl;
					land[i]->SetSize(Utils::RandomRange(100, 200), 720.f);
					land[i]->SetPosition(Utils::RandomRange(940.f, 1190.f), 720.f);
					land[i]->SetOrigin(Origins::TR);
				}
			}
			if (player->GetPosition().x <= -450.f)
			{
				for (int i = 0; i < 3; ++i)
				{
					islandbound[i] = false;
				}
				stickcollapse = false;
			}
		}

		totalRotation = 0.f;
		sticklength = 0.f;
		scorecount = true;
		stick->SetPosition({ -340.f,257.f });
		stick->SetRotaition(0.f);
		hitbox->SetPosition({ -340.f + sticklength, 257.f });
		stickfall = false;
	}
	else
	{
		ismove = false;
	}
}