#include "stdafx.h"
#include "SceneEasterEgg.h"
#include <Framework.h>
#include "StringTable.h"  
#include "DataTableMgr.h" 
#include <SpriteGO.h>
#include "SceneMgr.h" 
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include "EggAnimation.h"

SceneEasterEgg::SceneEasterEgg()
{
	resourceListPath = ("script/SceneGameResourceList.csv");
}

SceneEasterEgg::~SceneEasterEgg()
{
	Release();
}

void SceneEasterEgg::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	Scene::Enter();
}

void SceneEasterEgg::Reset()
{
	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void SceneEasterEgg::Exit()
{
	Scene::Exit();
}

void SceneEasterEgg::Init()
{
	Release();

	egg = (EggAnimation*)AddGo(new EggAnimation());

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneEasterEgg::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneEasterEgg::Update(float dt)
{
	Scene::Update(dt);
}

void SceneEasterEgg::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
