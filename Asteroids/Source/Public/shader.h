#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

/*Custom Library*/
#include "shader_resource.h"

/*
=====================================

SHADER

=====================================
*/

class Shader
{
public:
	Shader						(void);
	Shader						(const std::string& vertexSource, const std::string& fragmentSource);
	~Shader						(void);

	bool compile				(const std::string& vertexSource, const std::string& fragmentSource);
	void bind					(void) const;

	void setFloat				(const std::string& uniform, GLfloat value);
	void setInteger				(const std::string& uniform, GLint value);
	void setVector2f			(const std::string& uniform, glm::vec2 value);
	void setVector3f			(const std::string& uniform, glm::vec3 value);
	void setVector4f			(const std::string& uniform, glm::vec4 value);
	void setMatrix4				(const std::string& uniform, glm::mat4 value);

private:
	GLuint compileShader		(const std::string& source, GLuint type);
	bool linkProgram			(void);

	GLuint	_program;
};

std::string shaderToString(GLuint type);