#include <SFML/Graphics.hpp>

class Map
{
public:
    Map() = default;

    void initialize();
    void drawBackground(sf::RenderTarget& target) const;
    void drawWalls(sf::RenderTarget& target) const;
    void drawForeground(sf::RenderTarget& target) const;
    void drawLighting(sf::RenderTarget& target) const;

    // lookup if the position in world coordinates is a wall tile
    std::optional<sf::FloatRect> checkWallCollision(sf::FloatRect box) const;

private:
    void populateWallBoundingBoxes(const std::vector<int>& tiles);

    sf::Texture m_tileset{"../../assets/sprites/tileset.png"};
    sf::VertexArray m_backgroundVertices;
    sf::VertexArray m_wallsVertices;
    sf::VertexArray m_foregroundVertices;

    static constexpr sf::Vector2u s_mapSize {20, 15};
    sf::FloatRect m_staticColliders[s_mapSize.x][s_mapSize.y];

    sf::Texture m_lightingTexture{"../../assets/sprites/lighting.png"};
    sf::Sprite m_lightingSprite{m_lightingTexture};
};