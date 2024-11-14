#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Player.h"
#include "Entity.h"
#include "Inventory.h"
#include "Narrator.h"
using namespace sf;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

class GameState
{
private:
    Inventory* PlayerInv;
    Player* Player1;
    bool mainMenu;
    int optionMenu;
    string fAction;
    string fObjects;
    Font font;
    Font font2;
    RenderWindow window;
    Texture backgroundTexture;
    Texture jumpScareBG;
    Sprite backgroundSprite;
    Sprite jumpScareBGS;
    Music mainMusic;   
    Music introMusic;  
    Music jumpScare;
    Narrator* fNarrator;

public:
    GameState() : window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Finding Exit")
    {
        SanityPotion* PotionInRoom2 = new SanityPotion(50, 2);
        Objects* Default = new Objects("Your companion for the journey!", "Baseball Bat", 1);
        PlayerInv = new Inventory(Default);
        Player1 = new Player("Steve", true, PlayerInv);
        Player1->PickUpObject(PotionInRoom2);
        fNarrator = new Narrator("Finding Exit", Player1);
        if (!font.loadFromFile("Library/FONT/dksamhain.ttf"))
        {
            cerr << "Error loading font!" << endl;
        }

        if (!font2.loadFromFile("Library/FONT/DEAD.otf"))
        {
            cerr << "Error loading font!" << endl;
        }

        if (!backgroundTexture.loadFromFile("Library/ASSETS/IMAGES/BG2.jpg"))
        {
            cerr << "Error loading background image!" << endl;
        }

        if (!jumpScareBG.loadFromFile("Library/ASSETS/IMAGES/BG2.jpg"))
        {
            cerr << "Error loading background image!" << endl;
        }

        backgroundSprite.setTexture(backgroundTexture);
        jumpScareBGS.setTexture(jumpScareBG);

        if (!mainMusic.openFromFile("Library/ASSETS/SOUNDS/GameScreen.wav"))
        {
            cerr << "Error loading main screen music!" << endl;
        }

        if (!introMusic.openFromFile("Library/ASSETS/SOUNDS/MainScreen.wav"))
        {
            cerr << "Error loading main screen music!" << endl;
        }

        if (!jumpScare.openFromFile("Library/ASSETS/SOUNDS/JumpScare.wav"))
        {
            cerr << "Error loading main screen music!" << endl;
        }
    }

    ~GameState()
    {
        // Stop any playing music to avoid issues on deallocation
        mainMusic.stop();
        introMusic.stop();
        jumpScare.stop();

        // Delete dynamically allocated memory
        delete PlayerInv;
        delete Player1;
        delete fNarrator;
    }

