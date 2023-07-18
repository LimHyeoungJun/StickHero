#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "PlayerTest.h"
#include "Framework.h"
#include "Player2.h"
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
	/*resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/sprite_sheet.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/RubySheet.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/Button.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/Button2.png"));*/

	//resourceListPath.push_back(std::make_tuple(ResourceTypes::Font, "font/NanumGothic.ttf");

	//font.loadFromFile("font/NanumGothic.ttf");
	

	sticklength = 0.f;
}

void SceneGame::Init()
{
	Release();

	UiButton* reButton = (UiButton*)AddGo(new UiButton("graphics/ReButton.png"));   
	reButton->SetOrigin(Origins::MC);  
	reButton->sortLayer = 100;  
	reButton->SetPosition(640.f,450.f);  
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
	bg->SetOrigin(Origins::MC); 
	 
	
	//player = (Player2*)AddGo(new Player2());
	player = (PlayerTest*)AddGo(new PlayerTest());

	shape.setFillColor(sf::Color::Black); 
	shape.setSize({ 200.f,720.f }); 
	shape.setPosition({100.f,617.f}); 
	//shape.setOrigin(200.f,0.f);

	sticklength = 0.f;

	Stick* stick = (Stick*)AddGo(new Stick());
	stick->SetName("stick");
	stick->sortLayer = 1;
	//stick->SetSize(5.f, sticklength);
	stick->SetOrigin(Origins::BR);
	stick->SetPosition({ -340.f,257.f });
	stick->SetFillColor(sf::Color::Black);

	Land* land1 = (Land*)AddGo(new Land());
	land1->SetName("Land1");
	
	Land* land2 = (Land*)AddGo(new Land());
	land2->SetName("Land2");
	
	Hitbox* hitbox = (Hitbox*)AddGo(new Hitbox());
	hitbox->SetName("HitBox");
	hitbox->SetSize({0.1f, 10.f});
	hitbox->SetFillColor(sf::Color::Red);
	hitbox->sortLayer = -30;
	hitbox->SetOrigin(Origins::MC);

	land1->SetSize(Utils::RandomRange(100.f, 200.f), 720.f);
	land1->SetPosition(Utils::RandomRange(-250.f, 400.f), 257.f); 
	land1->SetFillColor(sf::Color::Black);
	land1->sortLayer = 20;
	land1->SetActive(true); 
	land1->SetOrigin(Origins::TC); 
	isflip = true;
	

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
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	//uiView.setCenter({ 0,0 });

	Scene::Enter();

	font = (RESOURCE_MGR.GetFont("font/NanumGothic.ttf"));
	text.setFont(*font);
	best.setFont(*font);

	backg = (RESOURCE_MGR.GetTexture("graphics/background.png"));
	

}
void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Stick* stick = (Stick*)FindGo("stick");
	Land* land1 = (Land*)FindGo("Land1");
	Land* land2 = (Land*)FindGo("Land2");
	Hitbox* hitbox = (Hitbox*)FindGo("HitBox");

	sf::FloatRect la1 = land1->GetGlobalBounds();
	sf::FloatRect la2 = land2->GetGlobalBounds();
	sf::FloatRect hitb = hitbox->GetGlobalBounds();

	UiButton* reButton = (UiButton*)FindGo("Restart");
	UiButton* homeButton = (UiButton*)FindGo("Home");
	UiButton* exitButton = (UiButton*)FindGo("Exit");
	
	if (!playerdie)
	{
		if (INPUT_MGR.GetKey(sf::Keyboard::Space))
		{
			sticklength += dt * speed;

			//std::cout << sticklength << std::endl;
		}
		stick->SetSize(7.f, sticklength);
		stick->SetOrigin(Origins::BR);
		hitbox->SetPosition({ -340.f + sticklength, 257.f });
		player->Setdistance(sticklength);

		if (INPUT_MGR.GetKeyUp(sf::Keyboard::Space))
		{
			wood = true;
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

				if (hitb.intersects(la1))
				{
					ismove = true;
				}
				if (hitb.intersects(la2))
				{
					ismove = true;
				}
			}
		}

		

		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		{
			hitbox->SetSize({ 10.f,10.f });
		}

		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		{
			hitbox->SetSize({ 0.1f,10.f });
		}

		if (ischeck)
		{
			if (isflip)
			{
				if (!hitb.intersects(la1))
				{
					ischeck = false;
					player->SetOrigin(Origins::BL); 
					player->PlayerDie(true);
					playerdie = true;
					player->PlayerArrival(false);
					playerdie = true; 
				}
				else
				{
					ischeck = false;
					ismove = true;
					player->PlayerArrival(true);
					if (scorecount)
					{
						score += 1;
					}
					scorecount = false;
				}
			}
			if (!isflip)
			{
				if (!hitb.intersects(la2))
				{
					ischeck = false;
					player->SetOrigin(Origins::BL); 
					player->PlayerDie(true);
					playerdie = true;
					player->PlayerArrival(false);
					playerdie = true;
				}
				else
				{
					ischeck = false;
					ismove = true;
					player->PlayerArrival(true);
					if (scorecount)
					{
						score += 1;
					}
					scorecount = false;
				}
			}
		}

		if (player->IsGo())
		{
			if (!playerdie)
			{
				shape.setScale(0.f, 0.f);
			}

			if (isflip && !playerdie)
			{
				if (player->GetPosition().x <= -450.f)
				{
					land1->SetActive(false);
					land2->SetSize(Utils::RandomRange(100.f, 200.f), 720.f);
					land2->SetPosition(Utils::RandomRange(-200.f, 400.f), 257.f);
					//land2->SetFillColor(sf::Color::White);
					land2->sortLayer = 20;
					land2->SetActive(true);
					land2->SetOrigin(Origins::TC);
					isflip = false;
					shape.setScale(1.f, 1.f);
					player->SetRun(false);
				}
				land1->SetPosition(player->GetPosition().x, 257.f);
			}
			if (!isflip && !playerdie)
			{
				land2->SetPosition(player->GetPosition().x, 257.f);
				if (player->GetPosition().x <= -450.f)
				{
					land2->SetActive(false);
					land1->SetSize(Utils::RandomRange(100.f, 200.f), 720.f);
					land1->SetPosition(Utils::RandomRange(-200.f, 400.f), 257.f);
					//land1->SetFillColor(sf::Color::White);
					land1->sortLayer = 20;
					land1->SetActive(true);
					land1->SetOrigin(Origins::TC);
					isflip = true;
					shape.setScale(1.f, 1.f);
					player->SetRun(false);
				}
			}

			totalRotation = 0.f;
			sticklength = 0.f;
			scorecount = true;
			stick->SetPosition({ -340.f,257.f });
			stick->SetRotaition(0.f);
			wood = false;

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
	}
	else
	{
		
		if (player->GetPosition().y > 1000.f)
		{
			reButton->SetActive(true);
			text.setCharacterSize(90);
			text.setPosition(450.f,100.f); 

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
	}

	if (record <= score)
	{
		record = score;
	}

	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	
	//window.setview(worldview); 
	window.draw(shape); 
	window.draw(text);
	window.draw(best);
	//window.draw(stick);
	
}

