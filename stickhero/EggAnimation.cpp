#include "stdafx.h"
#include "EggAnimation.h"
#include "ResourceMgr.h"

EggAnimation::EggAnimation(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId,n)
{
}

void EggAnimation::Init()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/EasterEgg.csv"));
	animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);
}

void EggAnimation::Reset()
{
	animation.Play("Start");
	std::cout << "animation start" << std::endl;
	sprite.setScale(3.f, 3.f);
	SetOrigin(origin);
}

void EggAnimation::Update(float dt)
{
	//animation.Play("Start");
	SpriteGo::Update(dt); 
	animation.Update(dt); 
}
