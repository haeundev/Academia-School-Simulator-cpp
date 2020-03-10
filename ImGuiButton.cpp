#include "stdafx.h"

ImGuiButton* ImGuiButton::CreateImGuiButton(string _name, Vector2 _size, string windowName)
{
	ImGuiButton* newButton = new ImGuiButton();
	newButton->name = _name;
	newButton->size = ImVec2(_size.x, _size.y);
	if(windowName != ".None")
		ImGuiManager::GetInstnace()->AddUI(newButton, windowName);
	return newButton;
}

void ImGuiButton::Render()
{
	if (ImGui::Button(name.c_str(), size))
		if (callBack)
			callBack();
}
