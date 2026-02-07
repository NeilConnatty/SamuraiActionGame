#include <LDtkLoader/Project.hpp>
#include <SFML/Graphics.hpp>

#include <Game.h>

void Game::initialize(const ldtk::Project& project)
{
    const ldtk::World& world = project.getWorld();
    const ldtk::Level& level = world.getLevel("Level_0");

    map.initialize(level);
    player.initialize();
}

void Game::update()
{
    player.update();
}

void Game::draw(sf::RenderTarget& target)
{
    target.setView(camera);

    map.drawLayer(target, Map::BACKGROUND);
    map.drawLayer(target, Map::MIDGROUND);
    player.draw(target);
    map.drawLayer(target, Map::FOREGROUND);
    // map.drawLayer(target, Map::LIGHTING); not implemented in ldtk yet
}

void Game::handleKeyPressed(const sf::Event::KeyPressed& keyPressed)
{
    player.handleKeyPressed(keyPressed);
}

void Game::handleKeyReleased(const sf::Event::KeyReleased& keyReleased)
{
    player.handleKeyReleased(keyReleased);
}