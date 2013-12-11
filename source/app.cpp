#include "stdafx.h"

App::App()
{
}

App::~App()
{
}

void App::Init()
{
	mesh = new MeshX("C:\\Program Files (x86)\\Microsoft DirectX SDK (August 2009)\\Samples\\Media\\Tiny\\tiny.x");

	matrixMan.Set(MatrixMan::PROJ, XMMatrixPerspectiveFovLH(45 * XM_PI / 180, (float)SCR_W / SCR_H, 0.1f, 1000.0f));
}

void App::Draw()
{
	LARGE_INTEGER t, f;
	QueryPerformanceCounter(&t);
	QueryPerformanceFrequency(&f);

	float time = (float)((double)t.QuadPart / f.QuadPart);

//	matrixMan.Set(MatrixMan::WORLD, XMMatrixIdentity());
//	matrixMan.Set(MatrixMan::VIEW, XMMatrixLookAtLH(XMVectorSet(5, 5, 5, 1), XMVectorSet(0, 0, 0, 0), XMVectorSet(0, 1, 0, 0)));
	matrixMan.Set(MatrixMan::WORLD, XMMatrixRotationQuaternion(XMQuaternionRotationAxis(XMVectorSet(1, 0, 0, 0), time / 2 * XM_PI)));

	float dist = 400;
	float rot = time / 5 * XM_PI;
	matrixMan.Set(MatrixMan::VIEW, XMMatrixLookAtLH(XMVectorSet(sin(rot) * dist, 0, cos(rot) * dist, 1), XMVectorSet(0, 0, 0, 0), XMVectorSet(0, 1, 0, 0)));

	mesh->Draw(0, time);
}

void App::Destroy()
{
	delete mesh;
}
