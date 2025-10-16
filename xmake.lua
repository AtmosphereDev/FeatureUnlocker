add_rules("mode.debug", "mode.release")

add_requires("nlohmann_json v3.11.3")

set_runtimes("c++_shared")

target("FeatureUnlocker")
    set_kind("shared")
    set_languages("c++20")
    add_files("src/**.cpp")
    add_includedirs("./src")
    add_includedirs("./include")
    add_packages("nlohmann_json")

    add_links("GlossHook")
    add_linkdirs("lib")
    add_cxflags("-O2")
    add_cxxflags("-DLLVM_TARGETS_TO_BUILD=\"ARM;AArch64;BPF\"")

    after_build(function (target)
        os.cp(target:targetfile(), "$(projectdir)/")
    end)