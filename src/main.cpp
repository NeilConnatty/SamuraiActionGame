#include <SFML/Graphics.hpp>
#include <LDtkLoader/Project.hpp>

#include <Player.h>
#include <Map.h>

constexpr sf::Vector2u windowResolution{sf::Vector2u{320u, 240u} * 3u};
constexpr sf::FloatRect viewport{{0.f, 0.f}, {320.f, 240.f}};

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode(windowResolution), "Samurai Action Game");
    window.setView(sf::View{viewport});
    window.setFramerateLimit(60);

    ldtk::Project project;
    try
    {
        project.loadFromFile("../../assets/ldtk/roningear.ldtk");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    const ldtk::World& world = project.getWorld();
    const ldtk::Level& level = world.getLevel("Level_0");

    Map map;
    map.initialize(level);
    Player player{map};
    player.initialize();

    auto onWindowClose = [&window](const sf::Event::Closed&)
    {
        window.close();
    };

    auto onKeyPressed = [&player](const sf::Event::KeyPressed& keyPressed)
    {
        player.handleKeyPressed(keyPressed);
    };

    auto onKeyReleased = [&player](const sf::Event::KeyReleased& keyReleased)
    {
        player.handleKeyReleased(keyReleased);
    };

    while (window.isOpen())
    {
        window.handleEvents(onWindowClose, onKeyPressed, onKeyReleased);

        player.update();

        window.clear(sf::Color::Black);
        map.drawLayer(window, Map::BACKGROUND);
        map.drawLayer(window, Map::MIDGROUND);
        player.draw(window);
        map.drawLayer(window, Map::FOREGROUND);
        // map.drawLayer(window, Map::LIGHTING); not implemented in ldtk yet
        window.display();
    }
}
