#pragma once
#include "GgaetIp.h"

class ImageManager
{
private:
	typedef map<string, shared_ptr<Image>>				mapImageList;
	typedef map<string, shared_ptr<Image>>::iterator	mapImageIter;

	mapImageList _mImageList;
	ImageManager() {};

public:
	~ImageManager() {};

	static ImageManager* GetInstance();

	shared_ptr<Image> AddImage(string strKey);
	shared_ptr<Image> FindImage(string strKey);

};
