#include "stdafx.h"
#include "GgaetIp.h"

Animation::Animation()
{
	frameSize = Vector2::zero;
}

void Animation::SetImage(shared_ptr<Image> image)
{
	this->image = image;
	if(frameCount != Vector2::zero)
		frameSize = image->GetContentSize() / frameCount;
}

void Animation::SetFrameCount(Vector2 frameCount)
{
	this->frameCount = frameCount;
	if(image)
		frameSize = image->GetContentSize() / frameCount;
}

Vector2 Animation::GetFrameSize()
{
	return frameSize;
};

Vector2 Animation::GetFrameCount()
{
	return frameCount;
};

shared_ptr<Image> Animation::GetImage()
{
	return image;
};