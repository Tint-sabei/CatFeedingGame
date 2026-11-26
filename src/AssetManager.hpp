#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>

class AssetManager {
private:
    std::string dir;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::SoundBuffer> buffers;  
    std::vector<sf::Sound> voices;                   
    std::size_t nextVoice = 0;
    sf::Font font;

    void loadTexture(const std::string& name);
    void loadSound(const std::string& name);

public:
    explicit AssetManager(const std::string& assetDir);

    const sf::Texture& texture(const std::string& name) const;
    const sf::Font& getFont() const;
    void play(const std::string& soundName);
};

#endif // ASSET_MANAGER_HPP
