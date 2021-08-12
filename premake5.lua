<<<<<<< HEAD
workspace "Workspace"
	architecture "x64"

	configurations {
		"debug",
		"release"
	}

	startproject "Sun Engine"

	include "Sun Engine"
	
	include "extern/glfw"
	include "extern/glad"
	include "extern/cglm"	
	include "extern/stb"
	include "extern/assimp"
	include "extern/miniaudio"
=======

project "Sun Engine"
	language "C"
	kind "ConsoleApp"
	staticruntime "on"
	
	targetdir "../bin"
	objdir "../bin-int"

	files {
		"include/**.h",
		"src/**.c"
	}

	defines {
		"WINDOWS"
	}

	includedirs {
		"../extern/glfw/include",
		"../extern/glad/include",
		"../extern/stb/include",
		"../extern/cglm/include",
		"../extern/assimp/include",
		"../extern/miniaudio/include",
		"include"
	}

	links {
		"assimp",
		"glfw",
		"glad",
		"stb",
		"cglm",
		"miniaudio",
		"opengl32",
		"gdi32",
		"user32",
		"kernel32"
	}

	filter "configurations:debug"
		runtime "debug"
		symbols "on"
	
	filter "configurations:release"
		runtime "release"
		optimize "on"
>>>>>>> 8685a6b4232ea912d47a3b786131f7023752b23b
