#pragma once
#include "GgaetIp.h"
#include "Observe.h"

class AdmissionWindow : public Script, public Observe
{
private:
	Transform* _transform;
	Sprite* _sprite;

	Object* _increaseButton;
	Object* _decreaseButton;

	Object* _interestedText;
	Object* _incomingText;
	Object* _returningText;
	Object* _totalText;
	Object* _tuitionText;
	Object* _subsidyText;

	Object* _greenStartButton;

	int _interested;
	int _incoming;
	int _returning;
	int _total;
	int _tuition;
	int _subsidy;


public:
	virtual void Init() override;
	virtual void Update() override;

	void Increase() { if (_incoming >= 13) return; _incoming++; }
	void Decrease() { if (_incoming <= 0) return; _incoming--; }

	int GetTotalNum() { return _total; }

	virtual void OnNotify(MTYPE type, string event) override;
};