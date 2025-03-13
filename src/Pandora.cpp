// Pandora Game Engine - Main CPP File
// Copyright (C) 2025 kernaltrap8
// This program is licensed under the BSD-3 Clause license.
// This file is a portion from the Pandora game engine.

/*
        pandora.cpp
*/

#include "Pandora.hpp"

GLuint VBO, VAO, shaderProgram;
float triangleColor[3] = {0.0f, 0.0f, 0.0f};
bool enableVerboseLogging = false;
SDL_GLContext glContext;
SDL_Window *window;

namespace Core {
namespace SDL {
auto InitSDL(void) -> int {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Could not initialize SDL: " << SDL_GetError() << "\n";
    return 1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  window = SDL_CreateWindow("Pandora", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 800, 600,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Could not create window: " << SDL_GetError() << "\n";
    SDL_Quit();
    return 1;
  }

  glContext = SDL_GL_CreateContext(window);
  if (!glContext) {
    std::cerr << "Could not create OpenGL context: " << SDL_GetError() << "\n";
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_GL_SetSwapInterval(1);
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "Could not initialize GLEW: " << glewGetErrorString(err)
              << "\n";
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  return 0;
}
auto Cleanup(void) -> void {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
} // namespace SDL

namespace Pandora {
auto setClearColorFromRGBA(unsigned char r, unsigned char g, unsigned char b,
                           unsigned char a) -> void {
  glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
auto SetupTriangle() -> void {
  // Vertex data for a triangle
  float vertices[] = {
      // Positions
      0.0f,  0.5f,  0.0f, // Top vertex
      -0.5f, -0.5f, 0.0f, // Bottom left vertex
      0.5f,  -0.5f, 0.0f  // Bottom right vertex
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
  glBindVertexArray(0);             // Unbind VAO
}
} // namespace Pandora
} // namespace Core

auto main(int argc, char *argv[]) -> int {
  if (argc > 1) {
    if (!std::strcmp(argv[1], "-v")) {
      enableVerboseLogging = true;
    }
  }

  if (Core::SDL::InitSDL() != 0) {
    return 1; // Quit if initialization fails
  }

  if (enableVerboseLogging) {
    const GLubyte *version = glGetString(GL_VERSION);
    std::cout << "Using OpenGL version "
              << (version ? reinterpret_cast<const char *>(version) : "Unknown")
              << '\n';
  }

  shaderProgram = Core::GL::createShaderProgram();
  Core::Pandora::SetupTriangle();

  // Main loop
  int running = 1;
  SDL_Event event;

  while (running) {
    Core::Pandora::setClearColorFromRGBA(196, 94, 255, 255); // Set the clear color
    glClear(GL_COLOR_BUFFER_BIT);             // Clear the screen

    // Use the shader program and set the triangle color
    glUseProgram(shaderProgram);
    glUniform3f(glGetUniformLocation(shaderProgram, "triangleColor"),
                triangleColor[0], triangleColor[1], triangleColor[2]);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle
    glBindVertexArray(0);             // Unbind VAO

    SDL_GL_SwapWindow(window);

    // Event handling
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        running = 0;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          running = 0;
        } else if (event.key.keysym.sym == SDLK_1) {
          triangleColor[0] = 1.0f; // Red
          triangleColor[1] = 0.0f; // Green
          triangleColor[2] = 0.0f; // Blue
        } else if (event.key.keysym.sym == SDLK_2) {
          triangleColor[0] = 0.0f; // Red
          triangleColor[1] = 1.0f; // Green
          triangleColor[2] = 0.0f; // Blue
        } else if (event.key.keysym.sym == SDLK_3) {
          triangleColor[0] = 0.0f; // Red
          triangleColor[1] = 0.0f; // Green
          triangleColor[2] = 1.0f; // Blue
        }
        break;
      }
    }
  }

  Core::SDL::Cleanup();

  return 0;
}
