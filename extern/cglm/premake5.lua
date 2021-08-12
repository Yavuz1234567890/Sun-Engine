project "cglm"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	architecture "x64"

	targetdir "bin"
	objdir "obj"

	pic "on"

	includedirs {
            "include/cglm",
	}

	files {
	    "include/cglm/**",
	}

	filter "configurations:debug"
		runtime "debug"
		symbols "on"

	filter "configurations:release"
		runtime "release"
		optimize "on"
