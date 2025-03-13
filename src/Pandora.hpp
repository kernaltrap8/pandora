// pandora Copyright (C) 2025 kernaltrap8
// This program comes with ABSOLUTELY NO WARRANTY
// This is free software, and you are welcome to redistribute it
// under certain conditions
// This file is a portion from the Pandora game engine.

/*
        pandora.hpp
*/
#ifndef PANDORA_HPP
#define PANDORA_HPP
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

namespace Core {
    namespace GL {
        GLuint compileShader(GLenum type, const char *source);
        GLuint createShaderProgram();
    }
    namespace SDL {
    }
}
#endif