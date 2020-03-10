#pragma once
#include "GgaetIp.h"
#include "AStar.h"
#include "CharacterManager.h"

enum class JanitorState
{
	MOVING,
	CLEANING
};

class JanitorMove : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	JanitorState _janitorState = JanitorState::MOVING;

	AStar* _star;
	vector<Object*>* _vTiles;
	Animator* _animator;
	float _characterAngle;

	vector<Vector2> _vRoute;

	Vector2 _characterNowIndex;
	Vector2 _characterNowPos;
	Vector2 _startIndex;
	Vector2 _nextIndex;

	int _nowArrayNum;

	bool _havePath = false;
	bool _havePathToLounge = false;
	int _cleanDoneCount = 0;

	CharacterManager* _characterManager;

	Object* _hands;

	bool _handsMoveRight = true;
	float _handsPosX = 0;

public:
	virtual void Init() override;
	virtual void Update() override;

	void SetVTilesLink(vector<Object*>* v) { _vTiles = v; }

	void Move();
	void SetDirection();
};