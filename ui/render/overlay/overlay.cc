#include "overlay.hpp"

AGui::Overlay::Overlay(HWND& Hwnd, OverlayParams* Params) : Hwnd(Hwnd), Params(Params) {

	this->Screens = new Screen();
	this->Renderer = new Device(Hwnd);

	this->Instance = this;
}

AGui::Overlay::~Overlay()  {
	this->Renderer->~Device();
	this->Close();
}

AGui::Overlay* AGui::Overlay::GetInstance() {
	return Overlay::Instance;
}

bool AGui::Overlay::RegisterOverlay() {

	if (!this->Renderer->CreateDevice()) {
		return false;
	}

	ShowWindow(Hwnd, SW_SHOWDEFAULT);
	UpdateWindow(Hwnd);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	{
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	}

	ImGuiStyle* Style = &ImGui::GetStyle();
	{
		Style->Alpha = 1.f;

		Style->WindowPadding = ImVec2();
		Style->WindowRounding = 0.f;

		Style->FrameRounding = 0.0f;
		Style->ItemSpacing = { 15.f, 5.f };

		Style->ScrollbarSize = 4.f;
		Style->ScrollbarRounding = 0.f;

		Style->GrabMinSize = 2.f;

		Style->AntiAliasedLines = true;
		Style->AntiAliasedFill = true;
		Style->AntiAliasedLinesUseTex = true;

		Style->TabBorderSize = 0.f;
		Style->FrameBorderSize = 0.f;
		Style->WindowBorderSize = 0.f;

		Style->FrameRounding = 2.f;

		Style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
		Style->Colors[ImGuiCol_TextDisabled] = ImColor(235, 235, 235, 255);

		Style->Colors[ImGuiCol_WindowBg] = ImColor(55, 55, 55);
		Style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		Style->Colors[ImGuiCol_Border] = ImColor(255, 255, 255, 0);
		Style->Colors[ImGuiCol_FrameBg] = ImColor(22, 22, 22);

		Style->Colors[ImGuiCol_Button] = ImColor(25, 25, 25);
		Style->Colors[ImGuiCol_ButtonHovered] = ImColor(35, 35, 35);
		Style->Colors[ImGuiCol_ButtonActive] = ImColor(40, 40, 40);

		Style->Colors[ImGuiCol_ScrollbarBg] = ImColor(55, 55, 60);
		Style->Colors[ImGuiCol_ScrollbarGrab] = ImColor(62, 87, 93);
		Style->Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(75, 95, 120);

		Style->Colors[ImGuiCol_SliderGrab] = ImColor(55, 55, 60);
		Style->Colors[ImGuiCol_SliderGrabActive] = ImColor(55, 75, 100);

		Style->Colors[ImGuiCol_FrameBg] = ImColor(25, 25, 25);
		Style->Colors[ImGuiCol_FrameBgHovered] = ImColor(35, 35, 35);
		Style->Colors[ImGuiCol_FrameBgActive] = ImColor(40, 40, 40);

		Style->Colors[ImGuiCol_CheckMark] = ImColor(255, 35, 35);
	}

	this->FontsList = new Fonts();
	if (!this->FontsList) {
		return false;
	}

	this->ImagesList = new Images(this->Renderer->GetDevice());
	if (!this->ImagesList) {
		return false;
	}

	if (!ImGui_ImplWin32_Init(Hwnd)) {
		return false;
	}

	if (!ImGui_ImplDX11_Init(this->Renderer->GetDevice(), this->Renderer->GetDeviceContext())) {
		return false;
	}

	return true;
}

void AGui::Overlay::Update() {

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();
	{
		auto CurrentScreen = this->Screens->GetCurrentScreen();
		if (CurrentScreen) {
			CurrentScreen->OnScreenUpdate(ImGui::GetTime());
			CurrentScreen->OnScreenRenderer();
		}
	}
	ImGui::Render();

	this->Renderer->Clear();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	this->Renderer->GetSwapChain()->Present(1, 0);
}

void AGui::Overlay::Close() {

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();

	this->Renderer->~Device();
}

AGui::Fonts* AGui::Overlay::GetFonts() {
	return this->FontsList;
}

AGui::Images* AGui::Overlay::GetImages() {
	return this->ImagesList;
}

AGui::Screen* AGui::Overlay::GetScreens() {
	return this->Screens;
}

AGui::OverlayParams* AGui::Overlay::GetParams() {
	return this->Params;
}

AGui::OverlayParams::OverlayParams(int Width, int Height) {
	this->Width = Width;
	this->Height = Height;
}
