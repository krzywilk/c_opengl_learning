#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include<tuple> // for tuple
#include <map>
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

	const int texturesWrapS;
	const int texturesWrapT;
	const int texturesMinFilter;
	const int texturesMagFilter;
	std::map<std::string, unsigned int> name2id;


public:
	TexturesDirLoader(const char* sourcePath, const int texturesWrapS, const int texturesWrapT, const int texturesMinFilter, const int texturesMagFilter) :
		sourcePath(sourcePath),
		texturesWrapS(texturesWrapS),
		texturesWrapT(texturesWrapT),
		texturesMinFilter(texturesMinFilter),
		texturesMagFilter(texturesMagFilter)
	{
		const auto& directoryIterator = fs::directory_iterator(sourcePath);
		texturesNum = static_cast<unsigned int> ((std::size_t)std::distance(directoryIterator, fs::directory_iterator{}));

		names = new std::string[texturesNum];
		textures = new unsigned int[texturesNum];
		texturesMetadata = new std::tuple< unsigned int, unsigned int, unsigned int, unsigned int>[texturesNum];
		std::map<std::string, int> name2id;
	}

	unsigned int getTextureId(std::string* name) {
		return name2id[*name];
	}

	void loadTextures();

	~TexturesDirLoader()
	{
		delete[] names;
		delete[] textures;
		delete[] texturesMetadata;
	}
};

