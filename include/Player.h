#include <SFML/Graphics.hpp> 

class Level;

class Player
{
public:
    Player(const Level& level) : m_level(level) {}

    void initialize();
    void update();
    void draw(sf::RenderTarget& target);

    void handleKeyPressed(const sf::Event::KeyPressed& keyPressed);
    void handleKeyReleased(const sf::Event::KeyReleased& keyReleased);
    
    sf::FloatRect getCollider() const;
    void resolveCollision(sf::FloatRect intersection);
    
private:
    sf::Transform m_transform{sf::Transform::Identity};
    std::array<bool, 4> m_inputs;
    sf::Texture m_texture{"../../assets/sprites/character.png"};
    sf::Sprite m_sprite{m_texture, {{0,0}, {16, 32}}};
    sf::FloatRect m_collider{{0.f, 16.f}, {16.f, 16.f}};
    const Level& m_level;
};