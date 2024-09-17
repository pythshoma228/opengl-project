#pragma once
#include <GL/glew.h>
#include <fstream>
#include <sstream>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};


ShaderProgramSource parseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    if(!stream.is_open()) std::cout << "error";
    
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream,line)) {
        if(line.find("#shader") != std::string::npos) {
            if(line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}


unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS,&result);
    if(result == GL_FALSE) {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char message[length];
        glGetShaderInfoLog(id,length,&length,message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << "\n";
        std::cout << message << "\n";
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);

    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;

}