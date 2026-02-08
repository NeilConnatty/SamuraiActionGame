#include <SFML/Graphics.hpp> 

class Level;
class Tilesets;

class Player
{
public:
    Player(const Level& level) : m_level(level) {}

    void initialize(const ldtk::EntityRef& playerData, const Tilesets& tilesets);
    void update();
    void draw(sf::RenderTarget& target);

    void handleKeyPressed(const sf::Event::KeyPressed& keyPressed);
    void handleKeyReleased(const sf::Event::KeyReleased& keyReleased);
    
    sf::FloatRect getCollider() const;
    void resolveCollision(sf::FloatRect intersection);
    
private:
    sf::Transform m_transform;
    std::array<bool, 4> m_inputs;
    sf::Texture m_texture;
    sf::Sprite m_sprite{m_texture};
    sf::FloatRect m_collider{{0.f, 16.f}, {16.f, 16.f}};
    float m_speed{0.f};
    const Level& m_level;
};