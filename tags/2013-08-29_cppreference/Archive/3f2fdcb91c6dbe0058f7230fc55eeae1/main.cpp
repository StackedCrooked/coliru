    class furrovineexport Texture2D : public Texture {
	protected:
		ID3D11Texture2D* tex2tex;
		union {
			D3D11_TEXTURE2D_DESC tex2desc;
			struct {
				uint tex2width;
				uint tex2height;
				uint tex2miplevels;
				uint tex2arraysize;
				union {
					DepthStencilFormat tex2depthformat;
					SurfaceFormat tex2surfaceformat;
				};
				uint tex2samplecount;
				uint tex2samplequality;
				ResourceUsage tex2usage;
				BindFlags tex2binding;
				CpuAccessFlags tex2access;
				uint tex2misc;
			};
		};

		virtual lword Create () override {
			apiresult r = 0;

			if ( tex2tex == null )
				r = device->Device().CreateTexture2D( &tex2desc, null, &tex2tex );
			
			if ( shaderresourceview == null &&
				(tex2binding & BindFlags::ShaderResource) == BindFlags::ShaderResource ) {

				shaderresourceviewdesc.Format = tex2desc.Format;
				shaderresourceviewdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				shaderresourceviewdesc.Texture2D.MipLevels = -1;
				shaderresourceviewdesc.Texture2D.MostDetailedMip = 0;

				r |= device->Device().CreateShaderResourceView( tex2tex, &shaderresourceviewdesc, &shaderresourceview );
			}

			return r;
		}

	public:

		Texture2D ( GraphicsDevice* graphicsdevice ) : Texture(graphicsdevice), tex2tex(null) {

		}

		Texture2D ( GraphicsDevice* graphicsdevice, ID3D11Texture2D* origintexture2d, bool create = true ) : Texture( graphicsdevice ), tex2tex(null) {
			if ( origintexture2d != null ) {
				tex2tex = origintexture2d;
				tex2tex->GetDesc( &tex2desc );

				if ( create )
					Create(  );
			}
		}
			
		Texture2D ( GraphicsDevice* graphicsdevice, int texturewidth, int textureheight, int mipmapcount, SurfaceFormat format, bool create = true ) : Texture(graphicsdevice), tex2tex(null) {
			Mem::Zero( tex2desc );
			
			tex2desc.Width = texturewidth;
			tex2desc.Height = textureheight;
			tex2desc.MipLevels = mipmapcount;
			tex2desc.ArraySize = 1;
			tex2desc.Format = (DXGI_FORMAT)format;
			tex2desc.Usage = (D3D11_USAGE)ResourceUsage::Default;
			tex2desc.BindFlags = (uint)BindFlags::ShaderResource;
			tex2desc.CPUAccessFlags = (uint)CpuAccessFlags::Default;
			tex2desc.MiscFlags = 0;
			tex2desc.SampleDesc.Count = 1;
			tex2desc.SampleDesc.Quality = 0;

			if ( create )
				Create();
		}

		Texture2D ( GraphicsDevice* graphicsdevice, int texturewidth, int textureheight, SurfaceFormat format, BindFlags bindingflags = BindFlags::ShaderResource, bool create = true ) : Texture(graphicsdevice), tex2tex(null) {
			Mem::Zero( tex2desc );
			
			tex2desc.Width = texturewidth;
			tex2desc.Height = textureheight;
			tex2desc.MipLevels = 1;
			tex2desc.ArraySize = 1;
			tex2desc.Format = (DXGI_FORMAT)format;
			tex2desc.Usage = (D3D11_USAGE)ResourceUsage::Default;
			tex2desc.BindFlags = (uint)bindingflags;
			tex2desc.CPUAccessFlags = (uint)CpuAccessFlags::Default;
			tex2desc.MiscFlags = 0;
			tex2desc.SampleDesc.Count = 1;
			tex2desc.SampleDesc.Quality = 0;

			if (create)
				Create();
		}

		Texture2D ( GraphicsDevice* graphicsdevice, int texturewidth, int textureheight, DepthStencilFormat format, BindFlags bindingflags = BindFlags::DepthStencil, bool create = true ) : Texture(graphicsdevice), tex2tex(null) {
			Mem::Zero( tex2desc );
			
			tex2desc.Width = texturewidth;
			tex2desc.Height = textureheight;
			tex2desc.MipLevels = 1;
			tex2desc.ArraySize = 1;
			tex2desc.Format = (DXGI_FORMAT)format;
			tex2desc.Usage = (D3D11_USAGE)ResourceUsage::Default;
			tex2desc.BindFlags = (uint)bindingflags;
			tex2desc.CPUAccessFlags = (uint)CpuAccessFlags::Default;
			tex2desc.MiscFlags = 0;
			tex2desc.SampleDesc.Count = 1;
			tex2desc.SampleDesc.Quality = 0;

			if (create)
				Create();
		}

		template <typename TPixelData> void SetData ( int mipmap, TPixelData* pixels, int count ) {
			SetData(0, null, pixels, 0, count);
		}

		template <typename TPixelData> void SetData ( TPixelData* pixels, int count ) {
			SetData(0, null, pixels, 0, count);
		}

		template <typename TPixelData> void SetData ( int mipmap, TPixelData* pixels, int start, int count ) {
			SetData(mipmap, null, pixels, start, count);
		}
		
		template <typename TPixelData> void SetData ( int mipmap, Rectangle& rect, TPixelData* pixels, int start, int count ) {
			SetData( mipmap, &rect, pixels, start, count );
		}

		template <typename TPixelData> void SetData ( int mipmap, Rectangle* rect, TPixelData* pixels, int start, int count ) {
			if ( device == null )
				return;

			apiresult r = 0;
			uint dest = D3D11CalcSubresource( mipmap, 0, tex2miplevels );
			uint pixelsize = ToByteSize( tex2surfaceformat );

			D3D11_BOX box;
			box.front = 0;
			box.back = 1;
			if ( rect != null ) {
				box.left = rect->Left;
				box.top = rect->Top;
				box.right = rect->Right();
				box.back = rect->Bottom();
			}

			if ( tex2desc.Usage == (uint)ResourceUsage::Default ) {
				device->DeviceContext().UpdateSubresource(tex2tex, dest, rect == null ? null : &box, pixels + start, tex2desc.Width * pixelsize, 0 );
			}
			else {

			}

		}

		virtual int Width () override {
			return tex2width;
		}

		virtual int Height () override {
			return tex2height;
		}

		~Texture2D () {
			if ( tex2tex != null ) {
				tex2tex->Release();
				tex2tex = null;
			}
		}
	
	};