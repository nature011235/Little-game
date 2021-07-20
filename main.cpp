#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<vector>
#include<sstream>
#include<conio.h>
using namespace sf;
using namespace std;
int windowheight = 720;
int windowwidth = 1280;
bool dropornot();
class car;
class obstacle;
bool collision(car car1, obstacle** ob, int arraysize);
void maingame();
void lose();
void begings();
void introduction();

class car
{
    friend bool collision(car car1, obstacle** ob, int arraysize);
public:
    car();
    void move();
    Sprite scar;
    double speed;
    Vector2f getposition();
private:
    Texture texture;
    double centertohead;
    double centertoside;
    Vector2f position;
    

};

class track1
{
public:
    track1();
    track1(double );
    void move();
    Sprite strack;
    double speed;
    bool runout();
    bool downtodown();
    static int picture_height;
    static int picture_width;
private:
    Texture texture;
    Vector2f position;
    Vector2f headposition;

};
int track1::picture_height = 1279;
int track1::picture_width = 1000;

class trackbegin
{
public:
    trackbegin();
    void move();
    Sprite strack;
    double speed = 0.4;
    bool runout();
private:
    Texture texture;
    Vector2f position;
    Vector2f headposition;

};

class obstacle
{
    friend bool collision(car car1, obstacle** ob, int arraysize);
public:
    obstacle();
    obstacle(int);
    obstacle(const obstacle&);
    void move();
    bool runout();
    Sprite sobstacle;
    double speed ;
    int select;
private:
    Texture texture;
    Vector2f position;
    double centertohead;
    double centertoside;

};
void speedup(track1* tr1, track1* tr2, obstacle** ob, int arraysize);

Clock gameclock;

RenderWindow window(VideoMode(windowwidth, windowheight), "STREET RACER");

Text text;
Text text1;
Font font;

Time duration;
int historytime = 0;


int main()
{
    Music music;
    music.openFromFile("images/wja1w-stt2c.ogg");
    music.play();
    music.setLoop(1);
    font.loadFromFile("images/joystix monospace.ttf");
    begings();
    introduction();
    while (1)
    {
        maingame();
        lose();
    }
    
    return 0;
}

car::car()
{
    texture.loadFromFile("images/車子pixel.png");
    texture.setSmooth(1);
    scar.setTexture(texture);
    scar.setOrigin(scar.getTexture()->getSize().x * 0.5+10, scar.getTexture()->getSize().y * 0.5);
    centertoside = scar.getTexture()->getSize().x * 0.5*0.27*0.45;
    centertohead = scar.getTexture()->getSize().y * 0.5*0.67 * 0.25;
    scar.setScale(0.45, 0.25);
    scar.setPosition(640,680);
    position = scar.getPosition();
    
    
}

void car::move()
{
    position.x += speed;
    scar.setPosition(position);
   

}

Vector2f car::getposition()
{
    return position;

}


track1::track1()
{
    texture.loadFromFile("images/pixel.png");
    texture.setSmooth(1);
    strack.setTexture(texture);
    strack.setOrigin(strack.getTexture()->getSize().x * 0.5, strack.getTexture()->getSize().y);
    strack.setScale(0.8, 1);
    strack.setPosition(windowwidth/2, windowheight-picture_height);
    position = strack.getPosition();
    headposition.y = position.y - strack.getTexture()->getSize().y;
    headposition.x = position.x;
}

track1::track1(double a)
{
    texture.loadFromFile("images/pixel.png");
    texture.setSmooth(1);
    strack.setTexture(texture);
    strack.setOrigin(strack.getTexture()->getSize().x * 0.5, strack.getTexture()->getSize().y);
    strack.setScale(0.8, 1);
    strack.setPosition(windowwidth / 2, a);
    position = strack.getPosition();
    headposition.y = position.y - strack.getTexture()->getSize().y;
    headposition.x = position.x;
}

void track1::move()
{
    position.y += speed;
    headposition.y += speed;
    strack.setPosition(position);
}


bool track1::runout()
{
    return headposition.y>0&& headposition.y < speed;
}

