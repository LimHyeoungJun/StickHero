#include "stdafx.h"
#include "SceneChooseCharacter.h"
#include <Framework.h>
#include "StringTable.h"  
#include "DataTableMgr.h" 
#include <SpriteGO.h>
#include "SceneMgr.h" 
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include"UiButton.h"

SceneChooseCharacter::SceneChooseCharacter()
{
	resourceListPath = ("script/SceneGameResourceList.csv");
}

SceneChooseCharacter::~SceneChooseCharacter()
{
	Release();
}

void SceneChooseCharacter::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	Scene::Enter();
}

void SceneChooseCharacter::Reset()
{
	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void SceneChooseCharacter::Exit()
{
	Scene::Exit();
}

void SceneChooseCharacter::Init()
{
	Release();

	SpriteGo* tex = (SpriteGo*)AddGo(new SpriteGo("graphics/background.png"));
	tex->SetOrigin(Origins::MC); 

	UiButton* homeButton = (UiButton*)AddGo(new UiButton("graphics/HomeButton.png"));
	homeButton->SetOrigin(Origins::TL);
	homeButton->sortLayer = 100;
	homeButton->SetPosition(0.f, 0.f);
	homeButton->sprite.setScale(0.65f, 0.65f);

	UiButton* P1Button = (UiButton*)AddGo(new UiButton("graphics/ProfileP1(2).png"));
	P1Button->SetName("Player1");
	
	UiButton* P2Button = (UiButton*)AddGo(new UiButton("graphics/ProfileP2(2).png"));
	P2Button->SetName("Player2");

	UiButton* P3Button = (UiButton*)AddGo(new UiButton("graphics/ProfileP3(2).png"));
	P3Button->SetName("Player3");


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
		SCENE_MGR.ChangeScene(SceneId::Title);
	};

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneChooseCharacter::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneChooseCharacter::Update(float dt)
{
	UiButton* P1Button = (UiButton*)FindGo("Player1");
	UiButton* P2Button = (UiButton*)FindGo("Player2");
	UiButton* P3Button = (UiButton*)FindGo("Player3");

	P1Button->SetOrigin(Origins::MC);
	P1Button->sortLayer = 100;
	P1Button->SetPosition(300.f, 300.f);

	P2Button->SetOrigin(Origins::MC);
	P2Button->sortLayer = 100;
	P2Button->sprite.setScale(0.34f, 0.37f);
	P2Button->SetPosition(650.f, 300.f);

	P3Button->SetOrigin(Origins::MC);
	P3Button->sortLayer = 100;
	P3Button->sprite.setScale(1.f, 1.f);
	P3Button->SetPosition(1000.f, 300.f);


	P1Button->OnEnter = [P1Button]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/ProfileP1.png");

		P1Button->sprite.setTexture(*tex);
	};
	P1Button->OnExit = [P1Button]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/ProfileP1(2).png");
		P1Button->sprite.setTexture(*tex);
	};
	P1Button->OnClick = [this]()
	{
		Variables::playerty = PlayerType::P1;

		SCENE_MGR.ChangeScene(SceneId::Title);
		std::cout << (int)Variables::playerty << std::endl;
		choose = true;
	};

	P2Button->OnEnter = [P2Button]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/ProfileP2.png");

		P2Button->sprite.setTexture(*tex);
	};
	P2Button->OnExit = [P2Button]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/ProfileP2(2).png");
		P2Button->sprite.setTexture(*tex);
	};
	P2Button->OnClick = [this]()
	{
		Variables::playerty = PlayerType::P2; 
		std::cout << (int)Variables::playerty << std::endl;
		SCENE_MGR.ChangeScene(SceneId::Title);
		
		choose = true;
	};

	P3Button->OnEnter = [P3Button]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/ProfileP3.png");

		P3Button->sprite.setTexture(*tex);
	};
	P3Button->OnExit = [P3Button]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/ProfileP3(2).png");
		P3Button->sprite.setTexture(*tex);
	};
	P3Button->OnClick = [this]()
	{
		Variables::playerty = PlayerType::P3; 

		SCENE_MGR.ChangeScene(SceneId::Title);
		std::cout << (int)Variables::playerty << std::endl;
		choose = true;
	};

	Scene::Update(dt);
}

void SceneChooseCharacter::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

//void SceneChooseCharacter::SetPlayer(PlayerType player)
//{
//	Variables::playerty = PlayerType::P2;
//	this->player = (PlayerType)player;
//}
//
//PlayerType SceneChooseCharacter::GetPlayer() 
//{
//	return player; 
//}
