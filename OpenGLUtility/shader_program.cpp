#include "shader_program.hpp"

ShaderProgram::ShaderProgram(Shader shaders[], eProgramMode mode) :
	program_(glCreateProgram()),
	mode_(mode)
{
	try
	{
		vertex_shader_ = new Shader(shaders[0]);
		fragment_shader_ = new Shader(shaders[1]);

		switch (mode_)
		{
		case VERT_FRAG:
			tesselation_shader_ = NULL;
			geometry_shader_ = NULL;
			break;
		case VERT_FRAG_GEOM:
			tesselation_shader_ = NULL;
			geometry_shader_ = new Shader(shaders[2]);
			break;
		case VERT_FRAG_TESS:
			tesselation_shader_ = new Shader(shaders[2]);
			geometry_shader_ = NULL;
			break;
		case VERT_FRAG_TESS_GEOM:
			tesselation_shader_ = new Shader(shaders[2]);
			geometry_shader_ = new Shader(shaders[3]);
			break;
		}

		linkShaders();
	}
	catch (int exception)
	{
		Logger::printToLog(GL_LOG_FILE,
			"EXCEPTION: The following exception was encountered in the creation of a ShaderProgram object: %i \n",
			exception);
	}
}

GLuint ShaderProgram::get_program()
{
	return program_;
}

ShaderProgram::~ShaderProgram()
{
	delete vertex_shader_;
	delete fragment_shader_;
	delete geometry_shader_;
	delete tesselation_shader_;
}

void ShaderProgram::linkShaders()
{
	glAttachShader(program_, vertex_shader_->get_shader());

	switch (mode_)
	{
	case VERT_FRAG:
		break;
	case VERT_FRAG_TESS:
		glAttachShader(program_, geometry_shader_->get_shader());
		break;
	case VERT_FRAG_GEOM:
		glAttachShader(program_, tesselation_shader_->get_shader());
		break;
	case VERT_FRAG_TESS_GEOM:
		glAttachShader(program_, geometry_shader_->get_shader());
		glAttachShader(program_, tesselation_shader_->get_shader());
		break;
	}

	glAttachShader(program_, fragment_shader_->get_shader());

	glLinkProgram(program_);
}