#include "fonts.hpp"

AGui::Fonts::Fonts() {

	this->GuiIo = ImGui::GetIO();

	this->FontConfig.PixelSnapH = 1;
	this->FontConfig.OversampleH = 2;
	this->FontConfig.OversampleV = 1;
	this->FontConfig.RasterizerMultiply = 0.9f;
}

AGui::Fonts::~Fonts()
{
}

ImFont* AGui::Fonts::GetFont(std::string Name, float Size) {
	return this->FontsMap.find(Name + "_" + std::to_string(Size))->second;
}

bool AGui::Fonts::AddFromFile(std::string Name, std::string Path, float Size) {
	
	auto Font = this->GuiIo.Fonts->AddFontFromFileTTF(Path.c_str(), Size, &this->FontConfig, this->GuiIo.Fonts->GetGlyphRangesCyrillic());
	if (!Font) {
		return false;
	}

	this->FontsMap.insert(std::pair<std::string, ImFont*>(Name + "_" + std::to_string(Size), Font));
	return true;
}

bool AGui::Fonts::AddFromBytes(std::string Name, std::vector<std::uint8_t> Data, float Size) {

	auto Font = this->GuiIo.Fonts->AddFontFromMemoryTTF(Data.data(), static_cast<int>(Data.size()), Size, &this->FontConfig, this->GuiIo.Fonts->GetGlyphRangesCyrillic());
	if (!Font) {
		return false;
	}

	this->FontsMap.insert(std::pair<std::string, ImFont*>(Name + "_" + std::to_string(Size), Font));
	return true;
}
