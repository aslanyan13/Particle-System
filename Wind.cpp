#include <iostream>
#include <time.h>
#include <vector>
#include <math.h>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct Particle {
    float X, Y;
    float DX, DY;
    Color color;
    Particle() {}
    Particle(float x, float y) : X(x), Y(y) {
        color = Color(255, 255, 255, rand() % 235 + 20);
        DX = DY = 0;
    };
    void move()
    {
        X += DX;
        Y += DY;
    }
};

// Screen size constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int main()
{
    float speedX = 1;
    const int particlesN = (SCREEN_WIDTH * SCREEN_HEIGHT) / 100;
    srand(time(NULL));

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Particle System: Wind");

    // Creating map
    Image mapImg;
    mapImg.create(SCREEN_WIDTH, SCREEN_HEIGHT);

    vector <Particle> particles;

    for (int i = 0; i < particlesN; i++)
        particles.push_back(Particle(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));

    int tick = 0;
    bool isMoving = false;

    while (window.isOpen())
    {
        window.clear();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            for (int i = 0; i < particlesN; i++)
            {
                particles[i].DX = speedX;
            }
            isMoving = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            for (int i = 0; i < particlesN; i++)
            {
                particles[i].DX = 0;
                particles[i].DY = 0;
            }
            isMoving = false;
        }

        if (Keyboard::isKeyPressed(Keyboard::Add))
        {
            speedX += 0.01;
            cout << speedX << endl;
            for (int i = 0; i < particlesN; i++)
            {
                particles[i].DX = speedX;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Subtract))
        {
            speedX -= 0.01;
            cout << speedX << endl;
            for (int i = 0; i < particlesN; i++)
            {
                particles[i].DX = speedX;
            }
        }
        for (int i = 0; i < particlesN; i++)
            if (particles[i].X >= 0 && particles[i].X < SCREEN_WIDTH && particles[i].Y >= 0 && particles[i].Y < SCREEN_HEIGHT) mapImg.setPixel(particles[i].X, particles[i].Y, Color::Black);

        if (tick % 5 == 0 && isMoving)
        {
            for (int i = 0; i < particlesN; i++)
            {
                particles[i].DY += (rand() % 100) / 100.0f - 0.5f;
            }
        }

        for (int i = 0; i < particlesN; i++)
        {
            particles[i].move();
            if (particles[i].X > SCREEN_WIDTH) {
                particles[i].X = 0;
                particles[i].Y = rand() % SCREEN_HEIGHT;
                particles[i].color.a = rand() % 235 + 20;
            }
            if (particles[i].X < 0) {
                particles[i].X = SCREEN_WIDTH - 1;
                particles[i].Y = rand() % SCREEN_HEIGHT;
                particles[i].color.a = rand() % 235 + 20;
            }
        }

        for (int i = 0; i < particlesN; i++)
        {
            if (particles[i].X >= 0 && particles[i].X < SCREEN_WIDTH && particles[i].Y >= 0 && particles[i].Y < SCREEN_HEIGHT)
                mapImg.setPixel(particles[i].X, particles[i].Y, particles[i].color);
        }

        Texture mapTexture;
        mapTexture.loadFromImage(mapImg);

        Sprite mapSprite;
        mapSprite.setPosition(0, 0);
        mapSprite.setTexture(mapTexture);

        window.draw(mapSprite);
        window.display();

        tick++;
    }

    return 0;
}
