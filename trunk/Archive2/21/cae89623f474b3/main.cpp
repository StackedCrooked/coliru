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

            Concurrency::accelerator_view dxView = Concurrency::direct3d::create_accelerator_view(device);
            
            UINT bufferSize = NumPixels;
            D3D11_BUFFER_DESC bufferDesc =
            {
                bufferSize * sizeof(Color),
                D3D11_USAGE_DEFAULT,
                D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS,
                0 /* no CPU access */,
                D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS /* misc flags */,
                sizeof(Color)
            };
            D3D11_SUBRESOURCE_DATA resourceData;
            ZeroMemory(&resourceData, sizeof(D3D11_SUBRESOURCE_DATA));

            std::vector<Color> pixels(bufferSize);

            resourceData.pSysMem = &pixels[0];
            CComPtr<ID3D11Buffer> buffer;
            hr = device->CreateBuffer(&bufferDesc, &resourceData, &buffer);
            assert(SUCCEEDED(hr));