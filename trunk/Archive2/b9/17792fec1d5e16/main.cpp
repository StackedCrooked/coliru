#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>

std::string h3d_header_str = R"_____(
#pragma once
#ifndef DLL
#if defined(WIN32)||defined(_WINDOWS)
#define DLL extern "C"__declspec(dllimport)
#else
#if defined(__GNUC__)&&__GNUC__>=4
#define DLL extern "C"__attribute__ ((visibility("default")))
#else
#define DLL extern "C"
#endif
#endif
#endif
typedef int H3DRes;
typedef int H3DNode;
######################################const H3DNode H3DRootNode=1;
struct H3DOptions
{
enum List
{
MaxLogLevel=1,
MaxNumMessages,
TrilinearFiltering,
MaxAnisotropy,
TexCompression,
SRGBLinearization,
LoadTextures,
FastAnimation,
ShadowMapSize,
SampleCount,
WireframeMode,
DebugViewMode,
DumpFailedShaders,
GatherTimeStats
};
};
struct H3DStats
{
enum List
{
TriCount=100,
BatchCount,
LightPassCount,
FrameTime,
AnimationTime,
GeoUpdateTime,
ParticleSimTime,
FwdLightsGPUTime,
DefLightsGPUTime,
ShadowsGPUTime,
ParticleGPUTime,
TextureVMem,
GeometryVMem
};
};
struct H3DResTypes
{
enum List
{
Undefined=0,
SceneGraph,
Geometry,
Animation,
Material,
Code,
Shader,
Texture,
ParticleEffect,
Pipeline
};
};
struct H3DResFlags
{
enum Flags
{
NoQuery=1,
NoTexCompression=2,
NoTexMipmaps=4,
TexCubemap=8,
TexDynamic=16,
TexRenderable=32,
TexSRGB=64
};
};
struct H3DFormats
{
enum List
{
Unknown=0,
TEX_BGRA8,
TEX_DXT1,
TEX_DXT3,
TEX_DXT5,
TEX_RGBA16F,
TEX_RGBA32F
};
};
struct H3DGeoRes
{
enum List
{
GeometryElem=200,
GeoIndexCountI,
GeoVertexCountI,
GeoIndices16I,
GeoIndexStream,
GeoVertPosStream,
GeoVertTanStream,
GeoVertStaticStream
};
};
struct H3DAnimRes
{
enum List
{
EntityElem=300,
EntFrameCountI
};
};
struct H3DMatRes
{
enum List
{
MaterialElem=400,
SamplerElem,
UniformElem,
MatClassStr,
MatLinkI,
MatShaderI,
SampNameStr,
SampTexResI,
UnifNameStr,
UnifValueF4
};
};
struct H3DShaderRes
{
enum List
{
ContextElem=600,
SamplerElem,
UniformElem,
ContNameStr,
SampNameStr,
SampDefTexResI,
UnifNameStr,
UnifSizeI,
UnifDefValueF4
};
};
struct H3DTexRes
{
enum List
{
TextureElem=700,
ImageElem,
TexFormatI,
TexSliceCountI,
ImgWidthI,
ImgHeightI,
ImgPixelStream
};
};
struct H3DPartEffRes
{
enum List
{
ParticleElem=800,
ChanMoveVelElem,
ChanRotVelElem,
ChanSizeElem,
ChanColRElem,
ChanColGElem,
ChanColBElem,
ChanColAElem,
PartLifeMinF,
PartLifeMaxF,
ChanStartMinF,
ChanStartMaxF,
ChanEndRateF,
ChanDragElem
};
};
struct H3DPipeRes
{
enum List
{
StageElem=900,
StageNameStr,
StageActivationI
};
};
struct H3DNodeTypes
{
enum List
{
Undefined=0,
Group,
Model,
Mesh,
Joint,
Light,
Camera,
Emitter
};
};
struct H3DNodeFlags
{
enum List
{
NoDraw=1,
NoCastShadow=2,
NoRayQuery=4,
Inactive=7
};
};
struct H3DNodeParams
{
enum List
{
NameStr=1,
AttachmentStr
};
};
struct H3DModel
{
enum List
{
GeoResI=200,
SWSkinningI,
LodDist1F,
LodDist2F,
LodDist3F,
LodDist4F,
AnimCountI
};
};
struct H3DMesh
{
enum List
{
MatResI=300,
BatchStartI,
BatchCountI,
VertRStartI,
VertREndI,
LodLevelI
};
};
struct H3DJoint
{
enum List
{
JointIndexI=400
};
};
struct H3DLight
{
enum List
{
MatResI=500,
RadiusF,
FovF,
ColorF3,
ColorMultiplierF,
ShadowMapCountI,
ShadowSplitLambdaF,
ShadowMapBiasF,
LightingContextStr,
ShadowContextStr
};
};
struct H3DCamera
{
enum List
{
PipeResI=600,
OutTexResI,
OutBufIndexI,
LeftPlaneF,
RightPlaneF,
BottomPlaneF,
TopPlaneF,
NearPlaneF,
FarPlaneF,
ViewportXI,
ViewportYI,
ViewportWidthI,
ViewportHeightI,
OrthoI,
OccCullingI
};
};
struct H3DEmitter
{
enum List
{
MatResI=700,
PartEffResI,
MaxCountI,
RespawnCountI,
DelayF,
EmissionRateF,
SpreadAngleF,
ForceF3
};
};
struct H3DModelUpdateFlags
{
enum Flags
{
Animation=1,
Geometry=2
};
};
DLL const char*h3dGetVersionString();
DLL bool h3dCheckExtension(const char*extensionName);
DLL bool h3dGetError();
DLL bool h3dInit();
DLL void h3dRelease();
DLL void h3dRender(H3DNode cameraNode);
DLL void h3dFinalizeFrame();
DLL void h3dClear();
DLL const char*h3dGetMessage(int*level,float*time);
DLL float h3dGetOption(H3DOptions::List param);
DLL bool h3dSetOption(H3DOptions::List param,float value);
DLL float h3dGetStat(H3DStats::List param,bool reset);
DLL void h3dShowOverlays(const float*verts,int vertCount,float colR,float colG,float colB,float colA,H3DRes materialRes,int flags);
DLL void h3dClearOverlays();
DLL int h3dGetResType(H3DRes res);
DLL const char*h3dGetResName(H3DRes res);
DLL H3DRes h3dGetNextResource(int type,H3DRes start);
DLL H3DRes h3dFindResource(int type,const char*name);
DLL H3DRes h3dAddResource(int type,const char*name,int flags);
DLL H3DRes h3dCloneResource(H3DRes sourceRes,const char*name);
DLL int h3dRemoveResource(H3DRes res);
DLL bool h3dIsResLoaded(H3DRes res);
DLL bool h3dLoadResource(H3DRes res,const char*data,int size);
DLL void h3dUnloadResource(H3DRes res);
DLL int h3dGetResElemCount(H3DRes res,int elem);
DLL int h3dFindResElem(H3DRes res,int elem,int param,const char*value);
DLL int h3dGetResParamI(H3DRes res,int elem,int elemIdx,int param);
DLL void h3dSetResParamI(H3DRes res,int elem,int elemIdx,int param,int value);
DLL float h3dGetResParamF(H3DRes res,int elem,int elemIdx,int param,int compIdx);
DLL void h3dSetResParamF(H3DRes res,int elem,int elemIdx,int param,int compIdx,float value);
DLL const char*h3dGetResParamStr(H3DRes res,int elem,int elemIdx,int param);
DLL void h3dSetResParamStr(H3DRes res,int elem,int elemIdx,int param,const char*value);
DLL void*h3dMapResStream(H3DRes res,int elem,int elemIdx,int stream,bool read,bool write);
DLL void h3dUnmapResStream(H3DRes res);
DLL H3DRes h3dQueryUnloadedResource(int index);
DLL void h3dReleaseUnusedResources();
DLL H3DRes h3dCreateTexture(const char*name,int width,int height,int fmt,int flags);
DLL void h3dSetShaderPreambles(const char*vertPreamble,const char*fragPreamble);
DLL bool h3dSetMaterialUniform(H3DRes materialRes,const char*name,float a,float b,float c,float d);
DLL void h3dResizePipelineBuffers(H3DRes pipeRes,int width,int height);
DLL bool h3dGetRenderTargetData(H3DRes pipelineRes,const char*targetName,int bufIndex,int*width,int*height,int*compCount,void*dataBuffer,int bufferSize);
DLL int h3dGetNodeType(H3DNode node);
DLL H3DNode h3dGetNodeParent(H3DNode node);
DLL bool h3dSetNodeParent(H3DNode node,H3DNode parent);
DLL H3DNode h3dGetNodeChild(H3DNode node,int index);
DLL H3DNode h3dAddNodes(H3DNode parent,H3DRes sceneGraphRes);
DLL void h3dRemoveNode(H3DNode node);
DLL bool h3dCheckNodeTransFlag(H3DNode node,bool reset);
DLL void h3dGetNodeTransform(H3DNode node,float*tx,float*ty,float*tz,float*rx,float*ry,float*rz,float*sx,float*sy,float*sz);
DLL void h3dSetNodeTransform(H3DNode node,float tx,float ty,float tz,float rx,float ry,float rz,float sx,float sy,float sz);
DLL void h3dGetNodeTransMats(H3DNode node,const float**relMat,const float**absMat);
DLL void h3dSetNodeTransMat(H3DNode node,const float*mat4x4);
DLL int h3dGetNodeParamI(H3DNode node,int param);
DLL void h3dSetNodeParamI(H3DNode node,int param,int value);
DLL float h3dGetNodeParamF(H3DNode node,int param,int compIdx);
DLL void h3dSetNodeParamF(H3DNode node,int param,int compIdx,float value);
DLL const char*h3dGetNodeParamStr(H3DNode node,int param);
DLL void h3dSetNodeParamStr(H3DNode node,int param,const char*value);
DLL int h3dGetNodeFlags(H3DNode node);
DLL void h3dSetNodeFlags(H3DNode node,int flags,bool recursive);
DLL void h3dGetNodeAABB(H3DNode node,float*minX,float*minY,float*minZ,float*maxX,float*maxY,float*maxZ);
DLL int h3dFindNodes(H3DNode startNode,const char*name,int type);
DLL H3DNode h3dGetNodeFindResult(int index);
DLL void h3dSetNodeUniforms(H3DNode node,float*uniformData,int count);
DLL int h3dCastRay(H3DNode node,float ox,float oy,float oz,float dx,float dy,float dz,int numNearest);
DLL bool h3dGetCastRayResult(int index,H3DNode*node,float*distance,float*intersection);
DLL int h3dCheckNodeVisibility(H3DNode node,H3DNode cameraNode,bool checkOcclusion,bool calcLod);
DLL H3DNode h3dAddGroupNode(H3DNode parent,const char*name);
DLL H3DNode h3dAddModelNode(H3DNode parent,const char*name,H3DRes geometryRes);
DLL void h3dSetupModelAnimStage(H3DNode modelNode,int stage,H3DRes animationRes,int layer,const char*startNode,bool additive);
DLL void h3dGetModelAnimParams(H3DNode modelNode,int stage,float*time,float*weight);
DLL void h3dSetModelAnimParams(H3DNode modelNode,int stage,float time,float weight);
DLL bool h3dSetModelMorpher(H3DNode modelNode,const char*target,float weight);
DLL void h3dUpdateModel(H3DNode modelNode,int flags);
DLL H3DNode h3dAddMeshNode(H3DNode parent,const char*name,H3DRes materialRes,int batchStart,int batchCount,int vertRStart,int vertREnd);
DLL H3DNode h3dAddJointNode(H3DNode parent,const char*name,int jointIndex);
DLL H3DNode h3dAddLightNode(H3DNode parent,const char*name,H3DRes materialRes,const char*lightingContext,const char*shadowContext);
DLL H3DNode h3dAddCameraNode(H3DNode parent,const char*name,H3DRes pipelineRes);
DLL void h3dSetupCameraView(H3DNode cameraNode,float fov,float aspect,float nearDist,float farDist);
DLL void h3dGetCameraProjMat(H3DNode cameraNode,float*projMat);
DLL H3DNode h3dAddEmitterNode(H3DNode parent,const char*name,H3DRes materialRes,H3DRes particleEffectRes,int maxParticleCount,int respawnCount);
DLL void h3dUpdateEmitter(H3DNode emitterNode,float timeDelta);
DLL bool h3dHasEmitterFinished(H3DNode emitterNode);

)_____";

