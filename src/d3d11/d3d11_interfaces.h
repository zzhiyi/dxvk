#pragma once

#include "../dxgi/dxgi_interfaces.h"

#include "d3d11_include.h"

/**
 * \brief D3D11 extension
 * 
 * Lists D3D11 extensions supported by DXVK.
 */
enum D3D11_VK_EXTENSION : uint32_t {
  D3D11_VK_EXT_MULTI_DRAW_INDIRECT        = 0,
  D3D11_VK_EXT_MULTI_DRAW_INDIRECT_COUNT  = 1,
  D3D11_VK_EXT_DEPTH_BOUNDS               = 2,
  D3D11_VK_EXT_BARRIER_CONTROL            = 3,
  D3D11_VK_NVX_BINARY_IMPORT              = 4,
  D3D11_VK_NVX_IMAGE_VIEW_HANDLE          = 5,
};


/**
 * \brief Barrier control flags
 */
enum D3D11_VK_BARRIER_CONTROL : uint32_t {
  D3D11_VK_BARRIER_CONTROL_IGNORE_WRITE_AFTER_WRITE   = 1 << 0,

  // Removed:
  // D3D11_VK_BARRIER_CONTROL_IGNORE_GRAPHICS_UAV        = 1 << 1,
};


/**
 * \brief Extended D3D11 device
 * 
 * Introduces a method to check for extension support.
 */
MIDL_INTERFACE("8a6e3c42-f74c-45b7-8265-a231b677ca17")
ID3D11VkExtDevice : public IUnknown {
  /**
   * \brief Checks whether an extension is supported
   * 
   * \param [in] Extension The extension to check
   * \returns \c TRUE if the extension is supported
   */
  virtual BOOL STDMETHODCALLTYPE GetExtensionSupport(
          D3D11_VK_EXTENSION      Extension) = 0;
  
};


/**
 * \brief Extended extended D3D11 device
 * 
 * Introduces methods to get virtual addresses and driver
 * handles for resources, and create and destroy objects
 * for D3D11-Cuda interop.
 */
MIDL_INTERFACE("cfcf64ef-9586-46d0-bca4-97cf2ca61b06")
ID3D11VkExtDevice1 : public ID3D11VkExtDevice {

  virtual bool STDMETHODCALLTYPE GetResourceHandleGPUVirtualAddressAndSizeNVX(
          void*                   hObject,
          uint64_t*               gpuVAStart,
          uint64_t*               gpuVASize) = 0;

  virtual bool STDMETHODCALLTYPE CreateUnorderedAccessViewAndGetDriverHandleNVX(
          ID3D11Resource*         pResource,
          const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc,
          ID3D11UnorderedAccessView** ppUAV,
          uint32_t*               pDriverHandle) = 0;

  virtual bool STDMETHODCALLTYPE CreateShaderResourceViewAndGetDriverHandleNVX(
          ID3D11Resource*         pResource,
          const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc,
          ID3D11ShaderResourceView** ppSRV,
          uint32_t*               pDriverHandle) = 0;

  virtual bool STDMETHODCALLTYPE CreateSamplerStateAndGetDriverHandleNVX(
          const D3D11_SAMPLER_DESC* pSamplerDesc,
          ID3D11SamplerState**    ppSamplerState,
          uint32_t*               pDriverHandle) = 0;

  virtual bool STDMETHODCALLTYPE CreateCubinComputeShaderWithNameNVX(
          const void*             pCubin,
          uint32_t                size,
          uint32_t                blockX,
          uint32_t                blockY,
          uint32_t                blockZ,
          const char*             pShaderName,
          IUnknown**              phShader) = 0;

  virtual bool STDMETHODCALLTYPE GetCudaTextureObjectNVX(
          uint32_t                srvDriverHandle,
          uint32_t                samplerDriverHandle,
          uint32_t*               pCudaTextureHandle) = 0;
};


/**
 * \brief Extended D3D11 context
 * 
 * Provides functionality for various D3D11
 * extensions.
 */
