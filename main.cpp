#include <iostream>
#include <ctime>
#include "Entity.h"
#include "Player.h"
#include "Objects.h"
#include "SanityPotion.h"
#include "PurifiedSalt.h"
#include "Inventory.h"
#include "Narrator.h"
#include "GameState.h"
using namespace std;

int main()
{

	GameState* MainGame = new GameState();

	MainGame->MainScreen();
	//bool mainMenu = true;

	///*while (mainMenu)
	//{

	//}*/

	return 0;
}





























//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 400;
//const float GRAVITY = 0.4f;
//const float JUMP_SPEED = -10.0f;

//#include <SFML/Graphics.hpp>

//const int WINDOW_WIDTH = 1500;
//const int WINDOW_HEIGHT = 700;

//int main() {
//    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sprite Animation");
//    window.setFramerateLimit(60);
//
//    Position Post;
//    Post.x = 100;
//    Post.y = 100;
//    Player* Player1 = nullptr;
//    Player1 = new Player("Assets/MainCharacter.png", Post, "Player1", 100, 0, 0, 6);
//
//    Clock clock;
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//        if (Keyboard::isKeyPressed(Keyboard::D))
//                {
//                    Player1->Run();
//                }
//
//        float deltaTime = clock.restart().asSeconds();
//
//        // Update and animate the sprite
//        Player1->update(deltaTime);
//
//        window.clear(sf::Color::White);
//        Player1->Draw(window);
//        window.display();
//    }
//
//    return 0;
//}



