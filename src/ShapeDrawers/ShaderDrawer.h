#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../utils/simples.cpp"
#include "../../files.cpp"
#include <string>
#include <string>


class ShaderDrawer 
{
private:
    const char* vertexShaderSource;
    const char* fragmentShaderSource;

    bool checkShaderCompilation(int shaderId) {
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            return false;
        }
        return true;

    }

protected: 
    unsigned int VBO, VAO;
    unsigned int shaderProgramId;
    int vertexColorLocation;
public:
    ShaderDrawer(const char* vertexShaderPath, const char* fragmentShaderPath)
        {
        std::string stringVertexShaderSource = loadShaderSourceCode(vertexShaderPath);
        vertexShaderSource = stringVertexShaderSource.c_str();

        std::string stringFragmentShaderPath = loadShaderSourceCode(fragmentShaderPath);
        fragmentShaderSource = stringFragmentShaderPath.c_str();

        unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShaderId);
        checkShaderCompilation(vertexShaderId);

        unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShaderId);
        checkShaderCompilation(fragmentShaderId);

        shaderProgramId = glCreateProgram();
        glAttachShader(shaderProgramId, vertexShaderId);
        glAttachShader(shaderProgramId, fragmentShaderId);
        glLinkProgram(shaderProgramId);

        int vertexColorLocation = glGetUniformLocation(shaderProgramId, "color");

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);


        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

    };

    virtual void transferData(float vertices[], int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum) = 0;
    virtual void drawShape(int shapeIdx) = 0;
    virtual void drawAllShapes() = 0;
    ~ShaderDrawer() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgramId);
    }


};