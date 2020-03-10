#pragma once
#include <string>

class Collider;
class Object;

class Component abstract
{
protected:
	Object* object;
public:
	virtual void Awake() {};
	virtual void Init() {};
	virtual void Update() {};
	virtual void Render() {};
	virtual void Release() { delete this; };

	void SetGameObject(Object* obj) { object = obj; };
	Object* GetGameObject() { return object; };
};
