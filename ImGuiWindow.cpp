#include "stdafx.h"

ImGuiWindow* ImGuiWindow::CreateImGuiWindow(string _name, Vector2 _size, Vector2 _position)
{
	ImGuiWindow* newWindow = new ImGuiWindow();
	newWindow->name = _name;
	ImGui::SetWindowSize(_name.c_str(),ImVec2(_size.x, _size.y));
	ImGui::SetWindowPos(_name.c_str(),ImVec2(_position.x, _position.y));
	ImGuiManager::GetInstnace()->AddWindow(newWindow);
	return newWindow;
}

void ImGuiWindow::Render()
{
	ImGui::Begin(name.c_str());
	for (auto u : ui)
		u->Render();
	ImGui::End();
}

bool Compare(UI* a, UI* b)
{
	return a->GetLineNumber() < b->GetLineNumber();
}

void ImGuiWindow::AddUI(UI* _ui)
{
	ui.push_back(_ui);
	ui.sort(Compare);
}
