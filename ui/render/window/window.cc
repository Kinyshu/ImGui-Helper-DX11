#include "window.hpp"

#include "../overlay/overlay.hpp"

AGui::Window::Window(WNDPROC WndProc, WindowParams* Params) : WndProc(WndProc), Params(Params)
{
}

AGui::Window::~Window() {
	this->Close();
}

bool AGui::Window::RegisterWindow() {
	
	WNDCLASSEXW WndClass = {
		sizeof(WNDCLASSEXW),
		CS_CLASSDC,
		this->WndProc,
		0L, 0L,
		GetModuleHandle(0),
		0, 0, 0, 0,
		this->Params->ClassName.c_str(),
		0
	};

	if (RegisterClassExW(&WndClass) == NULL) {
		return false;
	}

	const auto Width = GetSystemMetrics(SM_CXSCREEN);
	const auto Height = GetSystemMetrics(SM_CYSCREEN);

	this->Hwnd = CreateWindowW(
		WndClass.lpszClassName,
		this->Params->Name.c_str(),
		WS_POPUP | WS_VISIBLE,
		(Width / 2) - (this->Params->Width / 2),
		(Height / 2) - (this->Params->Height / 2),
		this->Params->Width, this->Params->Height,
		0, 0,
		WndClass.hInstance,
		0
	);

	ShowWindow(this->Hwnd, SW_SHOWDEFAULT);
	UpdateWindow(this->Hwnd);

	SetWindowLong(this->Hwnd, GWL_EXSTYLE, GetWindowLong(this->Hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	auto Renderer = new Overlay(this->Hwnd, new OverlayParams(this->Params->Width, this->Params->Height));
	if (!Renderer->RegisterOverlay()) {
		return false;
	}

	return true;
}

void AGui::Window::Run() {
	this->Update();
}

void AGui::Window::Stop() {
	this->Close();
}

void AGui::Window::Update() {

	MSG Msg;
	while (true) {

		while (::PeekMessage(&Msg, nullptr, 0U, 0U, PM_REMOVE)) {

			::TranslateMessage(&Msg);
			::DispatchMessage(&Msg);

			if (Msg.message == WM_QUIT) {
				this->Close();
				return;
			}
		}

		Overlay::GetInstance()->Update();
	}
}

void AGui::Window::Close() {

	Overlay::GetInstance()->~Overlay();

	DestroyWindow(this->Hwnd);
	UnregisterClassW(this->Params->ClassName.c_str(), 0);
}

AGui::WindowParams::WindowParams(int Width, int Height, std::wstring Name, std::wstring ClassName) {
	this->Width = Width;
	this->Height = Height;
	this->Name = Name;
	this->ClassName = ClassName;
}
