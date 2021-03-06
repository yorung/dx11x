class DeviceMan11
{
	ID3D11Device* pDevice;
	IDXGISwapChain* pSwapChain;
	ID3D11DeviceContext* pImmediateContext;
	ID3D11RenderTargetView*	pRenderTargetView;
	ID3D11DepthStencilView* pDepthStencilView;
public:
	DeviceMan11();
	~DeviceMan11();

	void Create(HWND hWnd);
	void Destroy();

	void BeginScene();
	void EndScene();

	ID3D11Device* GetDevice() { return pDevice; }
	ID3D11DeviceContext* GetContext() { return pImmediateContext; }
};

extern DeviceMan11 deviceMan11;
