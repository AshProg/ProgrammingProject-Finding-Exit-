#pragma once
#include <unordered_map>  
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Player.h"
#include "Inventory.h"
#include "Narrator.h"
#include "ImageRoom.h"
#include "OutwearInv.h"
using namespace sf;

// Constants for window dimensions
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

class GameState
{
private:
    // Variables for items and states in the kitchen
    bool potionKitchen, saltKitchen, paperKitchen;  // Booleans for items in the kitchen
    bool readPaper1;  // Whether the first paper in the kitchen has been read

    // Variables for items and states in the bathroom
    bool potionBathroom, boxBathroom;  // Booleans for items in the bathroom

    // Variables for items and states in the room
    bool keyInRoom;  // Whether a key is present in the room
    bool keyTaken;  // Whether the key has been taken by the player
    bool firstTime;  // Whether the player is entering the room for the first time
    bool thirdTime;  // Whether the player has entered the room three times
    int countInRoom;  // A counter for tracking the number of times the player enters the room

    // Variables for items and states at the entrance
    bool keyUsed;  // Whether the key has been used at the entrance
    bool saltUsed;  // Whether salt has been used at the entrance
    bool jacket;

    // Pointers to game-related objects
    Inventory* PlayerInv;  // Pointer to the player's inventory
    OutwearInv* PlayerOutwear;  // Pointer to the player's outwear inventory
    Player* Player1;  // Pointer to the player object
    ImageRoom* imgInv;  // Pointer to the ImageRoom object for handling room images

    // Fonts for displaying text
    Font font;  // Font used for general text
    Font font2;  // Another font for specific text

    // RenderWindow for creating the game window
    RenderWindow window;

    // Textures for different game scenes and objects
    Texture backgroundTexture;  // Texture for the background
    Texture jumpScareBG;  // Texture for the jump scare background
    Texture creepyKitchen;  // Texture for the creepy kitchen scene
    Texture creepyRoom;  // Texture for the creepy room scene
    Texture creepyBathroom;  // Texture for the creepy bathroom scene
    Texture creepyHall;  // Texture for the creepy hall scene
    Texture gameOverBG;  // Texture for the game over background
    Texture EntranceDoor;  // Texture for the entrance door
    Sprite backgroundSprite;  // Sprite for displaying the background
    Sprite jumpScareBGS;  // Sprite for displaying the jump scare background
    Sprite creepyKitchens;  // Sprite for displaying the creepy kitchen
    Sprite creepyRooms;  // Sprite for displaying the creepy room
    Sprite creepyBathrooms;  // Sprite for displaying the creepy bathroom
    Sprite creepyHalls;  // Sprite for displaying the creepy hall
    Sprite gameOverBGS;  // Sprite for displaying the game over background
    Sprite EntranceSprite;  // Sprite for displaying the entrance door

    // Music for different scenes
    Music mainMusic;  // Music for the main game loop
    Music introMusic;  // Music for the intro scene
    Music jumpScare;  // Music for the jump scare scene
    Music GameOver;  // Music for the game over scene

