#include "stdafx.h"
#include "GgaetIp.h"

Vector2 Sprite::GetFrameSize()
{
	return frameSize;
}

void Sprite::SetStartPoint(Vector2 startPoint)
{
	this->startPoint = startPoint;
};

shared_ptr<Image> Sprite::GetSprite()
{
	return image;
}

void Sprite::SetFrameSize(Vector2 frameSize)
{
	this->frameSize = frameSize;
};

Vector2 Sprite::GetStartPoint()
{
	return startPoint;
}

void Sprite::Awake()
{
	DrawComponent::Awake();
}

void Sprite::Render()
{
	if (!image)
		return;
	auto renderTarget = Direct2D::GetInstance()->GetRenderTarget();
	Vector2 anchorPoint = transform->GetAnchorPoint();
	float width = frameSize.x ;
	float height = frameSize.y ;
	auto bitmap = image->GetBitmap();
	Vector2 contentSize = image->GetContentSize();

	D2D1_RECT_F imageSize;
	imageSize = D2D1::RectF
	(
		-(width * anchorPoint.x ),
		-(height - height * anchorPoint.y ),
		(width - width * anchorPoint.x ),
		(height * anchorPoint.y )
	);
	transform->SetSize(imageSize);
	Matrix3x3 localToWorldMatrix = transform->GetScaleMatrix();
	if (isFliping)
		localToWorldMatrix = localToWorldMatrix * Image::flipMatrix;
	localToWorldMatrix = localToWorldMatrix * transform->GetRotateMatrix();
	localToWorldMatrix = localToWorldMatrix * transform->GetTranslateMatrix();
	localToWorldMatrix = localToWorldMatrix * object->GetParent()->GetTransform()->GetLocalToWorldMatrix();
	
	if (layer)
	{
		float width = layer->GetSize().x / 2;
		float height = layer->GetSize().y / 2;
		Vector2 position = layer->GetPosition();
		auto layerSize = D2D1::RectF(-width, -height, width, height);
		layerSize.left += DesignResolution.x / 2 + position.x;
		layerSize.top += DesignResolution.y / 2 - position.y;
		layerSize.right += DesignResolution.x / 2 + position.x;
		layerSize.bottom += DesignResolution.y / 2 - position.y;
		auto layerParameters = D2D1::LayerParameters(layerSize);
		//auto layerParameters = D2D1::LayerParameters(layerSize, 0, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE, layer->GetTransform()->GetLocalToWorldMatrix().To_D2D1_Matrix_3x2_F() * D2D1::Matrix3x2F::Translation(D2D1::SizeF(DesignResolution.x / 2, DesignResolution.y / 2)));
		//auto layerParameters = D2D1::LayerParameters(layerSize, 0, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE, D2D1::Matrix3x2F::Translation(D2D1::SizeF(DesignResolution.x / 2, DesignResolution.y / 2)));
		renderTarget->PushLayer(layerParameters, layer->GetLayer());
	}

	if (object->GetCameraAffected())
		localToWorldMatrix = localToWorldMatrix * CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetLocalToWorldMatrix();
	renderTarget->SetTransform(localToWorldMatrix.To_D2D1_Matrix_3x2_F());

	renderTarget->DrawBitmap(bitmap, imageSize, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(startPoint.x , startPoint.y , frameSize.x  + startPoint.x , startPoint.y  + frameSize.y ));
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	if (layer)
		renderTarget->PopLayer();

}

void Sprite::SetFlip(bool flip)
{
	isFliping = flip;
	return;
}

void Sprite::SetSprite(shared_ptr<Image> image)
{
	this->image = image;
	startPoint = Vector2::zero;
	frameSize = image->GetContentSize();
	transform->SetSize(image->GetSize());
	if (!object->GetComponent<Collider>())
		return;
	object->GetComponent<BoxCollider>()->UpdateSize();
}

void Sprite::Release()
{
	image = nullptr;
	DrawComponent::Release();
}