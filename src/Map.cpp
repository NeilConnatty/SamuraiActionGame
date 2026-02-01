#include <Map.h>
#include <string.h>

constexpr sf::Vector2u mapSize = {20, 15};
constexpr sf::Vector2u tileSize = {16, 16};

void populateVertexArray(sf::VertexArray& vertices, const sf::Texture& tileset, const std::vector<int> tiles)
{
    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(mapSize.x * mapSize.y * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < mapSize.x; ++i)
    {
        for (unsigned int j = 0; j < mapSize.y; ++j)
        {
            // get the current tile number
            const int tileNumber = tiles[i + j * mapSize.x];

            // find its position in the tileset texture
            const int tu = tileNumber % (tileset.getSize().x / tileSize.x);
            const int tv = tileNumber / (tileset.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex *triangles = &vertices[(i + j * mapSize.x) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            // define the 6 matching texture coordinates
            triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
}

void populateTiles(std::vector<int>& outTiles, const char* tilemapFilename)
{
    sf::FileInputStream tilemap{tilemapFilename};
    std::optional<size_t> fileSize = tilemap.getSize();
    
    char* fileData = new char[*fileSize + 1];
    auto success = tilemap.read(fileData, *fileSize);
    assert(success);
    const char* delimiters = " ,\n";
    char* split = strtok(fileData, delimiters);
    while (split != nullptr)
    {
        outTiles.push_back(atoi(split));
        split = strtok(nullptr, delimiters);
    }
    delete [] fileData;
}

void Map::initialize()
{
    std::vector<int> tiles;
    
    tiles.reserve(mapSize.x * mapSize.y);
    populateTiles(tiles, "../../assets/sprites/background-tilemap.txt");
    populateVertexArray(m_backgroundVertices, m_tileset, tiles);
    
    tiles.clear();
    populateTiles(tiles, "../../assets/sprites/walls-tilemap.txt");
    populateVertexArray(m_wallsVertices, m_tileset, tiles);
    populateWallBoundingBoxes(tiles);
    
    tiles.clear();
    populateTiles(tiles, "../../assets/sprites/foreground-tilemap.txt");
    populateVertexArray(m_foregroundVertices, m_tileset, tiles);

}

void Map::populateWallBoundingBoxes(const std::vector<int>& tiles)
{
    for (size_t i = 0; i < mapSize.x; ++i)
    {
        for (size_t j = 0; j < mapSize.y; ++j)
        {
            // get the current tile number
            const int tileNumber = tiles[i + j * mapSize.x];

            switch (tileNumber)
            {
            case 1:
            case 2:
            case 4:
            case 13:
            case 18:
            {
                sf::FloatRect& rect = m_boundingBoxes[i][j];
                rect.position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                rect.size = {tileSize.x, tileSize.y};
                break;
            }
            case 9:
            case 10:
            {
                sf::FloatRect& rect = m_boundingBoxes[i][j];
                rect.position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                rect.size = {tileSize.x / 2, tileSize.y};
                break;
            }
            case 11:
            case 12:
            case 17:
            {
                sf::FloatRect& rect = m_boundingBoxes[i][j];
                rect.position = sf::Vector2f((i * tileSize.x) + (tileSize.x / 2), j * tileSize.y);
                rect.size = {tileSize.x / 2, tileSize.y};
                break;
            }
            }
        }
    }
}

void Map::draw(sf::RenderTarget& target) const
{
    target.draw(m_backgroundVertices, sf::RenderStates{&m_tileset});
    target.draw(m_wallsVertices, sf::RenderStates{&m_tileset});
    target.draw(m_foregroundVertices, sf::RenderStates{&m_tileset});
    target.draw(m_lightingSprite);
}

bool Map::checkWallCollision(sf::Vector2f point) const
{
    size_t tileColumn = static_cast<size_t>(point.x) / tileSize.x;
    size_t tileRow = static_cast<size_t>(point.y) / tileSize.y;

    return m_boundingBoxes[tileColumn][tileRow].contains(point);
}
