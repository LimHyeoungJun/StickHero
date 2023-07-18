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
