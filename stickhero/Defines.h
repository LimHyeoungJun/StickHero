#pragma once

#define _USE_MATH_DEFINES

enum class Languages
{
	KOR,
	ENG,
	JP,
	COUNT,
};

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
	AimationClip,
};

enum class SceneId
{
	None = -1,
	Title,
	Game,
	Choose,
	Count,
};

enum class ShapeType
{
	None,
	Rectangle,
};

enum class PlayerType
{
	None,
	P1,
	P2,
	P3,
};

#include "AnimationClip.h"