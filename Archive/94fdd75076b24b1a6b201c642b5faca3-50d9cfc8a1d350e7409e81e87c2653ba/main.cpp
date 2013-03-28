depthenabled = true;
depthwritemask = DepthWriteMask::All;
depthfunc = Comparison::Less;

stencilenabled = false;
stencilreference = 0;
stencilreadmask = 0xFF;
stencilwritemask = 0xFF;

// Stencil operations if pixel is front-facing.
frontstencilfail = StencilOperations::Keep;
frontstencilpassdepthfail = StencilOperations::Keep;
frontstencilpassdepthpass = StencilOperations::Keep;
frontstencilfunc = Comparison::Always;

// Stencil operations if pixel is back-facing.
backstencilfail = StencilOperations::Keep;
backstencilpassdepthfail = StencilOperations::Keep;
backstencilpassdepthpass = StencilOperations::Keep;
backstencilfunc = Comparison::Always;