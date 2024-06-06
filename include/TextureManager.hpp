#pragma once

#include <unordered_map>
#include <string>

#include "raylib.h"

class TextureManager {
public:
    TextureManager();
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    ~TextureManager();

    void clear();
    Texture2D* loadTexture(const std::string& name, const std::string& filePath);
    Texture2D* getTexture(const std::string &name);
    Texture2D* getFallbackTexture();
    void unloadTexture(const std::string& name);
    size_t getNumTextures();


private:
    std::unordered_map<std::string, Texture2D*> m_textures;
};

