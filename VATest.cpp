#include <GaiaGL/Graphics.h>
#include <vector>

void function() {
    ga::Window window(800, 600, "Window");

    ga::Texture* texture = new ga::Texture("assets/images/red_fog.png");
    std::vector<ga::Sprite*> sprites;
    sprites.push_back(new ga::Sprite(texture, 50, 50));
    //ga::Sprite sprite(texture, 50, 50);
    //ga::Sprite* sprite = new ga::Sprite(texture, 50, 50);

    //sprite.Bind();
    //sprites.back().Bind();
    //sprite->Bind();
    sprites.back()->setPosition(100, 100);
    auto p = sprites.back()->getPosition();
    std::cout << p.x << " " << p.y << '\n';

    //delete sprite;

    delete texture;
}