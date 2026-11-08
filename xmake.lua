set_project("Flux")
set_version("0.1.0")
set_languages("cxx26")

add_rules("mode.debug", "mode.release")

set_policy("build.c++.modules", true)

add_requires("fast_io")
add_requires("glfw")
add_requires("glslang", {configs = {binaryonly = true}})
add_requires("spdlog")
add_requires("vulkan-hpp")
add_requires("vulkan-loader")

target("flux")
    set_kind("binary")

    add_files("src/*.cpp", "src/*.mpp")

    add_rules("utils.glsl2spv", {
        outputdir = "build/shaders"
    })

    add_files("shaders/*.vert", "shaders/*.frag")

    add_defines(
        'FLUX_SHADER_DIR="' .. "$(projectdir)/build/shaders" .. '"'
    )

    add_packages(
        "fast_io",
        "glfw",
        "glslang",
        "spdlog",
        "vulkan-hpp",
        "vulkan-loader"
    )

    set_warnings("allextra")

    if is_plat("linux") then
        add_syslinks("dl", "pthread")
    end
