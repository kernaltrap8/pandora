#include "Pandora.hpp"

const char *vertexShaderSource;
const char *fragmentShaderSource;

namespace Core {
namespace GL {
  std::string readShaderSource(const std::string& filename) {
    std::ifstream Shader(filename);
    if (!Shader) {
        throw std::runtime_error("Failed to open shader source: " + filename);
    }

    std::ostringstream shaderBuffer;
    shaderBuffer << Shader.rdbuf();
    std::string shaderSource = shaderBuffer.str();

    std::cout << "Shader Source:\n" << shaderSource << std::endl;

    return shaderSource;
}
GLuint compileShader(GLenum type, const char *source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);
  // Check for compilation errors
  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    char *log = new char[length];
    glGetShaderInfoLog(shader, length, nullptr, log);
    std::cerr << "Shader compilation error: " << log << "\n";
    delete[] log;
  }
  return shader;
}
GLuint createShaderProgram() {
  std::string vertexShaderPath = readShaderSource("../src/shaders/vertexshader.glsl");
  vertexShaderSource = vertexShaderPath.c_str();
  std::string fragmentShaderPath = readShaderSource("../src/shaders/fragmentshader.glsl");
  fragmentShaderSource = fragmentShaderPath.c_str();
  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
  GLuint fragmentShader =
      compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}
} // namespace GL
}