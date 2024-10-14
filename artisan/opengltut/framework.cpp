#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <string.h>
#include "framework.h"
#include "directories.h"

#ifndef _WIN32
#define APIENTRY
#endif

namespace framework
{

	GLuint CompileShader(GLenum shaderType, const char* source) {
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);
	
		// Check for shader compile errors
		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
			exit(-1);
		}
	
		return shader;
	}

	GLuint LinkProgram(GLuint program, const std::vector<GLuint>& shaderList) {
		for (GLuint shader : shaderList) {
			glAttachShader(program, shader);
		}
	
		glLinkProgram(program);
	
		// Check for linking errors
		GLint success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			throw std::runtime_error("Shader program linking failed");
		}
	
		for (GLuint shader : shaderList) {
			glDetachShader(program, shader);
		}
	
		return program;
	}

	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
	{
		std::string strFilename = FindFileOrThrow(strShaderFilename);
		std::ifstream shaderFile(strFilename.c_str());
		std::stringstream shaderData;
		shaderData << shaderFile.rdbuf();
		shaderFile.close();

		try
		{
			return CompileShader(eShaderType, shaderData.str());
		}
		catch(std::exception &e)
		{
			fprintf(stderr, "%s\n", e.what());
			throw;
		}
	}

	GLuint CreateProgram(const std::vector<GLuint> &shaderList)
	{
		try
		{
			GLuint prog = LinkProgram(glCreateProgram(), shaderList);
			std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
			return prog;
		}
		catch(std::exception &e)
		{
			std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
			fprintf(stderr, "%s\n", e.what());
			throw;
		}
	}

	float DegToRad(float fAngDeg)
	{
		const float fDegToRad = 3.14159f * 2.0f / 360.0f;
		return fAngDeg * fDegToRad;
	}

	std::string FindFileOrThrow( const std::string &strBasename )
	{
		std::string strFilename = LOCAL_FILE_DIR + strBasename;
		std::ifstream testFile(strFilename.c_str());
		if(testFile.is_open())
			return strFilename;

		
		strFilename = GLOBAL_FILE_DIR + strBasename;
		testFile.open(strFilename.c_str());
		if(testFile.is_open())
			return strFilename;

		throw std::runtime_error("Could not find the file " + strBasename);
	}
}


void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

unsigned int defaults(unsigned int displayMode, int &width, int &height);

void APIENTRY DebugFunc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
			   const GLchar* message, const GLvoid* userParam)
{
	std::string srcName;
	switch(source)
	{
	case GL_DEBUG_SOURCE_API_ARB: srcName = "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB: srcName = "Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: srcName = "Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY_ARB: srcName = "Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION_ARB: srcName = "Application"; break;
	case GL_DEBUG_SOURCE_OTHER_ARB: srcName = "Other"; break;
	}

	std::string errorType;
	switch(type)
	{
	case GL_DEBUG_TYPE_ERROR_ARB: errorType = "Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: errorType = "Deprecated Functionality"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB: errorType = "Undefined Behavior"; break;
	case GL_DEBUG_TYPE_PORTABILITY_ARB: errorType = "Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE_ARB: errorType = "Performance"; break;
	case GL_DEBUG_TYPE_OTHER_ARB: errorType = "Other"; break;
	}

	std::string typeSeverity;
	switch(severity)
	{
	case GL_DEBUG_SEVERITY_HIGH_ARB: typeSeverity = "High"; break;
	case GL_DEBUG_SEVERITY_MEDIUM_ARB: typeSeverity = "Medium"; break;
	case GL_DEBUG_SEVERITY_LOW_ARB: typeSeverity = "Low"; break;
	}

	printf("%s from %s,\t%s priority\nMessage: %s\n",
		errorType.c_str(), srcName.c_str(), typeSeverity.c_str(), message);
}

int main(int argc, char** argv)
{
	int width = 500;
	int height = 500;


	GLFWwindow* window;

	// glfwSetErrorCallback(error_callback); // TODO specify error_callback

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(width, height, "Tutorial", NULL, NULL);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// glfwSetKeyCallback(window, key_callback); // TODO specify key_callback
	
	glfwMakeContextCurrent(window);

	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

	init(); //TODO, get frum tut

	while (!glfwWindowShouldClose(window)) {
			display(); //TODO, get from tut
			glfwPollEvents();
	}



	return 0;
}

