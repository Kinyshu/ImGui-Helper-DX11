#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <Windows.h>
#include <string>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace AGui {

	inline LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
			return true;
		}

		switch (msg) {

		case WM_SIZE:
			if (wParam == SIZE_MINIMIZED)
				return 0;
			return 0;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU)
				return 0;
			break;
		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;

		}

		return ::DefWindowProcW(hWnd, msg, wParam, lParam);
	}

	struct WindowParams {

		WindowParams(int Width, int Height, std::wstring Name, std::wstring ClassName);

		int Width;
		int Height;
		std::wstring Name;
		std::wstring ClassName;
	};

	class Window {
	public:
		Window(WNDPROC WndProc, WindowParams* Params);
		~Window();

	public:
		bool RegisterWindow();
		void Run();
		void Stop();

	private:		
		void Update();
		void Close();

	private:
		HWND Hwnd;
		WNDPROC WndProc;
		WindowParams* Params;
	};
}

#endif // !WINDOW_HPP
