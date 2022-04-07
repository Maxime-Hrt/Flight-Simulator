#include "Classes.h"

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Application");


void image(string image_path){
    sf::Texture imageFond_texture;

    if(imageFond_texture.loadFromFile(image_path, sf::IntRect(0, 0, WIDTH, HEIGHT))){
        cout << "ERRRRRRRRRROOOOORRR" << endl;
    }
    sf::Sprite imageFond;
    imageFond.setTexture(imageFond_texture);

}

void drawSprite(sf::Sprite image){
    while (window.isOpen())
    {
        sf::Vector2i globalPosition = sf::Mouse::getPosition(window);
        sf::Event event;
        cout << globalPosition.x << " " << globalPosition.y << std::endl;

        //sf::CircleShape airplane = afficherAvion();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(image);

        window.display();
    }
}


sf::CircleShape afficherAvion(float x, float y){
    sf::CircleShape avion(20.f);
    avion.setFillColor(sf::Color::Blue);
    avion.setPosition(x, y);
    return avion;
}