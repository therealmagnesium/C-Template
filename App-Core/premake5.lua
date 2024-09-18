local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("App-Core")
kind("StaticLib")
language("C++")
cppdialect("C++17")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
	"source/**.h",
	"source/**.cpp",
})

includedirs({
	"source",
	"../vendor/glm",
	"../vendor/glad/include",
	"../vendor/imgui/include",
	"../vendor/stb_image/include",
})

libdirs({
	"../vendor/glad/lib",
	"../vendor/imgui/lib",
	"../vendor/stb_image/lib",
})

links({
	"SDL2",
	"glad",
	"imgui",
	"stb_image",
	"assimp",
})

filter("system:Unix")
system("linux")
systemversion("latest")
defines({
	"PLATFORM_LINUX",
})

filter({ "configurations:Debug" })
defines("DEBUG")
symbols("on")

filter({ "configurations:Release" })
defines("RELEASE")
optimize("on")

filter({ "configurations:Dist" })
defines("DIST")
optimize("on")
