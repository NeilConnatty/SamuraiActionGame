#include <Map.h>
#include <string.h>

constexpr sf::Vector2u mapSize = {20, 15};
constexpr sf::Vector2u tileSize = {16, 16};

void Map::initialize()
{
    sf::FileInputStream tilemap{"../../assets/sprites/tilemap.txt"};
    std::optional<size_t> fileSize = tilemap.getSize();
    std::vector<int> tiles;
    
    char* fileData = new char[*fileSize + 1];
    auto success = tilemap.read(fileData, *fileSize);
    assert(success);
    const char* delimiters = " ,\n";
    char* split = strtok(fileData, delimiters);
    while (split != nullptr)
    {
        tiles.push_back(atoi(split));
        split = strtok(nullptr, delimiters);
    }
    delete [] fileData;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(mapSize.x * mapSize.y * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < mapSize.x; ++i)
    {
        for (unsigned int j = 0; j < mapSize.y; ++j)
        {
            // get the current tile number
            const int tileNumber = tiles[i + j * mapSize.x];

            // find its position in the tileset texture
            const int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            const int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex *triangles = &m_vertices[(i + j * mapSize.x) * 6];

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

void Map::draw(sf::RenderTarget& target)
{
    target.draw(m_vertices, sf::RenderStates{&m_tileset});
}