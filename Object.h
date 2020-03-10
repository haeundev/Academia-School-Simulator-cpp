#pragma once
#include <Windows.h>
#include <vector>
#include <d2d1.h>
#include <d2d1helper.h>
#include <string>
#include <dwrite.h>
#include "CameraManager.h"

#pragma comment (lib,"dwrite.lib")

using namespace std;

struct Color
{
	float r;
	float g;
	float b;
	float a;
};

class DrawComponent;
class Vector2;
class Transform;
class Component;

class Object
{
protected:
	Object();

	vector<Component*> components;
	string name;
	string tag;
	Transform* transform;

	Object* parent;
	vector<Object*> children;

	bool allowsInit = true;
	bool isActive = true;
	bool cameraAffected = true;

	void SortChildren();
public:
	static Object* CreateObject(Object* parent = nullptr);

	void SetCameraAffected(bool affected);
	bool GetCameraAffected();

	void SetParent(Object* parent);
	void AddChild(Object* child);
	void RemoveChild(Object* child);

	Object* GetParent() { return parent; };
	vector<Object*> GetChildren() { return children; };
	Object* GetChildByName(string name);

	template<typename T>
	T* GetComponent();
	string GetName() { return name; };
	string GetTag() { return tag; };

	void SetName(string name) { this->name = name; };
	void SetTag(string tag) { this->tag = tag; };

	template<typename T>
	T* AddComponent();

	void RemoveComponent(Component* component);

	template<typename T>
	vector<T*> GetComponents();

	Transform* GetTransform() { return transform; };

	void SetIsActive(bool _isActive);
	bool GetIsActive();

	template<typename T>
	T* GetClone();

	bool GetAllowsInit();

	virtual void Init();
	bool CheckMouseEvent();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

#include "Object.hpp"