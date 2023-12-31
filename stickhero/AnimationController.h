#pragma once


class AnimationController
{
private:

protected:
	std::unordered_map<std::string, AnimationClip*> clips;
	std::queue<std::string> queue;
	float speed = 1.f; // aniation 동작시킬 속도
	bool isPlaying = false;

	AnimationClip* currentClip = nullptr;
	int currentFrame =-1; // 몇번째 clip인지 확인
	int totalFrame = 0;
	float clipDuration = 0.f;
	float accumTime = 0.f;

	sf::Sprite* target = nullptr; // img 가질예정
	

public:


	void AddClip(AnimationClip& newClip);
	void DeleteClip();
	void SetTarget(sf::Sprite* sprite) { target = sprite; };
	sf::Sprite* GetTarget()const { return target; };
	bool IsPlaying() { return isPlaying; };
	void SetSpeed(float s) { speed = s; };
	float Speed()const { return speed; };

	void Update(float dt);

	void Play(const std::string& clipid, bool clearQueue = true);
	void PlayQueue(const std::string& clipid); // play한것을 담아둘려고하는것

	void Stop(); //

	void SetFrame(const AnimationFrame& frame);

	std::queue<std::string> GetQueue()const;
	std::string GetCurrentClipId()const;
};

