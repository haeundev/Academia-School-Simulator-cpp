#pragma once
#include <list>
class ImGuiWindow;
class UI;
class ImGuiManager
{
private:
	ImGuiManager() {};
	list<ImGuiWindow*> windows;
public:
	static ImGuiManager* GetInstnace();
	void Init();
	void Render();

	void AddWindow(ImGuiWindow* window);
	void AddUI(UI* ui,string windowName);
	//void DeleteWindow(ImGuiWindow* window);
};

