#include <SFML/Graphics.hpp> 

class Map;

class Player
{
public:
    Player(const Map& map) : m_map(map) {}

    void initialize();
    void handleKeyPressed(const sf::Event::KeyPressed& keyPressed);
    void handleKeyReleased(const sf::Event::KeyReleased& keyReleased);
    void update();
    void draw(sf::RenderTarget& target);

private:
    sf::Transform m_transform{sf::Transform::Identity};
    std::array<bool, 4> m_inputs;
    sf::Texture m_texture{"../../assets/sprites/character.png"};
    sf::Sprite m_sprite{m_texture};
    const Map& m_map;
};