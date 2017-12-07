#include <cstring>

#include "d3d11_context.h"
#include "d3d11_device.h"

namespace dxvk {
  
  D3D11DeviceContext::D3D11DeviceContext(
      ID3D11Device*   parent,
      Rc<DxvkDevice>  device)
  : m_parent(parent),
    m_device(device) {
    m_context = m_device->createContext();
    m_context->beginRecording(
      m_device->createCommandList());
    
    m_defaultRsState = new DxvkRasterizerState(
      VK_FALSE, VK_FALSE,
      VK_POLYGON_MODE_FILL,
      VK_CULL_MODE_BACK_BIT,
      VK_FRONT_FACE_CLOCKWISE,
      VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f);
    
    this->ClearState();
  }
  
  
  D3D11DeviceContext::~D3D11DeviceContext() {
    
  }
  
  
  HRESULT D3D11DeviceContext::QueryInterface(
          REFIID  riid,
          void**  ppvObject) {
    COM_QUERY_IFACE(riid, ppvObject, IUnknown);
    COM_QUERY_IFACE(riid, ppvObject, ID3D11DeviceChild);
    COM_QUERY_IFACE(riid, ppvObject, ID3D11DeviceContext);
    
    Logger::warn("D3D11DeviceContext::QueryInterface: Unknown interface query");
    return E_NOINTERFACE;
  }
  
  
  void D3D11DeviceContext::GetDevice(ID3D11Device **ppDevice) {
    *ppDevice = ref(m_parent);
  }
  
  
  D3D11_DEVICE_CONTEXT_TYPE D3D11DeviceContext::GetType() {
    return m_type;
  }
  
  
  UINT D3D11DeviceContext::GetContextFlags() {
    return m_flags;
  }
  
  
  void D3D11DeviceContext::ClearState() {
//     this->IASetInputLayout(nullptr);
    this->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED);
//     this->IASetVertexBuffers(0, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT, nullptr, nullptr, nullptr);
//     this->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
    
    this->VSSetShader(nullptr, nullptr, 0);
//     this->VSSetConstantBuffers(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, nullptr);
//     this->VSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, nullptr);
//     this->VSSetSamplers       (0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, nullptr);
    
//     this->HSSetShader(nullptr, nullptr, 0);
//     this->HSSetConstantBuffers(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, nullptr);
//     this->HSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, nullptr);
//     this->HSSetSamplers       (0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, nullptr);
    
//     this->DSSetShader(nullptr, nullptr, 0);
//     this->DSSetConstantBuffers(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, nullptr);
//     this->DSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, nullptr);
//     this->DSSetSamplers       (0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, nullptr);
    
//     this->GSSetShader(nullptr, nullptr, 0);
//     this->GSSetConstantBuffers(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, nullptr);
//     this->GSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, nullptr);
//     this->GSSetSamplers       (0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, nullptr);
    
    this->PSSetShader(nullptr, nullptr, 0);
//     this->PSSetConstantBuffers(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, nullptr);
//     this->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, nullptr);
//     this->PSSetSamplers       (0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, nullptr);
    
//     this->CSSetShader(nullptr, nullptr, 0);
//     this->CSSetConstantBuffers(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, nullptr);
//     this->CSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, nullptr);
//     this->CSSetSamplers       (0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT, nullptr);
    
    this->OMSetRenderTargets(0, nullptr, nullptr);
//     this->OMSetBlendState(nullptr, nullptr, D3D11_DEFAULT_SAMPLE_MASK);
//     this->OMSetDepthStencilState(nullptr, 0);
    
