#pragma once

#ifndef IMAGES_HPP
#define IMAGES_HPP

#include <Windows.h>
#include <map>
#include <vector>
#include <string>
#include <d3d11.h>
#include <unordered_map>

#include "../../../deps/imgui/imgui.h"

namespace AGui {

	class Images {
	public:
		Images(ID3D11Device* Device);
		~Images();

	public:
		ID3D11ShaderResourceView* GetImage(std::string Name);

	public:
		bool UpdateImage(std::string Name, std::vector< std::uint8_t > Bytes);

		bool AddFromFile(std::string Name, std::string Path, int Width, int Height);
		bool AddFromBytes(std::string Name, std::vector< std::uint8_t > Bytes, int Width, int Height);

	private:
		bool CreateTexture(std::string Name, std::uint8_t* Bytes, int Width, int Height);

	public:
		ID3D11Device* Device;
		std::map< std::string, ID3D11ShaderResourceView* > ImagesMap;
	};
}

#endif // !IMAGES_HPP
