#include "stdafx.h"

static float CalcRadius(const MeshX* m)
{
	const Block& b = m->GetRawDatas();
	float maxSq = 0;
	for (auto& it : b.vertices) {
		float sq = XMVectorGetX(XMVector3LengthSq(XMLoadFloat3(&it.xyz)));
		maxSq = std::max(maxSq, sq);
	}
	return sqrt(maxSq);
}

App::App() : radius(0), mesh(nullptr)
{
}

App::~App()
{
}

void App::Init(const char* fileName)
{
	Destroy();

	mesh = new MeshX(fileName);
	radius = CalcRadius(mesh);

	matrixMan.Set(MatrixMan::PROJ, XMMatrixPerspectiveFovLH(45 * XM_PI / 180, (float)SCR_W / SCR_H, 0.1f, 1000.0f));
}

void App::Draw()
{
	LARGE_INTEGER t, f;
	QueryPerformanceCounter(&t);
	QueryPerformanceFrequency(&f);
	float time = (float)((double)t.QuadPart / f.QuadPart);
	float scale = 1 / radius;

	XMMATRIX mRot = XMMatrixRotationQuaternion(XMQuaternionRotationAxis(XMVectorSet(1, 0, 0, 0), time / 2 * XM_PI));
	XMMATRIX mScale = XMMatrixScaling(scale, scale, scale);

	matrixMan.Set(MatrixMan::WORLD, mScale * mRot);

	float dist = 3;
	float rot = time / 5 * XM_PI;
	matrixMan.Set(MatrixMan::VIEW, XMMatrixLookAtLH(XMVectorSet(sin(rot) * dist, 0, cos(rot) * dist, 1), XMVectorSet(0, 0, 0, 0), XMVectorSet(0, 1, 0, 0)));

	mesh->Draw(0, time);
}

void App::Destroy()
{
	SAFE_DELETE(mesh);
}
