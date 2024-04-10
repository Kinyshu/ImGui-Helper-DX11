#pragma once

#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <Windows.h>
#include <d3d11.h>

namespace AGui {

	class Device {
	public:
		Device(HWND& Hwnd);
		~Device();

	public:

		bool CreateDevice();
		void CleanupDevice();

		bool CreateRenderTargetView();
		void CleanupRenderTargetView();

	public:
		void Clear();

	public:
		IDXGISwapChain* GetSwapChain();
		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();
		ID3D11RenderTargetView* GetRenderTargetView();

	private:
		HWND Hwnd;

	protected:
		IDXGISwapChain* SwapChain;
		ID3D11Device* D3dDevice;
		ID3D11DeviceContext* DeviceContext;
		ID3D11RenderTargetView* RenderTargetView;
	};
}

#endif // !DEVICE_HPP