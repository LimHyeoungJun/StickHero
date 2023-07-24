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
	SpriteGo* cloud = (SpriteGo*)AddGo(new SpriteGo("graphics/cloud.png"));
	cloud->SetName("Cloud");
	cloud->SetOrigin(Origins::MC);
	cloud->sortLayer = 1;
	cloud->sprite.setScale(0.2f, 0.2f);
	cloud->SetPosition(0.f, 0.f);

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

	SpriteGo* bg = (SpriteGo*)AddGo(new SpriteGo("graphics/background.png"));
	bg->SetName("bg");
	bg->SetOrigin(Origins::MC);
	//bg->SetPosition(-640.f, 0.f);
	bg->SetPosition(0.f, 0.f);

	SpriteGo* bg2 = (SpriteGo*)AddGo(new SpriteGo("graphics/background.png")); 
	bg2->SetName("bg2"); 
	bg2->SetPosition(1280.f, 0.f);
	bg2->SetOrigin(Origins::MC); 

	player = (Player*)AddGo(new Player());

	sticklength = 0.f;

	Stick* stick = (Stick*)AddGo(new Stick());
	stick->SetName("stick");
	stick->sortLayer = 1;
	stick->SetOrigin(Origins::BR);
	stick->SetPosition({ -340.f,257.f });
	stick->SetFillColor(sf::Color::Black);

	Hitbox* hitbox = (Hitbox*)AddGo(new Hitbox());
	hitbox->SetName("HitBox");
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
		
		Land* land1 = (Land*)AddGo(new Land());
		land1->SetName("Land1");
		land1->SetSize(Utils::RandomRange(100.f, 200.f), 720.f);
		land1->SetPosition(Utils::RandomRange(100.f, 400.f), 257.f);
		land1->SetFillColor(sf::Color::Black);
		land1->sortLayer = 20;
		land1->SetOrigin(Origins::TR);
		Land* land1bs = (Land*)AddGo(new Land());
		land1bs->SetName("Land1bs");
		land1bs->SetSize(20.f, 20.f);
		land1bs->SetPosition(land1->GetPosition().x - (land1->GetSize().x * 0.5f), 257.f);
		land1bs->SetOrigin(Origins::TC);
		land1bs->SetFillColor(sf::Color::Red);
		land1bs->sortLayer = 21;

		Land* land2 = (Land*)AddGo(new Land());
		land2->SetName("Land2");
		land2->SetSize(220.f, 720.f);
		land2->SetPosition(-340.f, 257.f);
		land2->sortLayer = 20;
		land2->SetOrigin(Origins::TR);
		land2->SetFillColor(sf::Color::Black);
		Land* land2bs = (Land*)AddGo(new Land()); 
		land2bs->SetName("Land2bs");
		land2bs->SetSize(20.f, 20.f);
		land2bs->SetPosition(land2->GetPosition().x - (land2->GetSize().x * 0.5f), 257.f);
		land2bs->SetOrigin(Origins::TC);
		land2bs->SetFillColor(sf::Color::Red);
		land2bs->sortLayer = 21;

		Land* land3 = (Land*)AddGo(new Land());
		land3->SetName("Land3");
		land3->SetSize(Utils::RandomRange(100.f, 200.f), 720.f); 
		land3->SetPosition(840.f, 257.f); 
		land3->sortLayer = 20; 
		land3->SetOrigin(Origins::TR); 
		land3->SetFillColor(sf::Color::Black); 
		Land* land3bs = (Land*)AddGo(new Land()); 
		land3bs->SetName("Land3bs");
		land3bs->SetSize(20.f, 20.f);
		land3bs->SetPosition(land3->GetPosition().x - (land3->GetSize().x * 0.5f), 257.f);
		land3bs->SetOrigin(Origins::TC);
		land3bs->SetFillColor(sf::Color::Red);
		land3bs->sortLayer = 21;

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

	//std::cout << Variables::volume << std::endl;
	SpriteGo* cloud = (SpriteGo*)FindGo("Cloud");
	SpriteGo* bg = (SpriteGo*)FindGo("bg");
	SpriteGo* bg2 = (SpriteGo*)FindGo("bg2");

	sf::Vector2f cloudpos = cloud->GetPosition();
	sf::Vector2f bgpos = bg->GetPosition();
	sf::Vector2f bg2pos = bg2->GetPosition(); 

	if (ismove)
	{
		cloudpos.x -= dt * 30.f;
		bgpos.x -= dt * 10.f;
		bg2pos.x -= dt * 10.f;
	}
	cloud->SetPosition(cloudpos.x, cloudpos.y);
	bg->SetPosition(bgpos.x, bgpos.y);
	bg2->SetPosition(bg2pos.x, bg2pos.y);
	if (cloudpos.x < -800)
	{
		cloud->SetPosition(800.f, 0.f);
	}
	if (bgpos.x <= -1280.f)
	{
		bg->SetPosition(1280.f, 0.f);
		bg->SetOrigin(Origins::MC);
	}
	if (bg2pos.x <= -1280.f)
	{
		bg2->SetPosition(1280.f, 0.f);
		bg2->SetOrigin(Origins::MC);
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
	Stick* stick = (Stick*)FindGo("stick");
	Land* land1 = (Land*)FindGo("Land1");
	Land* land2 = (Land*)FindGo("Land2");
	Land* land3 = (Land*)FindGo("Land3");
	Hitbox* hitbox = (Hitbox*)FindGo("HitBox");

	UiButton* reButton = (UiButton*)FindGo("Restart");
	UiButton* homeButton = (UiButton*)FindGo("Home");
	UiButton* exitButton = (UiButton*)FindGo("Exit");

	totalRotation = 0.f;
	sticklength = 0.f;
	stick->SetPosition({ -340.f,257.f });
	stick->SetRotaition(0.f);
	wood = false;
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
	

	land1->SetSize(Utils::RandomRange(100.f, 200.f), 720.f);
	land1->SetPosition(Utils::RandomRange(-150.f, 400.f), 257.f);
	land1->SetOrigin(Origins::TR);

	land2->SetSize(220.f, 720.f);
	land2->SetPosition(-340.f, 257.f);
	land2->SetOrigin(Origins::TR);

	land3->SetSize(Utils::RandomRange(100.f, 200.f), 720.f);
	land3->SetPosition(840.f, 257.f);
	land3->SetOrigin(Origins::TR);
	
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

	reButton->SetActive(true);
	text.setCharacterSize(90);
	text.setPosition(450.f, 100.f);



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
	Stick* stick = (Stick*)FindGo("stick");

	Land* land1 = (Land*)FindGo("Land1"); 
	Land* land1bs = (Land*)FindGo("Land1bs");
	land1bs->SetPosition(land1->GetPosition().x - (land1->GetSize().x * 0.5f), 257.f);
	
	Land* land2 = (Land*)FindGo("Land2"); 
	Land* land2bs = (Land*)FindGo("Land2bs");
	land2bs->SetPosition(land2->GetPosition().x - (land2->GetSize().x * 0.5f), 257.f);
	
	Land* land3 = (Land*)FindGo("Land3"); 
	Land* land3bs = (Land*)FindGo("Land3bs");
	land3bs->SetPosition(land3->GetPosition().x - (land3->GetSize().x * 0.5f), 257.f);

	Hitbox* hitbox = (Hitbox*)FindGo("HitBox");

	sf::FloatRect la1 = land1->GetGlobalBounds();
	sf::FloatRect la1bs = land1bs->GetGlobalBounds();

	sf::FloatRect la2 = land2->GetGlobalBounds();
	sf::FloatRect la2bs = land2bs->GetGlobalBounds();

	sf::FloatRect la3 = land3->GetGlobalBounds();
	sf::FloatRect la3bs = land3bs->GetGlobalBounds();
	
	sf::FloatRect hitb = hitbox->GetGlobalBounds();

   


	if (INPUT_MGR.GetKey(sf::Keyboard::Space)&& !stickcollapse)
	{
		sticklength += dt * speed;
		std::cout << sticklength << std::endl;
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
		wood = true;
		soundstickup.stop();
		soundslash.play();
		sound = true;
		stickcollapse = true;
	}
	if (wood)
	{
		float rotationSpeed = 200.f; // 회전 속도 
		float rotationLimit = 90.f; // 회전한 총 각도 제한 

		float rotation = rotationSpeed * dt; // 회전 각도 계산 
		if (totalRotation + rotation > rotationLimit)
			rotation = rotationLimit - totalRotation; // 회전 총 각도 제한 

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
		if (hitb.intersects(la1))
		{
			land1bound = true;
		}
		if (hitb.intersects(la2))
		{
			land2bound = true;
		}
		if (hitb.intersects(la3))
		{
			land3bound = true;
		}

		if (hitb.intersects(la1) || hitb.intersects(la2) || hitb.intersects(la3))
		{
			player->Setdistance(sticklength);
			ischeck = false;
			player->PlayerArrival(true);
			if (scorecount)
			{
				if (hitb.intersects(la1bs) || hitb.intersects(la2bs) || hitb.intersects(la3bs))
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
			sf::Vector2f land1pos = land1->GetPosition();
			sf::Vector2f land2pos = land2->GetPosition();
			sf::Vector2f land3pos = land3->GetPosition();
			
			if (land1bound)
			{
				land1->SetPosition(player->GetPosition().x + 110.f, 257.f);
				player->SetRun(false);
				//std::cout << land1->GetSize().x << std::endl;
			}
			else
			{
				land1pos.x -= 700.f * dt;
				land1->SetPosition(land1pos.x, 257.f);
				player->SetRun(false);
			}

			if (land2bound)
			{
				land2->SetPosition(player->GetPosition().x + 110.f, 257.f);
				player->SetRun(false);
			}
			else
			{
				land2pos.x -= 700.f * dt;
				land2->SetPosition(land2pos.x, 257.f);
				player->SetRun(false);
			}

			if (land3bound)
			{
				land3->SetPosition(player->GetPosition().x + 110.f, 257.f);
				player->SetRun(false);
			}
			else
			{
				land3pos.x -= 700.f * dt;
				land3->SetPosition(land3pos.x, 257.f);
				player->SetRun(false);
			}

			if (land1pos.x <= -640.f)
			{
				land1->SetSize(Utils::RandomRange(100, 200), 720.f);
				land1->SetPosition(Utils::RandomRange(940.f, 1190.f), 720.f);
				land1->SetOrigin(Origins::TR);
			}
			if (land2pos.x <= -640.f)
			{
				land2->SetSize(Utils::RandomRange(100, 200), 720.f);
				land2->SetPosition(Utils::RandomRange(940.f, 1190.f), 720.f);
				land2->SetOrigin(Origins::TR);
			}
			if (land3pos.x <= -640.f)
			{
				land3->SetSize(Utils::RandomRange(100, 200), 720.f);
				land3->SetPosition(Utils::RandomRange(940.f, 1190.f), 720.f);
				land3->SetOrigin(Origins::TR);
			}

			if (player->GetPosition().x <= -450.f)
			{
				land1bound = false;
				land2bound = false;
				land3bound = false;
				stickcollapse = false;
			}
		}

		totalRotation = 0.f;
		sticklength = 0.f;
		scorecount = true;
		stick->SetPosition({ -340.f,257.f });
		stick->SetRotaition(0.f);
		hitbox->SetPosition({ -340.f + sticklength, 257.f });
		wood = false;
		
	}
	else
	{
        ismove = false;
	}

	
	
}
