#include <SFML/Graphics.hpp>

namespace ldtk
{
class Level;
class Layer;
}
class Tilesets;

class Level
{
public:
    Level() = default;

    void initialize(const ldtk::Level& level, const Tilesets& tilesets);

    enum Layer
    {
        BACKGROUND = 0,
        MIDGROUND = 1,
        FOREGROUND = 2,
        LIGHTING = 3,
        NUM_LAYERS = 4
    };
    void drawLayer(sf::RenderTarget& target, Layer layer) const;

    std::optional<sf::FloatRect> checkStaticCollision(sf::FloatRect box) const;

private:
    struct TileLayer
    {
        sf::VertexArray vertices;
        const sf::Texture* texture;
        void draw(sf::RenderTarget& target) const;
    };
    std::array<TileLayer, NUM_LAYERS> m_tileLayers;
    void populateTileLayer(TileLayer& tileLayer, const ldtk::Layer& layerDef, const Tilesets& tilesets);

    std::vector<sf::FloatRect> m_staticColliders;
    void populateStaticColliders(const ldtk::Layer& colliderLayer);
};