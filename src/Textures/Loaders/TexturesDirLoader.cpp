#define STB_IMAGE_IMPLEMENTATION

#include "TexturesDirLoader.h"
#include "../../stb_image.h"
void TexturesDirLoader::loadTextures()
{
	const auto& directoryIterator = fs::directory_iterator(sourcePath);

	int currentIdx = 0;
	for (const auto& entry : directoryIterator)
	{
		std::filesystem::path path(entry.path());
		std::string pth = path.string();
		const char* charPath = pth.c_str();
		int width, height, nrChannels;
		unsigned char* data = stbi_load(charPath, &width, &height, &nrChannels, 0);
		if (data)
		{
			glGenTextures(1, &textures[currentIdx]);
			glBindTexture(GL_TEXTURE_2D, textures[currentIdx]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texturesWrapS);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texturesWrapT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texturesMinFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texturesMagFilter);

			const std::string name = path.filename().string();
			names[currentIdx] = name;
			name2id[name] = textures[currentIdx];
			std::string ext = path.extension().string();
			int textureFormat = GL_RGB;
			//std::transform(name.begin(), name.end(), name.begin(),
			//	[](unsigned char c) { return std::tolower(c); });
			if (nrChannels == 4) {
				textureFormat = GL_RGBA;
			}
			glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			texturesMetadata[currentIdx] = std::make_tuple(width, height, nrChannels, textureFormat);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << charPath << std::endl;
		}

	}

}