#include "stdafx.h"
#include "JanitorMove.h"
#include "CharacterIndex.h"
#include "CharacterManager.h"
#include <time.h>

void JanitorMove::Init()
{
	_star = new AStar();
	_star->Init();
	_star->SetAllowDiagonalMove(true);
	_star->SetVTilesLink(*_vTiles);

	_transform = object->GetTransform();

	_animator = object->GetComponent<Animator>();

	_characterNowIndex = object->GetComponent<CharacterIndex>()->GetIndex();
	_characterNowPos = Vector2(GRID_STARTPOINT.x + GridWidth * _characterNowIndex.x, GRID_STARTPOINT.y - GridHeight * _characterNowIndex.y);

	_characterManager = SceneManager::GetInstance()->GetNowScene()->GetChildByName("CharacterManager")->GetComponent<CharacterManager>();

	SetDirection();

	Animation janitorHands;
	janitorHands.SetFrameCount(Vector2(1, 1));
	janitorHands.SetRepeat(true);
	janitorHands.SetImage(Image::CreateImage("Characters/JanitorHands.png"));
	janitorHands.SetTime(0.03f);
	_hands = Object::CreateObject(object);
	_hands->AddComponent<Sprite>();
	_hands->AddComponent<Animator>();
	_hands->GetComponent<Animator>()->AddAnimation("JanitorHands", janitorHands);
	_hands->SetIsActive(false);

	srand(time(NULL));
}

void JanitorMove::Update()
{
	if (_hands->GetTransform()->GetPosition().x < 0)
		_handsMoveRight = true;
	else if (_hands->GetTransform()->GetPosition().x > 50)
		_handsMoveRight = false;

	if (_handsMoveRight)
		_handsPosX += 2.f;
	else
		_handsPosX -= 2.f;

	_hands->GetTransform()->SetPosition(Vector2(_handsPosX, -20));
	

	if (_janitorState == JanitorState::MOVING && !_havePath)
	{
		_nowArrayNum = 0;
		_startIndex = _characterNowIndex;
		_vRoute = _star->GetPath(Vector2(_startIndex), Vector2(rand() % 50, rand() % 50));
		_havePath = true;
		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();

		_hands->SetIsActive(false);
	}
	if (_janitorState == JanitorState::CLEANING && !_havePath)
	{
		_hands->SetIsActive(true);
		
		_cleanDoneCount++;

		if (_cleanDoneCount > 300)
		{
			_cleanDoneCount = 0;

			_janitorState = JanitorState::MOVING;
		}
	}

	Move();
}

void JanitorMove::Move()
{
	// 가야할 곳이 없으면 return
	if (!_vRoute.size()) return;

	// 캐릭터 인덱스와 위치
	_characterNowIndex = object->GetComponent<CharacterIndex>()->GetIndex();
	_characterNowPos = object->GetTransform()->GetPosition();

	float angle = (Vector2::GetAngle(_characterNowPos, Vector2(GRID_STARTPOINT.x + GridWidth * _nextIndex.x, GRID_STARTPOINT.y - GridHeight * _nextIndex.y)));
	float distance = Vector2::GetDistance(_characterNowPos, Vector2(GRID_STARTPOINT.x + GridWidth * _nextIndex.x, GRID_STARTPOINT.y - GridHeight * _nextIndex.y));

	_transform->SetPosition(Vector2(_transform->GetPosition().x - cosf(angle) * CharacterMoveSpeed, _transform->GetPosition().y + sinf(angle) * CharacterMoveSpeed));

	if (distance < 30)
	{
		if (_nowArrayNum > _vRoute.size() - 1)
		{
			_vRoute.clear();
			_havePath = false;

			if (_janitorState == JanitorState::MOVING)
			{
				_janitorState = JanitorState::CLEANING;
			}

			_animator->SetParameter("Move", 1);
		}
		else
		{
			_nextIndex = _vRoute[_nowArrayNum++];

			SetDirection();
		}
	}
}

void JanitorMove::SetDirection()
{
	if (!_vRoute.size()) return;

	int paramNum = 1;

	if (_nextIndex.x == _characterNowIndex.x && _nextIndex.y < _characterNowIndex.y)
	{
		paramNum = 3;
	}
	else if (_nextIndex.x == _characterNowIndex.x && _nextIndex.y > _characterNowIndex.y)
	{
		paramNum = 1;
	}
	else if (_nextIndex.x > _characterNowIndex.x)
	{
		paramNum = 0;
		object->GetComponent<Sprite>()->SetFlip(true);
	}
	else if (_nextIndex.x < _characterNowIndex.x)
	{
		paramNum = 0;
		object->GetComponent<Sprite>()->SetFlip(false);
	}

	_animator->SetParameter("Move", paramNum);
}