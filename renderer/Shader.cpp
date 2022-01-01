#include "Shader.hpp"
#include <iostream>

namespace sj
{
    ShaderFile::ShaderFile(const std::string& vsFile, const std::string& fsFile)
        : vsFilePath(vsFile), fsFilePath(fsFile), shaderProgram(0)
    {
        auto shaderSource = parseShader();
        shaderProgram = glCreateProgram();
        unsigned int vsID = compileShader(GL_VERTEX_SHADER, shaderSource.first);
        unsigned int fsID = compileShader(GL_FRAGMENT_SHADER, shaderSource.second);
        glAttachShader(shaderProgram, vsID);
        glAttachShader(shaderProgram, fsID);
        glValidateProgram(shaderProgram);
        glLinkProgram(shaderProgram);
        glDeleteShader(vsID);
        glDeleteShader(fsID);
    }

    ShaderFile::~ShaderFile()
    {
        glDeleteShader(shaderProgram);
    }

    std::pair<std::string, std::string> ShaderFile::parseShader()
    {
        std::stringstream vsSS, fsSS;
        std::string line;

        std::ifstream vsStream(vsFilePath);
        while(std::getline(vsStream, line))
            vsSS << line << "\n";
        vsStream.close();

        std::ifstream fsStream(fsFilePath);
        while(std::getline(fsStream, line))
            fsSS << line << "\n";
        fsStream.close();

        return std::make_pair(vsSS.str(), fsSS.str());
    }

    unsigned int ShaderFile::compileShader(int s_type, const std::string& source)
    {
        unsigned int shaderID = glCreateShader(s_type);
        const char* source_c = source.c_str();
        glShaderSource(shaderID, 1, &source_c, nullptr);
        glCompileShader(shaderID);
        int shaderResult, shaderInfoLength;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderResult);
        if (shaderResult == GL_FALSE)
        {
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &shaderInfoLength);
            char* info_m = (char*)alloca(sizeof(char) * shaderInfoLength);
            glGetShaderInfoLog(shaderID, shaderInfoLength, &shaderInfoLength, info_m);
            std::cout << "Failed to compile" << ((s_type == GL_VERTEX_SHADER) ? " vertex" : " fragment") << " shader" << std::endl;
            std::cout << info_m << std::endl;
            glDeleteShader(shaderID);
        }
        return shaderID;
    }

    void ShaderFile::bind() const 
    {
        glUseProgram(shaderProgram);
    }

    void ShaderFile::unbind() const
    {
        glUseProgram(0);
    }

    unsigned int ShaderFile::shaderID() const
    {
        return shaderProgram;
    }
}