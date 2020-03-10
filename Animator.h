#pragma once
#include <map>
#include <list>
#include <string>
#include "Component.h"

using namespace std;

class AnimationTransition;
class Animation;
class Sprite;

class Animator : public Component
{
private:
	Sprite* renderer;

	map<string, bool> boolData;
	map<string, int> intData;
	map<string, float> floatData;
	map<string, Animation> animations;
	multimap<string, AnimationTransition*> transitions;

	string nowAnimation;
	int nowIndex = 0;
	int updateCount = 0;
public:
	template<typename T>
	void AddParameter(string key);

	template<typename T>
	void SetParameter(string key, T data);

	template<typename T>
	T GetData(string key);

	map<string, int> GetIntAllData();
	map<string, float> GetFloatAllData();
	map<string, bool> GetBoolAllData();

	void SetSpriteComponent(Sprite* spriteComponent) { renderer = spriteComponent; };
	Sprite* GetSpriteComponent() { return renderer; };

	void AddAnimation(string name,Animation animation);

	AnimationTransition* MakeTransition(string start, string end);

	virtual void Update() override;
	virtual void Init() override;
};
#include "Animator.hpp"
