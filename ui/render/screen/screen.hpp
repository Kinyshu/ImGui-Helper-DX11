#pragma once

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <vector>
#include <string>
#include <time.h>

namespace AGui {

	/* 
	* ����� VirtualScreen
	* 
	* ����� ��� ������������ ������������� Views
	* ������������ ��� ����������� ���������� 2D �����.
	* 
	* ������:
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
		* ������� OnScreenUpdate
		* 
		* ��������� ���������:
		* double Time - ��������� ������� �������, ������ GetCurrentTime()
		* 
		* ������������ ��� ������� ��������.
		*/
		virtual void OnScreenUpdate(double Time);

		/*
		* ������� OnScreenRenderer
		* 
		* ������������ ��� ��������� 2D ����������.
		*/
		virtual void OnScreenRenderer();

		/*
		* ������� GetScreenName
		* 
		* ���������� �������� Screen ������� ���������������� ��� ���������� ������, ������������ ��� ������ ���� (Screens).
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
		* ������� GetCurrentScreen
		*
		* ���������� ��������� �� ������� Screen.
		*/
		VirtualScreen* GetCurrentScreen();

		/*
		* ������� SetCurrentScreen
		*
		* ���������:
		* VirtualScreen* Screen - ��������� ��������� �� VirtualScreen
		* 
		* �������� ������� (CurrentScreen) Screen, �� ��������� � ���������.
		*/
		void SetCurrentScreen(VirtualScreen* Screen);

	public:
		/*
		* ������� RegisterScreen
		* 
		* ���������:
		* VirtualScreen* Screen - ��������� ��������� �� VirtualScreen
		* 
		* ������������ ����� Screen � ��������� ��� � ������ Screens.
		*/
		void RegisterScreen(VirtualScreen* Screen);

		/*
		* ������� GetScreen
		*
		* ���������:
		* std::string Name - ��������� �������� ���������� ����
		*
		* ���������� ��������� �� Screen.
		*/
		VirtualScreen* GetScreen(std::string Name);
		
	private:
		VirtualScreen* CurrentScreen;
		std::vector < VirtualScreen* > Screens;
	};
}

#endif // !SCREEN_HPP