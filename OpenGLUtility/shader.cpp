#include "shader.hpp"
#include <fstream>
#include <sstream>

#ifndef SHADERS_DIRECTORY
#define SHADERS_DIRECTORY "data/shaders/"
#endif

Shader::Shader(std::string shaderFile, GLenum shaderType) :
	shaderFile_(SHADERS_DIRECTORY + shaderFile),
	shader_(glCreateShader(shaderType)),
	shader_type_(shaderType)
{
	if (loadShaderFile())
	{
		glCompileShader(shader_);
		logShaderCompilation();
	}
}

bool Shader::loadShaderFile() const
{
	std::ifstream source_ifstream(shaderFile_, std::ifstream::in);

	if (source_ifstream.is_open())
	{
		std::stringstream source_sstream;
		source_sstream << source_ifstream.rdbuf();

		std::string source_s = source_sstream.str();
		const char * shader_source = source_s.c_str();

		glShaderSource(shader_, 1, &shader_source, 0);
		source_ifstream.close();
		return true;
	}
	else
	{
		Logger::printToLog(GL_LOG_FILE, "Failed to open %s (shader file)\n", shaderFile_);
		source_ifstream.close();
		return false;
	}
}

GLuint Shader::get_shader() const
{
	return shader_;
}
GLuint Shader::get_shader_type() const
{
	return shader_type_;
}

void Shader::logShaderCompilation() const
{
	GLint status;
	glGetShaderiv(shader_, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint errorMsgLength;
		glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &errorMsgLength);
		GLchar *errorMsg = new GLchar[errorMsgLength + 1];
		glGetShaderInfoLog(shader_, errorMsgLength, NULL, errorMsg);

		Logger::printToLog(GL_LOG_FILE, "Compilation failure in: %s shader:\n %s", shader_, errorMsg);

		delete[] errorMsg;
	}
}