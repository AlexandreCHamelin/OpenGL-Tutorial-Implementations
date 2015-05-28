#include "main.hpp"
#include "gl_includes.hpp"
#include "shader.hpp"
#include "shader_program.hpp"
#include <stdio.h>

void initTriangles();
void glfwErrorCallback(int error, const char* description);
void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);
void logGlParams();
void updateFpsCounter(GLFWwindow* window);

GLuint vao_1 = 0;
GLuint vbo_1 = 0;
GLuint vao_2 = 0;
GLuint vbo_2 = 0;

int g_gl_width = 800;
int g_gl_height = 600;

double previous_seconds;
int  frame_count;

int main(int argc, char *argv[])
{
	//start context
	if (!glfwInit())
	{
		fprintf(stderr, "Error, could not start GLFW3\n");
		return 1;
	}
	else
	{
		fprintf(stderr, "GLFW initialized properly.");
	}

	//Forward compatibility from version 3.2.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4); //Anti aliasing (4 passes)
	
	//start logs
	Logger::restartLog(GL_LOG_FILE);
	glfwSetErrorCallback(glfwErrorCallback);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	//init window with primary monitor resolution
	//Set these modes for a fullscreen window and don't for classic fullscreen:
	/*glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);*/
	//------------------------------------------------

	//GLFWwindow * window = glfwCreateWindow(mode->width, mode->height, "Tutorial 1: Draw a triangle", monitor, NULL); //Fullscreen
	GLFWwindow * window = glfwCreateWindow(800, 600, "Tutorial 1: Draw a triangle", NULL, NULL); //Not Fullscreen

	//if window initialisation failed
	if (!window)
	{
		fprintf(stderr, "Could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);

	//start glew extension handler;
	glewExperimental = GL_TRUE;
	glewInit();

	//get version info
	const GLubyte * renderer = glGetString(GL_RENDERER);
	const GLubyte * version = glGetString(GL_VERSION);

	//Log informations
	Logger::printToLog(GL_LOG_FILE, "Starting GLFW: %s \n", glfwGetVersionString());
	logGlParams();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//draw triangle
	initTriangles();

	Shader vertex = Shader("vertex.vert", GL_VERTEX_SHADER);
	Shader frag_1 = Shader("frag1.frag", GL_FRAGMENT_SHADER);
	Shader frag_2 = Shader("frag2.frag", GL_FRAGMENT_SHADER);

	Shader shaders_1[2] = { vertex, frag_1 };
	Shader shaders_2[2] = { vertex, frag_2 };

	ShaderProgram shader_programme_1 = ShaderProgram(shaders_1, VERT_FRAG);
	ShaderProgram shader_programme_2 = ShaderProgram(shaders_2, VERT_FRAG);

	while (!glfwWindowShouldClose(window)) {
		updateFpsCounter(window);

		// wipe the drawing surface clear 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, g_gl_width, g_gl_height);

		glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

		glUseProgram(shader_programme_1.get_program());
		glBindVertexArray(vao_1);

		// draw points 0-5 from the currently bound VAO with current in-use shader 
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glUseProgram(shader_programme_2.get_program());
		glBindVertexArray(vao_2);

		// draw points 0-5 from the currently bound VAO with current in-use shader 
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display 
		glfwSwapBuffers(window);

		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) 
		{
			glfwSetWindowShouldClose(window, 1);
		}
	}

	//close gl context and other glfw resources
	glfwTerminate();

	return 0;
}

void initTriangles()
{
	GLfloat points_1[] =
	{
		0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
	    0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	glGenBuffers(1, &vbo_1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points_1), points_1, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao_1);
	glBindVertexArray(vao_1);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	GLfloat points_2[] =
	{
		0.5f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.5f, 0.0f
	};

	glGenBuffers(1, &vbo_2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points_2), points_2, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao_2);
	glBindVertexArray(vao_2);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

//Log errors
void glfwErrorCallback(int error, const char* description)
{
	Logger::printToLog(GL_LOG_FILE, "GLFW ERROR: code %i msg: %s \n", error, description);
}

//Track window resize
void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	g_gl_width = width;
	g_gl_height = height;

	//update stuff here...
}

void logGlParams() {
	GLenum params[] =
	{
		GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		GL_MAX_CUBE_MAP_TEXTURE_SIZE,
		GL_MAX_DRAW_BUFFERS,
		GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
		GL_MAX_TEXTURE_IMAGE_UNITS,
		GL_MAX_TEXTURE_SIZE,
		GL_MAX_VARYING_FLOATS,
		GL_MAX_VERTEX_ATTRIBS,
		GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		GL_MAX_VERTEX_UNIFORM_COMPONENTS,
		GL_MAX_VIEWPORT_DIMS, GL_STEREO,
	};
	const char* names[] =
	{
		"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
		"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
		"GL_MAX_DRAW_BUFFERS",
		"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
		"GL_MAX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_TEXTURE_SIZE",
		"GL_MAX_VARYING_FLOATS",
		"GL_MAX_VERTEX_ATTRIBS",
		"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
		"GL_MAX_VIEWPORT_DIMS",
		"GL_STEREO",
	};

	Logger::printToLog(GL_LOG_FILE, "GL Context Params: \n");
	// integers - only works if the order is 0-10 integer return types 
	for (int i = 0; i < 10; i++)
	{
		int v = 0;
		glGetIntegerv(params[i], &v); 
		Logger::printToLog(GL_LOG_FILE, "%s %i \n", names[i], v);
	}
	// others 
	int v[2]; v[0] = v[1] = 0;
	glGetIntegerv(params[10], v);
	Logger::printToLog(GL_LOG_FILE, "%s %i %i \n", names[10], v[0], v[1]);
	unsigned char s = 0; glGetBooleanv(params[11], &s);
	Logger::printToLog(GL_LOG_FILE, "%s %u \n", names[11], (unsigned int)s);
	Logger::printToLog(GL_LOG_FILE, "-----------------------------\n");
}

void updateFpsCounter(GLFWwindow* window)
{
	double current_seconds;
	double elapsed_seconds;

	current_seconds = glfwGetTime();
	elapsed_seconds = current_seconds - previous_seconds;

	/*Limit text updates to 4 per second*/
	if (elapsed_seconds > 0.25)
	{
		previous_seconds = current_seconds;
		char tmp[128];
		double fps = (double)frame_count / elapsed_seconds;
		sprintf_s(tmp, "Tutorial 1: Draw a triangle - fps: %.2f", fps);
		glfwSetWindowTitle(window, tmp);
		frame_count = 0;
	}

	frame_count++;
}