    void MainScreen()
    {
        // Start playing main screen music
        mainMusic.setLoop(true); // Loop the music for continuous play
        mainMusic.play();

        // Narrator Screen Text
        fNarrator->push("(Q) Quit\n");
        fNarrator->push("(S) Settings\n");
        fNarrator->push("(P) Play\n");
        fNarrator->push("WELCOME TO \"FINDING EXIT\"\n");

        vector<Text> MenuTexts;
        Text line;
        line.setFont(font);
        line.setCharacterSize(80);
        line.setFillColor(Color::Red);

        int yOffset = 0;
        line.setString(fNarrator->peekThenPop());
        line.setPosition(30, 50 + yOffset);
        MenuTexts.push_back(line);
        yOffset += 100;

        while (!fNarrator->isEmpty())
        {
            line.setString(fNarrator->peekThenPop());
            line.setPosition(300, 50 + yOffset);
            MenuTexts.push_back(line);
            yOffset += 100;
        }

        // Main render loop
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Q))
            {
                window.close();
            }
            else if (Keyboard::isKeyPressed(Keyboard::P))
            {
                this->SettingName();
            }
            else if (Keyboard::isKeyPressed(Keyboard::S))
            {
                this->SettingsScreen();
            }

            window.clear();
            window.draw(backgroundSprite);
            for (const auto& text : MenuTexts)
                window.draw(text);

            window.display();
        }
    }

    void SettingsScreen()
    {
        Text volumeText;
        volumeText.setFont(font2);
        volumeText.setCharacterSize(50);
        volumeText.setFillColor(Color::White);
        volumeText.setPosition(50, 100);

        int volume = mainMusic.getVolume();
        Clock keyCooldown; // Clock to handle delay between key presses

        Text instructions;
        instructions.setFont(font2);
        instructions.setCharacterSize(30);
        instructions.setFillColor(Color::White);
        instructions.setPosition(50, 200);
        instructions.setString("Use UP and DOWN arrow keys to adjust volume.\nPress ESC to return.");

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                return; // Exit the settings screen
            }

            // Check if the cooldown period has passed before adjusting volume
            if (keyCooldown.getElapsedTime().asMilliseconds() > 100) // 200 ms delay
            {
                if (Keyboard::isKeyPressed(Keyboard::Up) && volume < 100)
                {
                    volume += 1;
                    mainMusic.setVolume(volume);
                    introMusic.setVolume(volume);
                    jumpScare.setVolume(volume);
                    keyCooldown.restart();
                }
                else if (Keyboard::isKeyPressed(Keyboard::Down) && volume > 0)
                {
                    volume -= 1;
                    mainMusic.setVolume(volume);
                    introMusic.setVolume(volume);
                    jumpScare.setVolume(volume);
                    keyCooldown.restart();
                }
            }

            volumeText.setString("Volume: " + std::to_string(volume));

            window.clear();
            window.draw(volumeText);
            window.draw(instructions);
            window.display();
        }
    }

    void SettingName()
    {
        string playerName = "";         
        Text nameInput;                 
        nameInput.setFont(font2);        
        nameInput.setCharacterSize(50); 
        nameInput.setFillColor(Color::Red);
        nameInput.setPosition(0, 70);

        Text instruction;
        instruction.setFont(font2);
        instruction.setString("Enter your name and press Enter to confirm:");
        instruction.setCharacterSize(50);
        instruction.setFillColor(Color::White);
        instruction.setPosition(0, 0);

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::TextEntered)
                {
                    if (event.text.unicode == '\b') // Backspace key
                    {
                        if (!playerName.empty())
                            playerName.pop_back();
                    }
                    else if (event.text.unicode < 128 && playerName.length() < 15) 
                    {
                        playerName += static_cast<char>(event.text.unicode);
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Enter)) // Confirm input
                {
                    Player1->set_Name(playerName); 
                    cout << Player1->get_Name();
                    mainMusic.stop();
                    this->IntroScreen();               
                }
            }

            nameInput.setString(playerName); 

            window.clear();
            window.draw(instruction);
            window.draw(nameInput);
            window.display();
        }
    }

    void IntroScreen()
    {
        introMusic.setLoop(true);
        introMusic.play();

        vector<Text> gameTexts;
        Text line;
        line.setFont(font);
        line.setCharacterSize(35);
        line.setFillColor(Color::Red);

        fNarrator->Introduction();

        int yOffset = 0;
        while (!fNarrator->isEmpty())
        {
            line.setString(fNarrator->peekThenPop());
            line.setPosition(40, 50 + yOffset);
            gameTexts.push_back(line);
            yOffset += 50;
        }

        Clock clock;
        int linesToShow = 0;

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                this->GameScreen();
            }
            if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::P))
            {
                this->PauseScreen();
            }

            if (clock.getElapsedTime().asSeconds() >= 1.5f && linesToShow < gameTexts.size())
            {
                linesToShow++;
                clock.restart();
            }

            window.clear();
            for (int i = 0; i < linesToShow; ++i)
                window.draw(gameTexts[i]);

            window.display();
        }
    }

    void PauseScreen()
    {
        fNarrator->Pause();
        vector<Text> pausetext;
        Text line;
        line.setFont(font2);
        line.setCharacterSize(60);
        line.setFillColor(Color::Red);

        line.setString(fNarrator->peekThenPop());
        line.setPosition(30, 50);
        pausetext.push_back(line);

        int yOffset = 150;
        while (!fNarrator->isEmpty())
        {
            line.setString(fNarrator->peekThenPop());
            line.setPosition(350, 50 + yOffset);
            pausetext.push_back(line);
            yOffset += 150;
        }

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::R))
            {
                return;
            }
            if (Keyboard::isKeyPressed(Keyboard::M))
            {
                mainMusic.setLoop(true);
                mainMusic.play();
                introMusic.stop();
                this->MainScreen();
            }
            if (Keyboard::isKeyPressed(Keyboard::Q))
            {
                window.close();
            }

            window.clear();
            for (const auto& text : pausetext)
                window.draw(text);

            window.display();
        }
    }

    void GameScreen()
    {
        introMusic.setLoop(true);
        introMusic.play();

        fNarrator->AfterWakeUp();
        vector<Text> narrationTexts;
        Text line;
        line.setFont(font2);
        line.setCharacterSize(35);
        line.setFillColor(Color::White);
        UpdateNarrationTexts(narrationTexts, fNarrator, line);

        string playerInput = "";
        Text inputDisplay, promptLine, prompt, errorHandler;
        SetupTextElements(inputDisplay, promptLine, prompt, errorHandler);

        bool progressed = true;

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                HandleTextInput(event, playerInput);

                if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::P))
                    this->PauseScreen();

                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    cout << "Player entered: " << playerInput << endl;
                    if (playerInput == "YES" || playerInput == "yes")
                    {
                        progressed = false;
                        playerInput = "";
                        fNarrator->Hall();
                        UpdateNarrationTexts(narrationTexts, fNarrator, line);
                        if (playerInput == "Kitchen" || playerInput == "KITCHEN" || playerInput == "kitchen")
                        {
                            playerInput = "";
                        }
                    }
                    else if (progressed && (playerInput == "NO" || playerInput == "no"))
                    {
                        this->JumpScareScreen();
                        Player1->set_Sanity(-99);
                        playerInput = "";
                    }
                    else if (playerInput == "Inventory" || playerInput == "INVENTORY" || playerInput == "inv" || playerInput == "INV" || playerInput == "Inv")
                    {
                        this->InventoryScreen();
                        playerInput = "";
                    }
                    else if (playerInput == "Status" || playerInput == "STATUS" || playerInput == "status")
                    {
                        this->StatusScreen();
                        playerInput = "";
                    }
                    else if (playerInput == "HELP" || playerInput == "help" || playerInput == "Help")
                    {
                        this->HelpScreen();
                        playerInput = "";
                    }
                    else
                    {
                        playerInput = "";
                    }
                }
            }

            inputDisplay.setString(playerInput);
            window.clear();

            for (const auto& text : narrationTexts)
                window.draw(text);

            window.draw(prompt);
            window.draw(promptLine);
            window.draw(inputDisplay);
            window.draw(errorHandler);
            window.display();
        }
    }

    // Helper functions used above for modularity

    void SetupTextElements(Text& inputDisplay, Text& promptLine, Text& prompt, Text& errorHandler) {
        inputDisplay.setFont(font2);
        inputDisplay.setCharacterSize(40);
        inputDisplay.setFillColor(Color::Green);
        inputDisplay.setPosition(0, WINDOW_HEIGHT - 50);

        promptLine.setFont(font2);
        promptLine.setString("----------------------------------------------------------------------------");
        promptLine.setCharacterSize(40);
        promptLine.setFillColor(Color::White);
        promptLine.setPosition(0, WINDOW_HEIGHT - 150);

        prompt.setFont(font2);
        prompt.setString("Enter your action: ");
        prompt.setCharacterSize(40);
        prompt.setFillColor(Color::White);
        prompt.setPosition(0, WINDOW_HEIGHT - 100);

        errorHandler.setFont(font2);
        errorHandler.setString("Type \"HELP\" for lists of commands!");
        errorHandler.setCharacterSize(35);
        errorHandler.setFillColor(Color::White);
        errorHandler.setPosition(0, WINDOW_HEIGHT - 170);
    }

    void UpdateNarrationTexts(vector<Text>& narrationTexts, Narrator* narrator, Text& line) {
        narrationTexts.clear();
        int yOffset = 0;
        while (!narrator->isEmpty())
        {
            line.setString(narrator->peekThenPop());
            line.setPosition(10, 50 + yOffset);
            narrationTexts.push_back(line);
            yOffset += 50;
        }
    }

    void HandleTextInput(const Event& event, string& playerInput) {
        if (event.type == Event::TextEntered)
        {
            if (event.text.unicode == '\b' && !playerInput.empty()) // Handle backspace
                playerInput.pop_back();
            else if (event.text.unicode < 128 && playerInput.length() < 50)
                playerInput += static_cast<char>(event.text.unicode);
        }
    }


    void MysteriousRoom()
    {

    }

    void JumpScareScreen()
    {
        introMusic.stop();
        jumpScare.play();  
        Clock clock;       

        // Main loop for the JumpScare screen
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            // Check if 5 seconds have passed
            if (clock.getElapsedTime().asSeconds() >= 5.0f)
            {
                jumpScare.stop();
                introMusic.setLoop(true);
                introMusic.play();
                return; 
            }

            window.clear();
            window.draw(jumpScareBGS);  // Draw the jump scare background
            window.display();
        }
    }

    void HelpScreen()
    {

    }

    void InventoryScreen()
    {
        fNarrator->SeeInventory();
        fNarrator->push("Press \"Esc\" key to go back..........");

        vector<Text> MenuTexts;
        Text line;
        line.setFont(font2);
        line.setCharacterSize(30);
        line.setFillColor(Color::White);

        int yOffset = 0;

        while (!fNarrator->isEmpty())
        {
            line.setString(fNarrator->peekThenPop());
            line.setPosition(0, 0 + yOffset);
            MenuTexts.push_back(line);
            yOffset += 50;
        }

        // Main render loop
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                return;
            }

            window.clear();
            for (const auto& text : MenuTexts)
                window.draw(text);

            window.display();
        }
    }

    void StatusScreen()
    {
        fNarrator->PlayerStatus();
        fNarrator->push("Press \"Esc\" key to go back..........");

        vector<Text> MenuTexts;
        Text line;
        line.setFont(font2);
        line.setCharacterSize(60);
        line.setFillColor(Color::White);

        int yOffset = 0;

        while (!fNarrator->isEmpty())
        {
            line.setString(fNarrator->peekThenPop());
            line.setPosition(0, 0 + yOffset);
            MenuTexts.push_back(line);
            yOffset += 100;
        }

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                return;
            }

            window.clear();
            for (const auto& text : MenuTexts)
                window.draw(text);

            window.display();
        }
    }

  
    void GameOverScreen()
    {
            
    }

};
