#pragma once

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define GLAB_LOAD_GL()
#else
#include <glad/glad.h>
#define GLAB_LOAD_GL() gladLoadGL()
#endif

// Limit OpenGL usage to version 4.1 or below to ensure compatibility with macOS
#define GLAB_GL_MAJOR 4
#define GLAB_GL_MINOR 1

#define GLAB_GLSL_VERSION "#version 410 core"
