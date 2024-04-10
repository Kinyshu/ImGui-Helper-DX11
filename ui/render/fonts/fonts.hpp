#pragma once

#ifndef FONTS_HPP
#define FONTS_HPP

#include <Windows.h>
#include <map>
#include <vector>
#include <string>
#include "../../../deps/imgui/imgui.h"

namespace AGui {

	class Fonts {
	public:
		Fonts();
		~Fonts();

	public:
		/* 
		* ������� GetFont
		* 
		* ���������:
		* std::string Name - �������� ������
		* float Size - ������ ������
		* 
		* ���������� ��������� �� ��������� ImFont*
		* 
		* ������:
		* In: GetFont("Arial", 17.f);
		* Out: ���� � ����� std::map "Arial_17,000000";
		*/
		ImFont* GetFont(std::string Name, float Size);

	public:
		/*
		* ������� AddFromFile
		*
		* ���������:
		* std::string Name - �������� ������
		* std::string Path - ���� � ������
		* float Size - ������ ������
		* 
		* ��������� ����� � ����� std::map
		*/
		bool AddFromFile(std::string Name, std::string Path, float Size);

		/*
		* ������� AddFromBytes
		*
		* ���������:
		* std::string Name - �������� ������
		* std::vector< std::uint8_t > Data - ������ � ������� ������
		* float Size - ������ ������
		*
		* ��������� ����� � ����� std::map
		*/
		bool AddFromBytes(std::string Name, std::vector< std::uint8_t > Data, float Size);

	private:
		ImGuiIO GuiIo;
		ImFontConfig FontConfig;

		std::map< std::string, ImFont* > FontsMap;
	};
}

#endif // !FONTS_HPP