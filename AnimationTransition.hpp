#pragma once
template<typename T>
void AnimationTransition::SetCondition(string key, T condition)
{
	this->key = key;
	this->condition = condition;
	type = ConditionType::Equal;
	dataType = typeid(T).name();
}

template<typename T>
void AnimationTransition::SetCondition(string key, T condition, ConditionType type)
{
	this->key = key;
	this->condition = condition;
	this->type = type;
	dataType = typeid(T).name();
}