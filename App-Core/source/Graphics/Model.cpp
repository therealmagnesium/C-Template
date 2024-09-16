#include "Graphics/Model.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"
#include "Graphics/Texture.h"

#include "Core/Base.h"
#include "Core/Log.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices)

static std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type)
{
    std::vector<Texture> textures;
    for (u32 i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString path;
        material->GetTexture(type, i, &path);

        Texture texture = LoadTexture(path.C_Str(), RGBA);
        textures.push_back(texture);
    }

    return textures;
}

static Mesh ProcessMesh(Model& model, aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<u32> indices;

    for (u32 i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 v;

        v.x = mesh->mVertices[i].x;
        v.y = mesh->mVertices[i].y;
        v.z = mesh->mVertices[i].z;
        vertex.position = v;

        v.x = mesh->mNormals[i].x;
        v.y = mesh->mNormals[i].y;
        v.z = mesh->mNormals[i].z;
        vertex.normal = v;

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 w;
            w.x = mesh->mTextureCoords[0][i].x;
            w.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoord = w;
        }
        else
            vertex.texCoord = glm::vec2(0.f, 0.f);

        vertices.push_back(vertex);
    }

    for (u32 i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (u32 j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* aiMaterial = scene->mMaterials[mesh->mMaterialIndex];

        model.materials.resize(scene->mNumMaterials);
        Material& material = model.materials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps = LoadMaterialTextures(aiMaterial, aiTextureType_DIFFUSE);
        material.maps[MATERIAL_MAP_DIFFUSE].color = {1.f, 1.f, 1.f, 1.f};

        if (diffuseMaps.size() > 0)
            material.maps[MATERIAL_MAP_DIFFUSE].texture = diffuseMaps[0];

        std::vector<Texture> specularMaps = LoadMaterialTextures(aiMaterial, aiTextureType_SPECULAR);
        material.maps[MATERIAL_MAP_SPECULAR].color = {1.f, 1.f, 1.f, 1.f};

        if (specularMaps.size() > 0)
            material.maps[MATERIAL_MAP_SPECULAR].texture = specularMaps[0];
    }

    return Mesh(vertices.data(), vertices.size(), indices.data(), indices.size());
}

static void ProcessNode(Model& model, aiNode* node, const aiScene* scene)
{
    for (u32 i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        Mesh processedMesh = ProcessMesh(model, mesh, scene);
        processedMesh.materialIndex = mesh->mMaterialIndex;
        model.meshes.push_back(processedMesh);
    }

    for (u32 i = 0; i < node->mNumChildren; i++)
        ProcessNode(model, node->mChildren[i], scene);
}

Model LoadModel(const char* path)
{
    Model model;
    model.transform = glm::mat4(1.f);

    Assimp::Importer importer;
    const aiScene* aiScene = importer.ReadFile(path, ASSIMP_LOAD_FLAGS);

    if (!aiScene || aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiScene->mRootNode)
    {
        ERROR("Assimp error - %s", importer.GetErrorString());
        return model;
    }

    ProcessNode(model, aiScene->mRootNode, aiScene);

    return model;
}
