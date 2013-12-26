            HRESULT hr = S_OK;
            
            UINT createDeviceFlags = 0;
            #ifdef _DEBUG 
                createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
            #endif 
            std::array<D3D_FEATURE_LEVEL, 1> featureLevels = { D3D_FEATURE_LEVEL_11_0 };

            CComPtr<ID3D11Device> device;
            D3D_FEATURE_LEVEL featureLevel;
            CComPtr<ID3D11DeviceContext> immediateContext;

            hr = D3D11CreateDevice(nullptr /* default adapter */,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr /* No software rasterizer */,
                createDeviceFlags,
                featureLevels.data(),
                UINT(featureLevels.size()),
                D3D11_SDK_VERSION,
                &device,
                &featureLevel,
                &immediateContext);
            assert(SUCCEEDED(hr));