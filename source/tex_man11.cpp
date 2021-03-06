#include "stdafx.h"

TexMan11 texMan;

TexMan11::TMID TexMan11::Create(const char *name, bool for3D)
{
	auto it = m_nameToId.find(name);
	if (it != m_nameToId.end())
	{
		return it->second;
	}

	ID3D11ShaderResourceView *tex = nullptr;

	WCHAR wname[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, name, -1, wname, dimof(wname));

	if (!_stricmp(".dds", name + strlen(name) - 4)) {
		CreateDDSTextureFromFileEx(deviceMan11.GetDevice(), wname, 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, false, nullptr, &tex);
	} else {
		CreateWICTextureFromFileEx(deviceMan11.GetDevice(), deviceMan11.GetContext(), wname, 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, false, nullptr, &tex);
	}
	if (!tex) {
		return -1;
	}
	m_texs.push_back(tex);
	return m_nameToId[name] = m_texs.size() - 1;
}

void TexMan11::Destroy()
{
	for (auto it = m_texs.begin(); it != m_texs.end(); it++)
	{
		(*it)->Release();
	}
	m_texs.clear();
}

ID3D11ShaderResourceView* TexMan11::Get(TMID id)
{
	if (id >= 0 && id < (TMID)m_texs.size())
	{
		return m_texs[id];
	}
	return nullptr;
}

SIZE TexMan11::GetSize(TMID id)
{
	ID3D11ShaderResourceView* view = Get(id);
	assert(view);
	ID3D11Resource* res;
	view->GetResource(&res);
	assert(res);
	ID3D11Texture2D* tx;
	res->QueryInterface(__uuidof(ID3D11Texture2D), (void**)(&tx));
	assert(tx);
	SAFE_RELEASE(res);

	D3D11_TEXTURE2D_DESC desc;
	tx->GetDesc(&desc);
	SAFE_RELEASE(tx);

	SIZE sz;
	sz.cx = (int)desc.Width;
	sz.cy = (int)desc.Height;

	return sz;
}
