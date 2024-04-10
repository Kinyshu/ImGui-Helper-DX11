#pragma once

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <vector>
#include <string>
#include <time.h>

namespace AGui {

	/* 
	* Класс VirtualScreen
	* 
	* Класс для наследования представления Views
	* предназначен для упрощённого рендеринга 2D сцены.
	* 
	* Пример:
	* 
	* class DefaultScreen : public VirtualScreen {
	* public:
	*	DefaultScreen(std::string Name);
	*	~DefaultScreen();
	*
	* public:
	*	void OnScreenUpdate(double Time);
	*	void OnScreenRenderer();
	* };
	* 
	*/
	class VirtualScreen {
	public:
		VirtualScreen(std::string Name);
		~VirtualScreen();

	public:
		/* 
		* Функция OnScreenUpdate
		* 
		* Принимает аргументы:
		* double Time - принимает счётчик времени, пример GetCurrentTime()
		* 
		* Используется для расчёта анимаций.
		*/
		virtual void OnScreenUpdate(double Time);

		/*
		* Функция OnScreenRenderer
		* 
		* Используется для отрисовки 2D примитивов.
		*/
		virtual void OnScreenRenderer();

		/*
		* Функция GetScreenName
		* 
		* Возвращает название Screen которое инициализируется при объявлении класса, используется для поиска окон (Screens).
		*/
		virtual std::string GetScreenName();

	protected:
		std::string Name;
	};

	class Screen {
	public:
		Screen();
		Screen(std::vector < VirtualScreen* > Screens);

		~Screen();

	public:
		/*
		* Функция GetCurrentScreen
		*
		* Возвращает указатель на текущий Screen.
		*/
		VirtualScreen* GetCurrentScreen();

		/*
		* Функция SetCurrentScreen
		*
		* Аргументы:
		* VirtualScreen* Screen - принимает указатель на VirtualScreen
		* 
		* Изменяет текущий (CurrentScreen) Screen, на указанный в аргументе.
		*/
		void SetCurrentScreen(VirtualScreen* Screen);

	public:
		/*
		* Функция RegisterScreen
		* 
		* Аргументы:
		* VirtualScreen* Screen - принимает указатель на VirtualScreen
		* 
		* Регистрирует новый Screen и добавляет его в массив Screens.
		*/
		void RegisterScreen(VirtualScreen* Screen);

		/*
		* Функция GetScreen
		*
		* Аргументы:
		* std::string Name - принимает название требуемого окна
		*
		* Возвращает указатель на Screen.
		*/
		VirtualScreen* GetScreen(std::string Name);
		
	private:
		VirtualScreen* CurrentScreen;
		std::vector < VirtualScreen* > Screens;
	};
}

#endif // !SCREEN_HPP