#include <iostream>
#include <cassert>
#include "../include/TextureManager.hpp"

TextureManager::TextureManager() {
    loadTexture("fallback", "assets/textures/image_load_failed48.png");
}

TextureManager::~TextureManager() {
    clear();
}

void TextureManager::clear() {
    // Unload all textures
    for (auto& pair: m_textures) {
        UnloadTexture(*pair.second);
        delete pair.second;
    }
    m_textures.clear();
}

Texture2D* TextureManager::loadTexture(const std::string &name, const std::string &filePath) {
    auto it = m_textures.find(name);
    // If not found
    if (it == m_textures.end()){
        Texture2D loadedTexture = LoadTexture(filePath.c_str());
        if (loadedTexture.id == 0) {
            std::cerr << "Failed to load texture from path: " << filePath << std::endl;
            return nullptr;
        }

        auto* texture = new Texture2D(loadedTexture);
        assert(texture && texture->id != 0);
        m_textures[name] = texture;
        return texture;
    }
    return it->second;
}

Texture2D* TextureManager::getTexture(const std::string &name) {
    auto it = m_textures.find(name);
    if (it != m_textures.end())
        return it->second;
    return nullptr;
}

void TextureManager::unloadTexture(const std::string &name) {
    auto it = m_textures.find(name);
    if (it != m_textures.end()) {
        UnloadTexture(*(it->second));
        delete it->second;
        m_textures.erase(it);
    }
}

size_t TextureManager::getNumTextures() {
    return m_textures.size();
}

Texture2D *TextureManager::getFallbackTexture() {
    return getTexture("fallback");
}


