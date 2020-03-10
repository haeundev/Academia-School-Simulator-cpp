#pragma once
#include <string>
#include <functional>
#include "UI.h"
using namespace std;
class Vector2;
class ImVec2;
class ImGuiButton : public UI
{
private:
	ImVec2 size;
	function<void()> callBack;
public:
	static ImGuiButton* CreateImGuiButton(string _name = "Button", Vector2 _size = Vector2(100, 30),string windowName = ".None");
	void SetFunc(function<void()> _callBack) { callBack = _callBack; }
	virtual void Render() override; 
};

