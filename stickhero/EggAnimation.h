#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class EggAnimation : public SpriteGo
{
public:

	AnimationController animation; 

	EggAnimation(const std::string& textureId = "", const std::string& n = "");
	virtual ~EggAnimation() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
};

