#pragma once
template<typename T>
vector<T*> Object::GetComponents()
{
	vector<T*> componentsList;
	for (auto c : components)
	{
		if (dynamic_cast<T*>(c))
			componentsList.push_back((T*)c);
	}
	return componentsList;
}

template<typename T>
T* Object::GetComponent()
{
	for (Component* c : components)
	{
		if (dynamic_cast<T*>(c))
			return (T*)c;
	}
	return nullptr;
}

template<typename T>
T* Object::AddComponent()
{
	Component* component = new T();
	component->SetGameObject(this);
	components.push_back(component);
	component->Awake();
	return (T*)component;
}

template<typename T>
T* Object::GetClone()
{
	T* newObj = new T();
	memmove(newObj, this, sizeof(T*));
	return newObj;
}