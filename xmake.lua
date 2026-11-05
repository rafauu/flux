set_project("Flux")
set_version("0.1.0")
set_languages("cxx26")

add_rules("mode.debug", "mode.release")

add_requires("vulkan-headers")
add_requires("vulkan-loader")

target("flux")
    set_kind("binary")

    add_files("src/main.cpp")

    add_packages(
        "vulkan-headers",
        "vulkan-loader"
    )

    set_warnings("allextra")

    if is_plat("linux") then
        add_syslinks("dl", "pthread")
    end