bool track1::downtodown()
{
    return position.y+speed  > windowheight&&position.y+speed<windowheight+speed;
}




trackbegin::trackbegin()
{
    texture.loadFromFile("images/pixel.png");
    texture.setSmooth(1);
    strack.setTexture(texture);
    strack.setOrigin(strack.getTexture()->getSize().x * 0.5, strack.getTexture()->getSize().y);
    strack.setScale(0.8, 1);
    strack.setPosition(640,720);
    position = strack.getPosition();
    headposition.y = position.y - strack.getTexture()->getSize().y;
    headposition.x = position.x;

}

void trackbegin::move()
{
    position.y += speed;
    headposition.y += speed;
    strack.setPosition(position);
}


bool trackbegin::runout()
{
    return headposition.y + speed > 0;
}

obstacle::obstacle()
{
    texture.loadFromFile("images/磚牆pixel.png");
    texture.setSmooth(1);
    sobstacle.setTexture(texture);
    sobstacle.setOrigin(sobstacle.getTexture()->getSize().x * 0.5, sobstacle.getTexture()->getSize().y*0.5);
    centertoside = sobstacle.getTexture()->getSize().x * 0.5 * 0.95;
    centertohead = sobstacle.getTexture()->getSize().y * 0.5 * 1;
    sobstacle.setScale(0.95, 1);
    sobstacle.setPosition(windowwidth / 2, 0);
    position = sobstacle.getPosition();
    
}

obstacle::obstacle(int a):select(a)
{
    texture.loadFromFile("images/磚牆pixel.png");
    texture.setSmooth(1);
    sobstacle.setTexture(texture);
    sobstacle.setOrigin(sobstacle.getTexture()->getSize().x * 0.5, sobstacle.getTexture()->getSize().y * 0.5);
    centertoside = sobstacle.getTexture()->getSize().x * 0.5 * 0.95;
    centertohead = sobstacle.getTexture()->getSize().y * 0.5 * 1;
    sobstacle.setScale(0.95, 1);
    switch (select)
    {
    case 0:
        sobstacle.setPosition(443, 0);
        break;
    case 1:
        sobstacle.setPosition(windowwidth / 2-7, 0);
        break;
    case 2:
        sobstacle.setPosition(822, 0);
        break;

    }
    position = sobstacle.getPosition();
}

obstacle::obstacle(const obstacle& oo) 
{
    texture.loadFromFile("images/磚牆pixel.png");
    texture.setSmooth(1);
    sobstacle.setTexture(texture);
    sobstacle.setOrigin(sobstacle.getTexture()->getSize().x * 0.5, sobstacle.getTexture()->getSize().y * 0.5);
    centertoside = sobstacle.getTexture()->getSize().x * 0.5 * 0.95;
    centertohead = sobstacle.getTexture()->getSize().y * 0.5 * 1;
    sobstacle.setScale(0.95, 1);
    select = oo.select;
    switch (select)
    {
    case 0:
        sobstacle.setPosition(460, 0);
        break;
    case 1:
        sobstacle.setPosition(windowwidth / 2, 0);
        break;
    case 2:
        sobstacle.setPosition(800, 0);
        break;

    }
    position = sobstacle.getPosition();
}

void obstacle::move()
{
    position.y += speed;
    sobstacle.setPosition(position);
}

bool obstacle::runout()
{
    return position.y + speed > 800;


}

bool dropornot()
{
    static Clock clock;
    Time sincelastin = clock.getElapsedTime();
    Time temp= gameclock.getElapsedTime();
    double interval = temp.asSeconds();
    double timeinterval;
    if (interval > 0 && interval < 20) timeinterval = 3;
    if (interval >= 20 && interval < 30) timeinterval = 2.3;
    if (interval >= 30 && interval < 60) timeinterval = 1.3;
    if (interval >= 60 ) timeinterval = 0.8;
   
    if (sincelastin.asSeconds() > timeinterval)
    {
        clock.restart();
        return true;
    }
    else
        return false;


}

