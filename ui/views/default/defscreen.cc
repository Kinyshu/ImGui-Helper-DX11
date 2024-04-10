#include "defscreen.hpp"

AGui::DefaultScreen::DefaultScreen(std::string Name) : VirtualScreen(Name)
{
    this->OverlayPtr = Overlay::GetInstance();

    if (!this->OverlayPtr->GetFonts()->AddFromFile("Arial Black", "C:\\Windows\\Fonts\\ariblk.ttf", 20.f)) {
        std::printf("[%s] Ошибка при добавлении шрифта\n", __FUNCTION__);
    }
}

AGui::DefaultScreen::~DefaultScreen()
{
}

void AGui::DefaultScreen::OnScreenUpdate(double Time)  {
	std::printf("[%s] Вызвана, время: %lf\n", __FUNCTION__, Time);
}

void AGui::DefaultScreen::OnScreenRenderer() {
	std::printf("[%s] Вызвана\n", __FUNCTION__);

    static auto Params = Overlay::GetInstance()->GetParams();
    {
        ImGui::SetNextWindowPos({ 0, 0 });
        ImGui::SetNextWindowSize({ static_cast<float>(Params->Width), static_cast<float>(Params->Height) });

        ImGui::Begin(
            u8"Фон", 0,
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs
        );
        {
            const static auto Font = this->OverlayPtr->GetFonts()->GetFont("Arial Black", 20.f);

            ImGui::PushFont(Font);
            {
                ImGui::GetWindowDrawList()->AddText({ 10.f, 10.f }, ImColor(255, 255, 255), this->GetScreenName().c_str());
            }
            ImGui::PopFont();
        }
        ImGui::End();
    }
}