#include "stdafx.h"
#include "GgaetIp.h"

void Text::CreateText(wstring text, wstring fontName, wstring locale,Color color, float fontSize, int maxWidth, int maxHeight)
{
	this->text = text;
	this->fontName = fontName;
	this->locale = locale;
	this->fontSize = fontSize;
	this->maxWidth = maxWidth;
	this->maxHeight = maxHeight;
	Create();
	transform->SetSize(D2D1::RectF(0, 0, maxWidth, maxHeight));
	Direct2D::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(color.r,color.g,color.b,color.a),&br);
}

void Text::ChangeText(wstring text)
{
	if (this->text == text)
		return;
	this->text = text;
	Create();
}

void Text::Render()
{                                                                                       	
	auto renderTarget = Direct2D::GetInstance()->GetRenderTarget();
	float rotation = transform->GetRotation();
	Vector2 position = transform->GetPosition();
	Vector2 scale = transform->GetScale();
	RECT rect = transform->GetRect();
	Vector2 center = Vector2(rect.left, (int)anchorPoint % 3 == 2 ? position.y  - (rect.bottom - rect.top) / 2 : rect.top);
	Matrix3x3 localToWorldMatrix = transform->GetLocalToWorldMatrix();
	if (object->GetCameraAffected())
		localToWorldMatrix = localToWorldMatrix * CameraManager::GetInstance()->GetRenderCamera()->GetTransform()->GetLocalToWorldMatrix();
	renderTarget->SetTransform(localToWorldMatrix.To_D2D1_Matrix_3x2_F());

	renderTarget->DrawTextLayout(D2D1::Point2F(center.x , center.y ), layout, br, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Text::SetSize(Vector2 _size)
{
	maxWidth = _size.x ;
	maxHeight = _size.y ;
}

void Text::SetColor(Color color, int startIndex, int length)
{
	ID2D1SolidColorBrush* br;
	Direct2D::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &br);
	layout->SetDrawingEffect((IUnknown*)br, {(UINT32)startIndex,(UINT32)length});
}

void Text::SetUnderLine(bool isUnderline, int startIndex, int length)
{
	layout->SetUnderline(isUnderline, { (UINT32)startIndex,(UINT32)length });
}

void Text::Create()
{
	if(layout)
		layout->Release();
	layout = Direct2D::GetInstance()->CreateTextLayout(text, fontName, locale, fontSize, maxWidth, maxHeight);
}

void Text::SetAnchorPoint(AnchorPoint point)
{
	anchorPoint = point;
	switch (point)
	{
	case AnchorPoint::LeftTop:
		layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		transform->SetAnchorPoint(Vector2(0, 1));
		break;
	case AnchorPoint::LeftCenter:
		layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		transform->SetAnchorPoint(Vector2(0,0.5f));
		break;
	case AnchorPoint::LeftBottom:
		layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		transform->SetAnchorPoint(Vector2(0, 0));
		break;
	case AnchorPoint::CenterTop:
		layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		transform->SetAnchorPoint(Vector2(0.5f, 1));
		break;
	case AnchorPoint::Center:
		layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		transform->SetAnchorPoint(Vector2(0.5f, 0.5f));
		break;
	case AnchorPoint::CenterBottom:
		layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		transform->SetAnchorPoint(Vector2(0.5f, 0));
		break;
	case AnchorPoint::RightTop:
		layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		transform->SetAnchorPoint(Vector2(1, 1));
		break;
	case AnchorPoint::RightCenter:
		layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		transform->SetAnchorPoint(Vector2(1, 0.5f));
		break;
	case AnchorPoint::RightBottom:
		layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		transform->SetAnchorPoint(Vector2(1, 0));
		break;
	}
}