//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 400;
//const float GRAVITY = 0.4f;
//const float JUMP_SPEED = -10.0f;
//
//class Dinosaur {
//public:
//    sf::RectangleShape shape;
//    float velocityY;
//    bool onGround;
//
//    Dinosaur(float size) {
//        shape.setSize({ size, size });
//        shape.setFillColor(sf::Color::Green);
//        shape.setPosition(100, WINDOW_HEIGHT - size - 50);
//        velocityY = 0;
//        onGround = true;
//    }
//
//    void jump() {
//        if (onGround) {
//            velocityY = JUMP_SPEED;
//            onGround = false;
//        }
//    }
//
//    void applyGravity() {
//        velocityY += GRAVITY;
//        shape.move(0, velocityY);
//
//        // Check if on ground
//        if (shape.getPosition().y >= WINDOW_HEIGHT - shape.getSize().y - 50) {
//            shape.setPosition(shape.getPosition().x, WINDOW_HEIGHT - shape.getSize().y - 50);
//            onGround = true;
//            velocityY = 0;
//        }
//    }
//};
//
//class Obstacle {
//public:
//    sf::RectangleShape shape;
//    float speed;
//
//    Obstacle(float size, float speed) {
//        shape.setSize({ size, size });
//        shape.setFillColor(sf::Color::Red);
//        shape.setPosition(WINDOW_WIDTH, WINDOW_HEIGHT - size - 50);
//        this->speed = speed;
//    }
//
//    void move() {
//        shape.move(-speed, 0);
//        if (shape.getPosition().x + shape.getSize().x < 0) {
//            shape.setPosition(WINDOW_WIDTH, WINDOW_HEIGHT - shape.getSize().y - 50);
//        }
//    }
//};
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dino Game");
//    window.setFramerateLimit(60);
//
//    Dinosaur dino(50.0f);
//    std::vector<Obstacle> obstacles = { Obstacle(40.0f, 5.0f), Obstacle(30.0f, 5.0f) };
//    float obstacleSpacing = 300.0f;
//    int score = 0;
//    bool gameOver = false;
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !gameOver) {
//                dino.jump();
//            }
//        }
//
//        if (!gameOver) {
//            dino.applyGravity();
//
//            for (auto& obstacle : obstacles) {
//                obstacle.move();
//
//                // Collision Detection
//                if (dino.shape.getGlobalBounds().intersects(obstacle.shape.getGlobalBounds())) {
//                    gameOver = true;
//                }
//            }
//
//            // Increase score based on obstacle passing
//            score += 1;
//
//            window.clear();
//            window.draw(dino.shape);
//            for (const auto& obstacle : obstacles) {
//                window.draw(obstacle.shape);
//            }
//            window.display();
//        }
//    }
//
//    return 0;
//}


//RenderWindow window(VideoMode(1500, 700), "TRUE HORROR");

//Position pos;
//pos.x = 100;
//pos.y = 100;

//Texture backgroundTexture;
//if (!backgroundTexture.loadFromFile("Assets/Resources/Background.jpg")) {
//    cout << "Failed to load background image!" << endl;
//    return -1;
//}

//Sprite backgroundSprite;
//backgroundSprite.setTexture(backgroundTexture);

//RectangleShape shape(Vector2f(pos.x, pos.y));
//shape.setFillColor(Color::Green);
//Entity* P1 = nullptr;
//P1 = new Player("Player 1", 100, 0, pos);

//// Movement speed
//float speed = 0.5f;

//while (window.isOpen())
//{
//    Event event;
//    while (window.pollEvent(event))
//    {
//        if (event.type == Event::Closed)
//            window.close();
//    }

//    // Move shape to the right when "D" key is pressed
//    if (Keyboard::isKeyPressed(Keyboard::D))
//    {
//        P1->Walk();
//        shape.move(P1->get_Speed(), 0); // Move right by 'speed' units
//    }
//    else if (Keyboard::isKeyPressed(Keyboard::A))
//    {
//        P1->Run();
//        shape.move(-(P1->get_Speed()), 0); // Move right by 'speed' units
//    }
//    else if (Keyboard::isKeyPressed(Keyboard::W))
//    {
//        P1->Walk();
//        shape.move(0, -(P1->get_Speed())); // Move right by 'speed' units
//    }
//    else if (Keyboard::isKeyPressed(Keyboard::S))
//    {
//        P1->Walk();
//        shape.move(0, P1->get_Speed()); // Move right by 'speed' units
//    }

//    window.clear();
//    window.draw(backgroundSprite);
//    window.draw(shape);
//    window.display();
//}

//delete P1;

//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Escape the Ghost!");
//    window.setFramerateLimit(60);
//
//    // Create rooms as rectangles
//    std::vector<sf::RectangleShape> rooms;
//    const int numRooms = 4;
//    for (int i = 0; i < numRooms; i++) {
//        sf::RectangleShape room(sf::Vector2f(150, 100));
//        room.setFillColor(sf::Color::White);
//        room.setPosition(50 + i * 180, 200);
//        rooms.push_back(room);
//    }
//
//    // Player and ghost as circles
//    sf::CircleShape player(20);
//    player.setFillColor(sf::Color::Green);
//    player.setPosition(50, 350);
//
//    sf::CircleShape ghost(20);
//    ghost.setFillColor(sf::Color::Red);
//    ghost.setPosition(50, 100);
//
//    // Game state
//    int currentRoomIndex = 0;
//    int correctRoomIndex = rand() % numRooms;
//    bool gameOver = false;
//    std::string message = "Hint: Go to room " + std::to_string(correctRoomIndex + 1);
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//
//            // Player chooses room by pressing 1, 2, 3, or 4 keys
//            if (!gameOver) {
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) currentRoomIndex = 0;
//                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) currentRoomIndex = 1;
//                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) currentRoomIndex = 2;
//                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) currentRoomIndex = 3;
//
//                // Check if the player picked the correct room
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
//                    if (currentRoomIndex == correctRoomIndex) {
//                        message = "Correct! Next room...";
//                        correctRoomIndex = rand() % numRooms; // New correct room
//                    }
//                    else {
//                        gameOver = true;
//                        message = "Wrong room! Ghost caught you!";
//                    }
//                }
//            }
//        }
//
//        // Update player position
//        player.setPosition(rooms[currentRoomIndex].getPosition().x + 50, 350);
//
//        // Render
//        window.clear();
//        for (auto& room : rooms) window.draw(room);
//        window.draw(player);
//        window.draw(ghost);
//
//        // Display hint or game over message
//        sf::Font font;
//        font.loadFromFile("Assets/Arial.ttf"); // Ensure "arial.ttf" is in the project directory
//        sf::Text text(message, font, 20);
//        text.setPosition(50, 50);
//        window.draw(text);
//
//        window.display();
//    }
//
//    return 0;
