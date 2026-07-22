add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "$(builddir)"})

set_languages("cxx23")

add_requires("imgui v1.92.7-docking", {configs = {opengl3 = true, glfw = true}})
add_requires("glfw", "glm", "stb", "spdlog")
if not is_plat("macos") then
    add_requires("glad", {configs = {profile = "core"}})
end

target("GLAB")
    set_kind("binary")
    set_rundir("$(projectdir)")
    add_files("src/**.cpp")
    add_defines("GLFW_INCLUDE_NONE")
    add_packages("imgui", "glfw", "glm", "stb", "spdlog")
    if not is_plat("macos") then
        add_packages("glad")
    end
