#pragma once

#ifndef DEFSCREEN_HPP
#define DEFSCREEN_HPP

#include "../../render/overlay/overlay.hpp"

namespace AGui {

	class DefaultScreen : public VirtualScreen {
	public:
		DefaultScreen(std::string Name);
		~DefaultScreen();

	public:
		void OnScreenUpdate(double Time);
		void OnScreenRenderer();

	private:
		Overlay* OverlayPtr;
	};
}

#endif // !DEFSCREEN_HPP
