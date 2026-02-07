#include <SFML/Graphics.hpp>
#include <LDtkLoader/Project.hpp>

#include <Game.h>

constexpr sf::Vector2u windowResolution{sf::Vector2u{320u, 240u} * 3u};
constexpr sf::FloatRect viewport{{0.f, 0.f}, {320.f, 240.f}};

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode(windowResolution), "Ronin Gear Bravo");
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
    
    Game game;
    game.initialize(project);

    auto onWindowClose = [&window](const sf::Event::Closed&)
    {
        window.close();
    };

    auto onKeyPressed = [&game](const sf::Event::KeyPressed& keyPressed)
    {
        game.handleKeyPressed(keyPressed);
    };

    auto onKeyReleased = [&game](const sf::Event::KeyReleased& keyReleased)
    {
        game.handleKeyReleased(keyReleased);
    };

    while (window.isOpen())
    {
        window.handleEvents(onWindowClose, onKeyPressed, onKeyReleased);

        game.update();

        window.clear(sf::Color::Black);
        game.draw(window);
        window.display();
    }
}
