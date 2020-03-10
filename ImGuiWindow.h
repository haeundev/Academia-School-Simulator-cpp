#pragma once
#include <string>

class Vector2;
class UI;
class ImGuiWindow
{
private:
	string name;
	ImGuiWindow() {};
	list<UI*> ui;
public:
	static ImGuiWindow* CreateImGuiWindow(string _name,Vector2 _size = Vector2(350,500), Vector2 _position = Vector2(0,0));
	void Render();
	string GetName() { return name; }
	void AddUI(UI* _ui);
};

