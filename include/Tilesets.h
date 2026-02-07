#include <SFML/Graphics.hpp>
#include <LDtkLoader/Project.hpp>

class Tilesets
{
public:
    Tilesets() = default;

    void initialize(const ldtk::Project& project)
    {
        const auto& projectTilesets = project.allTilesets();
        m_textures.reserve(projectTilesets.size());
        const std::string projectDir = project.getFilePath().directory();
        for (const ldtk::Tileset& tileset : projectTilesets)
        {
            m_textures[tileset.uid] = sf::Texture{projectDir + tileset.path};
        }
    }

    inline const sf::Texture& getTexture(int uid) const { return m_textures.at(uid); }
    
private:
    std::unordered_map<int, sf::Texture> m_textures;
};