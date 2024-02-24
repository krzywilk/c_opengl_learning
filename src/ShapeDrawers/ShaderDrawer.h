#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <string>
#include <map>
#include "../utils/simples.cpp"
#include "../../files.cpp"

#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>


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
    unsigned int trianglesNumber;
    unsigned int currentAttribElemSize;

    std::map<std::string, bool> *drawCachedBoolUniforms;
    std::map<std::string, int> *drawCachedIntUniforms;
    std::map<std::string, float> *drawCachedFloatUniforms;
    std::map<std::string, glm::vec2> *drawCachedVec2Uniforms;
    std::map<std::string, glm::vec3> *drawCachedVec3Uniforms;
    std::map<std::string, glm::vec3*> *drawCachedVec3Uniforms_pointerValue;

    std::map<std::string, glm::vec4> *drawCachedVec4Uniforms;

    std::map<std::string, glm::mat2> *drawCachedMat2Uniforms;
    std::map<std::string, glm::mat3> *drawCachedMat3Uniforms;
    std::map<std::string, glm::mat4>* drawCachedMat4Uniforms;

    void processCachedUniforms() {

        for (auto const& mat2Uniform : *drawCachedMat2Uniforms)
        {
            setMat2(mat2Uniform.first, mat2Uniform.second, false);
        }

        for (auto const& mat4Uniform : *drawCachedMat4Uniforms)
        {
            setMat4(mat4Uniform.first, mat4Uniform.second, false);
        }

        for (auto const& mat3Uniform : *drawCachedMat3Uniforms)
        {
            setMat3(mat3Uniform.first, mat3Uniform.second, false);
        }

        for (auto const& mat3Uniform : *drawCachedMat3Uniforms)
        {
            setMat3(mat3Uniform.first, mat3Uniform.second, false);
        }

        for (auto const& vec2Uniform : *drawCachedVec2Uniforms)
        {
            setVec2(vec2Uniform.first, vec2Uniform.second, false);
        }

        for (auto const& floatUniform : *drawCachedFloatUniforms)
        {
            setInt(floatUniform.first, floatUniform.second, false);
        }

        for (auto const& intUniform : *drawCachedIntUniforms)
        {
            setInt(intUniform.first, intUniform.second, false);
        }

        for (auto const& boolUniform : *drawCachedBoolUniforms)
        {
            setBool(boolUniform.first, boolUniform.second, false);
        }

        for (auto const& vec4Uniform : *drawCachedVec4Uniforms)
        {
            setVec4(vec4Uniform.first, vec4Uniform.second, false);
        }

        for (auto const& vec3Uniform : *drawCachedVec3Uniforms)
        {
            setVec3(vec3Uniform.first, vec3Uniform.second, false);
        }

        for (auto const& vec3Uniform : *drawCachedVec3Uniforms_pointerValue)
        {
            setVec3_pointerValue(vec3Uniform.first, vec3Uniform.second, false);
        }
    }

public:
    ShaderDrawer(const char* vertexShaderPath, const char* fragmentShaderPath, unsigned int &VAO, unsigned int &VBO) :
        trianglesNumber(0),
        currentAttribElemSize(0),
        VBO(VBO),
        VAO(VAO)
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

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
       
        drawCachedBoolUniforms = new std::map<std::string, bool>();
        drawCachedIntUniforms = new std::map<std::string, int>();
        drawCachedFloatUniforms = new std::map<std::string, float>();
        drawCachedVec2Uniforms = new std::map<std::string, glm::vec2>();
        drawCachedVec3Uniforms = new std::map<std::string, glm::vec3>();
        drawCachedVec3Uniforms_pointerValue = new std::map<std::string, glm::vec3*>();
        drawCachedVec4Uniforms = new std::map<std::string, glm::vec4>();
        drawCachedMat2Uniforms = new std::map<std::string, glm::mat2> ();
        drawCachedMat3Uniforms = new std::map<std::string, glm::mat3>();
        drawCachedMat4Uniforms = new std::map<std::string, glm::mat4>();
        

    };

    unsigned int getVBO() {
        return VBO;
    }


    unsigned int getVAO() {
        return VAO;
    }


    void setTrianglesNumber(unsigned int trianglesNumber) {
        this->trianglesNumber = trianglesNumber;
    }
    virtual void transferTriangles(float* vertices, int vertices_sizeof, int singleVerticleElemsNum, int singleVerticleDataElemsNum) = 0;
    virtual void drawShape(int shapeIdx) = 0;
    virtual void drawAllShapes() = 0;
    virtual void drawAllTriangles() = 0;
    ~ShaderDrawer() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgramId);


        delete drawCachedBoolUniforms;
        delete drawCachedIntUniforms;
        delete drawCachedFloatUniforms;
        delete drawCachedVec2Uniforms;
        delete drawCachedVec3Uniforms;
        delete drawCachedVec4Uniforms;
        delete drawCachedMat2Uniforms;
        delete drawCachedMat3Uniforms;
        delete drawCachedMat4Uniforms;
    }

    void setVertexAttribPointer(int attribId, int elemSize, int attribOffset) {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(attribId, elemSize, GL_FLOAT, GL_FALSE, currentAttribElemSize * sizeof(float), (void*)(attribOffset * sizeof(float)));
        glEnableVertexAttribArray(attribId);
    }

    void setCurrentAttribElemSize(unsigned int currentAttribElemSize) {
        this->currentAttribElemSize = currentAttribElemSize;
    }

    int getCurrentAttribElemSize() {
        return this->currentAttribElemSize;
    }

    //uniform setters

    void setBool(const std::string& name, bool value, bool drawCache = false) const
    {
        if (drawCache) {
            this->drawCachedBoolUniforms->insert({ name, value });
        }
        glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value, bool drawCache = false) const
    {
        if (drawCache) {
            this->drawCachedIntUniforms->insert({ name, value });
        }
        glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value, bool drawCache = false) const
    {
        if (drawCache) {
            this->drawCachedFloatUniforms->insert({ name, value });
        }
        glUniform1f(glGetUniformLocation(shaderProgramId, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const glm::vec2& value, bool drawCache = false) const
    {
        if (drawCache) {
            this->drawCachedVec2Uniforms->insert({ name, value });
        }
        glUniform2fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(shaderProgramId, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value, bool drawCache = false) const
    {
        if (drawCache) {
            this->drawCachedVec3Uniforms->insert({ name, value });
        }
        glUniform3fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, &value[0]);
    }

    void setVec3_pointerValue(const std::string& name, glm::vec3* value, bool drawCache = false) const
    //risky, pointer to value may be deleted and ShaderDrawer class cannnot reconize that
    {
        if (drawCache) {
            this->drawCachedVec3Uniforms_pointerValue->insert({ name, value });
        }
        glUniform3fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, glm::value_ptr(*value));
    }


    void setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(shaderProgramId, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value, bool drawCache = false) const
    {
        if (drawCache) {
            this->drawCachedVec4Uniforms->insert({ name, value });
        }
        glUniform4fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string& name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(shaderProgramId, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat, bool drawCache = false) const
    {
        if (drawCache) {
            this->drawCachedMat2Uniforms->insert({ name, mat });
        }
        glUniformMatrix2fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat, bool drawCache = true) const
    {
        if (drawCache) {
            this->drawCachedMat3Uniforms->insert({ name, mat });
        }
        glUniformMatrix3fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat, bool drawCache = true) const
    {
        if (drawCache) {
            this->drawCachedMat3Uniforms->insert({ name, mat });
        }
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

};