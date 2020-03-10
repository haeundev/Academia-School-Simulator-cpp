#include "stdafx.h"
#include "StudentMove.h"
#include "CharacterIndex.h"
#include "Schedule.h"
#include "ScheduleWindow.h"
#include <time.h>

void StudentMove::Init()
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

	_studentID = stoi(object->GetTag().substr(7));
	
	srand(time(NULL));

	_thoughts = Object::CreateObject(object);
	_thoughtsSprite = _thoughts->AddComponent<Sprite>();
	_thoughtsSprite->SetOpacity(0.72f);
	_thoughtsSprite->GetTransform()->SetScale(Vector2(0.65f, 0.65f));
	_thoughts->GetTransform()->SetPosition(Vector2(0, 75));
	_thoughts->SetIsActive(false);
}

void StudentMove::Update()
{
	Move();

	if (_studentState == StudentState::IDLE)
	{
		IdleMove();

		_idleCount++;
		_thoughtsCount++;

		if (_idleCount > 100)
		{
			_haveIdlePath = false;

			_idleCount = 0;
		}

		if (_thoughtsCount > 70)
		{
			_thoughts->SetIsActive(!_thoughts->GetIsActive());
			_thoughtsCount = 0;
		}
	}
	else if (_studentState == StudentState::TO_DESTINATION)
	{
		_thoughts->SetIsActive(false);
	}

	object->GetComponent<Sprite>()->SetDepth((int)ZORDER::CHARACTER + _characterNowIndex.y);
}

void StudentMove::OnNotify(MTYPE type, string event)
{
	_nowArrayNum = 0;

	if (type != MTYPE::TIME) return;

	_studentState = StudentState::TO_DESTINATION;

#pragma region 시간에 따른 이동
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 7시
	if (event == "Homeroom_StudentsIn")
	{
		_startIndex = _characterNowIndex;

		if (_studentID % 10 == 0)
			_vRoute = _star->GetPath(Vector2(49, 49), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[2][0]);
		if (_studentID % 10 == 1)
			_vRoute = _star->GetPath(Vector2(47, 49), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[2][1]);
		if (_studentID % 10 == 2)
			_vRoute = _star->GetPath(Vector2(49, 47), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[2][0]);
		if (_studentID % 10 == 3)
			_vRoute = _star->GetPath(Vector2(45, 49), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[2][1]);
		if (_studentID % 10 == 4)
			_vRoute = _star->GetPath(Vector2(49, 45), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[2][0]);
		if (_studentID % 10 == 5)
			_vRoute = _star->GetPath(Vector2(43, 49), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[2][1]);
		if (_studentID % 10 == 6)
			_vRoute = _star->GetPath(Vector2(49, 43), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[2][0]);
		if (_studentID % 10 == 7)
			_vRoute = _star->GetPath(Vector2(41, 49), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[2][1]);
		if (_studentID % 10 == 8)
			_vRoute = _star->GetPath(Vector2(49, 41), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[2][0]);
		if (_studentID % 10 == 9)
			_vRoute = _star->GetPath(Vector2(37, 49), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[2][1]);

		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();

		if (rand() % 6 == 0)	_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Crush.png"));
		if (rand() % 6 == 1)	_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Drowsy.png"));
		if (rand() % 6 == 2)	_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Energy.png"));
		if (rand() % 6 == 3)	_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Wooing.png"));
		if (rand() % 6 == 4)	_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/TV.png"));
		if (rand() % 6 == 5)	_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Robot.png"));
	}

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 8시
	if (event == "FirstPeriod")
	{
		_startIndex = _characterNowIndex;

		if (_studentID % 2 == 0)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[0][0]);
		if (_studentID % 2 == 1)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[0][1]);

		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();

		_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Student_" + _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()
			->GetVOrder()[0]->GetName() + ".png"));
	}

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 9시
	if (event == "SecondPeriod")
	{
		_startIndex = _characterNowIndex;

		if (_studentID % 2 == 0)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[1][0]);
		if (_studentID % 2 == 1)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[1][1]);

		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();

		_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Student_" + _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()
			->GetVOrder()[1]->GetName() + ".png"));
	}

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 10시
	if (event == "ThirdPeriod")
	{
		_startIndex = _characterNowIndex;

		if (_studentID % 2 == 0)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[2][0]);
		if (_studentID % 2 == 1)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[2][1]);

		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();

		_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Student_" + _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()
			->GetVOrder()[2]->GetName() + ".png"));
	}

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 11시
	if (event == "FourthPeriod")
	{
		_startIndex = _characterNowIndex;

		if (_studentID % 2 == 0)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[3][0]);
		if (_studentID % 2 == 1)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[3][1]);

		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();

		_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Student_" + _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()
			->GetVOrder()[3]->GetName() + ".png"));
	}

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 12시
	if (event == "FifthPeriod")
	{
		_startIndex = _characterNowIndex;

		if (_studentID % 2 == 0)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[4][0]);
		if (_studentID % 2 == 1)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[4][1]);

		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();

		_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Student_" + _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()
			->GetVOrder()[4]->GetName() + ".png"));
	}

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 1시
	if (event == "SixthPeriod")
	{
		_startIndex = _characterNowIndex;

		if (_studentID % 2 == 0)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[5][0]);
		if (_studentID % 2 == 1)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[5][1]);

		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();

		_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Student_" + _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()
			->GetVOrder()[5]->GetName() + ".png"));
	}

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 2시
	if (event == "SeventhPeriod")
	{
		_startIndex = _characterNowIndex;

		if (_studentID % 2 == 0)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[6][0]);
		if (_studentID % 2 == 1)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[6][1]);

		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();

		_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Student_" + _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()
			->GetVOrder()[6]->GetName() + ".png"));
	}

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 3시
	if (event == "EighthPeriod")
	{
		_startIndex = _characterNowIndex;

		if (_studentID % 2 == 0)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[7][0]);
		if (_studentID % 2 == 1)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[7][1]);

		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();

		_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Student_" + _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()
			->GetVOrder()[7]->GetName() + ".png"));
	}

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 4시
	if (event == "Dismissal_AllOut")
	{
		_startIndex = _characterNowIndex;

		if (_studentID % 2 == 0)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[8][0]);
		if (_studentID % 2 == 1)
			_vRoute = _star->GetPath(Vector2(_characterNowIndex), _schedule->GetScheduleWindow()->GetComponent<ScheduleWindow>()->GetVPosPerPeriodStudent()[8][1]);

		_nextIndex = _vRoute[_nowArrayNum];
		SetDirection();

		if (rand() % 6 == 0)	_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Crush.png"));
		if (rand() % 6 == 1)	_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Drowsy.png"));
		if (rand() % 6 == 2)	_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Energy.png"));
		if (rand() % 6 == 3)	_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Wooing.png"));
		if (rand() % 6 == 4)	_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/TV.png"));
		if (rand() % 6 == 5)	_thoughtsSprite->SetSprite(ImageManager::GetInstance()->AddImage("Thoughts/Robot.png"));
	}

