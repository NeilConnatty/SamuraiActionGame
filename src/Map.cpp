#include <LDtkLoader/Level.hpp>

#include <Map.h>
#include <string.h>

enum TileLayers
{
    BACKGROUND = 0,
    MIDGROUND = 1,
    FOREGROUND = 2,
    LIGHTING = 3
};

void Map::populateTileLayer(Map::TileLayer& tileLayer, const ldtk::Layer& layerDef)
{
    const std::vector<ldtk::Tile> tiles = layerDef.allTiles();
    // resize the vertex array to fit the level size
    tileLayer.vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    tileLayer.vertices.resize(tiles.size() * 6);

    size_t i = 0;
    for (const ldtk::Tile tile : tiles)
    {
        // tile coordinates are defined by 4 corners in clockwise order around the rectangle
        // we will translate that to 2 triangles
        std::array<ldtk::Vertex, 4> tileCoords = tile.getVertices();
        
        // get a pointer to the triangles' vertices of the current tile
        sf::Vertex *triangles = &tileLayer.vertices[i * 6];
        // define the 6 corners of the two triangles
        triangles[0].position = sf::Vector2f(tileCoords[0].pos.x, tileCoords[0].pos.y);
        triangles[1].position = sf::Vector2f(tileCoords[1].pos.x, tileCoords[1].pos.y);
        triangles[2].position = sf::Vector2f(tileCoords[3].pos.x, tileCoords[3].pos.y);
        triangles[3].position = sf::Vector2f(tileCoords[3].pos.x, tileCoords[3].pos.y);
        triangles[4].position = sf::Vector2f(tileCoords[1].pos.x, tileCoords[1].pos.y);
        triangles[5].position = sf::Vector2f(tileCoords[2].pos.x, tileCoords[2].pos.y);

        // define the 6 matching texture coordinates
        triangles[0].texCoords = sf::Vector2f(tileCoords[0].tex.x, tileCoords[0].tex.y);
        triangles[1].texCoords = sf::Vector2f(tileCoords[1].tex.x, tileCoords[1].tex.y);
        triangles[2].texCoords = sf::Vector2f(tileCoords[3].tex.x, tileCoords[3].tex.y);
        triangles[3].texCoords = sf::Vector2f(tileCoords[3].tex.x, tileCoords[3].tex.y);
        triangles[4].texCoords = sf::Vector2f(tileCoords[1].tex.x, tileCoords[1].tex.y);
        triangles[5].texCoords = sf::Vector2f(tileCoords[2].tex.x, tileCoords[2].tex.y);
        ++i;
    }
}

void Map::initialize(const ldtk::Level& level)
{
    populateTileLayer(m_tileLayers[BACKGROUND], level.getLayer("Background"));
    populateTileLayer(m_tileLayers[MIDGROUND], level.getLayer("Midground"));
    populateTileLayer(m_tileLayers[FOREGROUND], level.getLayer("Foreground"));
    populateStaticColliders(level.getLayer("StaticColliders"));
}

void Map::populateStaticColliders(const ldtk::Layer& layer)
{
    const auto& colliders = layer.getEntitiesByTag("Collider");
    m_staticColliders.reserve(colliders.size());
    for (const ldtk::Entity& collider : colliders)
    {
        ldtk::IntPoint pos = collider.getPosition();
        ldtk::IntPoint size = collider.getSize();
        m_staticColliders.push_back(sf::FloatRect(
            {static_cast<float>(pos.x), static_cast<float>(pos.y)}, 
            {static_cast<float>(size.x), static_cast<float>(size.y)}));
    }
}

void Map::drawBackground(sf::RenderTarget& target) const
{
    target.draw(m_tileLayers[BACKGROUND].vertices, sf::RenderStates{&m_tileset});
}

void Map::drawWalls(sf::RenderTarget& target) const
{
    target.draw(m_tileLayers[MIDGROUND].vertices, sf::RenderStates{&m_tileset});
}

void Map::drawForeground(sf::RenderTarget& target) const
{
    target.draw(m_tileLayers[FOREGROUND].vertices, sf::RenderStates{&m_tileset});

}

void Map::drawLighting(sf::RenderTarget& target) const
{
    target.draw(m_lightingSprite);
}

std::optional<sf::FloatRect> Map::checkWallCollision(sf::FloatRect box) const
{
    for (sf::FloatRect collider : m_staticColliders)
        if (auto ret = collider.findIntersection(box))
            return ret;
    return std::nullopt;
}
