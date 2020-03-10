#include "stdafx.h"
#include "GgaetIp.h"

void Object::Init()
{
	for (Object* c : children)
		c->Init();
	
	if (!allowsInit)
		return;

	for (Component* c : components)
		c->Init();

	allowsInit = false;
}

bool Object::CheckMouseEvent()
{
	if (!isActive)
		return false;
	auto collider = GetComponent<Collider>();
	Vector2 mousePosition = InputManager::GetInstance()->GetMouseWorldPosition();
	bool ptInCollider;
	if (collider)
	{
		ptInCollider = collider->PtInCollider(mousePosition);
		collider->SetOnMouse(ptInCollider);
	}
	vector<Object*> reverseChildren;
	reverseChildren.assign(children.rbegin(), children.rend());

	for (auto c : reverseChildren)
	{
		if (c->CheckMouseEvent())
			return true;
	}

	if (!collider)
		return false;

	if (InputManager::GetInstance()->GetKeyDown(VK_LBUTTON) && ptInCollider)
	{
		collider->OnMouseDown();
		return true;
	}
	else if (InputManager::GetInstance()->GetKeyUp(VK_LBUTTON) && ptInCollider)
	{
		collider->OnMouseUp();
		return true;
	}
	return false;
}

bool Object::GetAllowsInit()
{
	return allowsInit;
}

bool Compare(Object* a, Object* b)
{
	Transform* aD = a->GetTransform();
	Transform* bD = b->GetTransform();

	if (!aD)
		return false;
	else if (!bD)
		return true;

	return aD->GetDepth() < bD->GetDepth();
}

void Object::Update()
{
	SortChildren();
	for (int i = 0; i < children.size(); i++)
		if (children[i]->GetAllowsInit())
			children[i]->Init();

	if (!isActive)
		return;

	for (int i = 0; i < components.size(); i++)
		components[i]->Update();

	for (Object* c : children)
		c->Update();
}

void Object::SetCameraAffected(bool affected)
{
	cameraAffected = affected;
}

bool Object::GetCameraAffected()
{
	return cameraAffected;
}


void Object::Release()
{
	if (parent)
		parent->RemoveChild(this);
	for (Object* c : children)
		c->Release();
	for(int i = components.size()-1; i >= 0; i--)
		components[i]->Release();
	delete this;
}


bool Object::GetIsActive()
{
	return isActive;
}

void Object::Render()
{
	if (!isActive)
		return;

	for (auto c : components)
		c->Render();

	for (Object* c : children)
		c->Render();
}

void Object::SetIsActive(bool _isActive)
{
	isActive = _isActive;
}

void Object::RemoveComponent(Component* component)
{
	for (auto itr = components.begin(); itr != components.end(); itr++)
	{
		if (*itr == component)
		{
			components.erase(itr);
			component->Release();
			return;
		}
	}
}

Object::Object()
{
	transform = AddComponent<Transform>();
	transform->SetAnchorPoint(Vector2(0.5f,0.5f));
	transform->SetPosition(Vector2::zero);
}

void Object::SortChildren()
{
	sort(children.begin(), children.end(), Compare);
}

Object* Object::CreateObject(Object* parent)
{
	Object* newObject = new Object();

	if (parent == nullptr)
		newObject->SetParent(SceneManager::GetInstance()->GetNowScene());
	else
		newObject->SetParent(parent);

	return newObject;
}

void Object::SetParent(Object* parent)
{
	this->parent = parent;
	parent->children.push_back(this);
}

void Object::AddChild(Object* child)
{
	children.push_back(child);
	child->parent->RemoveChild(child);
	child->parent = this;
	if (allowsInit)
		child->Init();
	//sort(children.begin(), children.end(), Compare);
}

void Object::RemoveChild(Object* child)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i] != child)
			continue;
		children.erase(children.begin() + i);
		break;
	}
}

Object* Object::GetChildByName(string name)
{
	for (Object* c : children)
	{
		if (c->GetName() == name)
			return c;
	}
	return nullptr;
}

