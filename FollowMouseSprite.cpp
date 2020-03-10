#include "stdafx.h"
#include "FollowMouseSprite.h"

void FollowMouseSprite::Init()
{
	_transform = object->GetTransform();

	_sprite = object->AddComponent<Sprite>();
	_sprite->SetSprite(ImageManager::GetInstance()->AddImage("ImagesForPlacing/transparentTile.png"));
	_sprite->SetOpacity(0.3f);
	_sprite->SetDepth((int)ZORDER::FOLLOW_MOUSE_SPRITE);
}

void FollowMouseSprite::Update()
{
	Vector2 mousePosition = InputManager::GetInstance()->GetMouseWorldPosition();
	Vector3 mousePosition_V3 = Vector3(mousePosition.x, mousePosition.y, 1);
	Vector3 mouseWorldPosition = Matrix3x3::Mul(mousePosition_V3, CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetLocalToWorldMatrix().GetInverseMatrix());
	float mouseX = mouseWorldPosition.x;
	float mouseY = (-1) * mouseWorldPosition.y;

	_currentIndex.x = (int)(mouseX - (GRID_STARTPOINT.x - GridWidth / 2)) / GridWidth;
	_currentIndex.y = (int)(GRID_STARTPOINT.y + GridHeight / 2 - mouseY) / GridHeight;

	if (_sStoreImgKey.size())
	{
		_sprite->SetSprite(ImageManager::GetInstance()->AddImage("ImagesForPlacing/" + _sStoreImgKey.top() + ".png"));
	}

	if (InputManager::GetInstance()->GetKeyDown('Q'))
	{
		if (!_sStoreImgKey.size()) return;

		_sStoreImgKey.pop();
		_sprite->SetSprite(ImageManager::GetInstance()->AddImage("ImagesForPlacing/transparentTile.png"));
	}

	if (2 * GridWidth < _sprite->GetFrameSize().x && _sprite->GetFrameSize().x <= 3 * GridWidth)
	{
		_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth,
			GRID_STARTPOINT.y - _currentIndex.y * GridHeight));

		if (1.5 * GridHeight < _sprite->GetFrameSize().y && _sprite->GetFrameSize().y <= 2 * GridHeight)
		{
			_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth,
				GRID_STARTPOINT.y - _currentIndex.y * GridHeight - GridHeight / 2));
		}
	}
	else if (GridWidth < _sprite->GetFrameSize().x && _sprite->GetFrameSize().x <= 2 * GridWidth)
	{
		_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth / 2,
			GRID_STARTPOINT.y - _currentIndex.y * GridHeight));

		if (1.5 * GridHeight < _sprite->GetFrameSize().y && _sprite->GetFrameSize().y <= 2 * GridHeight)
		{
			_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth + GridWidth / 2,
				GRID_STARTPOINT.y - _currentIndex.y * GridHeight - GridHeight / 2));
		}
	}
	else
	{
		_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth,
			GRID_STARTPOINT.y - _currentIndex.y * GridHeight));

		if (1.5 * GridHeight < _sprite->GetFrameSize().y && _sprite->GetFrameSize().y <= 2 * GridHeight)
		{
			_sprite->GetTransform()->SetPosition(Vector2(GRID_STARTPOINT.x + _currentIndex.x * GridWidth,
				GRID_STARTPOINT.y - _currentIndex.y * GridHeight - GridHeight / 2));
		}
	}
}