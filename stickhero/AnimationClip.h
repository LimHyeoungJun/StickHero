#pragma once
#include "stdafx.h"

enum class AnimationLoopTypes
{
	Single,  // 한번 동작
	Loop,   // 계속 동작 시키기
};
struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;  
	std::function<void()> action;
};

struct AnimationClip 
{
	std::string id;
	AnimationLoopTypes loopType;
	int fps;

	std::vector<AnimationFrame> frames;
	bool LoadFromFile(const std::string path);
};