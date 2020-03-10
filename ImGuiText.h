#pragma once
#include "UI.h"

class ImGuiText : public UI
{
public:
	static ImGuiText* CreateText(string text, string windowName = ".None");
	void SetText(const char* text, ...);
	virtual void Render();
};

