#pragma once

#ifndef OVERLAY_HPP
#define OVERLAY_HPP

#include <Windows.h>

#include "../device/device.hpp"
#include "../screen/screen.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../../deps/imgui/imgui_internal.h"

#include "../../../deps/imgui/imgui.h"
#include "../../../deps/imgui/imgui_impl_dx11.h"
#include "../../../deps/imgui/imgui_impl_win32.h"

#include "../fonts/fonts.hpp"
#include "../images/images.hpp"

namespace AGui {

	struct OverlayParams {
	public:
		OverlayParams(int Width, int Height);

		int Width;
		int Height;
	};

	class Overlay {
	public:
		Overlay(HWND& Hwnd, OverlayParams* Params);
		~Overlay();

	public:
		static Overlay* GetInstance();

	public:
		bool RegisterOverlay();

	public:
		void Update();
		void Close();

	public:
		Fonts* GetFonts();
		Images* GetImages();
		Screen* GetScreens();
		OverlayParams* GetParams();

	private:
		Fonts* FontsList;
		Images* ImagesList;
		Screen* Screens;

	private:
		HWND Hwnd;
		OverlayParams* Params;

	private:
		Device* Renderer;

	protected:
		static inline Overlay* Instance;
	};
}

#endif // !OVERLAY_HPP