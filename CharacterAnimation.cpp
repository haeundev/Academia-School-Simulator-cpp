#include "stdafx.h"
#include "CharacterAnimation.h"
#include "Animation.h"

void CharacterAnimation::Init()
{
	auto animator = object->GetComponent<Animator>();

	Animation moveLR;
	moveLR.SetFrameCount(Vector2(1, 1));
	moveLR.SetRepeat(false);

	if (object->GetTag().substr(0, 7) == "Student")
	{
		moveLR.SetImage(Image::CreateImage("Characters/Students/" + object->GetName() + "_Left.png"));
	}
	else
	{
		moveLR.SetImage(Image::CreateImage("Characters/" + object->GetTag() + "/"
			+ object->GetName() + "_Left.png"));
	}
	moveLR.SetTime(0.07f);
	animator->AddAnimation("LRMove", moveLR);

	Animation moveUp;
	moveUp.SetFrameCount(Vector2(1, 1));
	moveUp.SetRepeat(false);
	if (object->GetTag().substr(0, 7) == "Student")
	{
		moveUp.SetImage(Image::CreateImage("Characters/Students/" + object->GetName() + "_Up.png"));
	}
	else
	{
		moveUp.SetImage(Image::CreateImage("Characters/" + object->GetTag() + "/"
			+ object->GetName() + "_Up.png"));
	}
	moveUp.SetTime(0.07f);
	animator->AddAnimation("UMove", moveUp);

	Animation moveDown;
	moveDown.SetFrameCount(Vector2(1, 1));
	moveDown.SetRepeat(false);
	if (object->GetTag().substr(0, 7) == "Student")
	{
		moveDown.SetImage(Image::CreateImage("Characters/Students/" + object->GetName() + "_Down.png"));
	}
	else
	{
		moveDown.SetImage(Image::CreateImage("Characters/" + object->GetTag() + "/"
			+ object->GetName() + "_Down.png"));
	}
	moveDown.SetTime(0.07f);
	animator->AddAnimation("DMove", moveDown);

	animator->AddParameter<int>("Move");

	auto leftRightToUp = animator->MakeTransition("LRMove", "UMove");
	leftRightToUp->SetCondition("Move", 3, ConditionType::Equal);

	auto UpToLeftRight = animator->MakeTransition("UMove", "LRMove");
	UpToLeftRight->SetCondition("Move", 0, ConditionType::Equal);

	auto leftRightToDown = animator->MakeTransition("LRMove", "DMove");
	leftRightToDown->SetCondition("Move", 1, ConditionType::Equal);

	auto downToLeftRight = animator->MakeTransition("DMove", "LRMove");
	downToLeftRight->SetCondition("Move", 0, ConditionType::Equal);

	auto upToDown = animator->MakeTransition("UMove", "DMove");
	upToDown->SetCondition("Move", 1, ConditionType::Equal);

	auto downToUp = animator->MakeTransition("DMove", "UMove");
	downToUp->SetCondition("Move", 3, ConditionType::Equal);
}