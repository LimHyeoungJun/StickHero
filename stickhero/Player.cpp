#include "stdafx.h"
#include "Player.h" 
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "SceneChooseCharacter.h"

Player::Player(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n)
{
	walk.loadFromFile("sound/walking.wav"); 
	soundwalk.setBuffer(walk); 
	

	falling.loadFromFile("sound/falling.wav");
	soundfalling.setBuffer(falling);
	
}

void Player::Init()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player2_Ani_idle.csv")); 
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player2_Ani_attack.csv"));  
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player2_Ani_run.csv"));  

	animation.SetTarget(&sprite);  

	SetOrigin(Origins::BC);  
}

void Player::Reset()
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
	soundfalling.stop();
}

void Player::Update(float dt)
{
	soundwalk.setVolume(Variables::volume);
	soundfalling.setVolume(Variables::volume);

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
			soundwalk.play();
			soundwalk.setLoop(true);   
			
		}
		if (isrun)
		{
			position.x += 700.f * dt;
		}
		if (isfulling && (animation.GetCurrentClipId() == "Idle")&& !playerArrival )
		{
			position.y += gravity * dt;
			isgo = false;
			if (sound)
			{
				sound = false;
				soundfalling.play();
			}
			
		}
		if (position.x >= oriPos.x + sticklength + 70.f && (animation.GetCurrentClipId() == "Move"))
		{
			animation.Play("Idle");
			position.x = oriPos.x + sticklength + 70.f;
			isrun = false;
			reset = true;
			isgo = true;
			soundwalk.stop();
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
				position.x -= 1000.f * dt;
			}

			sound = true; 
			
		}
	}	
	
	SetPosition(position); 
	SpriteGo::Update(dt);
	animation.Update(dt);
}

void Player::SetRun(bool n)
{
	animationStart = n;
}

void Player::SetStartAnimation(bool n)
{

}

void Player::Setdistance(float d)
{
	sticklength = d;
}

void Player::PlayerDie(bool n)
{
	isfulling = n;
}

void Player::PlayerArrival(bool p)
{
	playerArrival = p;
}

sf::Vector2f Player::Scales()  
{
	return { 0.f,0.f };
}



