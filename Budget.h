#pragma once
#include "Script.h"

class Budget : public Script
{
private:
	Transform* _transform;
	Sprite* _sprite;

	int _budgetValue = 100000;

	Object* _budgetText;

	bool _isSandBoxMode;

public:
	virtual void Init() override;
	virtual void Update() override;

	void BudgetPlus(int i) { if (_isSandBoxMode) return;  _budgetValue += i; }
	void BudgetMinus(int i) { if (_isSandBoxMode) return; _budgetValue -= i; }

	void SetIsSandBoxMode(bool tf) { _isSandBoxMode = tf; }
	bool GetIsSandBoxMode() { return _isSandBoxMode; }
};