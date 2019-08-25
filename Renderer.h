#pragma once
#include <Windows.h>
#include <d3dx9.h>
class Renderer
{
public:

	D3DMATRIX viewMatrix() {
		return *(D3DMATRIX*)((DWORD)this + 0x64);
	}

	D3DMATRIX projMatrix() {
		return *(D3DMATRIX*)((DWORD)this + 0xA4);
	}
};

