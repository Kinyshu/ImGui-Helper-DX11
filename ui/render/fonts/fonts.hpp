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
		* Функция GetFont
		* 
		* Аргументы:
		* std::string Name - название шрифта
		* float Size - размер шрифта
		* 
		* Возвращает указатель на структуру ImFont*
		* 
		* Пример:
		* In: GetFont("Arial", 17.f);
		* Out: Ищет в карте std::map "Arial_17,000000";
		*/
		ImFont* GetFont(std::string Name, float Size);

	public:
		/*
		* Функция AddFromFile
		*
		* Аргументы:
		* std::string Name - название шрифта
		* std::string Path - путь к шрифту
		* float Size - размер шрифта
		* 
		* Добавляет шрифт в карту std::map
		*/
		bool AddFromFile(std::string Name, std::string Path, float Size);

		/*
		* Функция AddFromBytes
		*
		* Аргументы:
		* std::string Name - название шрифта
		* std::vector< std::uint8_t > Data - массив с байтами шрифта
		* float Size - размер шрифта
		*
		* Добавляет шрифт в карту std::map
		*/
		bool AddFromBytes(std::string Name, std::vector< std::uint8_t > Data, float Size);

	private:
		ImGuiIO GuiIo;
		ImFontConfig FontConfig;

		std::map< std::string, ImFont* > FontsMap;
	};
}

#endif // !FONTS_HPP