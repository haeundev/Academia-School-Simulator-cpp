#pragma once
#include "GgaetIp.h"
#include "Observe.h"
#include <atlconv.h>

class BudgetNotification : public Script, public Observe
{
private:
	Transform* _transform;
	Text* _text;

	MTYPE _type;
	string _event;

	int _count = 0;
	int _fadeCount = 0;
	float _opacity = 1.f;
	bool _notified = false;

public:
	virtual void Init() override;
	virtual void Update() override;

	virtual void OnNotify(MTYPE type, string event) override;

	wstring String_to_wstring(string str)
	{
		USES_CONVERSION;
		return std::wstring(A2W(str.c_str()));
	}
};