#include "stdafx.h"
#include "SceneTitle.h"
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

SceneTitle::SceneTitle()
{
	resourceListPath = ("script/SceneGameResourceList.csv"); 
}

SceneTitle::~SceneTitle()
{
	Release();
}

void SceneTitle::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	Scene::Enter();
	//Reset();
}

void SceneTitle::Reset()
{
	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Init()
{
	Release();

	//sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/title.png");
	SpriteGo* tex = (SpriteGo*)AddGo(new SpriteGo("graphics/title.png"));
	tex->SetOrigin(Origins::MC);

	UiButton* button = (UiButton*)AddGo(new UiButton("graphics/Button.png"));
	button->SetOrigin(Origins::TC);
	button->sortLayer = 100;
	button->SetPosition(640.f, 450.f);
	
	UiButton* exitButton = (UiButton*)AddGo(new UiButton("graphics/ExitButton.png"));
	exitButton->SetOrigin(Origins::TR);
	exitButton->sortLayer = 100;
	exitButton->SetPosition(1280.f, 0.f);
	exitButton->sprite.setScale(0.65f, 0.65f);

	UiButton* charaterButton = (UiButton*)AddGo(new UiButton("graphics/charater.png"));
	charaterButton->SetOrigin(Origins::MC);
	charaterButton->sortLayer = 100;
	charaterButton->SetPosition(50.f, 500.f);

	UiButton* optionButton = (UiButton*)AddGo(new UiButton("graphics/option.png"));
	optionButton->SetOrigin(Origins::MC);
	optionButton->sortLayer = 100;
	optionButton->SetPosition(50.f, 630.f);
	

	button->OnEnter = [button]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/Button2.png");

		button->sprite.setTexture(*tex);
	};
	button->OnExit = [button]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/Button.png"); 
		button->sprite.setTexture(*tex); 
	};
	button->OnClick = [this]()
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	};

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

	charaterButton->OnEnter = [charaterButton]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/charater2.png");

		charaterButton->sprite.setTexture(*tex);
	};
	charaterButton->OnExit = [charaterButton]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/charater.png");
		charaterButton->sprite.setTexture(*tex);
	};
	charaterButton->OnClick = [this]()
	{
		SCENE_MGR.ChangeScene(SceneId::Choose); 
	};

	optionButton->OnEnter = [optionButton]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/option2.png");

		optionButton->sprite.setTexture(*tex);
	};
	optionButton->OnExit = [optionButton]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("graphics/option.png");
		optionButton->sprite.setTexture(*tex);
	};
	optionButton->OnClick = [this]()
	{
		SCENE_MGR.ChangeScene(SceneId::Option);
	};

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}*/
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window); 
}
