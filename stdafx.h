// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>

// C++
#include <algorithm>
#include <map>
#include <vector>

// DirectX
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <directxmath.h>
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
using namespace DirectX;

// TODO: reference additional headers your program requires here
#include "source/device_man11.h"
#include "source/tex_man11.h"
#include "source/shader_man11.h"
#include "source/mat_man.h"
#include "source/matrix_man.h"
#include "source/mesh_renderer11.h"
#include "source/mesh_x.h"

#include "source/app.h"

#define dimof(x) (sizeof(x) / sizeof(x[0]))

#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }

#define SCR_W 640
#define SCR_H 480
