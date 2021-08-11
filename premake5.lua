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