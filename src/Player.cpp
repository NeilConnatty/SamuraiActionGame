#include <SFML/Graphics.hpp>

#include <Player.h>
#include <Map.h>

enum PlayerInput : size_t
{
    INPUT_UP = 0,
    INPUT_LEFT ,
    INPUT_DOWN,
    INPUT_RIGHT,
};

#define PLAYER_SPEED 2.f // movement speed in pixels per frame

void Player::initialize()
{
    m_transform.translate({50.f, 50.f});
    m_inputs = {false, false, false, false};
}

void Player::handleKeyPressed(const sf::Event::KeyPressed& keyPressed)
{
    if (keyPressed.scancode == sf::Keyboard::Scancode::W)
        m_inputs[INPUT_UP] = true;
    else if (keyPressed.scancode == sf::Keyboard::Scancode::A)
        m_inputs[INPUT_LEFT] = true;
    else if (keyPressed.scancode == sf::Keyboard::Scancode::S)
        m_inputs[INPUT_DOWN] = true;
    else if (keyPressed.scancode == sf::Keyboard::Scancode::D)
        m_inputs[INPUT_RIGHT] = true;
}

void Player::handleKeyReleased(const sf::Event::KeyReleased& keyReleased)
{
    if (keyReleased.scancode == sf::Keyboard::Scancode::W)
        m_inputs[INPUT_UP] = false;
    else if (keyReleased.scancode == sf::Keyboard::Scancode::A)
        m_inputs[INPUT_LEFT] = false;
    else if (keyReleased.scancode == sf::Keyboard::Scancode::S)
        m_inputs[INPUT_DOWN] = false;
    else if (keyReleased.scancode == sf::Keyboard::Scancode::D)
        m_inputs[INPUT_RIGHT] = false;
}

void Player::update()
{
    sf::Vector2f direction{0.f, 0.f};
    if (m_inputs[INPUT_UP])
        direction.y -= 1;
    if (m_inputs[INPUT_DOWN])
        direction.y += 1;
    if (m_inputs[INPUT_LEFT])
        direction.x -= 1;
    if (m_inputs[INPUT_RIGHT])
        direction.x += 1;
    
    if (direction == sf::Vector2f{0.f, 0.f})
        return;

    direction = direction.normalized();
    sf::Vector2f velocity = direction * PLAYER_SPEED;

    sf::FloatRect boundingBox = m_transform.transformRect(m_sprite.getGlobalBounds());

    sf::FloatRect nextX = boundingBox;
    nextX.position.x += velocity.x;
    if (m_map.checkWallCollision(nextX))
        velocity.x = 0;

    sf::FloatRect nextY = boundingBox;
    nextY.position.y += velocity.y;
    if (m_map.checkWallCollision(nextY))
        velocity.y = 0;
    
    m_transform.translate(velocity);
}

void Player::draw(sf::RenderTarget& target)
{
    target.draw(m_sprite, m_transform);
}
