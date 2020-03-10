#include "stdafx.h"
#include "GgaetIp.h"

AnimationTransition::AnimationTransition(Animator* animator, string start, string end)
{
	this->start = start;
	this->end = end;
	this->animator = animator;
}

bool AnimationTransition::GetAnimation()
{
	if (dataType == "int")
	{
		map<string, int> data = animator->GetIntAllData();

		switch (type)
		{
		case ConditionType::Equal:
			return data[key] == (int)condition;
		case ConditionType::Greater:
			return data[key] > (int)condition;
		case ConditionType::Less:
			return data[key] < (int)condition;
		case ConditionType::NotEqual:
			return data[key] != (int)condition;
		}
	}
	else if (dataType == "float")
	{
		map<string, float> data = animator->GetFloatAllData();

		switch (type)
		{
		case ConditionType::Equal:
			return data[key] == condition;
		case ConditionType::Greater:
			return data[key] > condition;
		case ConditionType::Less:
			return data[key] < condition;
		case ConditionType::NotEqual:
			return data[key] != condition;
		}
	}
	else if (dataType == "bool")
	{
		map<string, bool> data = animator->GetBoolAllData();

		switch (type)
		{
		case ConditionType::Equal:
			return data[key] == (bool)condition;
		case ConditionType::Greater:
			return data[key] > (bool)condition;
		case ConditionType::Less:
			return data[key] < (bool)condition;
		case ConditionType::NotEqual:
			return data[key] != (bool)condition;
		}
	}
}