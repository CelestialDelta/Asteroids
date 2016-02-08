#include "..\Public\shader.h"

Shader::Shader(void)
	: _program(0)
{
}

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
	: _program(0)
{
	compile(vertexSource, fragmentSource);
}

Shader::~Shader(void)
{
	if (_program)
	{
		glDeleteProgram(_program);
	}
}

bool Shader::compile(const std::string& vertexSource, const std::string& fragmentSource)
{
	_program = glCreateProgram();
	GLuint vertex = compileShader(vertexSource, GL_VERTEX_SHADER);
	GLuint fragment = compileShader(fragmentSource, GL_FRAGMENT_SHADER);
	if (vertex && fragment)
	{
		glAttachShader(_program, vertex);
		glAttachShader(_program, fragment);
		//glAttachShader(_program, vertex | fragment);
		if (linkProgram())
		{
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			return true;
		}
	}
	return false;
}

void Shader::bind(void) const
{
	glUseProgram(_program);
}

GLuint Shader::compileShader(const std::string& source, GLuint type)
{
	GLuint shader = glCreateShader(type);
	const GLchar* cSource = source.c_str();
	glShaderSource(shader, 1, &cSource, NULL);
	glCompileShader(shader);

	GLint success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Failed to compile " << shaderToString(type) << " shader:\n"
			<< infoLog << std::endl;
		return 0;
	}
	else
	{
		return shader;
	}
}

bool Shader::linkProgram(void)
{
	glLinkProgram(_program);

	GLint success;
	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(_program, 512, NULL, infoLog);
		std::cout << "Failed to link shader program:\n" 
			<< infoLog << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}

void Shader::setFloat(const std::string& uniform, GLfloat value)
{
	glUniform1f(glGetUniformLocation(_program, uniform.c_str()), value);
}

void Shader::setInteger(const std::string& uniform, GLint value)
{
	glUniform1i(glGetUniformLocation(_program, uniform.c_str()), value);
}

void Shader::setVector2f(const std::string& uniform, glm::vec2 value)
{
	glUniform2f(glGetUniformLocation(_program, uniform.c_str()), value.x, value.y);
}

void Shader::setVector3f(const std::string& uniform, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(_program, uniform.c_str()), value.x, value.y, value.z);
}

void Shader::setVector4f(const std::string& uniform, glm::vec4 value)
{
	glUniform4f(glGetUniformLocation(_program, uniform.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const std::string& uniform, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(_program, uniform.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

std::string shaderToString(GLuint type)
{
	switch (type)
	{
	case GL_VERTEX_SHADER:
		return "Vertex";
	case GL_FRAGMENT_SHADER:
		return "Fragment";
	default:
		return "NULL";
	}
}