MIDL_INTERFACE("fd0bca13-5cb6-4c3a-987e-4750de2ca791")
ID3D11VkExtContext : public IUnknown {
  virtual void STDMETHODCALLTYPE MultiDrawIndirect(
          UINT                    DrawCount,
          ID3D11Buffer*           pBufferForArgs,
          UINT                    ByteOffsetForArgs,
          UINT                    ByteStrideForArgs) = 0;
  
  virtual void STDMETHODCALLTYPE MultiDrawIndexedIndirect(
          UINT                    DrawCount,
          ID3D11Buffer*           pBufferForArgs,
          UINT                    ByteOffsetForArgs,
          UINT                    ByteStrideForArgs) = 0;
  
  virtual void STDMETHODCALLTYPE MultiDrawIndirectCount(
          UINT                    MaxDrawCount,
          ID3D11Buffer*           pBufferForCount,
          UINT                    ByteOffsetForCount,
          ID3D11Buffer*           pBufferForArgs,
          UINT                    ByteOffsetForArgs,
          UINT                    ByteStrideForArgs) = 0;
  
  virtual void STDMETHODCALLTYPE MultiDrawIndexedIndirectCount(
          UINT                    MaxDrawCount,
          ID3D11Buffer*           pBufferForCount,
          UINT                    ByteOffsetForCount,
          ID3D11Buffer*           pBufferForArgs,
          UINT                    ByteOffsetForArgs,
          UINT                    ByteStrideForArgs) = 0;
  
  virtual void STDMETHODCALLTYPE SetDepthBoundsTest(
          BOOL                    Enable,
          FLOAT                   MinDepthBounds,
          FLOAT                   MaxDepthBounds) = 0;
  
  virtual void STDMETHODCALLTYPE SetBarrierControl(
          UINT                    ControlFlags) = 0;
};


/**
 * \brief Extended extended D3D11 context
 * 
 * Provides functionality to launch a Cuda kernel
 */
MIDL_INTERFACE("874b09b2-ae0b-41d8-8476-5f3b7a0e879d")
ID3D11VkExtContext1 : public ID3D11VkExtContext {

  virtual bool STDMETHODCALLTYPE LaunchCubinShaderNVX(
          IUnknown*               hShader,
          uint32_t                gridX,
          uint32_t                gridY,
          uint32_t                gridZ,
          const void*             pParams,
          uint32_t                paramSize,
          void* const*            pReadResources,
          uint32_t                numReadResources,
          void* const*            pWriteResources,
          uint32_t                numWriteResources) = 0;
};


/**
 * \brief Frame reports used for Reflex interop
 */
struct D3D_LOW_LATENCY_FRAME_REPORT
{
    UINT64 frameID;
    UINT64 inputSampleTime;
    UINT64 simStartTime;
    UINT64 simEndTime;
    UINT64 renderSubmitStartTime;
    UINT64 renderSubmitEndTime;
    UINT64 presentStartTime;
    UINT64 presentEndTime;
    UINT64 driverStartTime;
    UINT64 driverEndTime;
    UINT64 osRenderQueueStartTime;
    UINT64 osRenderQueueEndTime;
    UINT64 gpuRenderStartTime;
    UINT64 gpuRenderEndTime;
    UINT32 gpuActiveRenderTimeUs;
    UINT32 gpuFrameTimeUs;
    UINT8 rsvd[120];
};


/**
 * \brief Data structure used for Reflex interop
 */
struct D3D_LOW_LATENCY_RESULTS
{
    UINT32 version;
    D3D_LOW_LATENCY_FRAME_REPORT frameReports[64];
    UINT8 rsvd[32];
};


/**
 * \brief D3D interop interface for Nvidia Reflex
 */
MIDL_INTERFACE("f3112584-41f9-348d-a59b-00b7e1d285d6")
ID3DLowLatencyDevice : public IUnknown {
  virtual BOOL STDMETHODCALLTYPE SupportsLowLatency() = 0;

  virtual HRESULT STDMETHODCALLTYPE LatencySleep() = 0;

  virtual HRESULT STDMETHODCALLTYPE SetLatencySleepMode(
          BOOL                          LowLatencyEnable,
          BOOL                          LowLatencyBoost,
          UINT32                        MinIntervalUs) = 0;

  virtual HRESULT STDMETHODCALLTYPE SetLatencyMarker(
          UINT64                        FrameId,
          UINT32                        MarkerType) = 0;

  virtual HRESULT STDMETHODCALLTYPE GetLatencyInfo(
          D3D_LOW_LATENCY_RESULTS*      pLowLatencyResults) = 0;
};


