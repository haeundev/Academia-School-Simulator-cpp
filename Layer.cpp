#include "stdafx.h"
#include "GgaetIp.h"

shared_ptr<Layer> Layer::CreateLayer(Vector2 size,Vector2 position)
{
	Layer* layer = new Layer();
	if (size == Vector2::zero)
		layer->size = DesignResolution;
	else
		layer->size = size;
	layer->position = position;
	D2D1_SIZE_F layerSize = D2D1::SizeF(layer->size.x, layer->size.y);
	Direct2D::GetInstance()->GetRenderTarget()->CreateLayer(layerSize, &layer->layer);

	shared_ptr<Layer> instance = shared_ptr<Layer>(layer);
	return instance;
}

Layer::~Layer()
{
	layer->Release();
}
