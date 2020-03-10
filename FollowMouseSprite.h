#pragma once
#include "GgaetIp.h"
#include <stack>

class FollowMouseSprite : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	stack<string> _sStoreImgKey;

	Vector2 _currentIndex;

public:
	virtual void Init() override;
	virtual void Update() override;

	stack<string>& GetSStoreImgKey() { return _sStoreImgKey; }
	Vector2 GetSpriteFrameSize() { return _sprite->GetFrameSize(); }
};