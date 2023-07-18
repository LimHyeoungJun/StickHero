#include "stdafx.h"
#include "PlayerTest.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
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
	animation.Play("None");
	sprite.setScale(3.f, 3.f);
	SetOrigin(origin); 
	SetPosition(-450, 300);
	//SpriteGo::Reset();
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
			animation.Play("Run");
			isrun = true;
		}
		if (isrun)
		{
			position.x += 500.f * dt;
		}
		if (isfulling && (animation.GetCurrentClipId() == "None")&& !playerArrival )
		{
			position.y += gravity * dt;
			isgo = false;
		}
		if (position.x >= oriPos.x + sticklength + 70.f && (animation.GetCurrentClipId() == "Run"))
		{
			animation.Play("None");
			position.x = oriPos.x + sticklength + 70.f;
			isrun = false;
			reset = true;
			isgo = true;
		}
		if (reset && (animation.GetCurrentClipId() == "None")&&!isfulling)
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
	sprite.setPosition(position);

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



