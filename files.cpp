#pragma once
#include <fstream>
#include <sstream>
#include <iostream>

namespace
{
    std::string loadShaderSourceCode(const char* shaderSourceCodePath) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string code;
        std::ifstream shaderFile;
        // ensure ifstream objects can throw exceptions:
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            shaderFile.open(shaderSourceCodePath);
            std::stringstream shaderStream;
            // read file's buffer contents into streams
            shaderStream << shaderFile.rdbuf();
            // close file handlers
            shaderFile.close();

            // convert stream into string
            code = shaderStream.str();
            return code;
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            std::string str = "";
            return str;
        }

    }
}

