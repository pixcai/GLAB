#pragma once

#include <filesystem>
#include <string_view>

#include <glm/glm.hpp>

namespace glab::config {

inline constexpr int kGLVersionMajor = 4;
#if defined(__APPLE__)
// Due to macOS limitations, OpenGL is supported only up to version 4.1
inline constexpr int kGLVersionMinor = 1;
inline constexpr std::string_view kGLSLVersionString = "#version 410 core";

inline constexpr glm::ivec2 kWindowSize = glm::ivec2(1280, 720);
#else
// Unlike macOS, recent versions of Windows and Linux
// generally support the latest available OpenGL version
inline constexpr int kGLVersionMinor = 6;
inline constexpr std::string_view kGLSLVersionString = "#version 460 core";

inline constexpr glm::ivec2 kWindowSize = glm::ivec2(1920, 1080);
#endif
// For framebuffer
inline constexpr int kSampleCount = 4;

#ifdef PROJECT_ROOT
inline const std::filesystem::path kProjectRoot = PROJECT_ROOT;
#else
inline const std::filesystem::path kProjectRoot = std::filesystem::current_path();
#endif
inline const std::filesystem::path kShaderRoot = kProjectRoot / "assets" / "shaders";

}  // namespace glab::config
