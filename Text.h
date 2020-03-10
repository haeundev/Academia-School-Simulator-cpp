#pragma once
#include <d2d1.h>
#include "DrawComponent.h"
enum class AnchorPoint
{
	LeftTop,
	LeftCenter,
	LeftBottom,
	CenterTop,
	Center,
	CenterBottom,
	RightTop,
	RightCenter,
	RightBottom
};

struct Color;
class Transform;

class Text : public DrawComponent
{
private:
	wstring text;
	wstring format;
	wstring fontName;
	wstring locale;
	float fontSize;
	int maxWidth;
	int maxHeight;
	AnchorPoint anchorPoint;
	IDWriteTextLayout* layout;
	ID2D1SolidColorBrush* br;

	void Create();
public:
	void CreateText(wstring text, wstring fontName, wstring locale, Color color, float fontSize, int maxWidth, int maxHeight);
	void ChangeText(wstring text);

	void SetColor(Color color,int startIndex,int length);
	void SetAnchorPoint(AnchorPoint point);
	void SetUnderLine(bool isUnderline,int startIndex,int length);
	void SetSize(Vector2 _size);

	virtual void Render() override;
};

