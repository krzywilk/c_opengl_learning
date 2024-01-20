#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include<tuple> // for tuple

#include <glad/glad.h>
#include <sstream>
#include <iostream>



namespace fs = std::filesystem;

class TexturesDirLoader
{
private:
	unsigned int* textures;
	std::tuple< unsigned int,unsigned int,unsigned int, unsigned int>* texturesMetadata;
	unsigned int texturesNum;
	std::string* names;
	const char* sourcePath;

public:
	TexturesDirLoader(const char* sourcePath) :
		sourcePath(sourcePath)
	{
		const auto& directoryIterator = fs::directory_iterator(sourcePath);
		texturesNum = static_cast<unsigned int> ((std::size_t)std::distance(directoryIterator, fs::directory_iterator{}));

		names = new std::string[texturesNum];
		textures = new unsigned int[texturesNum];
		texturesMetadata = new std::tuple< unsigned int, unsigned int, unsigned int, unsigned int>[texturesNum];
		
	}

	void loadTextures();

	~TexturesDirLoader()
	{
		delete[] names;
		delete[] textures;
		delete[] texturesMetadata;
	}
};