bool typex(std::string& str, std::string t)
{
    if(!str.compare(0, t.length(), t))
    {
        str = str.substr(t.length() + (t.back() == '*'? 0 : 1));
        return true;
    }
    return false;
}

std::string rs_type(std::string& str)
{
    if(typex(str, "void")) return "";
    if(typex(str, "bool")) return "h3d_bool";
    if(typex(str, "int")) return "c_int";
    if(typex(str, "int*")) return "*mut c_int";
    if(typex(str, "float")) return "c_float";
    if(typex(str, "float*")) return "*mut c_float";
    if(typex(str, "const float*")) return "*const c_float";
    if(typex(str, "const char*")) return "*const c_char";
    if(typex(str, "H3DNode")) return "H3DNode";
    if(typex(str, "H3DRes")) return "H3DRes";
    if(typex(str, "H3DOptions::List")) return "H3DOptions";
    if(typex(str, "H3DStats::List")) return "H3DStats";
    
    throw std::runtime_error(std::string("unk type: ") + str);
}

std::string func_name(std::string& str)
{
    auto idx = str.find("(");
    if(idx == str.npos) throw std::runtime_error(std::string("unk func: ") + str);
    auto result = str.substr(0, idx);
    str = str.substr(idx+1);
    return result;
}

bool func_arg(std::string& str, std::pair<std::string, std::string>& arg)
{
    if(str.front() != ';' && str.front() != ')')
    {
        auto type     = rs_type(str);
        auto paramidx = str.find_first_of(",)");
        auto param    = str.substr(0, paramidx);
        
        str = str.substr(paramidx+1);
        arg = std::make_pair(type, param);
        return true;
    }
    str = "";
    return false;
}