void speedup(track1*tr1,track1*tr2,obstacle**ob,int arraysize)
{
    Time temp = gameclock.getElapsedTime();
    double interval = temp.asSeconds();
    if (interval > 0 && interval < 10)
    {
        double Speed = 0.4;
        tr1->speed = Speed;
        tr2->speed = Speed;
        for (int i = 0; i < arraysize; i++)
        {
            if (ob[i] != 0)
            {
                ob[i]->speed = Speed;
            }
        }
    }
    if (interval >= 10 && interval < 30)
    {
        double Speed = 0.42;
        tr1->speed = Speed;
        tr2->speed = Speed;
        for (int i = 0; i < arraysize; i++)
        {
            if (ob[i] != 0)
            {
                ob[i]->speed = Speed;
            }
        }
    }
    if (interval >= 30 && interval < 50)
    {
        double Speed = 0.45;
        tr1->speed = Speed;
        tr2->speed = Speed;
        for (int i = 0; i < arraysize; i++)
        {
            if (ob[i] != 0)
            {
                ob[i]->speed = Speed;
            }
        }
    }
    if (interval >= 50 && interval < 70)
    {
        double Speed = 0.47;
        tr1->speed = Speed;
        tr2->speed = Speed;
        for (int i = 0; i < arraysize; i++)
        {
            if (ob[i] != 0)
            {
                ob[i]->speed = Speed;
            }
        }
    }
    if (interval >= 70 && interval < 100)
    {
        double Speed = 0.49;
        tr1->speed = Speed;
        tr2->speed = Speed;
        for (int i = 0; i < arraysize; i++)
        {
            if (ob[i] != 0)
            {
                ob[i]->speed = Speed;
            }
        }
    }
    if (interval >= 100 && interval < 150)
    {
        double Speed = 0.51;
        tr1->speed = Speed;
        tr2->speed = Speed;
        for (int i = 0; i < arraysize; i++)
        {
            if (ob[i] != 0)
            {
                ob[i]->speed = Speed;
            }
        }
    }
    if (interval >=150)
    {
        double Speed = 0.53;
        tr1->speed = Speed;
        tr2->speed = Speed;
        for (int i = 0; i < arraysize; i++)
        {
            if (ob[i] != 0)
            {
                ob[i]->speed = Speed;
            }
        }
    }
}

bool collision(car car1, obstacle** ob, int arraysize)
{
    for (int i = 0; i < arraysize; i++)
    {
        if (ob[i] != 0)
        {
            if (abs(car1.position.x - ob[i]->position.x) < car1.centertoside + ob[i]->centertoside)
            {
                if ((abs(car1.position.y - ob[i]->position.y) < car1.centertohead + ob[i]->centertohead))
                {
                    return true;
                }
            }
        }
    }
    return false;
}


