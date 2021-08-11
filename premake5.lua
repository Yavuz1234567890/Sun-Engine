
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
