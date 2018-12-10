#pragma once

#include "../dxgi/dxgi_interfaces.h"

#include "d3d11_include.h"

namespace dxvk {
    class D3D11DXGIDevice;

    class D3D11DeviceSwapChainFactory : public IWineDXGISwapChainFactory {
        public:
          D3D11DeviceSwapChainFactory(D3D11DXGIDevice*  pContainer);

          ~D3D11DeviceSwapChainFactory();

          ULONG STDMETHODCALLTYPE AddRef();

          ULONG STDMETHODCALLTYPE Release();

          HRESULT STDMETHODCALLTYPE QueryInterface(
              REFIID                  riid,
              void**                  ppvObject);

          HRESULT STDMETHODCALLTYPE CreateSwapChainForHwnd(
              IUnknown*             pDevice,
              HWND                  hWnd,
              const DXGI_SWAP_CHAIN_DESC1* pDesc,
              const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc,
              IDXGIOutput*          pRestrictToOutput,
              IDXGISwapChain1**     ppSwapChain);

        private:
            D3D11DXGIDevice* m_container;
            IDXGIFactory2*   m_factory;
            HMODULE          m_module;
    };
}