void maingame()
{
    gameclock.restart();
    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(Color::White);
    text.setPosition(5, 20);
    text1.setFont(font);
    text1.setCharacterSize(25);
    text1.setFillColor(Color::White);
    text1.setPosition(5, 70);
    car car1;
    trackbegin trackbegin1;
    track1* trackptr1 = new track1;
    track1* trackptr2 = new track1(windowheight - 2 * track1::picture_height);
    const int arraysize = 13;
    obstacle* OBSTACLE[arraysize] = {};
    srand(time(NULL));
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                exit(1);
            }
        }
        duration = gameclock.getElapsedTime();
        car1.speed = 0;
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            if (car1.getposition().x + car1.speed < 885)
            {
                car1.speed = 0.35;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            if (car1.getposition().x - car1.speed > 375)
            {
                car1.speed = -0.35;
            }
        }
        if (trackptr1->downtodown())
        {

            delete trackptr2;
            trackptr2 = new track1;
        }
        if (trackptr2->downtodown())
        {

            delete trackptr1;
            trackptr1 = new track1;
        }

        if (dropornot())
        {
            int i = 0;
            for (; i < arraysize - 1; i++)
            {
                if (OBSTACLE[i] == 0)
                    break;

            }
            if (duration.asSeconds() < 20)
            {
                OBSTACLE[i] = new obstacle(rand() % 3);
            }
            else
            {
                OBSTACLE[i++] = new obstacle(rand() % 3);
                OBSTACLE[i] = new obstacle(rand() % 3);
            }
        }
        for (int i = 0; i < arraysize; i++)
        {
            if (OBSTACLE[i] != 0)
            {
                if (OBSTACLE[i]->runout())
                {
                    delete OBSTACLE[i];
                    OBSTACLE[i] = 0;
                }
            }
        }
        speedup(trackptr1, trackptr2, OBSTACLE, arraysize);
        if ((int)duration.asSeconds() >= historytime)
        {
            historytime = (int)duration.asSeconds();
        }
        text.setString("Survial time:" + to_string((int)duration.asSeconds()));
        text1.setString("Best time:" + to_string(historytime));
        if (collision(car1, OBSTACLE, arraysize))
            break;
        car1.move();
        trackptr1->move();
        trackptr2->move();
        trackbegin1.move();
        for (int i = 0; i < arraysize; i++)
        {
            if (OBSTACLE[i] != 0)
            {
                OBSTACLE[i]->move();
            }
        }
        window.clear();
        window.draw(trackptr1->strack);
        window.draw(trackptr2->strack);
        window.draw(trackbegin1.strack);
        window.draw(car1.scar);
        for (int i = 0; i < arraysize; i++)
        {
            if (OBSTACLE[i] != 0)
            {
                window.draw(OBSTACLE[i]->sobstacle);
            }
        }
        window.draw(text);
        window.draw(text1);
        window.display();
    }

}

void lose()
{
    Texture texture;
    texture.loadFromFile("images/lose.jpg");
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getTexture()->getSize().x * 0.5, sprite.getTexture()->getSize().y * 0.5);
    sprite.setPosition(windowwidth / 2, 250);
    sprite.setScale(1.6, 1.2);
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(Color::White);
    text.setPosition(490, 370);
    text1.setFont(font);
    text1.setCharacterSize(30);
    text1.setFillColor(Color::White);
    text1.setPosition(490, 420);
    Text text2;
    text2.setString("PRESS SPACE BAR TO PLAY AGAIN...");
    text2.setFont(font);
    text2.setCharacterSize(20);
    text2.setFillColor(Color::White);
    text2.setPosition(410, 620);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                exit(1);
            }
            else if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Space)
                    return;

            }
        }
        text.setString("Survial time:" + to_string((int)duration.asSeconds()));
        text1.setString("Best time:" + to_string(historytime));
        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.draw(text1);
        window.draw(text2);
        window.display();

    }


}

void begings()
{
    Texture texture;
    texture.loadFromFile("images/封面圖片.jpg");
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getTexture()->getSize().x * 0.5, sprite.getTexture()->getSize().y * 0.5);
    sprite.setPosition(windowwidth / 2, windowheight/2);
    sprite.setScale(0.9, 0.9);
    Text text2;
    text2.setString("PRESS ANY KEY TO START...");
    text2.setFont(font);
    text2.setCharacterSize(35);
    text2.setFillColor(Color::White);
    text2.setPosition(330, 600);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                exit(1);
            }
            else if (event.type == Event::KeyPressed)
            {
                return ;
            }
        }
        
        window.clear();
        window.draw(sprite);
        window.draw(text2);
        window.display();

    }


}
void introduction()
{

    Texture texture;
    texture.loadFromFile("images/說明.jpg");
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getTexture()->getSize().x * 0.5, sprite.getTexture()->getSize().y * 0.5);
    sprite.setPosition(windowwidth / 2, windowheight / 2-70);
    sprite.setScale(0.9, 0.9);
    Text text2;
    text2.setString("PRESS ANY KEY TO CONTINUE...");
    text2.setFont(font);
    text2.setCharacterSize(35);
    text2.setFillColor(Color::White);
    text2.setPosition(300, 600);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                exit(1);
            }
            else if (event.type == Event::KeyPressed)
            {
                return ;
            }
        }
        window.clear();
        window.draw(sprite);
        window.draw(text2);
        window.display();

    }

}