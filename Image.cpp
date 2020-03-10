#include "stdafx.h"
#include <memory>
#include "GgaetIp.h"

const Matrix3x3 Image::flipMatrix = Matrix3x3(-1, 0, 0, 0, 1, 0, 0, 0, 1);

shared_ptr<Image> Image::CreateImage(string path)
{
	string fullPath = "Resources/Sprite/" + path;
	wstring path_W;
	path_W.assign(fullPath.begin(), fullPath.end());
	shared_ptr<Image> newSprite = shared_ptr<Image>(new Image());
	newSprite->bitmap = Direct2D::GetInstance()->CreateBitmap(path_W, &newSprite->size);
	newSprite->contentSize = Vector2(newSprite->size.right, newSprite->size.bottom);
	newSprite->path = path;
	return newSprite;
}

Vector2 Image::GetContentSize()
{
	return contentSize;
};

Image::~Image()
{
	bitmap->Release();
}