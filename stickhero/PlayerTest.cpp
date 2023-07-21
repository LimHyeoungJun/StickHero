#include "stdafx.h"
#include "PlayerTest.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "SceneChooseCharacter.h"

PlayerTest::PlayerTest(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n)
{
	
}

void PlayerTest::Init()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player2_Ani_idle.csv")); 
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player2_Ani_attack.csv"));  
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player2_Ani_run.csv"));  

	animation.SetTarget(&sprite);  

	SetOrigin(Origins::BC);  
}

void PlayerTest::Reset()
{
	switch (Variables::playerty)
	{
	case PlayerType::P1:
	{
		animation.DeleteClip();
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player2_Ani_idle.csv")); 
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player2_Ani_attack.csv")); 
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player2_Ani_run.csv")); 
		animation.SetTarget(&sprite); 
		SetOrigin(Origins::BC); 
		SetPosition(-430, 286);
		Ypos = 286.f;
		break;
	}
	case PlayerType::P2:
	{
		animation.DeleteClip();
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player2_idle.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player2_attack.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player2_move.csv"));
		animation.SetTarget(&sprite);
		SetOrigin(Origins::BC);
		SetPosition(-450, 260);
		Ypos = 260.f;
		break;
	}
	case PlayerType::P3:
	{
		animation.DeleteClip();
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player3_idle.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player3_attack.csv"));
		animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player3_move.csv"));
		animation.SetTarget(&sprite); 
		SetOrigin(Origins::BC); 
		SetPosition(-450, 260);
		Ypos = 260.f;


		break;
	}
	}

	animation.Play("Idle");
	sprite.setScale(2.f, 2.f);
	SetOrigin(origin); 
	SetPosition(-450, Ypos);
	
	oriPos = GetPosition(); 

}

void PlayerTest::Update(float dt)
{
	if (!isdie)
	{
		if (INPUT_MGR.GetKeyUp(sf::Keyboard::Space))
		{
			animation.Play("Attack");
		}

		if ((animation.GetCurrentClipId() == "Attack") && animationStart)
		{
			animation.Play("Move");
			isrun = true;
		}
		if (isrun)
		{
			position.x += 700.f * dt;
		}
		if (isfulling && (animation.GetCurrentClipId() == "Idle")&& !playerArrival )
		{
			position.y += gravity * dt;
			isgo = false;
		}
		if (position.x >= oriPos.x + sticklength + 70.f && (animation.GetCurrentClipId() == "Move"))
		{
			animation.Play("Idle");
			position.x = oriPos.x + sticklength + 70.f;
			isrun = false;
			reset = true;
			isgo = true;
		}
		if (reset && (animation.GetCurrentClipId() == "Idle")&&!isfulling)
		{
			if (position.x <= oriPos.x)
			{
				position.x = -450;
				isgo = false;
			}
			else
			{
				position.x -= 700.f * dt;
			}
		}
	}	
	//sprite.setPosition(position);
	
	SetPosition(position); 
	SpriteGo::Update(dt);
	animation.Update(dt);
}

void PlayerTest::SetRun(bool n)
{
	animationStart = n;
}

void PlayerTest::SetStartAnimation(bool n)
{

}

void PlayerTest::Setdistance(float d)
{
	sticklength = d;
}

void PlayerTest::PlayerDie(bool n)
{
	isfulling = n;
}

void PlayerTest::PlayerArrival(bool p)
{
	playerArrival = p;
}

sf::Vector2f PlayerTest::Scales()  
{
	return { 0.f,0.f };
}



