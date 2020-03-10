#pragma once
#include "GgaetIp.h"
class DrawLine : public ScriptComponent
{
private:
	LineComponent* line;
	Object* obj[2];
	Color color;
public:
	virtual void Init();
	virtual void Update();
	virtual void Release();

	void SetObject(int number, Object* obj);
	void SetLine(int number);
};

