#include <iostream>
#include <list>
#include "Paddle.h"
#include "SFML Game engine/Utilities/FrameRate.h"
#include "SFML Game engine/States/StateManager.h"
#include "SFML Game engine/GUI/Textbox.h"
#include "SFML Game engine/Asset Manager/AssetManager.h"
using namespace std;

class MyEntity : public sf::Drawable, public sf::Transformable{
    public:
        MyEntity(const sf::VertexArray &vertices): m_vertices(vertices){
            m_vertices[0] = sf::Vector2f(0.f, 0.f);
            m_vertices[1] = sf::Vector2f(-50.f, 50.f);
            m_vertices[2] = sf::Vector2f(50.f, 50.f);

            m_vertices[0].color = sf::Color::Blue;
            m_vertices[1].color = sf::Color::Green;
            m_vertices[2].color = sf::Color::Yellow;
                
        }

        void setVertices() {

        }

        // add functions to play with the entity's geometry / colors / texturing...

    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // apply the entity's transform -- combine it with the one that was passed by the caller
            states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

            // you may also override states.shader or states.blendMode if you want

            // draw the vertex array
            target.draw(m_vertices, states);
        }

        sf::VertexArray m_vertices;
};

class PlusSign : public sf::Drawable {
public:
    PlusSign(const sf::Vector2f& position, const sf::Vector2f& size) : horizontal(size), vertical(size) {
        horizontal.rotate(-90);
        horizontal.setPosition(position);
    }
    void setColor(const sf::Color& color);
    void eventHandler(const sf::Event& e, const sf::RenderWindow& window);
    void setOnClickEvent(const std::function<void()>& onClick);
 
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override  {
        target.draw(horizontal);
        target.draw(vertical);
    }
private:
    sf::RectangleShape horizontal, vertical;
};

int main() {
    StateManager manager(650, 500, "Pong");

    manager.runGame();
	/*sf::RenderWindow window(sf::VideoMode(650, 500), "SFML works!");
    Paddle left(Orientation::LEFT, { 20.f, window.getSize().y / 6.f}, window.getSize());
    Paddle right(Orientation::RIGHT, { 20.f, window.getSize().y / 6.f }, window.getSize());
    FrameRate FPS({ 0.f, window.getSize().y - 30.f });
    Textbox box({ 50.f, 50.f }, { window.getSize().x / 2.f, window.getSize().y / 2.f },
        AssetManager::get().getDefaultFont(Fonts::CALIBRI_B), "e");
    MyEntity entity(sf::VertexArray(sf::Triangles, 3));
    sf::CircleShape c(5);
    PlusSign s({ 300.f, 300.f }, { 40.f, 150.f });
    sf::Texture plusTexture, minusTexture;
    sf::Sprite plusSprite, minusSprite;

    plusTexture.loadFromFile("plus.jpg");
    minusTexture.loadFromFile("minus.png");

    plusSprite.setTexture(plusTexture);
    minusSprite.setTexture(minusTexture);

    plusSprite.setPosition(200, 300);
    minusSprite.setPosition(100, 100);

    plusSprite.setScale(0.25f, 0.25f);
    minusSprite.setScale(0.25f, 0.25f);


    c.setFillColor(sf::Color::Red);
    c.setOrigin(c.getRadius() / 2.f, c.getRadius() / 2.f);
    c.setPosition(300, 300);
    entity.setPosition(300, 300);
    
    
    float angle = 0;
    box.setCharacterLimit(1);
    window.setFramerateLimit(60);
    while (window.isOpen()){
        sf::Event e;
        while (window.pollEvent(e)){
            if (e.type == sf::Event::Closed)
                window.close();
        }
        
        left.move(window.getSize(), FPS.getDeltaTime());
        right.move(window.getSize(), FPS.getDeltaTime());        

        
        angle += FPS.getDeltaTime();
        FPS.calculate();
        window.clear(sf::Color::Green);
        left.drawPaddle(window);
        right.drawPaddle(window);
        window.draw(c);
        window.draw(plusSprite);
        window.draw(minusSprite);
        window.display();
    }	*/
}