    this->RSSetState(nullptr);
    this->RSSetViewports(0, nullptr);
    this->RSSetScissorRects(0, nullptr);
    
//     this->SOSetTargets(0, nullptr, nullptr);
    
//     this->SetPredication(nullptr, FALSE);
  }
  
  
  void D3D11DeviceContext::Flush() {
    if (m_type == D3D11_DEVICE_CONTEXT_IMMEDIATE) {
      m_device->submitCommandList(
        m_context->endRecording(),
        nullptr, nullptr);
      
      m_context->beginRecording(
        m_device->createCommandList());
    } else {
      Logger::err("D3D11DeviceContext::Flush: Not supported on deferred context");
    }
  }
  
  
  void D3D11DeviceContext::ExecuteCommandList(
          ID3D11CommandList*  pCommandList,
          WINBOOL             RestoreContextState) {
    Logger::err("D3D11DeviceContext::ExecuteCommandList: Not implemented");
  }
  
  
  HRESULT D3D11DeviceContext::FinishCommandList(
          WINBOOL             RestoreDeferredContextState,
          ID3D11CommandList   **ppCommandList) {
    if (m_type == D3D11_DEVICE_CONTEXT_DEFERRED) {
      Logger::err("D3D11DeviceContext::FinishCommandList: Not implemented");
      return E_NOTIMPL;
    } else {
      Logger::err("D3D11DeviceContext::FinishCommandList: Not supported on immediate context");
      return DXGI_ERROR_INVALID_CALL;
    }
  }
  
  
  HRESULT D3D11DeviceContext::Map(
          ID3D11Resource*             pResource,
          UINT                        Subresource,
          D3D11_MAP                   MapType,
          UINT                        MapFlags,
          D3D11_MAPPED_SUBRESOURCE*   pMappedResource) {
    Logger::err("D3D11DeviceContext::Map: Not implemented");
    return E_NOTIMPL;
  }
  
  
  void D3D11DeviceContext::Unmap(
          ID3D11Resource*             pResource,
          UINT                        Subresource) {
    Logger::err("D3D11DeviceContext::Unmap: Not implemented");
  }
  
  
  void D3D11DeviceContext::Begin(ID3D11Asynchronous *pAsync) {
    Logger::err("D3D11DeviceContext::Begin: Not implemented");
  }
  
  
  void D3D11DeviceContext::End(ID3D11Asynchronous *pAsync) {
    Logger::err("D3D11DeviceContext::End: Not implemented");
  }
  
  
  HRESULT D3D11DeviceContext::GetData(
          ID3D11Asynchronous*               pAsync,
          void*                             pData,
          UINT                              DataSize,
          UINT                              GetDataFlags) {
    Logger::err("D3D11DeviceContext::GetData: Not implemented");
    return E_NOTIMPL;
  }
  
  
  void D3D11DeviceContext::SetPredication(
          ID3D11Predicate*                  pPredicate,
          WINBOOL                           PredicateValue) {
    Logger::err("D3D11DeviceContext::SetPredication: Not implemented");
  }
  
  
  void D3D11DeviceContext::GetPredication(
          ID3D11Predicate**                 ppPredicate,
          WINBOOL*                          pPredicateValue) {
    Logger::err("D3D11DeviceContext::GetPredication: Not implemented");
  }
  
  
  void D3D11DeviceContext::CopySubresourceRegion(
          ID3D11Resource*                   pDstResource,
          UINT                              DstSubresource,
          UINT                              DstX,
          UINT                              DstY,
          UINT                              DstZ,
          ID3D11Resource*                   pSrcResource,
          UINT                              SrcSubresource,
    const D3D11_BOX*                        pSrcBox) {
    Logger::err("D3D11DeviceContext::CopySubresourceRegion: Not implemented");
  }
  
  
  void D3D11DeviceContext::CopyResource(
          ID3D11Resource*                   pDstResource,
          ID3D11Resource*                   pSrcResource) {
    Logger::err("D3D11DeviceContext::CopyResource: Not implemented");
  }
  
  
  void D3D11DeviceContext::CopyStructureCount(
          ID3D11Buffer*                     pDstBuffer,
          UINT                              DstAlignedByteOffset,
          ID3D11UnorderedAccessView*        pSrcView) {
    Logger::err("D3D11DeviceContext::CopyStructureCount: Not implemented");
  }
  
  
  void D3D11DeviceContext::ClearRenderTargetView(
          ID3D11RenderTargetView*           pRenderTargetView,
    const FLOAT                             ColorRGBA[4]) {
    auto rtv = static_cast<D3D11RenderTargetView*>(pRenderTargetView);
    
    const Rc<DxvkImageView> dxvkView  = rtv->GetDXVKImageView();
    const Rc<DxvkImage>     dxvkImage = dxvkView->image();
    
    // Find out whether the given attachment is currently bound
    // or not, and if it is, which attachment index it has.
    int32_t attachmentIndex = -1;
    
    if (m_state.om.framebuffer != nullptr) {
      attachmentIndex = m_state.om.framebuffer
        ->renderTargets().getAttachmentId(dxvkView);
    }
    
    // Copy the clear color into a clear value structure.
    // This should also work for images that don nott have
    // a floating point format.
    VkClearColorValue clearValue;
    std::memcpy(clearValue.float32, ColorRGBA,
      sizeof(clearValue.float32));
    
    if (attachmentIndex >= 0) {
      // Image is bound to the pipeline for rendering. We can
      // use the clear function that operates on attachments.
      VkClearAttachment clearInfo;
      clearInfo.aspectMask          = VK_IMAGE_ASPECT_COLOR_BIT;
      clearInfo.colorAttachment     = static_cast<uint32_t>(attachmentIndex);
      clearInfo.clearValue.color    = clearValue;
      
      // Clear the full area. On FL 9.x, only the first array
      // layer will be cleared, rather than all array layers.
      VkClearRect clearRect;
      clearRect.rect.offset.x       = 0;
      clearRect.rect.offset.y       = 0;
      clearRect.rect.extent.width   = dxvkImage->info().extent.width;
      clearRect.rect.extent.height  = dxvkImage->info().extent.height;
      clearRect.baseArrayLayer      = 0;
      clearRect.layerCount          = dxvkImage->info().numLayers;
      
      if (m_parent->GetFeatureLevel() < D3D_FEATURE_LEVEL_10_0)
        clearRect.layerCount        = 1;
      
      m_context->clearRenderTarget(clearInfo, clearRect);
    } else {
      // Image is not bound to the pipeline. We can still clear
      // it, but we'll have to use a generic clear function.
      m_context->clearColorImage(dxvkImage,
        clearValue, dxvkView->subresources());
    }
  }
  
  
  void D3D11DeviceContext::ClearUnorderedAccessViewUint(
          ID3D11UnorderedAccessView*        pUnorderedAccessView,
    const UINT                              Values[4]) {
    Logger::err("D3D11DeviceContext::ClearUnorderedAccessViewUint: Not implemented");
  }
  
  
  void D3D11DeviceContext::ClearUnorderedAccessViewFloat(
          ID3D11UnorderedAccessView*        pUnorderedAccessView,
    const FLOAT                             Values[4]) {
    Logger::err("D3D11DeviceContext::ClearUnorderedAccessViewFloat: Not implemented");
  }
  
  
  void D3D11DeviceContext::ClearDepthStencilView(
          ID3D11DepthStencilView*           pDepthStencilView,
          UINT                              ClearFlags,
          FLOAT                             Depth,
          UINT8                             Stencil) {
    Logger::err("D3D11DeviceContext::ClearDepthStencilView: Not implemented");
  }
  
  
  void D3D11DeviceContext::GenerateMips(ID3D11ShaderResourceView* pShaderResourceView) {
    Logger::err("D3D11DeviceContext::GenerateMips: Not implemented");
  }
  
  
  void D3D11DeviceContext::UpdateSubresource(
          ID3D11Resource*                   pDstResource,
          UINT                              DstSubresource,
    const D3D11_BOX*                        pDstBox,
    const void*                             pSrcData,
          UINT                              SrcRowPitch,
          UINT                              SrcDepthPitch) {
    Logger::err("D3D11DeviceContext::UpdateSubresource: Not implemented");
  }
  
  
  void D3D11DeviceContext::SetResourceMinLOD(
          ID3D11Resource*                   pResource,
          FLOAT                             MinLOD) {
    Logger::err("D3D11DeviceContext::SetResourceMinLOD: Not implemented");
  }
  
  
  FLOAT D3D11DeviceContext::GetResourceMinLOD(ID3D11Resource* pResource) {
    Logger::err("D3D11DeviceContext::GetResourceMinLOD: Not implemented");
    return 0.0f;
  }
  
  
  void D3D11DeviceContext::ResolveSubresource(
          ID3D11Resource*                   pDstResource,
          UINT                              DstSubresource,
          ID3D11Resource*                   pSrcResource,
          UINT                              SrcSubresource,
          DXGI_FORMAT                       Format) {
    Logger::err("D3D11DeviceContext::ResolveSubresource: Not implemented");
  }
  
  
  void D3D11DeviceContext::DrawAuto() {
    Logger::err("D3D11DeviceContext::DrawAuto: Not implemented");
  }
  
  
  void D3D11DeviceContext::Draw(
          UINT            VertexCount,
          UINT            StartVertexLocation) {
    m_context->draw(
      VertexCount, 1,
      StartVertexLocation, 0);
  }
  
  
  void D3D11DeviceContext::DrawIndexed(
          UINT            IndexCount,
          UINT            StartIndexLocation,
          INT             BaseVertexLocation) {
    m_context->drawIndexed(
      IndexCount, 1,
      StartIndexLocation,
      BaseVertexLocation, 0);
  }
  
  
  void D3D11DeviceContext::DrawInstanced(
          UINT            VertexCountPerInstance,
          UINT            InstanceCount,
          UINT            StartVertexLocation,
          UINT            StartInstanceLocation) {
    m_context->draw(
      VertexCountPerInstance,
      InstanceCount,
      StartVertexLocation,
      StartInstanceLocation);
  }
  
  
  void D3D11DeviceContext::DrawIndexedInstanced(
          UINT            IndexCountPerInstance,
          UINT            InstanceCount,
          UINT            StartIndexLocation,
          INT             BaseVertexLocation,
          UINT            StartInstanceLocation) {
    m_context->drawIndexed(
      IndexCountPerInstance,
      InstanceCount,
      StartIndexLocation,
      BaseVertexLocation,
      StartInstanceLocation);
  }
  
  
  void D3D11DeviceContext::DrawIndexedInstancedIndirect(
          ID3D11Buffer*   pBufferForArgs,
          UINT            AlignedByteOffsetForArgs) {
    Logger::err("D3D11DeviceContext::DrawIndexedInstancedIndirect: Not implemented");
  }
  
  
  void D3D11DeviceContext::DrawInstancedIndirect(
          ID3D11Buffer*   pBufferForArgs,
          UINT            AlignedByteOffsetForArgs) {
    Logger::err("D3D11DeviceContext::DrawInstancedIndirect: Not implemented");
  }
  
  
  void D3D11DeviceContext::Dispatch(
          UINT            ThreadGroupCountX,
          UINT            ThreadGroupCountY,
          UINT            ThreadGroupCountZ) {
    m_context->dispatch(
      ThreadGroupCountX,
      ThreadGroupCountY,
      ThreadGroupCountZ);
  }
  
  
  void D3D11DeviceContext::DispatchIndirect(
          ID3D11Buffer*   pBufferForArgs,
          UINT            AlignedByteOffsetForArgs) {
    Logger::err("D3D11DeviceContext::DispatchIndirect: Not implemented");
  }
  
  
  void D3D11DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout) {
    Logger::err("D3D11DeviceContext::IASetInputLayout: Not implemented");
  }
  
  
  void D3D11DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) {
    if (m_state.ia.primitiveTopology != Topology) {
      m_state.ia.primitiveTopology = Topology;
      
      Rc<DxvkInputAssemblyState> iaState;
      
      switch (Topology) {
        case D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED:
          break;
        
        case D3D11_PRIMITIVE_TOPOLOGY_POINTLIST:
          iaState = new DxvkInputAssemblyState(
            VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
            VK_FALSE);
          break;
        
        case D3D11_PRIMITIVE_TOPOLOGY_LINELIST:
          iaState = new DxvkInputAssemblyState(
            VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
            VK_FALSE);
          break;
        
        case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP:
          iaState = new DxvkInputAssemblyState(
            VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,
            VK_TRUE);
          break;
        
        case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
          iaState = new DxvkInputAssemblyState(
            VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
            VK_FALSE);
          break;
        
        case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
          iaState = new DxvkInputAssemblyState(
            VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
            VK_TRUE);
          break;
        
        case D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ:
          iaState = new DxvkInputAssemblyState(
            VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,
            VK_FALSE);
          break;
        
        case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ:
          iaState = new DxvkInputAssemblyState(
            VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,
            VK_TRUE);
          break;
        
        case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ:
          iaState = new DxvkInputAssemblyState(
            VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY,
            VK_FALSE);
          break;
        
        case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ:
          iaState = new DxvkInputAssemblyState(
            VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY,
            VK_TRUE);
          break;
        
        default:
          Logger::err(str::format(
            "D3D11DeviceContext::IASetPrimitiveTopology: Unknown primitive topology: ",
            Topology));
      }
      
      m_context->setInputAssemblyState(iaState);
    }
  }
  
  
  void D3D11DeviceContext::IASetVertexBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer* const*              ppVertexBuffers,
    const UINT*                             pStrides,
    const UINT*                             pOffsets) {
    Logger::err("D3D11DeviceContext::IASetVertexBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::IASetIndexBuffer(
          ID3D11Buffer*                     pIndexBuffer,
          DXGI_FORMAT                       Format,
          UINT                              Offset) {
    Logger::err("D3D11DeviceContext::IASetIndexBuffer: Not implemented");
  }
  
  
  void D3D11DeviceContext::IAGetInputLayout(ID3D11InputLayout** ppInputLayout) {
    Logger::err("D3D11DeviceContext::IAGetInputLayout: Not implemented");
  }
  
  
  void D3D11DeviceContext::IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY* pTopology) {
    *pTopology = m_state.ia.primitiveTopology;
  }
  
  
  void D3D11DeviceContext::IAGetVertexBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer**                    ppVertexBuffers,
          UINT*                             pStrides,
          UINT*                             pOffsets) {
    Logger::err("D3D11DeviceContext::IAGetVertexBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::IAGetIndexBuffer(
          ID3D11Buffer**                    pIndexBuffer,
          DXGI_FORMAT*                      Format,
          UINT*                             Offset) {
    Logger::err("D3D11DeviceContext::IAGetIndexBuffer: Not implemented");
  }
  
  
  void D3D11DeviceContext::VSSetShader(
          ID3D11VertexShader*               pVertexShader,
          ID3D11ClassInstance* const*       ppClassInstances,
          UINT                              NumClassInstances) {
    auto shader = static_cast<D3D11VertexShader*>(pVertexShader);
    
    if (NumClassInstances != 0)
      Logger::err("D3D11DeviceContext::VSSetShader: Class instances not supported");
    
    if (m_state.vs.shader != shader) {
      m_state.vs.shader = shader;
      
      m_context->bindShader(VK_SHADER_STAGE_VERTEX_BIT,
        shader != nullptr ? shader->GetShader() : nullptr);
    }
  }
  
  
  void D3D11DeviceContext::VSSetConstantBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer* const*              ppConstantBuffers) {
    Logger::err("D3D11DeviceContext::VSSetConstantBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::VSSetShaderResources(
          UINT                              StartSlot,
          UINT                              NumViews,
          ID3D11ShaderResourceView* const*  ppShaderResourceViews) {
    Logger::err("D3D11DeviceContext::VSSetShaderResources: Not implemented");
  }
  
  
  void D3D11DeviceContext::VSSetSamplers(
          UINT                              StartSlot,
          UINT                              NumSamplers,
          ID3D11SamplerState* const*        ppSamplers) {
    Logger::err("D3D11DeviceContext::VSSetSamplers: Not implemented");
  }
  
  
  void D3D11DeviceContext::VSGetShader(
          ID3D11VertexShader**              ppVertexShader,
          ID3D11ClassInstance**             ppClassInstances,
          UINT*                             pNumClassInstances) {
    Logger::err("D3D11DeviceContext::VSGetShader: Not implemented");
  }
  
  
  void D3D11DeviceContext::VSGetConstantBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer**                    ppConstantBuffers) {
    Logger::err("D3D11DeviceContext::VSGetConstantBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::VSGetShaderResources(
          UINT                              StartSlot,
          UINT                              NumViews,
          ID3D11ShaderResourceView**        ppShaderResourceViews) {
    Logger::err("D3D11DeviceContext::VSGetShaderResources: Not implemented");
  }
  
  
  void D3D11DeviceContext::VSGetSamplers(
          UINT                              StartSlot,
          UINT                              NumSamplers,
          ID3D11SamplerState**              ppSamplers) {
    Logger::err("D3D11DeviceContext::VSGetSamplers: Not implemented");
  }
  
  
  void D3D11DeviceContext::HSSetShader(
          ID3D11HullShader*                 pHullShader,
          ID3D11ClassInstance* const*       ppClassInstances,
          UINT                              NumClassInstances) {
    Logger::err("D3D11DeviceContext::HSSetShader: Not implemented");
  }
  
  
  void D3D11DeviceContext::HSSetShaderResources(
          UINT                              StartSlot,
          UINT                              NumViews,
          ID3D11ShaderResourceView* const*  ppShaderResourceViews) {
    Logger::err("D3D11DeviceContext::HSSetShaderResources: Not implemented");
  }
  
  
  void D3D11DeviceContext::HSSetConstantBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer* const*              ppConstantBuffers) {
    Logger::err("D3D11DeviceContext::HSSetConstantBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::HSSetSamplers(
          UINT                              StartSlot,
          UINT                              NumSamplers,
          ID3D11SamplerState* const*        ppSamplers) {
    Logger::err("D3D11DeviceContext::HSSetSamplers: Not implemented");
  }
  
  
  void D3D11DeviceContext::HSGetShader(
          ID3D11HullShader**                ppHullShader,
          ID3D11ClassInstance**             ppClassInstances,
          UINT*                             pNumClassInstances) {
    Logger::err("D3D11DeviceContext::HSGetShader: Not implemented");
  }
  
  
  void D3D11DeviceContext::HSGetConstantBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer**                    ppConstantBuffers) {
    Logger::err("D3D11DeviceContext::HSGetConstantBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::HSGetShaderResources(
          UINT                              StartSlot,
          UINT                              NumViews,
          ID3D11ShaderResourceView**        ppShaderResourceViews) {
    Logger::err("D3D11DeviceContext::HSGetShaderResources: Not implemented");
  }
  
  
  void D3D11DeviceContext::HSGetSamplers(
          UINT                              StartSlot,
          UINT                              NumSamplers,
          ID3D11SamplerState**              ppSamplers) {
    Logger::err("D3D11DeviceContext::HSGetSamplers: Not implemented");
  }
  
  
  void D3D11DeviceContext::DSSetShader(
          ID3D11DomainShader*               pDomainShader,
          ID3D11ClassInstance* const*       ppClassInstances,
          UINT                              NumClassInstances) {
    Logger::err("D3D11DeviceContext::DSSetShader: Not implemented");
  }
  
  
  void D3D11DeviceContext::DSSetShaderResources(
          UINT                              StartSlot,
          UINT                              NumViews,
          ID3D11ShaderResourceView* const*  ppShaderResourceViews) {
    Logger::err("D3D11DeviceContext::DSSetShaderResources: Not implemented");
  }
  
  
  void D3D11DeviceContext::DSSetConstantBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer* const*              ppConstantBuffers) {
    Logger::err("D3D11DeviceContext::DSSetConstantBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::DSSetSamplers(
          UINT                              StartSlot,
          UINT                              NumSamplers,
          ID3D11SamplerState* const*        ppSamplers) {
    Logger::err("D3D11DeviceContext::DSSetSamplers: Not implemented");
  }
  
  
  void D3D11DeviceContext::DSGetShader(
          ID3D11DomainShader**              ppDomainShader,
          ID3D11ClassInstance**             ppClassInstances,
          UINT*                             pNumClassInstances) {
    Logger::err("D3D11DeviceContext::DSGetShader: Not implemented");
  }
  
  
  void D3D11DeviceContext::DSGetConstantBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer**                    ppConstantBuffers) {
    Logger::err("D3D11DeviceContext::DSGetConstantBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::DSGetShaderResources(
          UINT                              StartSlot,
          UINT                              NumViews,
          ID3D11ShaderResourceView**        ppShaderResourceViews) {
    Logger::err("D3D11DeviceContext::DSGetShaderResources: Not implemented");
  }
  
  
  void D3D11DeviceContext::DSGetSamplers(
          UINT                              StartSlot,
          UINT                              NumSamplers,
          ID3D11SamplerState**              ppSamplers) {
    Logger::err("D3D11DeviceContext::DSGetSamplers: Not implemented");
  }
  
  
  void D3D11DeviceContext::GSSetShader(
          ID3D11GeometryShader*             pShader,
          ID3D11ClassInstance* const*       ppClassInstances,
          UINT                              NumClassInstances) {
    Logger::err("D3D11DeviceContext::GSSetShader: Not implemented");
  }
  
  
  void D3D11DeviceContext::GSSetConstantBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer* const*              ppConstantBuffers) {
    Logger::err("D3D11DeviceContext::GSSetConstantBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::GSSetShaderResources(
          UINT                              StartSlot,
          UINT                              NumViews,
          ID3D11ShaderResourceView* const*  ppShaderResourceViews) {
    Logger::err("D3D11DeviceContext::GSSetShaderResources: Not implemented");
  }
  
  
  void D3D11DeviceContext::GSSetSamplers(
          UINT                              StartSlot,
          UINT                              NumSamplers,
          ID3D11SamplerState* const*        ppSamplers) {
    Logger::err("D3D11DeviceContext::GSSetSamplers: Not implemented");
  }
  
  
  void D3D11DeviceContext::GSGetShader(
          ID3D11GeometryShader**            ppGeometryShader,
          ID3D11ClassInstance**             ppClassInstances,
          UINT*                             pNumClassInstances) {
    Logger::err("D3D11DeviceContext::GSGetShader: Not implemented");
  }
  
  
  void D3D11DeviceContext::GSGetConstantBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer**                    ppConstantBuffers) {
    Logger::err("D3D11DeviceContext::GSGetConstantBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::GSGetShaderResources(
          UINT                              StartSlot,
          UINT                              NumViews,
          ID3D11ShaderResourceView**        ppShaderResourceViews) {
    Logger::err("D3D11DeviceContext::GSGetShaderResources: Not implemented");
  }
  
  
  void D3D11DeviceContext::GSGetSamplers(
          UINT                              StartSlot,
          UINT                              NumSamplers,
          ID3D11SamplerState**              ppSamplers) {
    Logger::err("D3D11DeviceContext::GSGetSamplers: Not implemented");
  }
  
  
  void D3D11DeviceContext::PSSetShader(
          ID3D11PixelShader*                pPixelShader,
          ID3D11ClassInstance* const*       ppClassInstances,
          UINT                              NumClassInstances) {
    auto shader = static_cast<D3D11PixelShader*>(pPixelShader);
    
    if (NumClassInstances != 0)
      Logger::err("D3D11DeviceContext::VSSetShader: Class instances not supported");
    
    if (m_state.ps.shader != shader) {
      m_state.ps.shader = shader;
      
      m_context->bindShader(VK_SHADER_STAGE_FRAGMENT_BIT,
        shader != nullptr ? shader->GetShader() : nullptr);
    }
  }
  
  
  void D3D11DeviceContext::PSSetConstantBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer* const*              ppConstantBuffers) {
    Logger::err("D3D11DeviceContext::PSSetConstantBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::PSSetShaderResources(
          UINT                              StartSlot,
          UINT                              NumViews,
          ID3D11ShaderResourceView* const*  ppShaderResourceViews) {
    Logger::err("D3D11DeviceContext::PSSetShaderResources: Not implemented");
  }
  
  
  void D3D11DeviceContext::PSSetSamplers(
          UINT                              StartSlot,
          UINT                              NumSamplers,
          ID3D11SamplerState* const*        ppSamplers) {
    Logger::err("D3D11DeviceContext::PSSetSamplers: Not implemented");
  }
  
  
  void D3D11DeviceContext::PSGetShader(
          ID3D11PixelShader**               ppPixelShader,
          ID3D11ClassInstance**             ppClassInstances,
          UINT*                             pNumClassInstances) {
    Logger::err("D3D11DeviceContext::PSGetShader: Not implemented");
  }
  
  
  void D3D11DeviceContext::PSGetConstantBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer**                    ppConstantBuffers) {
    Logger::err("D3D11DeviceContext::PSGetConstantBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::PSGetShaderResources(
          UINT                              StartSlot,
          UINT                              NumViews,
          ID3D11ShaderResourceView**        ppShaderResourceViews) {
    Logger::err("D3D11DeviceContext::PSGetShaderResources: Not implemented");
  }
  
  
  void D3D11DeviceContext::PSGetSamplers(
          UINT                              StartSlot,
          UINT                              NumSamplers,
          ID3D11SamplerState**              ppSamplers) {
    Logger::err("D3D11DeviceContext::PSGetSamplers: Not implemented");
  }
  
  
  void D3D11DeviceContext::CSSetShader(
          ID3D11ComputeShader*              pComputeShader,
          ID3D11ClassInstance* const*       ppClassInstances,
          UINT                              NumClassInstances) {
    Logger::err("D3D11DeviceContext::CSSetShader: Not implemented");
  }
  
  
  void D3D11DeviceContext::CSSetConstantBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer* const*              ppConstantBuffers) {
    Logger::err("D3D11DeviceContext::CSSetConstantBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::CSSetShaderResources(
          UINT                              StartSlot,
          UINT                              NumViews,
          ID3D11ShaderResourceView* const*  ppShaderResourceViews) {
    Logger::err("D3D11DeviceContext::CSSetShaderResources: Not implemented");
  }
  
  
  void D3D11DeviceContext::CSSetSamplers(
          UINT                              StartSlot,
          UINT                              NumSamplers,
          ID3D11SamplerState* const*        ppSamplers) {
    Logger::err("D3D11DeviceContext::CSSetSamplers: Not implemented");
  }
  
  
  void D3D11DeviceContext::CSSetUnorderedAccessViews(
          UINT                              StartSlot,
          UINT                              NumUAVs,
          ID3D11UnorderedAccessView* const* ppUnorderedAccessViews,
    const UINT*                             pUAVInitialCounts) {
    Logger::err("D3D11DeviceContext::CSSetUnorderedAccessViews: Not implemented");
  }
  
  
  void D3D11DeviceContext::CSGetShader(
          ID3D11ComputeShader**             ppComputeShader,
          ID3D11ClassInstance**             ppClassInstances,
          UINT*                             pNumClassInstances) {
    Logger::err("D3D11DeviceContext::CSGetShader: Not implemented");
  }
  
  
  void D3D11DeviceContext::CSGetConstantBuffers(
          UINT                              StartSlot,
          UINT                              NumBuffers,
          ID3D11Buffer**                    ppConstantBuffers) {
    Logger::err("D3D11DeviceContext::CSGetConstantBuffers: Not implemented");
  }
  
  
  void D3D11DeviceContext::CSGetShaderResources(
          UINT                              StartSlot,
          UINT                              NumViews,
          ID3D11ShaderResourceView**        ppShaderResourceViews) {
    Logger::err("D3D11DeviceContext::CSGetShaderResources: Not implemented");
  }
  
  
  void D3D11DeviceContext::CSGetSamplers(
          UINT                              StartSlot,
          UINT                              NumSamplers,
          ID3D11SamplerState**              ppSamplers) {
    Logger::err("D3D11DeviceContext::CSGetSamplers: Not implemented");
  }
  
  
  void D3D11DeviceContext::CSGetUnorderedAccessViews(
          UINT                              StartSlot,
          UINT                              NumUAVs,
          ID3D11UnorderedAccessView**       ppUnorderedAccessViews) {
    Logger::err("D3D11DeviceContext::CSGetUnorderedAccessViews: Not implemented");
  }
  
  
  void D3D11DeviceContext::OMSetRenderTargets(
          UINT                              NumViews,
          ID3D11RenderTargetView* const*    ppRenderTargetViews,
          ID3D11DepthStencilView*           pDepthStencilView) {
    // Update state vector for OMGetRenderTargets
    for (UINT i = 0; i < m_state.om.renderTargetViews.size(); i++) {
      D3D11RenderTargetView* view = nullptr;
      
      if ((i < NumViews) && (ppRenderTargetViews[i] != nullptr))
        view = static_cast<D3D11RenderTargetView*>(ppRenderTargetViews[i]);
      
      m_state.om.renderTargetViews.at(i) = view;
    }
    
    // TODO unbind overlapping shader resource views
    
    Rc<DxvkFramebuffer> framebuffer = nullptr;
    
    if (ppRenderTargetViews != nullptr || pDepthStencilView != nullptr) {
      // D3D11 doesn't have the concept of a framebuffer object,
      // so we'll just create a new one every time the render
      // target bindings are updated. Set up the attachments.
      DxvkRenderTargets attachments;
      
      for (UINT i = 0; i < m_state.om.renderTargetViews.size(); i++) {
        if (m_state.om.renderTargetViews.at(i) != nullptr)
          attachments.setColorTarget(i, m_state.om.renderTargetViews.at(i)->GetDXVKImageView());
      }
      
      // TODO implement depth-stencil views
      if (pDepthStencilView != nullptr)
        Logger::err("D3D11DeviceContext::OMSetRenderTargets: Depth-stencil view not supported");
      
      framebuffer = m_device->createFramebuffer(attachments);
    }
    
    // Bind the framebuffer object to the context
    m_state.om.framebuffer = framebuffer;
    m_context->bindFramebuffer(framebuffer);
  }
  
  
  void D3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews(
          UINT                              NumRTVs,
          ID3D11RenderTargetView* const*    ppRenderTargetViews,
          ID3D11DepthStencilView*           pDepthStencilView,
          UINT                              UAVStartSlot,
          UINT                              NumUAVs,
          ID3D11UnorderedAccessView* const* ppUnorderedAccessViews,
    const UINT*                             pUAVInitialCounts) {
    Logger::err("D3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews: Not implemented");
  }
  
  
  void D3D11DeviceContext::OMSetBlendState(
          ID3D11BlendState*                 pBlendState,
    const FLOAT                             BlendFactor[4],
          UINT                              SampleMask) {
    Logger::err("D3D11DeviceContext::OMSetBlendState: Not implemented");
  }
  
  
  void D3D11DeviceContext::OMSetDepthStencilState(
          ID3D11DepthStencilState*          pDepthStencilState,
          UINT                              StencilRef) {
    Logger::err("D3D11DeviceContext::OMSetDepthStencilState: Not implemented");
  }
  
  
  void D3D11DeviceContext::OMGetRenderTargets(
          UINT                              NumViews,
          ID3D11RenderTargetView**          ppRenderTargetViews,
          ID3D11DepthStencilView**          ppDepthStencilView) {
    if (ppRenderTargetViews != nullptr) {
      for (UINT i = 0; i < NumViews; i++)
        ppRenderTargetViews[i] = i < m_state.om.renderTargetViews.size()
          ? m_state.om.renderTargetViews.at(i).ref()
          : nullptr;
    }
    
    if (ppDepthStencilView != nullptr) {
      Logger::err("D3D11DeviceContext::OMGetRenderTargets: Stencil view not supported");
      *ppDepthStencilView = nullptr;
    }
  }
  
  
  void D3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews(
          UINT                              NumRTVs,
          ID3D11RenderTargetView**          ppRenderTargetViews,
          ID3D11DepthStencilView**          ppDepthStencilView,
          UINT                              UAVStartSlot,
          UINT                              NumUAVs,
          ID3D11UnorderedAccessView**       ppUnorderedAccessViews) {
    Logger::err("D3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews: Not implemented");
  }
  
  
  void D3D11DeviceContext::OMGetBlendState(
          ID3D11BlendState**                ppBlendState,
          FLOAT                             BlendFactor[4],
          UINT*                             pSampleMask) {
    Logger::err("D3D11DeviceContext::OMGetBlendState: Not implemented");
  }
  
  
  void D3D11DeviceContext::OMGetDepthStencilState(
          ID3D11DepthStencilState**         ppDepthStencilState,
          UINT*                             pStencilRef) {
    Logger::err("D3D11DeviceContext::OMGetDepthStencilState: Not implemented");
  }
  
  
  void D3D11DeviceContext::RSSetState(ID3D11RasterizerState* pRasterizerState) {
    auto rasterizerState = static_cast<D3D11RasterizerState*>(pRasterizerState);
    
    if (m_state.rs.state != rasterizerState) {
      m_state.rs.state = rasterizerState;
      
      // Use default state if the rasterizer
      // state is not explicitly defined.
      m_context->setRasterizerState(
        rasterizerState != nullptr
          ? rasterizerState->GetDXVKRasterizerState()
          : m_defaultRsState);
      
      // In D3D11, the rasterizer state defines
      // whether the scissor test is enabled, so
      // we have to update the scissor rectangles.
      this->ApplyViewportState();
    }
  }
  
  
  void D3D11DeviceContext::RSSetViewports(
          UINT                              NumViewports,
    const D3D11_VIEWPORT*                   pViewports) {
    m_state.rs.numViewports = NumViewports;
    
    for (uint32_t i = 0; i < NumViewports; i++)
      m_state.rs.viewports.at(i) = pViewports[i];
    
    this->ApplyViewportState();
  }
  
  
  void D3D11DeviceContext::RSSetScissorRects(
          UINT                              NumRects,
    const D3D11_RECT*                       pRects) {
    m_state.rs.numScissors = NumRects;
    
    for (uint32_t i = 0; i < NumRects; i++)
      m_state.rs.scissors.at(i) = pRects[i];
    
    if (m_state.rs.state != nullptr) {
      D3D11_RASTERIZER_DESC rsDesc;
      m_state.rs.state->GetDesc(&rsDesc);
      
      if (rsDesc.ScissorEnable)
        this->ApplyViewportState();
    }
  }
  
  
  void D3D11DeviceContext::RSGetState(ID3D11RasterizerState** ppRasterizerState) {
    *ppRasterizerState = m_state.rs.state.ref();
  }
  
  
  void D3D11DeviceContext::RSGetViewports(
          UINT*                             pNumViewports,
          D3D11_VIEWPORT*                   pViewports) {
    if (pViewports != nullptr) {
      for (uint32_t i = 0; i < *pNumViewports; i++) {
        if (i < m_state.rs.numViewports) {
          pViewports[i] = m_state.rs.viewports.at(i);
        } else {
          pViewports[i].TopLeftX = 0.0f;
          pViewports[i].TopLeftY = 0.0f;
          pViewports[i].Width    = 0.0f;
          pViewports[i].Height   = 0.0f;
          pViewports[i].MinDepth = 0.0f;
          pViewports[i].MaxDepth = 0.0f;
        }
      }
    }
    
    *pNumViewports = m_state.rs.numViewports;
  }
  
  
  void D3D11DeviceContext::RSGetScissorRects(
          UINT*                             pNumRects,
          D3D11_RECT*                       pRects) {
    if (pRects != nullptr) {
      for (uint32_t i = 0; i < *pNumRects; i++) {
        if (i < m_state.rs.numScissors) {
          pRects[i] = m_state.rs.scissors.at(i);
        } else {
          pRects[i].left   = 0;
          pRects[i].top    = 0;
          pRects[i].right  = 0;
          pRects[i].bottom = 0;
        }
      }
    }
    
    *pNumRects = m_state.rs.numScissors;
  }
  
  
  void D3D11DeviceContext::SOSetTargets(
          UINT                              NumBuffers,
          ID3D11Buffer* const*              ppSOTargets,
    const UINT*                             pOffsets) {
    Logger::err("D3D11DeviceContext::SOSetTargets: Not implemented");
  }
  
  
  void D3D11DeviceContext::SOGetTargets(
          UINT                              NumBuffers,
          ID3D11Buffer**                    ppSOTargets) {
    Logger::err("D3D11DeviceContext::SOGetTargets: Not implemented");
  }
  
  
  void D3D11DeviceContext::ApplyViewportState() {
    // We cannot set less than one viewport in Vulkan, and
    // rendering with no active viewport is illegal anyway.
    if (m_state.rs.numViewports == 0)
      return;
    
    std::array<VkViewport, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE> viewports;
    std::array<VkRect2D,   D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE> scissors;
    
    // TODO find out if we need to flip the viewports vertically
    for (uint32_t i = 0; i < m_state.rs.numViewports; i++) {
      const D3D11_VIEWPORT& vp = m_state.rs.viewports.at(i);
      
      viewports.at(i) = VkViewport {
        vp.TopLeftX, vp.TopLeftY,
        vp.Width,    vp.Height,
        vp.MaxDepth, vp.MinDepth,
      };
    }
    
    // Scissor rectangles. Vulkan does not provide an easy way
    // to disable the scissor test, so we'll have to set scissor
    // rects that are at least as large as the framebuffer.
    bool enableScissorTest = false;
    
    if (m_state.rs.state != nullptr) {
      D3D11_RASTERIZER_DESC rsDesc;
      m_state.rs.state->GetDesc(&rsDesc);
      enableScissorTest = rsDesc.ScissorEnable;
    }
    
    for (uint32_t i = 0; i < m_state.rs.numViewports; i++) {
      // TODO D3D11 docs aren't clear about what should happen
      // when there are undefined scissor rects for a viewport.
      // Figure out what it does on Windows.
      if (enableScissorTest && (i < m_state.rs.numScissors)) {
        const D3D11_RECT& sr = m_state.rs.scissors.at(i);
        
        scissors.at(i) = VkRect2D {
          VkOffset2D { sr.left, sr.top },
          VkExtent2D {
            static_cast<uint32_t>(sr.right  - sr.left),
            static_cast<uint32_t>(sr.bottom - sr.top) } };
      } else {
        scissors.at(i) = VkRect2D {
          VkOffset2D { 0, 0 },
          VkExtent2D {
            D3D11_VIEWPORT_BOUNDS_MAX,
            D3D11_VIEWPORT_BOUNDS_MAX } };
      }
    }
    
    m_context->setViewports(
      m_state.rs.numViewports,
      viewports.data(),
      scissors.data());
  }
  
}
