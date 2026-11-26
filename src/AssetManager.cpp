#include "AssetManager.hpp"
#include <stdexcept>

AssetManager::AssetManager(const std::string& assetDir) : dir(assetDir) {
    const char* types[] = {"domestic", "fat", "stray"};
    const char* moods[] = {"idle", "happy", "eat", "full", "over", "hungry"};
    for (const char* t : types)
        for (const char* m : moods)
            loadTexture(std::string("cats/") + t + "_" + m);

    const char* icons[] = {"fish", "dry", "milk", "heart", "sparkle"};
    for (const char* i : icons)
        loadTexture(std::string("ui/") + i);

    const char* sounds[] = {"meow", "crunch", "munch", "splash", "happy", "buzz", "pop"};
    for (const char* s : sounds)
        loadSound(s);

    if (!font.openFromFile(dir + "fonts/DejaVuSans.ttf"))
        throw std::runtime_error("Cannot load font: " + dir + "fonts/DejaVuSans.ttf");

    voices.reserve(8);
    for (int i = 0; i < 8; ++i)
        voices.emplace_back(buffers.begin()->second);
}

void AssetManager::loadTexture(const std::string& name) {
    sf::Texture& tex = textures[name];
    if (!tex.loadFromFile(dir + name + ".png"))
        throw std::runtime_error("Cannot load picture: " + dir + name + ".png");
    tex.setSmooth(true);
}

void AssetManager::loadSound(const std::string& name) {
    sf::SoundBuffer& buf = buffers[name];
    if (!buf.loadFromFile(dir + "sounds/" + name + ".wav"))
        throw std::runtime_error("Cannot load sound: " + dir + "sounds/" + name + ".wav");
}

const sf::Texture& AssetManager::texture(const std::string& name) const {
    return textures.at(name);
}

const sf::Font& AssetManager::getFont() const {
    return font;
}

void AssetManager::play(const std::string& soundName) {
    auto it = buffers.find(soundName);
    if (it == buffers.end()) return;
    sf::Sound& voice = voices[nextVoice];
    nextVoice = (nextVoice + 1) % voices.size();
    voice.setBuffer(it->second);
    voice.play();
}
