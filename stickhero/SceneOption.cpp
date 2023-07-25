#include "stdafx.h"
#include "SceneOption.h"
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
#include "Land.h"

SceneOption::SceneOption()
{
	resourceListPath = ("script/SceneGameResourceList.csv");
}

SceneOption::~SceneOption()
{
	Release();
}

void SceneOption::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
	Scene::Enter();
}

void SceneOption::Reset()
{
	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void SceneOption::Exit()
{
	Scene::Exit();
}

void SceneOption::Init()
{
	Release();

	SpriteGo* tex = (SpriteGo*)AddGo(new SpriteGo("graphics/charaterBg.png"));
	tex->SetOrigin(Origins::MC);

	UiButton* homeButton = (UiButton*)AddGo(new UiButton("graphics/HomeButton.png"));
	homeButton->SetOrigin(Origins::TL);
	homeButton->sortLayer = 100;
	homeButton->SetPosition(0.f, 0.f);
	homeButton->sprite.setScale(0.65f, 0.65f);

	SpriteGo* arrow = (SpriteGo*)AddGo(new SpriteGo("graphics/arrow.png"));
	arrow->SetName("Arrow");
	arrow->sortLayer = 100;
	arrow->SetOrigin(Origins::TC);
	arrow->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y * 0.5f+300.f);

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

	shape.setSize(sf::Vector2f(500.f, 20.f)); 
	shape.setOrigin(500.f * 0.5f, 20.f * 0.5f);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(FRAMEWORK.GetWindowSize().x*0.5f, FRAMEWORK.GetWindowSize().y * 0.5f+300.f);

	shapepoint.setSize(sf::Vector2f(20.f, 20.f));
	shapepoint.setOrigin(20.f * 0.5f, 20.f * 0.5f);
	shapepoint.setFillColor(sf::Color::Green);
	shapepoint.setPosition(FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y * 0.5f+300.f);

	shapevolBg = (Land*)AddGo(new Land());
	shapevolBg->SetSize(20.f, 500.f);
	shapevolBg->SetOrigin(Origins::BC);
	shapevolBg->SetFillColor(sf::Color(128, 128, 128));
	shapevolBg->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y * 0.5f +290.f);
	shapevolBg->sortLayer = 100;

	shapevol = (Land*)AddGo(new Land());
	//shapevol->SetSize(20.f, 250.f);
	shapevol->SetOrigin(Origins::BC);
	shapevol->SetFillColor(sf::Color::White);
	shapevol->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y * 0.5f + 290.f);
	shapevol->sortLayer = 120;

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneOption::Release()
{
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneOption::Update(float dt)
{

	SpriteGo* arrow = (SpriteGo*)FindGo("Arrow");

	sf::Vector2f pos = arrow->GetPosition();
	sf::FloatRect shapepos = shapepoint.getGlobalBounds();
	sf::FloatRect arrowpos = arrow->sprite.getGlobalBounds();
	if (first)
	{
		pos.x += dt * 700.f;
	}
	else
	{
		pos.x -= dt * 700.f;
	}
	if (pos.x > 890.f)
	{
		first = false;
	}
	if (pos.x < 390.f)
	{
		first = true;
	}
	
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		if (shapepos.intersects(arrowpos))
		{
			
			if (Variables::volume >= 100)
			{
				Variables::volume = 100;
			}
			else
			{
				Variables::volume += 5;
			}
		}
		else
		{
			std::cout << Variables::volume << std::endl;
			if (Variables::volume == 0)
			{
				Variables::volume = 0;
			}
			else
			{
				Variables::volume -= 5;
			}
		}
	}
	shapevol->SetSize(20.f, Variables::volume * 5.f); 
	shapevol->SetOrigin(Origins::BC);

	arrow->SetPosition(pos);

	Scene::Update(dt);
}

void SceneOption::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window); 
	window.draw(shape); 
	window.draw(shapepoint); 
}