void expect(std::string& str, char c)
{
    if(str.empty() || str.front() != c)
        throw std::runtime_error(std::string("expected ") + c + " but found " + str);
}

std::string conv_func(std::string line)
{
    std::string& text = line;
    
    if(!text.compare(0, 3, "DLL"))
        text = text.substr(4);
        
    std::pair<std::string, std::string> arg;
    std::vector<std::pair<std::string, std::string>> args;
        
    auto ret   = rs_type(text);
    auto fname = func_name(text);
        
    while(func_arg(text, arg))
        args.emplace_back(arg);
        
    std::ostringstream os;
    os << "pub fn " << fname << '(';
    for(auto& arg : args) os << arg.second << ": " << arg.first;
    os << ')';
    if(ret.size()) os << " -> " << ret;
    os << ';';
    return os.str();
}

std::string conv_typedef(std::string line)
{
    // skip typedef text
    line = line.substr(8);
    auto oritype    = rs_type(line);
    auto newtypeidx = line.find_first_of(";");
    auto newtype    = line.substr(0, newtypeidx);
    return std::string("pub type ").append(newtype).append(" = ").append(oritype).append(";");
}

int main()
{
    std::istringstream header(h3d_header_str);
    std::string line;
    int instruct = -1;
    //bool inenum   = false;
    std::string struname;
    
    while(std::getline(header, line))
    {
        if(line.size() && line.front() != '#')
        {
            if(instruct != -1)
            {
                if(line[0] == '{')
                {
                    ++instruct;
                    if(instruct == 1)
                    {
                        std::cout << "#[repr(C)]\n" << "enum " << struname << "\n{\n";
                    }
                    continue;
                }
                
                if(line[0] == '}')
                {
                    --instruct;
                    if(instruct == 0)
                    {
                        std::cout << "}\n";
                        instruct = -1;
                    }
                    continue;
                }
                
                if(instruct == 2)
                {
                    std::cout << "    " << line << '\n'; // enum
                }
            }
            else if(!line.compare(0, 7, "struct "))
            {
                struname =  line.substr(7);
                instruct = 0;
            }
            else if(!line.compare(0, 8, "typedef "))
            {
                std::cout << conv_typedef(line) << '\n';
            }
            else
            {
                std::cout << conv_func(line) << '\n';
            }
        }
    }
    
}