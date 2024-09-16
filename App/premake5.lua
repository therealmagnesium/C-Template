local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("Application")
kind("ConsoleApp")
language("C++")
cppdialect("C++17")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
	"source/**.h",
	"source/**.cpp",
})

includedirs({
	"../App-Core/source",
	"../vendor/glm",
	"../vendor/glad/include",
	"../vendor/stb_image/include",
})

libdirs({
	"../vendor/glad/lib",
	"../vendor/stb_image/lib",
})

links({
	"App-Core",
	"SDL2",
	"glad",
	"stb_image",
})

postbuildcommands({
	"cp -r assets/ %{cfg.buildtarget.directory}",
})

filter("system:Unix")
system("linux")
systemversion("latest")
defines({
	"PLATFORM_LINUX",
})

filter("configurations:Debug")
defines("DEBUG")
symbols("on")

filter("configurations:Release")
defines("RELEASE")
optimize("on")

filter("configurations:Dist")
defines("DIST")
optimize("on")
kind("WindowedApp")
