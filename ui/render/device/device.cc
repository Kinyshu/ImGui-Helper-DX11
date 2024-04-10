#include "device.hpp"

AGui::Device::Device(HWND& Hwnd) : Hwnd(Hwnd)
{
}

AGui::Device::~Device() {
    this->CleanupDevice();
}

bool AGui::Device::CreateDevice() {
	
	DXGI_SWAP_CHAIN_DESC Desc;
	ZeroMemory(&Desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	{
        Desc.BufferCount = 2;
        Desc.BufferDesc.Width = 0;
        Desc.BufferDesc.Height = 0;
        Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        Desc.BufferDesc.RefreshRate.Numerator = 60;
        Desc.BufferDesc.RefreshRate.Denominator = 1;
        Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        Desc.OutputWindow = this->Hwnd;
        Desc.SampleDesc.Count = 1;
        Desc.SampleDesc.Quality = 0;
        Desc.Windowed = TRUE;
        Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

    D3D_FEATURE_LEVEL FeatureLevel;
    const D3D_FEATURE_LEVEL FeatureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

    auto Result = D3D11CreateDeviceAndSwapChain(
        0,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        0,
        FeatureLevelArray,
        2,
        D3D11_SDK_VERSION,
        &Desc,
        &this->SwapChain,
        &this->D3dDevice,
        &FeatureLevel,
        &this->DeviceContext
    );

    if (Result == DXGI_ERROR_UNSUPPORTED) {
        Result = D3D11CreateDeviceAndSwapChain(
            0,
            D3D_DRIVER_TYPE_WARP,
            0,
            0,
            FeatureLevelArray,
            2,
            D3D11_SDK_VERSION,
            &Desc,
            &this->SwapChain,
            &this->D3dDevice,
            &FeatureLevel,
            &this->DeviceContext
        );
    }

    if (Result != S_OK) {
        return false;
    }

    return this->CreateRenderTargetView();
}

void AGui::Device::CleanupDevice() {

    this->CleanupRenderTargetView();

    if (this->SwapChain) {
        this->SwapChain->Release();
        this->SwapChain = nullptr;
    }

    if (this->DeviceContext) {
        this->DeviceContext->Release();
        this->DeviceContext = nullptr;
    }

    if (this->DeviceContext) {
        this->DeviceContext->Release();
        this->DeviceContext = nullptr;
    }

    if (this->D3dDevice) {
        this->D3dDevice->Release();
        this->D3dDevice = nullptr;
    }
}

bool AGui::Device::CreateRenderTargetView() {
    
    ID3D11Texture2D* Texture2d;
    auto Result = this->SwapChain->GetBuffer(0, IID_PPV_ARGS(&Texture2d));
    if (Result != S_OK) {
        this->CleanupDevice();
        return false;
    }

    Result = this->D3dDevice->CreateRenderTargetView(Texture2d, 0, &this->RenderTargetView);
    if (Result != S_OK) {
        this->CleanupDevice();
        return false;
    }

    Texture2d->Release();

    return true;
}

void AGui::Device::CleanupRenderTargetView() {

    if (this->RenderTargetView) {
        this->RenderTargetView->Release();
        this->RenderTargetView = nullptr;
    }
}

void AGui::Device::Clear() {
    static const float ClearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
    this->DeviceContext->OMSetRenderTargets(1, &this->RenderTargetView, nullptr);
    this->DeviceContext->ClearRenderTargetView(this->RenderTargetView, ClearColor);
}

IDXGISwapChain* AGui::Device::GetSwapChain() {
    return this->SwapChain;
}

ID3D11Device* AGui::Device::GetDevice() {
    return this->D3dDevice;
}

ID3D11DeviceContext* AGui::Device::GetDeviceContext() {
    return this->DeviceContext;
}

ID3D11RenderTargetView* AGui::Device::GetRenderTargetView() {
    return this->RenderTargetView;
}
