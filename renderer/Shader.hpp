#ifndef SJ_SHADER_H
#define SJ_SHADER_H
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>

namespace sj
{
    class ShaderFile
    {
    public:
        ShaderFile(const std::string& vsFile, const std::string& fsFile);
        ~ShaderFile();
        
        void bind() const;
        void unbind() const;

        unsigned int shaderID() const;

    private:
        unsigned int shaderProgram;

        std::string vsFilePath, fsFilePath;

    private:
        std::pair<std::string, std::string> parseShader();

        unsigned int compileShader(int s_type, const std::string& source);
    };

    class ShaderSource
    {
    public:
        ShaderSource(const std::string& vsSource, const std::string& fsSource);
    };
}

#endif