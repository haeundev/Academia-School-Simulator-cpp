#pragma once
#include "GgaetIp.h"
#include "Observe.h"

class HireWindow;
class FacultyButton : public Script, public Observe
{
private:
	Transform* _transform;
	Sprite* _sprite;

	HireWindow* _hireWindow;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void OnMouseDown() override;

	void SetHireWindowLink(HireWindow* h) { _hireWindow = h; }
	void SetGreenSprite(string path) { _sprite->SetSprite(ImageManager::GetInstance()->AddImage(path)); }

	virtual void OnNotify(MTYPE type, string event) override;
};