void SceneGame::ReStart()
{
	Stick* stick = (Stick*)FindGo("stick");
	Land* land1 = (Land*)FindGo("Land1");
	Land* land2 = (Land*)FindGo("Land2");
	Hitbox* hitbox = (Hitbox*)FindGo("HitBox");

	sf::FloatRect la1 = land1->GetGlobalBounds();
	sf::FloatRect la2 = land2->GetGlobalBounds();
	sf::FloatRect hitb = hitbox->GetGlobalBounds();
	UiButton* reButton = (UiButton*)FindGo("Restart");
	UiButton* homeButton = (UiButton*)FindGo("Home");
	UiButton* exitButton = (UiButton*)FindGo("Exit");

	totalRotation = 0.f;
	sticklength = 0.f;
	stick->SetPosition({ -340.f,257.f });
	stick->SetRotaition(0.f);
	wood = false;
	SCENE_MGR.ChangeScene(sceneId);
	land2->SetActive(false);
	land1->SetSize(Utils::RandomRange(100.f, 200.f), 720.f);
	land1->SetPosition(Utils::RandomRange(-250.f, 400.f), 257.f);
	//land1->SetFillColor(sf::Color::Black);
	land1->sortLayer = 20;
	land1->SetActive(true);
	land1->SetOrigin(Origins::TC);
	isflip = true;
	player->SetRun(false);
	player->SetPosition(-450.f, 300.f);
	ischeck = false;
	player->PlayerDie(false);
	playerdie = false;
	ismove = false;
	shape.setScale(1.f, 1.f);
	score = 0;
	reButton->SetActive(false);
	time = 1.7f;
	homeButton->SetActive(false);
	player->SetOrigin(Origins::BC);
	text.setCharacterSize(30);
	text.setPosition(600.f, 0.f);
	exitButton->SetActive(false);
}
