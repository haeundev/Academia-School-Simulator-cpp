#include "stdafx.h"
#include "WorkerMove.h"
#include "MapTool.h"
#include "CharacterIndex.h"
#include "CharacterManager.h"
#include <time.h>

void WorkerMove::Init()
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

	if (stoi(object->GetName()) < 6)
		_loungePosition = Vector2(stoi(object->GetName()) + 30, 29);
	else
		_loungePosition = Vector2(stoi(object->GetName()) % 6 + 30, 31);

	Animation workerHands;
	workerHands.SetFrameCount(Vector2(14, 1));
	workerHands.SetRepeat(true);
	workerHands.SetImage(Image::CreateImage("Characters/WorkerHands.png"));
	workerHands.SetTime(0.03f);
	_hands = Object::CreateObject(object);
	_hands->AddComponent<Sprite>();
	_hands->AddComponent<Animator>();
	_hands->GetComponent<Animator>()->AddAnimation("WorkerHands", workerHands);
	_hands->SetIsActive(false);

	_activity = Object::CreateObject(object);

	int rnd = stoi(object->GetName()) % 5;

	if (rnd % 5 == 0)
	{
		_activity->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Activity/ItemCoffeeMug.png"));
		_activity->GetTransform()->SetPosition(Vector2(-20, -20));
	}
	else if (rnd % 5 == 1)
	{
		_activity->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Activity/ItemNewspaper.png"));
		_activity->GetTransform()->SetPosition(Vector2(0, -20));
	}
	else if (rnd % 5 == 2)
	{
		_activity->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Activity/ItemGranolaBar.png"));
		_activity->GetTransform()->SetPosition(Vector2(15, -20));
	}
	else if (rnd % 5 == 3)
	{
		_activity->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Activity/ItemHeadphones.png"));
		_activity->GetTransform()->SetPosition(Vector2(0, 30));
	}
	else if (rnd % 5 == 4)
	{
		_activity->AddComponent<Sprite>()->SetSprite(ImageManager::GetInstance()->AddImage("Activity/ItemCoffeeMug.png"));
		_activity->GetTransform()->SetPosition(Vector2(-20, -20));
	}
	
	_activity->SetIsActive(false);


	srand(time(NULL));
}

void WorkerMove::Update()
{
	Move();

	if (_workerState == WorkerState::AT_LOUNGE)
		_activity->SetIsActive(true);
	else 
		_activity->SetIsActive(false);

	object->GetComponent<Sprite>()->SetDepth((int)ZORDER::CHARACTER + _characterNowIndex.y);

	if (_workerState == WorkerState::AT_LOUNGE)
	{
		_hands->SetIsActive(false);

		IdleMove();

		_idleCount++;

		if (_idleCount > 150)
		{
			_haveIdlePath = false;

			_idleCount = 0;
		}

		if (!_mapTool->GetMWorkLoad()[object->GetName()].size()) return;
		if (_mapTool->GetMWorkLoad()[object->GetName()].front().isDummy) return;

		_workerState = WorkerState::GOING;
	}
	else if (_workerState == WorkerState::GOING && !_havePath)
	{
		_hands->SetIsActive(false);
		
		if (!_mapTool->GetMWorkLoad()[object->GetName()].size()) return;

		_nowArrayNum = 0;
		_startIndex = _characterNowIndex;
		_vRoute = _star->GetPath(/*시작점 Index*/ Vector2(_startIndex), /*도착점 Index*/ _mapTool->GetMWorkLoad()[object->GetName()].front().workAreaIndex);
		_havePath = true;
		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();
	}
	else if (_workerState == WorkerState::UNDER_CONSTRUCTION)
	{
		_hands->SetIsActive(true);

		_workDoneCount++;

		if (_workDoneCount < 50) return;
		if (_mapTool->GetMWorkLoad()[object->GetName()].size())
		{
			_workerState = WorkerState::GOING;

			_workDoneCount = 0;
		}
		else
		{
			_workerState = WorkerState::RETURNING;

			_workDoneCount = 0;
		}
	}
	else if (_workerState == WorkerState::RETURNING && !_havePath)
	{
		_hands->SetIsActive(false);
		
		_workDoneCount = 0;

		if (_characterNowIndex == _loungePosition)
		{
			_workerState = WorkerState::AT_LOUNGE;
		}

		_nowArrayNum = 0;
		_startIndex = _characterNowIndex;
		_vRoute = _star->GetPath(/*시작점 Index*/ Vector2(_startIndex), /*도착점 Index*/ _loungePosition);
		_havePath = true;
		if (_vRoute.size())
		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();
	}

}

void WorkerMove::Move()
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

			if (_mapTool->GetMWorkLoad()[object->GetName()].size())
			{
				_mapTool->GetMWorkLoad()[object->GetName()].front().object->GetComponent<Sprite>()->SetOpacity(1);
				_mapTool->GetMWorkLoad()[object->GetName()].pop();
			}

			if (_workerState == WorkerState::GOING)
			{
				_workerState = WorkerState::UNDER_CONSTRUCTION;
			}
			else if (_workerState == WorkerState::RETURNING)
			{
				_workerState = WorkerState::AT_LOUNGE;
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

void WorkerMove::IdleMove()
{
	if (_workerState != WorkerState::AT_LOUNGE) return;
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

void WorkerMove::SetDirection()
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