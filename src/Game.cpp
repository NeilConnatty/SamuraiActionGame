#include <LDtkLoader/Project.hpp>
#include <SFML/Graphics.hpp>

#include <Game.h>

void Game::initialize(const ldtk::Project& project)
{
    const ldtk::World& worldDef = project.getWorld();
    const ldtk::Level& levelDef = worldDef.getLevel("Level_0");

    tilesets.initialize(project);
    level.initialize(levelDef, tilesets);

    const ldtk::EntityRef& playerData = project.getTocEntitiesByName("Player").front();
    player.initialize(playerData, tilesets);
}

void Game::update()
{
    player.update();
}

void Game::draw(sf::RenderTarget& target)
{
    target.setView(camera);

    level.drawLayer(target, Level::BACKGROUND);
    level.drawLayer(target, Level::MIDGROUND);
    player.draw(target);
    level.drawLayer(target, Level::FOREGROUND);
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