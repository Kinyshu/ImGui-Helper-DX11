#include "images.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../deps/stb/stb_image.hpp"

AGui::Images::Images(ID3D11Device* Device) : Device(Device)
{
}

AGui::Images::~Images()
{
}

ID3D11ShaderResourceView* AGui::Images::GetImage(std::string Name) {
	return this->ImagesMap.find(Name)->second;
}

bool AGui::Images::UpdateImage(std::string Name, std::vector<std::uint8_t> Bytes) {

	if (this->ImagesMap.find(Name)->second != nullptr) {
		this->ImagesMap.erase(Name);
	}

	int x;
	int y;

	std::uint8_t* Data = stbi_load_from_memory(Bytes.data(), static_cast<int>(Bytes.size()), &x, &y, 0, 4);
	if (!Data) {
		return false;
	}

	return this->CreateTexture(Name, Data, x, y);
}

bool AGui::Images::AddFromFile(std::string Name, std::string Path, int Width, int Height) {
	
	int x;
	int y;

	std::uint8_t* Data = stbi_load(Path.c_str(), &x, &y, 0, 4);
	if (!Data) {
		return false;
	}

	return this->CreateTexture(Name, Data, Width, Height);
}

bool AGui::Images::AddFromBytes(std::string Name, std::vector<std::uint8_t> Bytes, int Width, int Height) {
	
	int x;
	int y;

	std::uint8_t* Data = stbi_load_from_memory(Bytes.data(), static_cast<int>(Bytes.size()), & x, &y, 0, 4);
	if (!Data) {
		return false;
	}

	return this->CreateTexture(Name, Data, Width, Height);
}

bool AGui::Images::CreateTexture(std::string Name, std::uint8_t* Bytes,  int Width, int Height) {

	ID3D11Texture2D* Texture2d;
	D3D11_TEXTURE2D_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_TEXTURE2D_DESC));
	{
		Desc.Width = Width;
		Desc.Height = Height;
		Desc.MipLevels = 1;
		Desc.ArraySize = 1;
		Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		Desc.SampleDesc.Count = 1;
		Desc.Usage = D3D11_USAGE_DEFAULT;
		Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		Desc.CPUAccessFlags = 0;
	}

	D3D11_SUBRESOURCE_DATA ResourceData;
	{
		ResourceData.pSysMem = Bytes;
		ResourceData.SysMemPitch = Desc.Width * 4;
		ResourceData.SysMemSlicePitch = 0;
	}

	auto Result = this->Device->CreateTexture2D(&Desc, &ResourceData, &Texture2d);
	if (Result != S_OK) {
		return false;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC ViewDesc;
	ZeroMemory(&ViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	{
		ViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		ViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		ViewDesc.Texture2D.MipLevels = Desc.MipLevels;
		ViewDesc.Texture2D.MostDetailedMip = 0;
	}

	ID3D11ShaderResourceView* ResourceView;
	Result = this->Device->CreateShaderResourceView(Texture2d, &ViewDesc, &ResourceView);
	if (Result != S_OK) {
		return false;
	}

	this->ImagesMap.insert(std::pair< std::string, ID3D11ShaderResourceView* >(Name, ResourceView));

	return true;
}