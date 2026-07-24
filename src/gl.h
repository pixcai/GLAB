#pragma once

#include <glad/glad.h>

// Always use OpenGL 4.x. Do not change this
#define GLAB_GL_MAJOR 4

#if defined(__APPLE__)
// Due to macOS limitations, OpenGL is supported only up to version 4.1
#    define GLAB_GL_MINOR 1
#    define GLAB_GLSL_VERSION "#version 410 core"
#else
// Unlike macOS, recent versions of Windows and Linux
// generally support the latest available OpenGL version
#    define GLAB_GL_MINOR 6
#    define GLAB_GLSL_VERSION "#version 460 core"
#endif
