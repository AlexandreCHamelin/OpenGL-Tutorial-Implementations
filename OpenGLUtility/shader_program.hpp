#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include "gl_includes.hpp"
#include "shader.hpp"

enum eProgramMode
{
	VERT_FRAG,
	VERT_FRAG_TESS,
	VERT_FRAG_GEOM,
	VERT_FRAG_TESS_GEOM,
};

class ShaderProgram
{
public:
	ShaderProgram(Shader shaders[], eProgramMode mode);
	GLuint get_program();
	~ShaderProgram();
private:
	void linkShaders();

	const GLuint program_;
	const eProgramMode mode_;

	Shader* vertex_shader_;
	Shader* fragment_shader_;
	Shader* geometry_shader_;
	Shader* tesselation_shader_;
};

#endif