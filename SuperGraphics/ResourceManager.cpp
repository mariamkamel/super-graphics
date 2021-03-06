#include "ResourceManager.h"

unordered_map<string, Shader*> ResourceManager::shaders;
unordered_map<string, Texture*> ResourceManager::textures;

void ResourceManager::initializeShaders()
{
    shaders["programShader"] = new Shader("shaders/VertexShader.vertexshader", "shaders/FragmentShader.fragmentshader");
    shaders["cubemapShader"] = new Shader("shaders/cubemap.vertexshader", "shaders/cubemap.fragmentshader");
    shaders["skyboxShader"] = new Shader("shaders/skybox.vertexshader", "shaders/skybox.fragmentshader");
}

void ResourceManager::initializeTextures()
{
    textures["cat"] = new Texture("Assets/cat.png", 0);
    textures["bricks"] = new Texture("Assets/bricks.jpg", 0);

    textures["box"] = new Texture(vector<string> {
        "Assets/box/box.jpg",
        "Assets/box/box.jpg",
        "Assets/box/box.jpg",
        "Assets/box/box.jpg",
        "Assets/box/box.jpg",
        "Assets/box/box.jpg"
    }, 0);

    textures["skybox"] = new Texture(vector<string> {
        "Assets/skybox/skybox_right.jpg",
        "Assets/skybox/skybox_left.jpg",
        "Assets/skybox/skybox_up.jpg",
        "Assets/skybox/skybox_down.jpg",
        "Assets/skybox/skybox_back.jpg",
        "Assets/skybox/skybox_front.jpg"
    }, 0);
}

void ResourceManager::initializeResources()
{
    initializeShaders();
    initializeTextures();
}

Shader * ResourceManager::getShader(string shaderName)
{
    return shaders[shaderName];
}

Texture * ResourceManager::getTexture(string textureName)
{
    return ResourceManager::textures[textureName];
}

void ResourceManager::bindCamera(FPCamera * activeCamera)
{
    for (auto &shader : shaders) {
        shader.second->setMat4("ProjectionMatrix", &activeCamera->GetProjectionMatrix()[0][0]);
        shader.second->setMat4("ViewMatrix", &activeCamera->GetViewMatrix()[0][0]);
    }
}

Shader * ResourceManager::getAppropriateShader(Texture * texture)
{
    if (texture && texture->textureType == GL_TEXTURE_CUBE_MAP) {
        return ResourceManager::getShader("cubemapShader");
    } else {
        return ResourceManager::getShader("programShader");
    }
}

ResourceManager::~ResourceManager()
{
    for (auto &shader : shaders) {
        delete shader.second;
    }
    for (auto &texture : textures) {
        delete texture.second;
    }
}
