#include <SFML/Graphics.hpp>

class Map
{
public:
    Map() = default;

    void initialize();
    void draw(sf::RenderTarget& target) const;

    // lookup if the position in world coordinates is a wall tile
    bool checkWallCollision(sf::Vector2f point) const;

private:
    void populateWallBoundingBoxes(const std::vector<int>& tiles);

    sf::Texture m_backgroundTileset{"../../assets/sprites/background-tileset.png"};
    sf::Texture m_wallsTileset{"../../assets/sprites/walls-tileset.png"};
    sf::VertexArray m_backgroundVertices;
    sf::VertexArray m_wallsVertices;
    static constexpr sf::Vector2u s_mapSize {20, 15};
    sf::FloatRect m_boundingBoxes[s_mapSize.x][s_mapSize.y];
};