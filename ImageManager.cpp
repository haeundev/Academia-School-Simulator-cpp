#include "stdafx.h"
#include "ImageManager.h"
#include "Image.h"

ImageManager* ImageManager::GetInstance()
{
	static ImageManager* instance = new ImageManager();
	return instance;
}

shared_ptr<Image> ImageManager::AddImage(string strKey)
{
	shared_ptr<Image> img = FindImage(strKey);

	if (img)
		return img;

	shared_ptr<Image> newImg;
	newImg = newImg->CreateImage(strKey);
	_mImageList.insert(make_pair(strKey, newImg));

	return newImg;
}

shared_ptr<Image> ImageManager::FindImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}

	return nullptr;
}
