#include <Player.h>
#include <Level.h>
#include <Tilesets.h>

namespace ldtk
{
class Project;
}

class Game
{
public:
    Game() = default;

    void initialize(const ldtk::Project& project);
    void update();
    void draw(sf::RenderTarget& target);

    void handleKeyPressed(const sf::Event::KeyPressed& keyPressed);
    void handleKeyReleased(const sf::Event::KeyReleased& keyReleased);

private:
    Tilesets tilesets;
    Level level;
    Player player{level};

    sf::FloatRect viewRect{{0.f, 0.f}, {320.f, 240.f}};
    sf::View camera{viewRect};
};