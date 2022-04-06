#include "Classes.h"

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Application");


void image(string image_path){
    sf::Texture imageFond_texture;

    if(imageFond_texture.loadFromFile(image_path, sf::IntRect(0, 0, WIDTH, HEIGHT))){
        //Message d'erreur t'as vu
    }
    sf::Sprite imageFond;
    imageFond.setTexture(imageFond_texture);
    drawSprite(imageFond);

}

void drawSprite(sf::Sprite image){
    while (window.isOpen())
    {
        sf::Vector2i globalPosition = sf::Mouse::getPosition(window);
        sf::Event event;
        cout << globalPosition.x << " " << globalPosition.y << std::endl;

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

void drawAvion(){

}