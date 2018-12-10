#include "d3d11_deviceswapchainfactory.h"
#include "d3d11_device.h"

namespace dxvk {
D3D11DeviceSwapChainFactory::D3D11DeviceSwapChainFactory(D3D11DXGIDevice* pContainer): m_container (pContainer){
    HRESULT (WINAPI * pCreateDXGIFactory)(REFIID, void **);
    HRESULT hr;

    m_module = LoadLibraryA("dxvk_dxgi.dll");
    if (!m_module) Logger::err("D3D11DeviceSwapChainFactory::D3D11DeviceSwapChainFactory failed to load dxvk_dxgi.dll");
    pCreateDXGIFactory = (HRESULT (WINAPI *)(REFIID, void **))GetProcAddress(m_module, "CreateDXGIFactory");
    if (pCreateDXGIFactory)
        hr = pCreateDXGIFactory(__uuidof(IDXGIFactory2), (void **)&m_factory);

    if (FAILED(hr))
        Logger::err("D3D11DeviceSwapChainFactory::D3D11DeviceSwapChainFactory failed to CreateDXGIFactory()");
}

D3D11DeviceSwapChainFactory::~D3D11DeviceSwapChainFactory() {
    m_factory->Release();
    FreeLibrary(m_module);
}

ULONG STDMETHODCALLTYPE D3D11DeviceSwapChainFactory::AddRef() {
    return m_container->AddRef();
}

ULONG STDMETHODCALLTYPE D3D11DeviceSwapChainFactory::Release() {
    return m_container->Release();
}

HRESULT STDMETHODCALLTYPE D3D11DeviceSwapChainFactory::QueryInterface(REFIID riid, void** ppvObject) {
    return m_container->QueryInterface(riid, ppvObject);
}

HRESULT STDMETHODCALLTYPE D3D11DeviceSwapChainFactory::CreateSwapChainForHwnd(
                                                            IUnknown*             pDevice,
                                                            HWND                  hWnd,
                                                            const DXGI_SWAP_CHAIN_DESC1* pDesc,
                                                            const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc,
                                                            IDXGIOutput*          pRestrictToOutput,
                                                            IDXGISwapChain1**     ppSwapChain) {

    if (m_factory)
        return m_factory->CreateSwapChainForHwnd(m_container,
                                                 hWnd,
                                                 pDesc,
                                                 pFullscreenDesc,
                                                 pRestrictToOutput,
                                                 ppSwapChain);
    else
        return DXGI_ERROR_UNSUPPORTED;
}
}