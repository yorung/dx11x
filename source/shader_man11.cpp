#include "stdafx.h"

ShaderMan11 shaderMan;

ShaderMan11::SMID ShaderMan11::Create(const char *name, const D3D11_INPUT_ELEMENT_DESC elements[], int numElements)
{
	auto it = m_nameToId.find(name);
	if (it != m_nameToId.end())
	{
		return it->second;
	}

	Effect effect;
	memset(&effect, 0, sizeof(effect));

	ID3D10Blob* pBlobVS = 0;
	ID3D10Blob* pErrMsg = 0;

	WCHAR wname[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, name, -1, wname, dimof(wname));

	D3DCompileFromFile(wname, nullptr, nullptr, "mainVS", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR, 0, &pBlobVS, &pErrMsg);
//	D3DX11CompileFromFileA(name, nullptr, nullptr, "mainVS", "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR, 0, nullptr, &pBlobVS, &pErrMsg, nullptr);
	if(pErrMsg) {
		OutputDebugStringA( (const char*) pErrMsg->GetBufferPointer() );
		OutputDebugStringA( "\n" );
		pErrMsg->Release();
		pErrMsg = 0;
	}

	HRESULT hr = deviceMan11.GetDevice()->CreateVertexShader(pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), nullptr, &effect.pVertexShader);

	ID3D10Blob* pBlobPS = 0;
	D3DCompileFromFile(wname, nullptr, nullptr, "mainPS", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR, 0, &pBlobPS, &pErrMsg);
	if( pErrMsg ) {
		OutputDebugStringA( (const char*) pErrMsg->GetBufferPointer() );
		OutputDebugStringA( "\n" );
		pErrMsg->Release();
		pErrMsg = 0;
	}

	hr = deviceMan11.GetDevice()->CreatePixelShader(pBlobPS->GetBufferPointer(), pBlobPS->GetBufferSize(), nullptr, &effect.pPixelShader);
	assert(!hr);

	hr = deviceMan11.GetDevice()->CreateInputLayout(elements, numElements, pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), &effect.pInputLayout);
	assert(!hr);

	SAFE_RELEASE(pBlobVS);
	SAFE_RELEASE(pBlobPS);

	m_effects.push_back(effect);
	return m_nameToId[name] = m_effects.size() - 1;
}

void ShaderMan11::Destroy()
{
	for (auto it = m_effects.begin(); it != m_effects.end(); it++)
	{
		SAFE_RELEASE(it->pInputLayout);
		SAFE_RELEASE(it->pVertexShader);
		SAFE_RELEASE(it->pPixelShader);
	}
	m_effects.clear();
}

void ShaderMan11::Apply(SMID id)
{
	if (id >= 0 && id < (SMID)m_effects.size())
	{
		Effect& it = m_effects[id];
		deviceMan11.GetContext()->IASetInputLayout(it.pInputLayout);
		deviceMan11.GetContext()->VSSetShader(it.pVertexShader, nullptr, 0);
		deviceMan11.GetContext()->PSSetShader(it.pPixelShader, nullptr, 0);
	}
}
