set_project("Flux")
set_version("0.1.0")
set_languages("cxx26")

add_rules("mode.debug", "mode.release")

set_policy("build.c++.modules", true)

add_requires("fast_io")
add_requires("glfw")
add_requires("glm")
add_requires("glslang", {configs = {binaryonly = true}})
add_requires("spdlog")
add_requires("vulkan-hpp")
add_requires("vulkan-loader")

target("flux")
    set_kind("binary")

    add_files(
        "src/main.cpp",
        "src/app/*.mpp",
        "src/core/*.mpp",
        "src/core/*.cpp",
        "src/graphics/*.mpp",
        "src/platform/*.mpp",
        "src/simulation/*.mpp"
    )

    add_rules("utils.glsl2spv", {
        outputdir = "build/shaders"
    })

    add_files("shaders/*.vert", "shaders/*.frag", "shaders/*.comp")

    add_defines(
        'FLUX_SHADER_DIR="' .. "$(projectdir)/build/shaders" .. '"'
    )

    add_packages(
        "fast_io",
        "glfw",
        "glm",
        "glslang",
        "spdlog",
        "vulkan-hpp",
        "vulkan-loader"
    )

    set_warnings("allextra")

    if is_plat("linux") then
        add_syslinks("dl", "pthread")
    end
