
//**| DEFERRED |**********************************************************/

// The G-Buffer will store pre-lighting data about each pixel in the scene, e.g. normal, diffuse colour, etc.
// There is no rule about what makes up a G-Buffer, there are many choices and trade-offs. There is a performance
// advantage to store the minimum of data, but storing more data gives more flexibility to the renderer
// For this tutorial, we will keep it extremely simple, and ignore performance issues:
//   GBuffer is three 8-bit RGBA textures:
//   1. Pixel diffuse colour in RGB, specular strength in Alpha (before lighting, i.e. the basic colour and shininess of that pixel)
//   2. Pixel world normal in RGB, Alpha unused
//   3. Pixel world position in RGB, Alpha unused
// In the first rendering pass, all the scene geometry is rendered to these three textures, *simultaneously*
ID3D11Texture2D*          GBuffer[3];
ID3D11RenderTargetView*   GBufferRenderTarget[3];
ID3D11ShaderResourceView* GBufferShaderResource[3];
ID3DX11EffectShaderResourceVariable* GBufferShaderVar[3];

//************************************************************************/