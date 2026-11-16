set_languages("cxx23")

add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "$(builddir)"})

add_requires("imgui v1.92.7-docking", {configs = {opengl3 = true, glfw = true}})
add_requires("glad", {configs = {profile = "core"}})
add_requires("glfw", "glm", "stb", "spdlog", "fastgltf")

add_packages("imgui","glad", "glfw", "glm", "stb", "spdlog", "fastgltf")

add_defines('PROJECT_ROOT="' .. path.unix(os.projectdir()) .. '"')
add_defines("GLFW_INCLUDE_NONE")

target("GLAB")
    set_kind("binary")
    add_files("src/**.cpp")
    add_includedirs("src")
