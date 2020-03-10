#include "stdafx.h"
#include "GgaetIp.h"

void Animator::AddAnimation(string name,Animation animation)
{
	if (!animations.size())
	{
		renderer = object->GetComponent<Sprite>();
		nowAnimation = name;
		renderer->SetSprite(animation.GetImage());
		renderer->SetFrameSize(animation.GetFrameSize());
		renderer->SetStartPoint(Vector2::zero);
	}
	animations.insert(make_pair(name, animation));
}

void Animator::Update()
{
	if (!animations.size())
		return;
	Animation animation = animations[nowAnimation];
	float TimeManager = animation.GetTimeManager();
	Vector2 frameCount = animation.GetFrameCount();
	Vector2 frameSize = animation.GetFrameSize();
	Vector2 startPoint;
	string now = nowAnimation;
	startPoint.x = frameSize.x * (nowIndex % (int)frameCount.x);
	startPoint.y = 0;
	nowIndex = updateCount / (FrameRate * TimeManager);
	renderer->SetStartPoint(startPoint);

	if (animation.GetRepeat())
		updateCount = (updateCount + 1) % (int)(FrameRate * TimeManager * frameCount.x*frameCount.y);
	else
		updateCount = (updateCount + 1) >= (FrameRate * TimeManager * frameCount.x*frameCount.y) ? updateCount : updateCount+1;

	for (auto itr = transitions.lower_bound(now); itr != transitions.upper_bound(now); itr++)
	{
		if (!itr->second->GetAnimation())
			continue;

		nowAnimation = itr->second->GetEndAnimation();
		renderer->SetSprite(animations[nowAnimation].GetImage());
		renderer->SetFrameSize(animations[nowAnimation].GetFrameSize());
		renderer->SetStartPoint(Vector2::zero);
		nowIndex = 0;
		updateCount = 0;
	}
}

void Animator::Init()
{
	renderer = object->GetComponent<Sprite>();
}

AnimationTransition* Animator::MakeTransition(string start, string end)
{
	AnimationTransition* transition = new AnimationTransition(this, start, end);
	transitions.insert(make_pair(start, transition));
	return transition;
}

map<string, int> Animator::GetIntAllData()
{
	return intData;
}

map<string, float> Animator::GetFloatAllData()
{
	return floatData;
}

map<string, bool> Animator::GetBoolAllData()
{
	return boolData;
}