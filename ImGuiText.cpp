#include "stdafx.h"

void ImGuiText::Render()
{
	ImGui::Text(name.c_str());
}

ImGuiText* ImGuiText::CreateText(string text, string windowName)
{
	ImGuiText* newText = new ImGuiText();
	newText->name = text;
	if (windowName != ".None")
		ImGuiManager::GetInstnace()->AddUI(newText, windowName);
	return newText;
}

void ImGuiText::SetText(const char* text,...)
{
	string str;
	va_list list;
	va_start(list, text);
	for (int i = 0; i < text[i] != '\0'; i++)
	{
		if (text[i] == '%')
		{
			switch (text[i + 1])
			{
			case 'd':
				str += to_string(va_arg(list, int));
				break;
			case 'f':
				str += to_string(va_arg(list, double));
				break;
			case 's':
				str += va_arg(list, char*);
				break;
			}
			i++;
			continue;
		}
		str += text[i];
	}
	va_end(list);
	name = str;
}