#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLFunctions_4_1_Core>

//#include "GL/glew.h" //We use QOpenGLFunctions instead, so no need for Glew (or GLAD)!

//This class is pretty much a copy of the shader class at
//https://github.com/SonarSystems/Modern-OpenGL-Tutorials/blob/master/%5BLIGHTING%5D/%5B8%5D%20Basic%20Lighting/Shader.h
//which is based on stuff from http://learnopengl.com/ and http://open.gl/.

//must inherit from QOpenGLFunctions_4_1_Core, since we use that instead of glfw/glew/glad
class Shader : protected QOpenGLFunctions_4_1_Core
{
public:
    // Constructor generates the shader on the fly
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

    ///Use the current shader
    void use( );

    ///Returns the program number for this shader
    GLuint getProgram() const;
    void SetUniformMatrix4fv(QMatrix4x4 matrix, std::string name);
    void SetUniform3f(GLfloat v1, GLfloat v2, GLfloat v3, std::string name);
    void SetUniform1f(GLfloat v1, std::string name);
    void SetUniform1i(GLint v1, std::string name);
private:
    ///The int OpenGL gives as a reference to this shader
    GLuint mProgram;

    ///The logger - Output Log in the application
    class Logger *mLogger{nullptr};
};

#endif
