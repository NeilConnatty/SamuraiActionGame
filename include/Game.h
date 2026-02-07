#include <Player.h>
#include <Map.h>

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
    Map map;
    Player player{map};

    sf::FloatRect viewRect{{0.f, 0.f}, {320.f, 240.f}};
    sf::View camera{viewRect};
};