    // Pointer to the Narrator object for handling narrative text
    Narrator* fNarrator;

public:
    GameState() : window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Finding Exit")  // Initialize the window with the specified dimensions and title
    {
        // Initialize the default object for the player
        Objects* Default = new Objects("Your companion for the journey!", "Yourself");

        // Create a new inventory for the player with the default object
        PlayerInv = new Inventory(Default);

        Outwear* Cap = new Outwear("Cap", 100);
        PlayerOutwear = new OutwearInv(Cap);
        // Initialize the player with a default name and the inventory and outwear
        Player1 = new Player("Default Name", PlayerInv, PlayerOutwear);

        // Initialize the narrator with the title and player
        fNarrator = new Narrator("Finding Exit", Player1);

        // Load fonts for text rendering, handle errors if the font files cannot be loaded
        if (!font.loadFromFile("Library/FONT/dksamhain.ttf"))
        {
            cerr << "Error loading font!" << endl;
        }

        if (!font2.loadFromFile("Library/FONT/DEAD.otf"))
        {
            cerr << "Error loading font!" << endl;
        }

        // Load background textures for different scenes, handle errors if the texture files cannot be loaded
        if (!backgroundTexture.loadFromFile("Library/ASSETS/IMAGES/BG2.png"))
        {
            cerr << "Error loading background image!" << endl;
        }

        if (!jumpScareBG.loadFromFile("Library/ASSETS/IMAGES/JumpScare.png"))
        {
            cerr << "Error loading background image!" << endl;
        }

        if (!creepyKitchen.loadFromFile("Library/ASSETS/IMAGES/CreepyKitchen.png"))
        {
            cerr << "Error loading background image!" << endl;
        }

        if (!creepyBathroom.loadFromFile("Library/ASSETS/IMAGES/CreepyBathroom.png"))
        {
            cerr << "Error loading background image!" << endl;
        }

        if (!creepyRoom.loadFromFile("Library/ASSETS/IMAGES/CreepyRoom.png"))
        {
            cerr << "Error loading background image!" << endl;
        }

        if (!creepyHall.loadFromFile("Library/ASSETS/IMAGES/CreepyHall.png"))
        {
            cerr << "Error loading background image!" << endl;
        }

        if (!gameOverBG.loadFromFile("Library/ASSETS/IMAGES/GameOver.png"))
        {
            cerr << "Error loading background image!" << endl;
        }

        if (!EntranceDoor.loadFromFile("Library/ASSETS/IMAGES/EntranceDoor.png"))
        {
            cerr << "Error loading background image!" << endl;
        }

        // Set the textures to corresponding sprites
        backgroundSprite.setTexture(backgroundTexture);
        jumpScareBGS.setTexture(jumpScareBG);
        creepyKitchens.setTexture(creepyKitchen);
        creepyBathrooms.setTexture(creepyBathroom);
        creepyHalls.setTexture(creepyHall);
        creepyRooms.setTexture(creepyRoom);
        gameOverBGS.setTexture(gameOverBG);
        EntranceSprite.setTexture(EntranceDoor);

        // Initialize the ImageRoom object with the background sprite
        imgInv = new ImageRoom(backgroundSprite);

        // Enqueue images to the ImageRoom object for different scenes (entrance, game over, jump scare, etc.)
        imgInv->Enqueue(new ImageRoom(EntranceSprite));
        imgInv->Enqueue(new ImageRoom(gameOverBGS));
        imgInv->Enqueue(new ImageRoom(jumpScareBGS));
        imgInv->Enqueue(new ImageRoom(creepyKitchens));
        imgInv->Enqueue(new ImageRoom(creepyBathrooms));
        imgInv->Enqueue(new ImageRoom(creepyHalls));
        imgInv->Enqueue(new ImageRoom(creepyRooms));

        // Load game music files, handle errors if the music files cannot be loaded
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

        if (!GameOver.openFromFile("Library/ASSETS/SOUNDS/GameOver.wav"))
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
        // Initializing game states for different areas and settings

        // Kitchen: Set all items to true, meaning they're available
        potionKitchen = true, saltKitchen = true, paperKitchen = true;
        readPaper1 = false;  // No paper has been read yet

        // Bathroom: Set items available in the bathroom
        potionBathroom = true, boxBathroom = true;

        // Room: Set initial conditions for the room
        keyInRoom = false;  // Key is not in the room initially
        keyTaken = false;  // Key has not been taken yet
        firstTime = true;  // First time entering the room
        thirdTime = false;  // Not the third time yet
        countInRoom = 0;  // Initial count for interactions in the room

        // Entrance: Track the use of key and salt
        keyUsed = false;  // Key has not been used yet
        saltUsed = false;  // Salt has not been used yet
        jacket = false;

        // Set the player's sanity to 100
        Player1->set_Sanity(100);
        Player1->RemoveOutwear();
        Outwear* Cap = new Outwear("Cap", 100);
        Player1->UseOutwear(Cap);

        // Start playing the main screen music, set it to loop for continuous playback
        mainMusic.setLoop(true);  // Loop the music indefinitely
        mainMusic.play();

        // Add text to the narrator's stack to display the main screen menu options
        fNarrator->push("(Q) Quit\n");  // Option to quit the game
        fNarrator->push("(S) Settings\n");  // Option to access settings
        fNarrator->push("(P) Play\n");  // Option to start playing the game
        fNarrator->push("WELCOME TO \"FINDING EXIT\"\n");  // Welcome message

        // Create a vector to store the text objects that will be displayed on the menu screen
        vector<Text> MenuTexts;
        Text line;
        line.setFont(font);  // Set the font for the text
        line.setCharacterSize(80);  // Set the text size
        line.setFillColor(Color::Red);  // Set the text color to red

        int yOffset = 0;  // Vertical offset for text positioning
        line.setString(fNarrator->peekThenPop());  // Get the first narrator message
        line.setPosition(30, 50 + yOffset);  // Set the position for the first line
        MenuTexts.push_back(line);  // Add the line to the menu text vector
        yOffset += 100;  // Increase the vertical offset for the next line

        // Loop to process and display all remaining narrator text messages
        while (!fNarrator->isEmpty())
        {
            line.setString(fNarrator->peekThenPop());  // Get the next narrator message
            line.setPosition(300, 50 + yOffset);  // Set the position for the next line
            MenuTexts.push_back(line);  // Add the line to the menu text vector
            yOffset += 100;  // Increase the vertical offset for the next line
        }

        // Main render loop: Keep the window open and process user input
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))  // Check for any window events
            {
                if (event.type == Event::Closed)  // If the window is closed
                    window.close();  // Close the window
            }

            // Handle key press events for menu navigation
            if (Keyboard::isKeyPressed(Keyboard::Q))  // If 'Q' is pressed
            {
                window.close();  // Close the window (quit the game)
            }
            else if (Keyboard::isKeyPressed(Keyboard::P))  // If 'P' is pressed
            {
                this->SettingName();  // Start the game (or change settings name)
            }
            else if (Keyboard::isKeyPressed(Keyboard::S))  // If 'S' is pressed
            {
                this->SettingsScreen();  // Show the settings screen
            }

            // Clear the window to prepare for the next frame
            window.clear();

            // Draw the background image (from ImageRoom)
            window.draw(imgInv->get_Sprite());

            // Draw all the menu text lines
            for (const auto& text : MenuTexts)
                window.draw(text);  // Render each text in the MenuTexts vector

            // Display the rendered content on the screen
            window.display();
        }
    }

    void SettingsScreen()
    {
        // Create a hash table to store settings, with the setting name as the key and the value as the setting's value
        std::unordered_map<std::string, int> settings;  // Hash table for storing settings
        settings["volume"] = mainMusic.getVolume();  // Initialize the volume from the main music

        // Create a text object to display the volume settings
        Text volumeText;
        volumeText.setFont(font2);  // Set the font for the volume text
        volumeText.setCharacterSize(50);  // Set the text size
        volumeText.setFillColor(Color::White);  // Set the text color to white
        volumeText.setPosition(50, 100);  // Set the position of the volume text on screen

        // Get the current volume from the hash table
        int volume = settings["volume"];

        // Create a clock to handle the cooldown between key presses (prevents rapid changes)
        Clock keyCooldown;

        // Create a text object to display instructions for the player
        Text instructions;
        instructions.setFont(font2);  // Set the font for the instructions text
        instructions.setCharacterSize(30);  // Set the text size
        instructions.setFillColor(Color::White);  // Set the text color to white
        instructions.setPosition(50, 200);  // Set the position of the instructions text
        instructions.setString("Use UP and DOWN arrow keys to adjust volume.\nPress ESC to return.");  // Set the instruction text

        // Start the settings screen loop
        while (window.isOpen())
        {
            Event event;
            // Handle window events (e.g., closing the window)
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();  // Close the window if the user closes it
            }

            // Check if the Escape key is pressed, and if so, exit the settings screen
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                return;  // Exit the settings screen and return to the previous screen
            }

            // Check if the cooldown period has passed (200 ms delay before adjusting volume again)
            if (keyCooldown.getElapsedTime().asMilliseconds() > 100)
            {
                // If the UP arrow key is pressed and the volume is less than 100, increase the volume
                if (Keyboard::isKeyPressed(Keyboard::Up) && volume < 100)
                {
                    volume += 1;  // Increase the volume by 1
                    settings["volume"] = volume;  // Update the volume in the hash table
                    mainMusic.setVolume(volume);  // Set the new volume for main music
                    introMusic.setVolume(volume);  // Set the new volume for intro music
                    jumpScare.setVolume(volume);  // Set the new volume for jump scare sound
                    keyCooldown.restart();  // Restart the cooldown timer to prevent rapid key presses
                }
                // If the DOWN arrow key is pressed and the volume is greater than 0, decrease the volume
                else if (Keyboard::isKeyPressed(Keyboard::Down) && volume > 0)
                {
                    volume -= 1;  // Decrease the volume by 1
                    settings["volume"] = volume;  // Update the volume in the hash table
                    mainMusic.setVolume(volume);  // Set the new volume for main music
                    introMusic.setVolume(volume);  // Set the new volume for intro music
                    jumpScare.setVolume(volume);  // Set the new volume for jump scare sound
                    keyCooldown.restart();  // Restart the cooldown timer
                }
            }

            // Update the volume text to reflect the current volume level from the hash table
            volumeText.setString("Volume: " + std::to_string(settings["volume"]));

            // Clear the window to prepare for the next frame
            window.clear();

            // Draw the volume text and the instructions text
            window.draw(volumeText);
            window.draw(instructions);

            // Display the updated contents of the window
            window.display();
        }
    }

    void SettingName()
    {
        string playerName = ""; // Initialize an empty string to store the player's name
        Text nameInput; // Text object to display the player's input on the screen
        nameInput.setFont(font2); // Set the font for the name input text
        nameInput.setCharacterSize(50); // Set the font size for the name input
        nameInput.setFillColor(Color::Red); // Set the text color for the name input to red
        nameInput.setPosition(0, 70); // Set the position for the name input text on the screen

        Text instruction; // Text object to display the instruction to the player
        instruction.setFont(font2); // Set the font for the instruction text
        instruction.setString("Enter your name and press Enter to confirm:"); // Set the instruction text
        instruction.setCharacterSize(50); // Set the font size for the instruction text
        instruction.setFillColor(Color::White); // Set the text color for the instruction to white
        instruction.setPosition(0, 0); // Set the position for the instruction text on the screen

        // Main input loop for the name input screen
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event)) // Poll for any events (like key presses)
            {
                if (event.type == Event::Closed) // If the window is closed, exit the program
                    window.close();

                if (event.type == Event::TextEntered) // If a text key is pressed
                {
                    // Handle backspace key to remove last character from playerName
                    if (event.text.unicode == '\b')
                    {
                        if (!playerName.empty()) // Only pop a character if the name is not empty
                            playerName.pop_back(); // Remove the last character
                    }
                    else if (event.text.unicode < 128 && playerName.length() < 15) // Only allow printable characters and limit name length to 15
                    {
                        playerName += static_cast<char>(event.text.unicode); // Add the character to playerName
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Enter)) // When Enter key is pressed, confirm the name
                {
                    Player1->set_Name(playerName); // Set the player's name using the Player1 object
                    cout << Player1->get_Name() << endl; // Output the player's name to the console for verification
                    mainMusic.stop(); // Stop the background music
                    this->IntroScreen(); // Transition to the IntroScreen after setting the name
                }
            }

            // Update the nameInput text to reflect the current playerName input
            nameInput.setString(playerName);

            window.clear(); // Clear the window before drawing the updated content
            window.draw(instruction); // Draw the instruction text
            window.draw(nameInput); // Draw the player's name input text
            window.display(); // Display the updated window content
        }
    }

    void IntroScreen()
    {
        // Set the intro music to loop and play it
        introMusic.setLoop(true);
        introMusic.play();

        vector<Text> gameTexts; // Vector to hold all the lines of text to display on the screen
        Text line; // Text object to store each individual line of narration
        line.setFont(font); // Set the font for the text
        line.setCharacterSize(35); // Set the font size for the text
        line.setFillColor(Color::Red); // Set the color of the text to red

        fNarrator->Introduction(); // Call the Introduction method of the Narrator object to add text to the stack

        int yOffset = 0; // Variable to control vertical spacing for each line of text
        // Loop through all the lines in the narrator stack and prepare them for rendering
        while (!fNarrator->isEmpty())
        {
            // Get the next line of narration and set it for the current text object
            line.setString(fNarrator->peekThenPop());
            line.setPosition(40, 50 + yOffset); // Position each line of text with an increasing yOffset
            gameTexts.push_back(line); // Add the current line of text to the gameTexts vector
            yOffset += 50; // Increase the yOffset for the next line
        }

        Clock clock; // Clock to handle timing for displaying the lines
        int linesToShow = 0; // Variable to track how many lines of text should be displayed

        // Main game loop for the intro screen
        while (window.isOpen())
        {
            Event event;
            // Poll for events like window close or key presses
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed) // If the window is closed, exit the loop
                    window.close();
            }

            // Check for specific key presses to navigate to different screens
            if (Keyboard::isKeyPressed(Keyboard::W)) // Press 'W' to go to the main game screen
            {
                this->GameScreen(); // Transition to the main game screen
            }
            if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::P)) // Press 'LControl' + 'P' to pause
            {
                this->PauseScreen(); // Transition to the pause screen
            }

            // Display the next line of text every 1.5 seconds
            if (clock.getElapsedTime().asSeconds() >= 1.5f && linesToShow < gameTexts.size())
            {
                linesToShow++; // Increase the number of lines to show
                clock.restart(); // Restart the clock to count the next 1.5 seconds
            }

            window.clear(); // Clear the window before drawing new content
            // Draw the lines of text that should be visible based on the elapsed time
            for (int i = 0; i < linesToShow; ++i)
                window.draw(gameTexts[i]);

            window.display(); // Display the updated window content
        }
    }

    void PauseScreen()
    {
        // Pause the narration
        fNarrator->Pause();

        vector<Text> pausetext; // Vector to hold all the lines of pause screen text
        Text line; // Text object to store each individual line of pause screen text
        line.setFont(font2); // Set the font for the text
        line.setCharacterSize(60); // Set the font size for the text
        line.setFillColor(Color::Red); // Set the color of the text to red

        // Set the first line of text for the pause screen and position it
        line.setString(fNarrator->peekThenPop());
        line.setPosition(30, 50); // Set the position of the first line
        pausetext.push_back(line); // Add the first line to the pausetext vector

        int yOffset = 150; // Initial y-offset for the subsequent lines of text
        // Loop through the remaining lines of narration and add them to the pausetext vector
        while (!fNarrator->isEmpty())
        {
            line.setString(fNarrator->peekThenPop()); // Get the next line of narration
            line.setPosition(350, 50 + yOffset); // Position each line with an increasing yOffset
            pausetext.push_back(line); // Add the current line to the pausetext vector
            yOffset += 150; // Increase the yOffset for the next line
        }

        // Main loop for the pause screen
        while (window.isOpen())
        {
            Event event;
            // Poll for events like window close or key presses
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed) // If the window is closed, exit the loop
                    window.close();
            }

            // Check for specific key presses to resume or navigate
            if (Keyboard::isKeyPressed(Keyboard::R)) // Press 'R' to resume the game (close pause screen)
            {
                return; // Exit the pause screen and resume the game
            }
            if (Keyboard::isKeyPressed(Keyboard::M)) // Press 'M' to return to the main menu
            {
                // Reset the game state when returning to the main menu
                bool potionKitchen = true, saltKitchen = true, paperKitchen = true;
                bool readPaper1 = false;

                bool potionBathroom = true, boxBathroom = true;

                bool keyInRoom = false;
                bool firstTime = true;
                thirdTime = false;
                countInRoom = 0;

                Player1->RemoveObject(); // Remove all objects from the player
                Player1->set_Sanity(100); // Reset player's sanity to 100
                mainMusic.setLoop(true); // Loop the main music
                mainMusic.play(); // Play the main music
                introMusic.stop(); // Stop the intro music
                this->MainScreen(); // Return to the main screen
            }
            if (Keyboard::isKeyPressed(Keyboard::Q)) // Press 'Q' to quit the game
            {
                window.close(); // Close the game window
            }

            window.clear(); // Clear the window before drawing new content
            // Draw all the lines of text for the pause screen
            for (const auto& text : pausetext)
                window.draw(text);

            window.display(); // Display the updated window content
        }
    }

    void GameScreen()
    {
        // Play intro music and set it to loop
        introMusic.setLoop(true);
        introMusic.play();

        // Start the narration after the player wakes up
        fNarrator->AfterWakeUp();

        // Set up text elements for displaying narration
        vector<Text> narrationTexts; // Vector to store the narration text lines
        Text line; // Single Text object to store a line of narration
        line.setFont(font2); // Set the font for the text
        line.setCharacterSize(35); // Set the size of the text
        line.setFillColor(Color::White); // Set the text color to white

        // Update the narration texts using the narration from the narrator
        UpdateNarrationTexts(narrationTexts, fNarrator, line);

        // Initialize variables for player input and display text elements
        string playerInput = ""; // Player's input as a string
        Text inputDisplay, promptLine, prompt, errorHandler; // Text elements for input display and error handling
        SetupTextElements(inputDisplay, promptLine, prompt, errorHandler); // Set up text elements (probably positions, styles)

        bool hall = false; // Boolean to track if the player has entered the hall

        // Main game screen loop
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event)) // Poll for events such as key presses or window closing
            {
                if (event.type == Event::Closed) // If window is closed, close the game
                    window.close();

                HandleTextInput(event, playerInput); // Handle player input as text
                // Check for pause screen activation
                if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::P))
                    this->PauseScreen(); // Open the pause screen

                // Check for player pressing Enter to submit input
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    cout << "Player entered: " << playerInput << endl;

                    // Main input handling logic for navigating between rooms or triggering options
                    if (hall)
                    {
                        fNarrator->Hall(jacket); // Start the hall narration
                        UpdateNarrationTexts(narrationTexts, fNarrator, line); // Update narration text
                    }
                    if (!hall && (playerInput == "YES" || playerInput == "yes"))
                    {
                        hall = true; // Player enters the hall
                        playerInput = ""; // Clear input
                        
                    }
                    else if (!hall && (playerInput == "NO" || playerInput == "no"))
                    {
                        this->JumpScareScreen(); // Show jump scare screen
                        Player1->set_Sanity(-99); // Decrease player's sanity drastically
                        playerInput = ""; // Clear input
                    }
                    else if (jacket && hall && (playerInput == "Pick Jacket" || playerInput == "PICK JACKET" || playerInput == "pick jacket"))
                    {
                        Outwear* Jacket = new Outwear("Jacket", 200);
                        Player1->UseOutwear(Jacket);
                        jacket = false;;
                    }
                    else if (hall && (playerInput == "Kitchen" || playerInput == "KITCHEN" || playerInput == "kitchen"))
                    {
                        this->Kitchen(); // Move to the kitchen screen
                        playerInput = ""; // Clear input
                    }
                    else if (hall && (playerInput == "Bathroom" || playerInput == "BATHROOM" || playerInput == "bathroom"))
                    {
                        this->Bathroom(); // Move to the bathroom screen
                        playerInput = ""; // Clear input
                    }
                    else if (hall && (playerInput == "room" || playerInput == "ROOM" || playerInput == "Room"))
                    {
                        this->Room(); // Move to the room screen
                        playerInput = ""; // Clear input
                    }
                    else if (playerInput == "Entrance" || playerInput == "ENTRANCE" || playerInput == "entrance")
                    {
                        // If the key is taken, mark as used, otherwise set to false
                        if (keyTaken)
                        {
                            keyUsed = true;
                        }
                        else
                        {
                            keyUsed = false;
                        }
                        this->Entrance(); // Go to the entrance screen
                        playerInput = ""; // Clear input
                    }
                    else if (playerInput == "Inventory" || playerInput == "INVENTORY" || playerInput == "inv" || playerInput == "INV" || playerInput == "Inv")
                    {
                        this->InventoryScreen(); // Show the inventory screen
                        playerInput = ""; // Clear input
                    }
                    else if (playerInput == "Status" || playerInput == "STATUS" || playerInput == "status")
                    {
                        this->StatusScreen(); // Show the player's status screen
                        playerInput = ""; // Clear input
                    }
                    else if (playerInput == "HELP" || playerInput == "help" || playerInput == "Help")
                    {
                        this->HelpScreen(); // Show the help screen
                        playerInput = ""; // Clear input
                    }
                    else
                    {
                        playerInput = ""; // Reset the input if it's unrecognized
                    }
                }
            }

            inputDisplay.setString(playerInput); // Set the string for the player input text display
            window.clear(); // Clear the window before redrawing

            // Draw different content based on whether the player is in the hall or not
            if (!hall)
            {
                window.draw(imgInv->get_Sprite()); // Draw inventory sprite if not in hall
            }
            else
            {
                // Draw the sprite for the current room if in hall
                Sprite currentSprite = imgInv->get_Next()->get_Next()->get_Sprite();
                window.draw(currentSprite);
            }

            // Draw the narration text, input prompt, and error handler
            for (const auto& text : narrationTexts)
                window.draw(text); // Draw all the narration lines

            window.draw(prompt); // Draw the prompt text
            window.draw(promptLine); // Draw the prompt line
            window.draw(inputDisplay); // Draw the player's input
            window.draw(errorHandler); // Draw any error messages if applicable

            window.display(); // Display the updated window content
        }
    }

    // Rooms inside the house
    void Kitchen()
    {
        // Create a vector to hold the narration text for the kitchen scene
        vector<Text> narrationTexts;
        Text line; // Text object to store a single line of narration
        line.setFont(font2); // Set the font for the narration text
        line.setCharacterSize(35); // Set the size of the narration text
        line.setFillColor(Color::White); // Set the text color to white

        string playerInput = ""; // Store the player's input
        Text inputDisplay, promptLine, prompt, errorHandler; // Text objects for displaying input, prompt, and error messages
        SetupTextElements(inputDisplay, promptLine, prompt, errorHandler); // Initialize the text elements (position, style, etc.)

        // Main kitchen screen loop
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event)) // Poll for events like key presses
            {
                // Call the narrator's kitchen method to update the narration
                fNarrator->Kitchen(potionKitchen, saltKitchen, paperKitchen);
                // Update the narration texts with the latest narrative content
                UpdateNarrationTexts(narrationTexts, fNarrator, line);

                if (event.type == Event::Closed) // If the window is closed, exit the loop
                    window.close();

                HandleTextInput(event, playerInput); // Handle the player input

                // Check for pause screen activation
                if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::P))
                    this->PauseScreen(); // Show the pause screen

                // Check for Enter key press to submit input
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    cout << "Player entered: " << playerInput << endl;

                    // Handle different kitchen-related commands based on the player's input
                    if (playerInput == "PICK SALT" || playerInput == "pick salt" || playerInput == "Pick Salt")
                    {
                        // If salt is still available, allow the player to pick it up
                        if (saltKitchen)
                        {
                            PurifiedSalt* kitchenSalt = new PurifiedSalt(); // Create a new salt object
                            Player1->PickUpObject(kitchenSalt); // Add the salt to the player's inventory
                            cout << "SALT has been picked up!" << endl;
                            saltKitchen = false; // Mark that salt is no longer available
                            playerInput = ""; // Clear the input
                        }
                        else
                        {
                            cout << "NO MORE SALT!" << endl; // If no salt is available, inform the player
                        }
                    }
                    else if (playerInput == "PICK POTION" || playerInput == "pick potion" || playerInput == "Pick Potion")
                    {
                        // If potion is still available, allow the player to pick it up
                        if (potionKitchen)
                        {
                            SanityPotion* kitchenPotion = new SanityPotion(50); // Create a new potion object
                            Player1->PickUpObject(kitchenPotion); // Add the potion to the player's inventory
                            cout << "POTION has been picked up!" << endl;
                            potionKitchen = false; // Mark that the potion is no longer available
                            playerInput = ""; // Clear the input
                        }
                        else
                        {
                            cout << "NO MORE POTION!" << endl; // If no potion is available, inform the player
                        }
                    }
                    else if (playerInput == "PICK PAPER" || playerInput == "pick paper" || playerInput == "Pick Paper")
                    {
                        // If paper is still available, allow the player to pick it up
                        if (paperKitchen)
                        {
                            Objects* kitchenPaper = new Objects("Clue for what you must do...", "Paper"); // Create a paper object with a clue
                            Player1->PickUpObject(kitchenPaper); // Add the paper to the player's inventory
                            cout << "PAPER has been picked up!" << endl;
                            readPaper1 = true; // Mark the paper as read
                            paperKitchen = false; // Mark that the paper is no longer available
                            playerInput = ""; // Clear the input
                        }
                        else
                        {
                            cout << "Paper has been taken" << endl; // Inform the player that the paper is no longer available
                        }
                    }
                    else if (playerInput == "BACK" || playerInput == "back")
                    {
                        return; // If the player types "back", return to the previous screen (exit the kitchen)
                    }
                    else if (playerInput == "Inventory" || playerInput == "INVENTORY" || playerInput == "inv" || playerInput == "INV" || playerInput == "Inv")
                    {
                        this->InventoryScreen(); // Show the inventory screen
                        playerInput = ""; // Clear the input
                    }
                    else if (playerInput == "Status" || playerInput == "STATUS" || playerInput == "status")
                    {
                        this->StatusScreen(); // Show the player's status screen
                        playerInput = ""; // Clear the input
                    }
                    else if (playerInput == "HELP" || playerInput == "help" || playerInput == "Help")
                    {
                        this->HelpScreen(); // Show the help screen
                        playerInput = ""; // Clear the input
                    }
                    else
                    {
                        playerInput = ""; // If the input is unrecognized, clear it
                    }
                }
            }

            inputDisplay.setString(playerInput); // Update the input display text with the player's input
            window.clear(); // Clear the window before redrawing

            // Draw the current kitchen scene sprite (sprite in sequence from the inventory)
            Sprite currentSprite = imgInv->get_Next()->get_Next()->get_Next()->get_Next()->get_Sprite();
            window.draw(currentSprite);

            // Draw the narration texts on the screen
            for (const auto& text : narrationTexts)
                window.draw(text);

            window.draw(prompt); // Draw the prompt text
            window.draw(promptLine); // Draw the prompt line
            window.draw(inputDisplay); // Draw the player's input
            window.draw(errorHandler); // Draw any error messages if applicable

            window.display(); // Display the updated window content
        }
    }

    void Bathroom()
    {
        // Create a vector to hold the narration text for the bathroom scene
        vector<Text> narrationTexts;
        Text line; // Text object to store a single line of narration
        line.setFont(font2); // Set the font for the narration text
        line.setCharacterSize(35); // Set the size of the narration text
        line.setFillColor(Color::White); // Set the text color to white

        string playerInput = ""; // Store the player's input
        Text inputDisplay, promptLine, prompt, errorHandler; // Text objects for displaying input, prompt, and error messages
        SetupTextElements(inputDisplay, promptLine, prompt, errorHandler); // Initialize the text elements (position, style, etc.)

        // Main bathroom screen loop
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event)) // Poll for events like key presses
            {
                // Call the narrator's bathroom method to update the narration
                fNarrator->Bathroom(potionBathroom, boxBathroom);
                // Update the narration texts with the latest narrative content
                UpdateNarrationTexts(narrationTexts, fNarrator, line);

                if (event.type == Event::Closed) // If the window is closed, exit the loop
                    window.close();

                HandleTextInput(event, playerInput); // Handle the player input

                // Check for pause screen activation
                if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::P))
                    this->PauseScreen(); // Show the pause screen

                // Check for Enter key press to submit input
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    cout << "Player entered: " << playerInput << endl;

                    // Handle specific bathroom commands based on the player's input
                    if (playerInput == "PICK POTION" || playerInput == "pick potion" || playerInput == "Pick Potion")
                    {
                        // If potion is still available, allow the player to pick it up
                        if (potionBathroom)
                        {
                            SanityPotion* bathroomPotion = new SanityPotion(50); // Create a new potion object
                            Player1->PickUpObject(bathroomPotion); // Add the potion to the player's inventory
                            cout << "POTION has been picked up!" << endl;
                            potionBathroom = false; // Mark that the potion is no longer available
                            playerInput = ""; // Clear the input
                        }
                        else
                        {
                            cout << "NO MORE POTION!" << endl; // If no potion is available, inform the player
                        }
                    }
                    else if (playerInput == "OPEN BOX" || playerInput == "open box" || playerInput == "Open Box")
                    {
                        // If box is still available, allow the player to open it
                        if (boxBathroom)
                        {
                            Player1->set_Sanity(-50); // Decrease the player's sanity by 50
                            cout << "BOX has been opened" << endl;
                            boxBathroom = false; // Mark that the box is no longer available
                            keyInRoom = true; // Indicate that the key is now in the room
                            jacket = true;
                            playerInput = ""; // Clear the input
                            this->JumpScareScreen(); // Show the jump scare screen
                        }
                        else
                        {
                            cout << "BOX DISAPPEARED!" << endl; // If the box is not available, inform the player
                        }
                    }
                    else if (playerInput == "BACK" || playerInput == "back")
                    {
                        return; // If the player types "back", return to the previous screen (exit the bathroom)
                    }
                    else if (playerInput == "Inventory" || playerInput == "INVENTORY" || playerInput == "inv" || playerInput == "INV" || playerInput == "Inv")
                    {
                        this->InventoryScreen(); // Show the inventory screen
                        playerInput = ""; // Clear the input
                    }
                    else if (playerInput == "Status" || playerInput == "STATUS" || playerInput == "status")
                    {
                        this->StatusScreen(); // Show the player's status screen
                        playerInput = ""; // Clear the input
                    }
                    else if (playerInput == "HELP" || playerInput == "help" || playerInput == "Help")
                    {
                        this->HelpScreen(); // Show the help screen
                        playerInput = ""; // Clear the input
                    }
                    else
                    {
                        playerInput = ""; // If the input is unrecognized, clear it
                    }
                }
            }

            inputDisplay.setString(playerInput); // Update the input display text with the player's input
            window.clear(); // Clear the window before redrawing

            // Draw the current bathroom scene sprite (sprite in sequence from the inventory)
            Sprite currentSprite = imgInv->get_Next()->get_Next()->get_Next()->get_Sprite();
            window.draw(currentSprite);

            // Draw the narration texts on the screen
            for (const auto& text : narrationTexts)
                window.draw(text);

            window.draw(prompt); // Draw the prompt text
            window.draw(promptLine); // Draw the prompt line
            window.draw(inputDisplay); // Draw the player's input
            window.draw(errorHandler); // Draw any error messages if applicable

            window.display(); // Display the updated window content
        }
    }

    void Room()
    {
        // Create a vector to hold the narration text for the room scene
        vector<Text> narrationTexts;
        Text line; // Text object to store a single line of narration
        line.setFont(font2); // Set the font for the narration text
        line.setCharacterSize(35); // Set the size of the narration text
        line.setFillColor(Color::White); // Set the text color to white

        string playerInput = ""; // Store the player's input
        Text inputDisplay, promptLine, prompt, errorHandler; // Text objects for displaying input, prompt, and error messages
        SetupTextElements(inputDisplay, promptLine, prompt, errorHandler); // Initialize the text elements (position, style, etc.)

        countInRoom++; // Increment the counter for how many times the player has entered the room
        cout << countInRoom; // Output the count for debugging purposes

        // Main room screen loop
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event)) // Poll for events like key presses
            {
                // Call the narrator's room method to update the narration
                fNarrator->Room1(keyInRoom, firstTime);
                // Update the narration texts with the latest narrative content
                UpdateNarrationTexts(narrationTexts, fNarrator, line);

                // Change text properties if it's not the first time entering the room
                if (!firstTime)
                {
                    line.setFont(font); // Set a different font for non-first-time entries
                    line.setCharacterSize(50); // Increase font size for non-first-time entries
                    line.setFillColor(Color::Red); // Change text color to red for non-first-time entries
                }

                if (event.type == Event::Closed) // If the window is closed, exit the loop
                    window.close();

                HandleTextInput(event, playerInput); // Handle the player input

                // Check for pause screen activation
                if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::P))
                    this->PauseScreen(); // Show the pause screen

                // Check for Enter key press to submit input
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    cout << "Player entered: " << playerInput << endl;

                    // Handle specific room commands based on the player's input
                    if (playerInput == "PICK KEY" || playerInput == "pick key" || playerInput == "Pick Key")
                    {
                        // If the key is still in the room, allow the player to pick it up
                        if (keyInRoom)
                        {
                            keyInRoom = false; // Mark that the key is no longer in the room
                            keyTaken = true; // Mark that the player has taken the key
                            firstTime = false; // Indicate that the player has now visited this room before
                            line.setFont(font); // Set the font for the new text
                            line.setCharacterSize(50); // Set the font size
                            line.setFillColor(Color::Red); // Set the text color to red to highlight the action
                            playerInput = ""; // Clear the input
                        }
                    }
                    else if (playerInput == "BACK" || playerInput == "back")
                    {
                        return; // If the player types "back", return to the previous screen (exit the room)
                    }
                    else if (playerInput == "Inventory" || playerInput == "INVENTORY" || playerInput == "inv" || playerInput == "INV" || playerInput == "Inv")
                    {
                        this->InventoryScreen(); // Show the inventory screen
                        playerInput = ""; // Clear the input
                    }
                    else if (playerInput == "Status" || playerInput == "STATUS" || playerInput == "status")
                    {
                        this->StatusScreen(); // Show the player's status screen
                        playerInput = ""; // Clear the input
                    }
                    else if (playerInput == "HELP" || playerInput == "help" || playerInput == "Help")
                    {
                        this->HelpScreen(); // Show the help screen
                        playerInput = ""; // Clear the input
                    }
                    else
                    {
                        playerInput = ""; // If the input is unrecognized, clear it
                    }
                }
            }

            inputDisplay.setString(playerInput); // Update the input display text with the player's input
            window.clear(); // Clear the window before redrawing

            // Draw the current room scene sprite (sprite in sequence from the inventory)
            Sprite currentSprite = imgInv->get_Next()->get_Sprite();
            window.draw(currentSprite);

            // Draw the narration texts on the screen
            for (const auto& text : narrationTexts)
                window.draw(text);

            window.draw(prompt); // Draw the prompt text
            window.draw(promptLine); // Draw the prompt line
            window.draw(inputDisplay); // Draw the player's input
            window.draw(errorHandler); // Draw any error messages if applicable

            window.display(); // Display the updated window content
        }
    }

    void Entrance()
    {
        if ((!keyUsed && !saltUsed) || (!keyUsed && saltUsed))
        {
            Player1->set_Sanity(-20);
        }

        vector<Text> narrationTexts;
        Text line;
        line.setFont(font2);
        line.setCharacterSize(35);
        line.setFillColor(Color::White);

        int yOffset = 0;
        while (!fNarrator->isEmpty())
        {
            line.setString(fNarrator->peekThenPop());
            line.setPosition(0, 50 + yOffset);
            narrationTexts.push_back(line);
            yOffset += 70;
        }

        Clock clock;
        int linesToShow = 0;

        while (window.isOpen())
        {
            fNarrator->Entrance(keyUsed, saltUsed);
            UpdateNarrationTexts(narrationTexts, fNarrator, line);
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            if (keyUsed && !saltUsed)
            {
                if (Keyboard::isKeyPressed(Keyboard::L))
                {
                    Player1->set_Sanity(-999);
                    this->JumpScareScreen();
                }
            }
            else if (keyUsed && saltUsed)
            {
                if (Keyboard::isKeyPressed(Keyboard::W))
                {
                    this->WinningScreen();
                }
            }
            else
            {
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    return;
                }
            }

            window.clear();

            Sprite currentSprite = imgInv->get_Next()->get_Next()->get_Next()->get_Next()->get_Next()->get_Next()->get_Next()->get_Sprite();
            window.draw(currentSprite);

            for (const auto& text : narrationTexts)
                window.draw(text);

            window.display();
        }
    }

    // Setting up the text prompt for user
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
        prompt.setString("Enter your action " + Player1->get_Name() + " : ");
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

    // TBA
    void MysteriousRoom()
    {

    }

    // Other screens
    void ClueScreen()
    {
        fNarrator->Clue1();

        vector<Text> MenuTexts;
        Text line;
        line.setFont(font2);
        line.setCharacterSize(40);
        line.setFillColor(Color::White);

        int yOffset = 0;

        while (!fNarrator->isEmpty())
        {
            line.setString(fNarrator->peekThenPop());
            line.setPosition(0, 0 + yOffset);
            MenuTexts.push_back(line);
            yOffset += 50;
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
            
            if (clock.getElapsedTime().asSeconds() >= 5.0f)
            {
                jumpScare.stop();
                introMusic.setLoop(true);
                introMusic.play();

                if (Player1->get_Sanity() == 0)
                {
                    this->GameOverScreen();
                }
                else
                {
                    return;
                }
                
            }

            window.clear();
            Sprite currentSprite = imgInv->get_Next()->get_Next()->get_Next()->get_Next()->get_Next()->get_Sprite();
            window.draw(currentSprite);
            window.display();
        }
    }

    void HelpScreen()
    {
        fNarrator->HelpScreen();
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

    void InventoryScreen()
    {

        vector<Text> MenuTexts;
        Text line;
        line.setFont(font2);
        line.setCharacterSize(30);
        line.setFillColor(Color::White);

        string playerInput = "";
        Text inputDisplay, promptLine, prompt, errorHandler;
        SetupTextElements(inputDisplay, promptLine, prompt, errorHandler);

        // Main render loop
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                fNarrator->SeeInventory();
                fNarrator->push("Press \"Esc\" key to go back..........");

                int yOffset = 0;

                while (!fNarrator->isEmpty())
                {
                    line.setString(fNarrator->peekThenPop());
                    line.setPosition(0, 0 + yOffset);
                    MenuTexts.push_back(line);
                    yOffset += 40;
                }

                if (event.type == Event::Closed)
                    window.close();
                HandleTextInput(event, playerInput);

                if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::P))
                    this->PauseScreen();

                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    return;
                }
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    cout << "Player entered: " << playerInput << endl;

                    if (playerInput == "use potion" || playerInput == "USE POTION")
                    {
                        if (Player1->ReplenishSanity())
                        {
                            errorHandler.setString("Increase sanity by 50! Capped at 100");
                            playerInput = "";
                            MenuTexts.clear();
                        }
                        else
                        {
                            errorHandler.setString("Out of Sanity Potion!");
                            playerInput = "";
                        }
                        
                    }
                    else if (playerInput == "USE SALT" || playerInput == "use salt")
                    {
                        if (Player1->UseSalt())
                        {
                            saltUsed = true;
                            errorHandler.setString("You felt nothing");
                            playerInput = "";
                            MenuTexts.clear();
                        }
                        else
                        {
                            errorHandler.setString("Out of Purified Salt!");
                            playerInput = "";
                        }
                    }
                    else if (playerInput == "READ PAPER" || playerInput == "read paper")
                    {
                        this->ClueScreen();
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
            for (const auto& text : MenuTexts)
                window.draw(text);

            window.draw(prompt);
            window.draw(promptLine);
            window.draw(inputDisplay);
            window.draw(errorHandler);
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
        GameOver.setLoop(true);
        GameOver.play();
        
        vector<Text> gameTexts;
        Text line;
        line.setFont(font);
        line.setCharacterSize(45);
        line.setFillColor(Color::Red);

        fNarrator->GameOver();

        int yOffset = 0;
        while (!fNarrator->isEmpty())
        {
            line.setString(fNarrator->peekThenPop());
            line.setPosition(0, 50 + yOffset);
            gameTexts.push_back(line);
            yOffset += 70;
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

            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                GameOver.stop();
                this->MainScreen();
            }

            if (clock.getElapsedTime().asSeconds() >= 1.5f && linesToShow < gameTexts.size())
            {
                linesToShow++;
                clock.restart();
            }

            window.clear();

            Sprite currentSprite = imgInv->get_Next()->get_Next()->get_Next()->get_Next()->get_Next()->get_Next()->get_Sprite();
            window.draw(currentSprite);

            for (int i = 0; i < linesToShow; ++i)
                window.draw(gameTexts[i]);

            window.display();
        }
    }

    void WinningScreen()
    {
        GameOver.setLoop(true);
        GameOver.play();

        vector<Text> gameTexts;
        Text line;
        line.setFont(font);
        line.setCharacterSize(60);
        line.setFillColor(Color::Red);

        fNarrator->Winning();

        int yOffset = 0;
        while (!fNarrator->isEmpty())
        {
            line.setString(fNarrator->peekThenPop());
            line.setPosition(350, 50 + yOffset);
            gameTexts.push_back(line);
            yOffset += 70;
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

            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                GameOver.stop();
                this->MainScreen();
            }

            if (clock.getElapsedTime().asSeconds() >= 1.5f && linesToShow < gameTexts.size())
            {
                linesToShow++;
                clock.restart();
            }

            window.clear();

            Sprite currentSprite = imgInv->get_Next()->get_Next()->get_Next()->get_Next()->get_Next()->get_Next()->get_Next()->get_Sprite();
            window.draw(currentSprite);

            for (int i = 0; i < linesToShow; ++i)
                window.draw(gameTexts[i]);

            window.display();
        }
    }

};
