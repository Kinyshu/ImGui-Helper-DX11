#include "screen.hpp"

AGui::VirtualScreen::VirtualScreen(std::string Name) : Name(Name)
{
}

AGui::VirtualScreen::~VirtualScreen()
{
}

void AGui::VirtualScreen::OnScreenUpdate(double Time)
{
}

void AGui::VirtualScreen::OnScreenRenderer()
{
}

std::string AGui::VirtualScreen::GetScreenName() {
	return this->Name;
}

AGui::Screen::Screen() : CurrentScreen(nullptr)
{
}

AGui::Screen::Screen(std::vector<VirtualScreen*> Screens) : Screens(Screens), CurrentScreen(nullptr)
{
}

AGui::Screen::~Screen()
{
	this->Screens.clear();
}

AGui::VirtualScreen* AGui::Screen::GetCurrentScreen() {
	return this->CurrentScreen;
}

void AGui::Screen::SetCurrentScreen(VirtualScreen* Screen) {

	if (!Screen) {
		return;
	}

	this->CurrentScreen = Screen;
}

void AGui::Screen::RegisterScreen(VirtualScreen* Screen) {
	this->Screens.push_back(Screen);
}

AGui::VirtualScreen* AGui::Screen::GetScreen(std::string Name) {

	for (auto Screen : this->Screens) {
		if (!Screen->GetScreenName().compare(Name)) {
			return Screen;
		}
	}

	return nullptr;
}