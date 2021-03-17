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
        color = Color(255, 0, 0);
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
    const int delay = 300;
    const int particlesN = (SCREEN_WIDTH * SCREEN_HEIGHT) / 20;
    srand(time(NULL));

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Particle System");

    // Creating map
    Image mapImg;
    mapImg.create(SCREEN_WIDTH, SCREEN_HEIGHT);

    vector <Particle> particles;

    for (int i = 0; i < particlesN; i++)
        particles.push_back(Particle(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));

    int lastClick = -delay;

    while (window.isOpen())
    {
        window.clear();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Mouse::isButtonPressed(Mouse::Left) && clock() - lastClick >= delay)
        {
            Vector2i pos = Mouse::getPosition(window);
            cout << pos.x << " " << pos.y << endl;

            lastClick = clock();

            if (pos.x >= 0 && pos.y >= 0 && pos.x < SCREEN_WIDTH && pos.y < SCREEN_HEIGHT)
            {
                cout << "\n\n";
                for (int i = 0; i < particlesN; i++)
                {
                    float angle = atan2(particles[i].Y - pos.y, particles[i].X - pos.x);

                    /* Beautiful effect
                    particles[i].DX = 1.5 * cos(angle) * (SCREEN_WIDTH / abs(particles[i].X - pos.x)) / 50;
                    particles[i].DY = 1.5 * sin(angle) * (SCREEN_HEIGHT / abs(particles[i].Y - pos.y)) / 50;
                    */

                    particles[i].DX = 1.2 * cos(angle);
                    particles[i].DY = 1.2 * sin(angle);
                }
            }
        } else {
            for (int i = 0; i < particlesN; i++)
            {
                particles[i].DX /= 1.05;
                particles[i].DY /= 1.05;
            }
        }

        for (int i = 0; i < particlesN; i++)
            if (particles[i].X >= 0 && particles[i].X < SCREEN_WIDTH && particles[i].Y >= 0 && particles[i].Y < SCREEN_HEIGHT) mapImg.setPixel(particles[i].X, particles[i].Y, Color::Black);

        for (int i = 0; i < particlesN; i++)
        {
            particles[i].move();
            if (particles[i].X < 0 || particles[i].X > SCREEN_WIDTH || particles[i].Y < 0 || particles[i].Y > SCREEN_HEIGHT)
            {
                /* Beautiful effect
                particles[i].X = Mouse::getPosition(window).x;
                particles[i].Y = Mouse::getPosition(window).y;
                */
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
    }

    return 0;
}
