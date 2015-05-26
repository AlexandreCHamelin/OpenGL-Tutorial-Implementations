#include "main.hpp"

//opengl includes
#define GLEW_STATIC
#include <GL/glew.h>
#define GL_GLEXT_PROTOTYPES

#include <GLFW/glfw3.h>
#include <stdio.h>
#include "logger.hpp"

void initTriangles();
void glfw_error_callback(int error, const char* description);

GLuint vao1 = 0;
GLuint vbo1 = 0;
GLuint vao2 = 0;
GLuint vbo2 = 0;

int main(int argc, char *argv[])
{
	//start logs
	Logger::restart_log("log.txt");
	std::string log = "Starting GLFW: \n";
	log += glfwGetVersionString();
	log += "\n";
	Logger::print_to_log("log.txt", log);
	glfwSetErrorCallback(glfw_error_callback);

	//start context
	if (!glfwInit())
	{
		fprintf(stderr, "Error, could not start GLFW3\n");
		return 1;
	}
	
	//init window with 640x480 resolution
	GLFWwindow * window = glfwCreateWindow(640, 480, "Tutorial 1: Draw a triangle", NULL, NULL);

	//if window initialisation failed
	if (!window)
	{
		fprintf(stderr, "Could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	//start glew extension handler;
	glewExperimental = GL_TRUE;
	glewInit();

	//get version info
	const GLubyte * renderer = glGetString(GL_RENDERER);
	const GLubyte * version = glGetString(GL_VERSION);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//draw triangle
	initTriangles();

	const char* vertex_shader =
		"# version 410\n" 
		"in vec3 vp;"
		"void main () {"
		" gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader1 =
		"# version 410\n"
		"out vec4 frag_colour;"
		"void main () {"
		" frag_colour = vec4 (0.5, 0.5, 0.5, 1.0);"
		"}";

	const char* fragment_shader2 =
		"# version 410\n"
		"out vec4 frag_colour;"
		"void main () {"
		" frag_colour = vec4 (0.5, 0.0, 0.0, 1.0);"
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	GLuint fs1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs1, 1, &fragment_shader1, NULL);
	glCompileShader(fs1);

	GLuint fs2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs2, 1, &fragment_shader2, NULL);
	glCompileShader(fs2);

	GLuint shader_programme1 = glCreateProgram();
	glAttachShader(shader_programme1, fs1);
	glAttachShader(shader_programme1, vs);
	glLinkProgram(shader_programme1);

	GLuint shader_programme2 = glCreateProgram();
	glAttachShader(shader_programme2, fs2);
	glAttachShader(shader_programme2, vs);
	glLinkProgram(shader_programme2);

	while (!glfwWindowShouldClose(window)) {
		// wipe the drawing surface clear 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

		glUseProgram(shader_programme1);
		glBindVertexArray(vao1);

		// draw points 0-5 from the currently bound VAO with current in-use shader 
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glUseProgram(shader_programme2);
		glBindVertexArray(vao2);

		// draw points 0-5 from the currently bound VAO with current in-use shader 
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display 
		glfwSwapBuffers(window);
	}

	//close gl context and other glfw resources
	glfwTerminate();

	return 0;
}

void initTriangles()
{
	GLfloat points1[] =
	{
		0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
	    0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	glGenBuffers(1, &vbo1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points1), points1, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao1);
	glBindVertexArray(vao1);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	GLfloat points2[] =
	{
		0.5f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.5f, 0.0f
	};

	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points2), points2, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

//Log errors
void glfw_error_callback(int error, const char* description)
{
	std::string errorText = "GLFW ERROR: code ";
	errorText += std::to_string(error);
	errorText += " msg: ";
	errorText += description;
	errorText += "\n";

	Logger::print_to_log("log.txt", errorText);
}