/**
 * \brief Undocumented D3D11 device interface
 */
MIDL_INTERFACE("26c5dc23-e49c-4b0a-8f79-e7b1ac804d32")
ID3D11DeviceUnknown : public IUnknown {
  virtual HRESULT STDMETHODCALLTYPE Unknown1() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown2() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown3() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown4() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown5() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown6() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown7() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown8() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown9() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown10() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown11() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown12() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown13() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown14() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown15() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown16() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown17() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown18() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown19() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown20() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown21() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown22() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown23() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown24() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown25() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown26() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown27() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown28() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown29() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown30() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown31() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown32() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown33() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown34() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown35() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown36() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown37() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown38() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown39() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown40() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown41() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown42() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown43() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown44() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown45() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown46() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown47() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown48() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown49() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown50() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown51() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown52() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown53() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown54() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown55() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown56() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown57() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown58() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown59() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown60() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown61() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown62() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown63() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown64() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown65() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown66() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown67() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown68() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown69() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown70() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown71() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown72() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown73() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown74() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown75() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown76() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown77() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown78() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown79() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown80() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown81() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown82() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown83() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown84() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown85() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown86() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown87() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown88() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown89() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown90() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown91() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown92() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown93() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown94() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown95() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown96() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown97() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown98() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown99() = 0;
};


/**
 * \brief Undocumented D3D11 device interface 2
 */
MIDL_INTERFACE("f13ebcd1-672c-4f8b-a631-9539ca748d71")
ID3D11DeviceUnknown2 : public IUnknown {
  virtual HRESULT STDMETHODCALLTYPE Unknown1() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown2() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown3() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown4() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown5() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown6() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown7() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown8() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown9() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown10() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown11() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown12() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown13() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown14() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown15() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown16() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown17() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown18() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown19() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown20() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown21() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown22() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown23() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown24() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown25() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown26() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown27() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown28() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown29() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown30() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown31() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown32() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown33() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown34() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown35() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown36() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown37() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown38() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown39() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown40() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown41() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown42() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown43() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown44() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown45() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown46() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown47() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown48() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown49() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown50() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown51() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown52() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown53() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown54() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown55() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown56() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown57() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown58() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown59() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown60() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown61() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown62() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown63() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown64() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown65() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown66() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown67() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown68() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown69() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown70() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown71() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown72() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown73() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown74() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown75() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown76() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown77() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown78() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown79() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown80() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown81() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown82() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown83() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown84() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown85() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown86() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown87() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown88() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown89() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown90() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown91() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown92() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown93() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown94() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown95() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown96() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown97() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown98() = 0;
  virtual HRESULT STDMETHODCALLTYPE Unknown99() = 0;
};


#ifndef _MSC_VER
__CRT_UUID_DECL(ID3D11DeviceUnknown,       0x26c5dc23,0xe49c,0x4b0a,0x8f,0x79,0xe7,0xb1,0xac,0x80,0x4d,0x32);
__CRT_UUID_DECL(ID3D11DeviceUnknown2,      0xf13ebcd1,0x672c,0x4f8b,0xa6,0x31,0x95,0x39,0xca,0x74,0x8d,0x71);
__CRT_UUID_DECL(ID3D11VkExtDevice,         0x8a6e3c42,0xf74c,0x45b7,0x82,0x65,0xa2,0x31,0xb6,0x77,0xca,0x17);
__CRT_UUID_DECL(ID3D11VkExtDevice1,        0xcfcf64ef,0x9586,0x46d0,0xbc,0xa4,0x97,0xcf,0x2c,0xa6,0x1b,0x06);
__CRT_UUID_DECL(ID3D11VkExtContext,        0xfd0bca13,0x5cb6,0x4c3a,0x98,0x7e,0x47,0x50,0xde,0x2c,0xa7,0x91);
__CRT_UUID_DECL(ID3D11VkExtContext1,       0x874b09b2,0xae0b,0x41d8,0x84,0x76,0x5f,0x3b,0x7a,0x0e,0x87,0x9d);
__CRT_UUID_DECL(ID3DLowLatencyDevice,      0xf3112584,0x41f9,0x348d,0xa5,0x9b,0x00,0xb7,0xe1,0xd2,0x85,0xd6);
#endif
