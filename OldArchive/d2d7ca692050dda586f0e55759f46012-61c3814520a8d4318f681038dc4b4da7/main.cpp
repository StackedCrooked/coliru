D3D_FEATURE_LEVEL targetlevel = (D3D_FEATURE_LEVEL)featurelevel;
D3D_FEATURE_LEVEL* usedfeaturelevel = reinterpret_cast<D3D_FEATURE_LEVEL*>( &featurelevel );
r = D3D11CreateDeviceAndSwapChain( deviceadapter, 
	deviceadapter != null ? D3D_DRIVER_TYPE_UNKNOWN : (D3D_DRIVER_TYPE)drivertype,
	null, (D3D11_CREATE_DEVICE_FLAG)creationflags, &targetlevel, 1, D3D11_SDK_VERSION, 
	&swapchaindesc, &swapchain, &device, usedfeaturelevel, &devicecontext); 

if ( r != 0 ) {
	r = D3D11CreateDeviceAndSwapChain( deviceadapter, deviceadapter != null ? D3D_DRIVER_TYPE_UNKNOWN : (D3D_DRIVER_TYPE)drivertype, 
		null, (D3D11_CREATE_DEVICE_FLAG)creationflags, null, 0, D3D11_SDK_VERSION,
		&swapchaindesc, &swapchain, &device, usedfeaturelevel, &devicecontext );
	if ( r != 0 ) {
		swapchaindesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		r = D3D11CreateDeviceAndSwapChain( deviceadapter, deviceadapter != null ? D3D_DRIVER_TYPE_UNKNOWN : (D3D_DRIVER_TYPE)drivertype, 
			null, (D3D11_CREATE_DEVICE_FLAG)creationflags, null, 0, D3D11_SDK_VERSION,
			&swapchaindesc, &swapchain, &device, usedfeaturelevel, &devicecontext );
		if ( r != 0 )
			throw FurrovineException( "Unable to create a DirectX Device or SwapChain Factory", r );
	}
}