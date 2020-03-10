#pragma once
#include <string>
#include <map>

class AnimatorComponent;

using namespace std;

enum class ConditionType
{
	Equal,
	NotEqual,
	Less,
	Greater
};

class AnimationTransition
{
private:
	Animator* animator;

	string start;
	string end;
	
	string key;
	float condition;

	ConditionType type;
	string dataType;
public:
	AnimationTransition(Animator* animator,string start,string end);
	template<typename T>
	void SetCondition(string key, T condition);
	template<typename T>
	void SetCondition(string key, T condition,ConditionType type);

	bool GetAnimation();
	string GetStartAnimation() { return start; };
	string GetEndAnimation() { return end; };
};
#include "AnimationTransition.hpp"