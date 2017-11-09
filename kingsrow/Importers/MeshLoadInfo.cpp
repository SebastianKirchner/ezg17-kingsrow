#include "MeshLoadInfo.h"
const MeshLoadInfo::ShaderLoadInfo* MeshLoadInfo::LIGHTING_SHADER = new ShaderLoadInfo(std::string("vertexShaderPath"), std::string("fragmentShaderPath"));
const MeshLoadInfo::ShaderLoadInfo* MeshLoadInfo::TEXTURE_SHADER = new ShaderLoadInfo(std::string("../kingsrow/Shader/Vertex/texture_vertex_shader.glsl"), std::string("../kingsrow/Shader/Fragment/texture_fragment_shader.glsl"));
const MeshLoadInfo::ShaderLoadInfo* MeshLoadInfo::SIMPLE_LIGHTING_SHADER = new ShaderLoadInfo(std::string("../kingsrow/Shader/Vertex/SimpleVertexShader.vertexshader"), std::string("../kingsrow/Shader/Fragment/SimpleFragmentShader.fragmentshader"));

const MeshLoadInfo::LoadInfo* MeshLoadInfo::BRIDGE = new LoadInfo(std::string("../kingsrow/Assets/Models/bridge_old.obj"), std::string("../kingsrow/Assets/Models/textures/wood_bridge.jpg"), SIMPLE_LIGHTING_SHADER, MeshLoadInfo::CollisionType::DYNAMIC, MeshLoadInfo::CollisionShapeType::CONVEX);

const MeshLoadInfo::LoadInfo* MeshLoadInfo::TREE = new LoadInfo(std::string("../kingsrow/Assets/Models/tree1_1.obj"), std::string("../kingsrow/Assets/Models/textures/BarkDecidious0194_7_S.jpg"), SIMPLE_LIGHTING_SHADER, MeshLoadInfo::CollisionType::DYNAMIC, MeshLoadInfo::CollisionShapeType::CONVEX);