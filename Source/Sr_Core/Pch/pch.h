#pragma once

// Pre-Compile Headers
//#pragma comment(lib,"opengl32.lib")
// Basic
#include <set>
#include <map>
#include <array>
#include <tuple>
#include <queue>
#include <vector>
#include <string>
#include <bitset>
#include <stdio.h>
#include <memory>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <unordered_map>
#include <assert.h>
#include <ctime>

// OpenGL
//#pragma comment(lib,"glew32.lib")
#include <GL/glew.h>

// GLFW
#include <glfw/glfw3.h>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Errors/Errors.h"
#include "Engine/PathHelper.h"

// Platform
#ifdef SrEngine_WINDOW

#endif

#ifdef SrEngine_LINUX
	// linux platform related stuff
#endif

#ifdef SrEngine_MAC
	// mac platform related stuff
#endif

#define VAR_NAME(var) (#var)