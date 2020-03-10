#include "stdafx.h"
#include "PrincipalMove.h"
#include "CharacterIndex.h"
#include <time.h>

void PrincipalMove::Init()
{
	_star = new AStar();
	_star->Init();
	_star->SetAllowDiagonalMove(true);
	_star->SetVTilesLink(*_vTiles);

	_transform = object->GetTransform();

	_animator = object->GetComponent<Animator>();

	_characterNowIndex = object->GetComponent<CharacterIndex>()->GetIndex();
	_characterNowPos = Vector2(GRID_STARTPOINT.x + GridWidth * _characterNowIndex.x, GRID_STARTPOINT.y - GridHeight * _characterNowIndex.y);

	SetDirection();

	srand(time(NULL));
}

void PrincipalMove::Update()
{
	Move();

	if (_principalState == PrincipalState::WORKING)
	{
		IdleMove();

		_idleCount++;

		if (_idleCount > 150)
		{
			_haveIdlePath = false;

			_idleCount = 0;
		}
	}

	object->GetComponent<Sprite>()->SetDepth((int)ZORDER::CHARACTER + _characterNowIndex.y);
}

void PrincipalMove::OnNotify(MTYPE type, string event)
{
	_nowArrayNum = 0;

	if (type != MTYPE::TIME) return;

	if (event == "Homeroom_StaffIn")
	{
		_principalState = PrincipalState::TO_DESTINATION;

		_startIndex = _characterNowIndex;
		_vRoute = _star->GetPath(Vector2(_characterNowIndex), Vector2(14, 30));
		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();
	}

	if (event == "Dismissal_AllOut")
	{
		_principalState = PrincipalState::TO_DESTINATION;

		_startIndex = _characterNowIndex;
		_vRoute = _star->GetPath(Vector2(_characterNowIndex), Vector2(49, 49));
		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();
	}
}

void PrincipalMove::Move()
{
	// ������ ���� ������ return
	if (!_vRoute.size()) return;

	// ĳ���� �ε����� ��ġ
	_characterNowIndex = object->GetComponent<CharacterIndex>()->GetIndex();
	_characterNowPos = object->GetTransform()->GetPosition();

	float angle = (Vector2::GetAngle(_characterNowPos, Vector2(GRID_STARTPOINT.x + GridWidth * _nextIndex.x, GRID_STARTPOINT.y - GridHeight * _nextIndex.y)));

	float distance = Vector2::GetDistance(_characterNowPos, Vector2(GRID_STARTPOINT.x + GridWidth * _nextIndex.x, GRID_STARTPOINT.y - GridHeight * _nextIndex.y));

	_transform->SetPosition(Vector2(_transform->GetPosition().x - cosf(angle) * CharacterMoveSpeed, _transform->GetPosition().y + sinf(angle) * CharacterMoveSpeed));

	if (distance < 10)
	{
		if (_nowArrayNum >= _vRoute.size() - 1)
		{
			_principalState = PrincipalState::WORKING;

			_vRoute.clear();

			_animator->SetParameter("Move", 1);

			return;
		}
		else
		{
			_nextIndex = _vRoute[_nowArrayNum++];

			SetDirection();
		}
	}
}

void PrincipalMove::IdleMove()
{
	if (_principalState != PrincipalState::WORKING) return;
	if (_haveIdlePath) return;
	if (_vRoute.size()) return;

	while (true)
	{
		int rndX = rand() % 2;
		int rndY = rand() % 2;
		int plmnX = rand() % 2;
		int plmnY = rand() % 2;
		if (plmnX == 0) rndX = -rndX;
		if (plmnY == 0) rndY = -rndY;

		_nowArrayNum = 0;
		_startIndex = _characterNowIndex;

		if (_startIndex.x + rndX > 49 || _startIndex.x + rndX < 0
			|| _startIndex.y + rndY > 49 || _startIndex.y + rndY < 0)
			continue;

		_vRoute = _star->GetPath(Vector2(_startIndex), Vector2(_startIndex.x + rndX, _startIndex.y + rndY));
		_haveIdlePath = true;

		if (!_vRoute.size())
			return;

		_nextIndex = _vRoute[_nowArrayNum];

		if (rndX != 0 && rndY != 0)
			break;
	}

	SetDirection();
}

void PrincipalMove::SetDirection()
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