#pragma endregion

}

void StudentMove::Move()
{
	// 가야할 곳이 없으면 return
	if (!_vRoute.size()) return;

	// 캐릭터 인덱스와 위치
	_characterNowIndex = object->GetComponent<CharacterIndex>()->GetIndex();
	_characterNowPos = object->GetTransform()->GetPosition();

	float angle = (Vector2::GetAngle(_characterNowPos, Vector2(GRID_STARTPOINT.x + GridWidth * _nextIndex.x, GRID_STARTPOINT.y - GridHeight * _nextIndex.y)));
	float distance = Vector2::GetDistance(_characterNowPos, Vector2(GRID_STARTPOINT.x + GridWidth * _nextIndex.x, GRID_STARTPOINT.y - GridHeight * _nextIndex.y));

	_transform->SetPosition(Vector2(_transform->GetPosition().x - cosf(angle) * CharacterMoveSpeed, _transform->GetPosition().y + sinf(angle) * CharacterMoveSpeed));

	if (distance < 10)
	{
		if (_nowArrayNum >= _vRoute.size() - 1)
		{
			_vRoute.clear();

			_studentState = StudentState::IDLE;
			_thoughtsCount = 0;

			_thoughts->SetIsActive(true);

			return;
		}
		else
		{
			_nextIndex = _vRoute[_nowArrayNum++];

			SetDirection();
		}
	}
}
void StudentMove::IdleMove()
{
	if (_studentState != StudentState::IDLE) return;
	if (_haveIdlePath) return;
	if (_vRoute.size()) return;

	while (true)
	{
		int rndX = rand() % 3;
		int rndY = rand() % 3;
		int plmnX = rand() % 3;
		int plmnY = rand() % 3;
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

void StudentMove::SetDirection()
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