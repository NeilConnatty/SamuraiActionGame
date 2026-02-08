#include <LDtkLoader/Entity.hpp>

#include <SFML/Graphics.hpp>

#include <Player.h>
#include <Level.h>
#include <Tilesets.h>

enum PlayerInput : size_t
{
    INPUT_UP = 0,
    INPUT_LEFT,
    INPUT_DOWN,
    INPUT_RIGHT,
};

void Player::initialize(const ldtk::EntityRef& playerData, const Tilesets& tilesets)
{
    m_speed = playerData->getField<float>("Speed").value();

    m_transform = sf::Transform::Identity;
    ldtk::IntPoint worldPos = playerData->getWorldPosition();
    m_transform.translate({static_cast<float>(worldPos.x), static_cast<float>(worldPos.y)});
    
    m_inputs = {false, false, false, false};

    auto tileData = playerData->getField<ldtk::TileRect>("IdleSprite").value();
    ldtk::IntPoint texSize = playerData->getSize();
    m_texture = tilesets.getTexture(tileData.getTileset().uid);
    m_sprite.setTextureRect({{tileData.bounds.x, tileData.bounds.y}, {texSize.x, texSize.y}});
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
    sf::Vector2f velocity = direction * m_speed;
   
    // resolve collisions in y axis
    m_transform.translate({0.f, velocity.y});
    sf::FloatRect nextCollider = m_transform.transformRect(m_collider);
    if (auto ret = m_level.checkStaticCollision(nextCollider))
    {
        sf::FloatRect intersect = *ret;
        if (nextCollider.position.y < intersect.position.y)
            m_transform.translate({0.f, -intersect.size.y});
        else
            m_transform.translate({0.f, intersect.size.y});
    }

    // resolve collisions in x axis
    m_transform.translate({velocity.x, 0.f});
    nextCollider = m_transform.transformRect(m_collider);
    if (auto ret = m_level.checkStaticCollision(nextCollider))
    {
        sf::FloatRect intersect = *ret;
        if (nextCollider.position.x < intersect.position.x)
            m_transform.translate({-intersect.size.x, 0.f});
        else
            m_transform.translate({intersect.size.x, 0.f});
    }
}

void Player::draw(sf::RenderTarget& target)
{
    target.draw(m_sprite, m_transform);
}
