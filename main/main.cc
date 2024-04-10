#include "stdafx.hpp"

int main() {

    std::setlocale(LC_ALL, "Russian");

	AGui::Window* Window = new AGui::Window(AGui::WndProc, new AGui::WindowParams(1024, 600, L"Aceid.cc", L"AGui"));
    if (!Window) {
        return -1;
    }

    if (!Window->RegisterWindow()) {
        return -1;
    }

    try {

        auto Screen = AGui::Overlay::GetInstance()->GetScreens();

        Screen->RegisterScreen(new AGui::DefaultScreen("DefaultScreen"));
        Screen->SetCurrentScreen(Screen->GetScreen("DefaultScreen"));

        Window->Run();
    }
    catch (std::exception e) {
        std::printf("[-] Îøèáêà, %s", e.what());
        Window->Stop();
    }

    return 0;
}