#include "stdafx.h"
#include "GgaetIp.h"

DrawComponent::DrawComponent()
{
	layer = nullptr;
}

void DrawComponent::Awake()
{
	this->transform = object->GetTransform();
}

void DrawComponent::SetDepth(int _depth)
{
	object->GetTransform()->SetDepth(_depth);
}

int DrawComponent::GetDepth()
{
	return  object->GetTransform()->GetDepth();
}

void DrawComponent::SetLayer(shared_ptr<Layer> layer)
{
	this->layer = layer;
}

shared_ptr<Layer> DrawComponent::GetLayer()
{
	return layer;
}