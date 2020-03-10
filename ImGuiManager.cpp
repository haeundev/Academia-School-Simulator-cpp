#include "stdafx.h"

ImGuiManager* ImGuiManager::GetInstnace()
{
	static ImGuiManager* instance = new ImGuiManager();
	return instance;
}

void ImGuiManager::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(_hWnd);
	ImGui_ImplDX11_Init(Direct3D::GetInstance()->GetDevice(), Direct3D::GetInstance()->GetDeviceContext());
}
void ImGuiManager::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//
	for (auto w : windows)
		w->Render();
	//

	// Rendering
	ImGui::Render();
	auto renderTargetView = Direct3D::GetInstance()->GetRenderTargetView();
	Direct3D::GetInstance()->GetDeviceContext()->OMSetRenderTargets(1, &renderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Direct3D::GetInstance()->GetSwapChain()->Present(1, 0); // Present with vsync
}

void ImGuiManager::AddWindow(ImGuiWindow* window)
{
	windows.push_back(window);
}

void ImGuiManager::AddUI(UI* ui, string windowName)
{
	for (auto w : windows)
	{
		if (w->GetName() != windowName)
			continue;
		w->AddUI(ui);
		return;
	}
}

//void ImGuiManager::DeleteWindow(ImGuiWindow* window)
//{
//	windows.remove(window);
//	delete window;
//}
