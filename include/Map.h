#include <SFML/Graphics.hpp>

namespace ldtk
{
class Level;
class Layer;
}

class Map
{
public:
    Map() = default;

    void initialize(const ldtk::Level& level);

    enum Layer
    {
        BACKGROUND = 0,
        MIDGROUND = 1,
        FOREGROUND = 2,
        LIGHTING = 3,
        NUM_LAYERS = 4
    };
    void drawLayer(sf::RenderTarget& target, Layer layer) const;

    // lookup if the position in world coordinates is a wall tile
    std::optional<sf::FloatRect> checkWallCollision(sf::FloatRect box) const;

private:
    struct TileLayer
    {
        sf::VertexArray vertices;
        void draw(sf::RenderTarget& target) const;
    };
    std::array<TileLayer, NUM_LAYERS> m_tileLayers;
    void populateTileLayer(TileLayer& tileLayer, const ldtk::Layer& layerDef);
    void populateStaticColliders(const ldtk::Layer& colliderLayer);

    sf::Texture m_tileset{"../../assets/sprites/tileset.png"};

    std::vector<sf::FloatRect> m_staticColliders;
};