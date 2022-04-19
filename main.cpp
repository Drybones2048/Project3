#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include "Header.h"
#include "Random.h"
#include "TextureManager.h"
using namespace sf;
using namespace std; 

void checkNeighbors(vector<vector<Tile*>>& tileList, Board& test); //prototype for check neighbors function
bool checkForWin(vector<vector<Tile*>>& tileList, Board& test); //prototype for a function checking to see if the user won the game 
void numberTiles(vector<vector<Tile*>>& tileList, Board& test); //protptype for function that updates the number on a tile depending on where the mines are 
void revealTile(Tile* tile); //prototype for function that reveals groups of tiles when an empty tile has been clicked on 

int main() {

	Board test; //creates a test board
    vector<vector<Tile*>> tileList; //contains pointers for every tile on the grid
    bool onlyOnce = true; //used to set up the board only one time
    bool debugButtonPressed = false; //boolean used to determine if the debug button has been shown and therefore all the mines should show where they are
    bool gameWon = false; //boolean for if the game has been won
    bool gameLost = false; //boolean for if tha game has been lost
    bool negativeCounter = false; 

    string digitString = ""; //empty string to use for substring to get mine count 
    digitString.append(to_string(test.minesCount)); //appends mine count to the string to use substring
    int tensPlaceInt;
    int onesPlaceInt;
    int signPlaceInt = 0; 

    if (test.minesCount > 9) {
        tensPlaceInt = stoi(digitString.substr(0, 1));
        onesPlaceInt = stoi(digitString.substr(1, 2));
    }
    else {
        tensPlaceInt = 1;
        onesPlaceInt = stoi(digitString.substr(0, 1));
    }


    map<int, Texture> digitTextures;
    digitTextures[0].loadFromFile("images/digits.png", sf::IntRect(0, 0, 21, 32));
    digitTextures[1].loadFromFile("images/digits.png", sf::IntRect(21, 0, 21, 32));
    digitTextures[2].loadFromFile("images/digits.png", sf::IntRect(21 * 2, 0, 21, 32));
    digitTextures[3].loadFromFile("images/digits.png", sf::IntRect(21 * 3, 0, 21, 32));
    digitTextures[4].loadFromFile("images/digits.png", sf::IntRect(21 * 4, 0, 21, 32));
    digitTextures[5].loadFromFile("images/digits.png", sf::IntRect(21 * 5, 0, 21, 32));
    digitTextures[6].loadFromFile("images/digits.png", sf::IntRect(21 * 6, 0, 21, 32));
    digitTextures[7].loadFromFile("images/digits.png", sf::IntRect(21 * 7, 0, 21, 32));
    digitTextures[8].loadFromFile("images/digits.png", sf::IntRect(21 * 8, 0, 21, 32));
    digitTextures[9].loadFromFile("images/digits.png", sf::IntRect(21 * 9, 0, 21, 32));
    digitTextures[-1].loadFromFile("images/digits.png", sf::IntRect(21 * 10, 0, 21, 32));
    
        
    unordered_map<string, Texture> textures; //creates an unordered map for all of the textures used in the game 
    textures["emptyTile"].loadFromFile("images/tile_revealed.png");
    textures["hiddenTile"].loadFromFile("images/tile_hidden.png");
    textures["mine"].loadFromFile("images/mine.png");
    textures["number"];
    textures["mineDebug"].loadFromFile("images/debug.png");
    textures["test1"].loadFromFile("images/test_1.png");
    textures["test2"].loadFromFile("images/test_2.png");
    textures["test3"].loadFromFile("images/test_3.png");
    textures["happyFace"].loadFromFile("images/face_happy.png");
    textures["flag"].loadFromFile("images/flag.png");
    textures["winningFace"].loadFromFile("images/face_win.png");
    textures["losingFace"].loadFromFile("images/face_lose.png");

   


    Sprite debugButton; //creates the debug mine button 

    Sprite test1Button;  //creates the test1 button

    Sprite test2Button; //creates a sprite to represent the test2 button 

    Sprite test3Button; //creates a sprite for the test3 button 

    Sprite happyFace; //creates a sprite for the face in the middle

    Sprite onesPlace; //ones place in score counter 
    
    Sprite tensPlace; //tens place in score counter

    Sprite signPlace; //sign place in the sign counter 

    Color color(255, 255, 255); //color white for the background of the window

    sf::RenderWindow window(sf::VideoMode(test.windowWidth, test.windowHeight), "Minesweeper"); //creates the window 

    

    while (window.isOpen()) //while loop that persists for the duration of the window being open
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(color); //makes the background of the window white 
        

        if (onlyOnce) { //sets up the board one time
            test.setUp(window, tileList);

            test.placeMines(tileList); //places the mines on the board one time

            checkNeighbors(tileList, test); //sets the tiles to recognize their neighbors 

            numberTiles(tileList, test); //puts the numbers on tiles based on mine locations 

            onlyOnce = false; //do not repeat this if-statement
        }
        else { //sets up the board after the first initial set up run
            for (unsigned int i = 0; i < test.boardWidth; i++) { //goes through the entire width of each row
                for (unsigned int j = 0; j < test.boardHeight; j++) { //goes through most of the height of the board except 100 at the bottom for the main buttons

                    
                    if (tileList[i][j]->isRevealed) { //if this tile has been clicked on, give it the empty tile texture 
                       
                        if (tileList[i][j]->hasMine) { //if the revealed tile also has a mine on it, display that 
                            tileList[i][j]->tileSprite.setTexture(textures["emptyTile"]); //first it draws the empty tile to screen
                            window.draw(tileList[i][j]->tileSprite); //displays the empty tile on screen
                            
                            tileList[i][j]->tileSprite.setTexture(textures["mine"]); //sets the texture for the mine 
                            window.draw(tileList[i][j]->tileSprite); //displays the mine on top of the empty tile
                        }
                        else if (tileList[i][j]->numberOnTile != 0) {
                            tileList[i][j]->tileSprite.setTexture(textures["emptyTile"]); //first it draws the empty tile to screen
                            window.draw(tileList[i][j]->tileSprite); //displays the empty tile on screen

                            if (tileList[i][j]->numberOnTile == 1) { //sets the texture to be from the images given
                                textures["number"].loadFromFile("images/number_1.png");
                            }
                            else if (tileList[i][j]->numberOnTile == 2) {
                                textures["number"].loadFromFile("images/number_2.png");
                            }
                            else if (tileList[i][j]->numberOnTile == 3) {
                                textures["number"].loadFromFile("images/number_3.png");
                            }
                            else if (tileList[i][j]->numberOnTile == 4) {
                                textures["number"].loadFromFile("images/number_4.png");
                            }
                            else if (tileList[i][j]->numberOnTile == 5) {
                                textures["number"].loadFromFile("images/number_5.png");
                            }
                            else if (tileList[i][j]->numberOnTile == 6) {
                                textures["number"].loadFromFile("images/number_6.png");
                            }
                            else if (tileList[i][j]->numberOnTile == 7) {
                                textures["number"].loadFromFile("images/number_7.png");
                            }
                            else if (tileList[i][j]->numberOnTile == 8) {
                                textures["number"].loadFromFile("images/number_8.png");
                            }

                            tileList[i][j]->tileSprite.setTexture(textures["number"]); //sets the texture for the mine 
                            window.draw(tileList[i][j]->tileSprite); //displays the mine on top of the empty tile
                        }
                        else //if the tile has not been revealed, keep it hidden
                        {
                            
                          tileList[i][j]->tileSprite.setTexture(textures["emptyTile"]);
                            
                        }
                        
                    }
                    else if (!tileList[i][j]->isRevealed) { //if this tile has not been clicked on, give it a hidden texture
                        
                        if (debugButtonPressed && tileList[i][j]->hasMine) { //if the debug button has been pressed once and a tile has a mine on it, draw the mine on the unrevealed tile
                            tileList[i][j]->tileSprite.setTexture(textures["hiddenTile"]);
                            window.draw(tileList[i][j]->tileSprite);
                            tileList[i][j]->tileSprite.setTexture(textures["mine"]);
                        }
                        else if (gameLost && tileList[i][j]->hasMine) { //if the user has lost the game, display the tiles that have mines on them with mines on them
                            tileList[i][j]->tileSprite.setTexture(textures["emptyTile"]);
                            window.draw(tileList[i][j]->tileSprite);
                            tileList[i][j]->tileSprite.setTexture(textures["mine"]);
                        }
                        else if (tileList[i][j]->isFlagged) { //if the mine has been flagged, keep it flagged 
                          
                            tileList[i][j]->tileSprite.setTexture(textures["hiddenTile"]);
                            window.draw(tileList[i][j]->tileSprite);

                            tileList[i][j]->tileSprite.setTexture(textures["flag"]);
                            
                            
                            
                            
                        }
                        else { //if the debug button has not been pressed, keep it as a hidden tile
                            tileList[i][j]->tileSprite.setTexture(textures["hiddenTile"]);
                        }
                        
                    }
                    
                    Sprite hiddenTile = tileList[i][j]->tileSprite; //creates a sprite that represents the unrevealed tile above an empty tile

                    window.draw(hiddenTile); //draws the unrevealed tile to the screen

                }
                
                

            }

            
            debugButton.setTexture(textures["mineDebug"]); //sets the texture for the button 
            debugButton.setPosition(test.boardWidth * 21.7 - 48, test.boardHeight * 32); //places it in the right location

            window.draw(debugButton); 

            test1Button.setTexture(textures["test1"]); //gives the button the test1 texture 
            test1Button.setPosition(test.boardWidth * 21.7 + 16, test.boardHeight * 32); //positions the button 

            window.draw(test1Button);

            test2Button.setTexture(textures["test2"]); //gives the button the test2 texture
            test2Button.setPosition(test.boardWidth * 21.7 + 80, test.boardHeight * 32); //positions the button

            window.draw(test2Button);

            test3Button.setTexture(textures["test3"]); //gives the button the test3 texture 
            test3Button.setPosition(test.boardWidth * 21.7 + 144, test.boardHeight * 32); //posotions the button 

            window.draw(test3Button);

            if (checkForWin(tileList, test)) { //if the user won the game, change the face 
                happyFace.setTexture(textures["winningFace"]); //gives the button the test3 texture 
                happyFace.setPosition(test.boardWidth * 21.7 - 176, test.boardHeight * 32); //posotions the button 

                window.draw(happyFace);
            }
            else if (gameLost) { //if the user has lost the game, change the face to a dead face
                happyFace.setTexture(textures["losingFace"]); //gives the button the test3 texture 
                happyFace.setPosition(test.boardWidth * 21.7 - 176, test.boardHeight * 32); //posotions the button 

                window.draw(happyFace);
            }
            else { //otherwise, keep the face the same
                happyFace.setTexture(textures["happyFace"]); //gives the button the test3 texture 
                happyFace.setPosition(test.boardWidth * 21.7 - 176, test.boardHeight * 32); //posotions the button 

                window.draw(happyFace);
            }

             

            onesPlace.setTexture(digitTextures[onesPlaceInt]); //creates the ones place in the score box 
            onesPlace.setPosition(test.boardWidth * 21.7 - 488, test.boardHeight * 32); 

            window.draw(onesPlace); 

            tensPlace.setTexture(digitTextures[tensPlaceInt]);
            tensPlace.setPosition(test.boardWidth * 21.7 - 509, test.boardHeight * 32);

            window.draw(tensPlace);

            signPlace.setTexture(digitTextures[signPlaceInt]);
            signPlace.setPosition(test.boardWidth * 21.7 - 530, test.boardHeight * 32);

            window.draw(signPlace);
        }

        
        if (Mouse::isButtonPressed(Mouse::Left)) { //if the player clicks the left mouse button to reveal a tile, go into this if
            int mouseX = Mouse::getPosition(window).x; //represent the x of the mouse's coordinates
            int mouseY = Mouse::getPosition(window).y; //represents the y of the mouse's coordinates

            int neighborMines; //counter that will be used to keep track of how many mines are around the tile

            

            for (unsigned int i = 0; i < test.boardWidth; i++) { 
                for (unsigned int j = 0; j < test.boardHeight; j++) {
                    Tile* currentTile = tileList[i][j]; //represents the current tile under investigation

                    if ((mouseX >= currentTile->tileSprite.getPosition().x && mouseX <= (currentTile->tileSprite.getPosition().x + currentTile->tileSprite.getTextureRect().width))) { //if the mouse is clicked within the dimensions of a box, go into this if 
                        if ((mouseY >= currentTile->tileSprite.getPosition().y && mouseY <= (currentTile->tileSprite.getPosition().y + currentTile->tileSprite.getTextureRect().height))) { //if the mouse is clicked within the dimensions of a box, go into this if 
                           
                            neighborMines = 0; //sets the amount of mines around the tile to 0 

                            for (int x = 0; x < currentTile->numNeighbors; x++) { //goes through all tile neighbors
                                
                                if (currentTile->neighbors[x] == nullptr) { //if the tile does not have a neighbor in that location, skip the check for mines
                                    continue; 
                                }

                                if (currentTile->neighbors[x]->hasMine) { //if the tile has a mine, increment the counter
                                    neighborMines++;
                                    
                                }
                                
                                
                                
                            }


                            if(currentTile->hasMine){ //if a mine is found, set the mine tecture
                                currentTile->tileSprite.setTexture(textures["mine"]);

                                gameLost = true; //when the user clicked on the mine, they lost the game 

                                happyFace.setTexture(textures["losingFace"]);

                                for (unsigned int i = 0; i < test.boardWidth; i++) {
                                    for (unsigned int j = 0; j < test.boardHeight; j++) {
                                        Tile* currentTile = tileList[i][j]; //represents the current tile under investigation

                                        if (currentTile->hasMine) {
                                            tileList[i][j]->tileSprite.setTexture(textures["emptyTile"]); //sets the texture for an empty tile for the mine to be drawn on
                                            window.draw(tileList[i][j]->tileSprite); //displays the mine on top of the empty tile
                                            tileList[i][j]->tileSprite.setTexture(textures["mine"]); //sets the texture for the mine 
                                            window.draw(tileList[i][j]->tileSprite); //displays the mine on top of the empty tile
                                        }
                                    }
                                }

                            }

                            else if (currentTile->numberOnTile != 0) { //if the number on the tile is not 0, then there is a number that should appear 
                                string appendString = "images/number_"; //used to append together the right address for the number
                                appendString.append(to_string(currentTile->numberOnTile));
                                appendString.append(".png");

                                textures["number"].loadFromFile(appendString); //loads the texture based off the combined string 

                                currentTile->tileSprite.setTexture(textures["number"]); //sets the texture for the sprite
                            }

                            else { //if a tile is clicked that is not a mine or it is not a number, then it is blank and should remove all blank tiles it is touching
                  
                                currentTile->tileSprite.setTexture(textures["emptyTile"]); //sets the texture as revealed 

                                revealTile(currentTile); //runs the method to remove groups of tile
                               
                            }
                            
                           
                            currentTile->isRevealed = true; //updates the boolean in the tile class 

                            window.draw(currentTile->tileSprite); //draws the change to the window
                        }

                    }
                }
                
            }

            if ((mouseX >= debugButton.getPosition().x && mouseX <= (debugButton.getPosition().x + debugButton.getTextureRect().width))) { //if the mouse is clicked within the dimensions of a box, go into this if 
                if ((mouseY >= debugButton.getPosition().y && mouseY <= (debugButton.getPosition().y + debugButton.getTextureRect().height))) { //if the mouse is clicked within the dimensions of a box, go into this if
                    
                    debugButtonPressed = true; 

                    for (unsigned int i = 0; i < test.boardWidth; i++) {
                        for (unsigned int j = 0; j < test.boardHeight; j++) {
                            Tile* currentTile = tileList[i][j]; //represents the current tile under investigation
                        
                            if (currentTile->hasMine) {
                                tileList[i][j]->tileSprite.setTexture(textures["mine"]); //sets the texture for the mine 
                                window.draw(tileList[i][j]->tileSprite); //displays the mine on top of the empty tile
                            }
                        }
                    }

                }
            }
            if ((mouseX >= test1Button.getPosition().x && mouseX <= (test1Button.getPosition().x + test1Button.getTextureRect().width))) { //if test button 1 is clicked 
                if ((mouseY >= test1Button.getPosition().y && mouseY <= (test1Button.getPosition().y + test1Button.getTextureRect().height))) { //if the mouse is clicked within the dimensions of a box, go into this if
                    ifstream testboard1; //creates an input file to read from 
                    testboard1.open("boards/testboard1.brd"); //opens the board file 

                    string fileTileLine = ""; //creates an empty string to represent a line of the board 
                    
                    test.minesCount = 0; 

                    for (unsigned int i = 0; i < test.boardHeight; i++) {

                        getline(testboard1, fileTileLine); //gets a line of the board 

                        for (unsigned int j = 0; j < test.boardWidth; j++) {
                            Tile* currentTile = tileList[j][i]; //represents the current tile under investigation

                            if (fileTileLine.substr(j, 1) == "1") {
                                currentTile->hasMine = true; //sets the tile in this location to be a mine 
                                test.minesCount++;
                            }
                            else {
                                currentTile->hasMine = false; //otherwise, the location is not a mine
                            }

                        }
                    }

                    
                    tensPlaceInt = 0;
                    onesPlaceInt = 1;
                    

                    numberTiles(tileList, test);

                }
            }
            if ((mouseX >= test2Button.getPosition().x && mouseX <= (test2Button.getPosition().x + test2Button.getTextureRect().width))) { //if test button 2 is clicked  
                if ((mouseY >= test2Button.getPosition().y && mouseY <= (test2Button.getPosition().y + test2Button.getTextureRect().height))) { //if the mouse is clicked within the dimensions of a box, go into this if
                    ifstream testboard2; //creates an input file to read from 
                    testboard2.open("boards/testboard2.brd"); //opens the board file 

                    string fileTileLine = ""; //creates an empty string to represent a line of the board 

                    test.minesCount = 0; 

                    for (unsigned int i = 0; i < test.boardHeight; i++) {

                        getline(testboard2, fileTileLine); //gets a line of the board 

                        for (unsigned int j = 0; j < test.boardWidth; j++) {
                            Tile* currentTile = tileList[j][i]; //represents the current tile under investigation

                            if (fileTileLine.substr(j, 1) == "1") {
                                currentTile->hasMine = true; //sets the tile in this location to be a mine 
                                test.minesCount++;
                            }
                            else {
                                currentTile->hasMine = false; //otherwise, the location is not a mine
                            }

                        }
                    }

                    
                    signPlaceInt = 1; 
                    tensPlaceInt = 0;
                    onesPlaceInt = 2; 

                    numberTiles(tileList, test);
                }
            }
            if ((mouseX >= test3Button.getPosition().x && mouseX <= (test3Button.getPosition().x + test3Button.getTextureRect().width))) { //if the test button 3 is clicked 
                if ((mouseY >= test3Button.getPosition().y && mouseY <= (test3Button.getPosition().y + test3Button.getTextureRect().height))) { 
                    ifstream testboard3; //creates an input file to read from 
                    testboard3.open("boards/testboard3.brd"); //opens the board file 

                    string fileTileLine = ""; //creates an empty string to represent a line of the board 

                    test.minesCount = 0;

                    for (unsigned int i = 0; i < test.boardHeight; i++) {

                        getline(testboard3, fileTileLine); //gets a line of the board 

                        for (unsigned int j = 0; j < test.boardWidth; j++) {
                            Tile* currentTile = tileList[j][i]; //represents the current tile under investigation

                            if (fileTileLine.substr(j, 1) == "1") {
                                currentTile->hasMine = true; //sets the tile in this location to be a mine 
                                test.minesCount++;
                            }
                            else {
                                currentTile->hasMine = false; //otherwise, the location is not a mine
                            }

                        }
                    }

                     
                    tensPlaceInt = 8; 
                    onesPlaceInt = 3;

                    numberTiles(tileList, test);
                }
            }
            if ((mouseX >= happyFace.getPosition().x && mouseX <= (happyFace.getPosition().x + happyFace.getTextureRect().width))) { //checks to see if the smiley button is clicked, giving the mines new positions and resetting the board 
                if ((mouseY >= happyFace.getPosition().y && mouseY <= (happyFace.getPosition().y + happyFace.getTextureRect().height))) {
                    tileList.clear(); //clears the list of tiles 
                    
                    gameLost = false; //says the game has not been lost

                    test.setUp(window, tileList); //sets up a new board

                    test.placeMines(tileList); //places the mines on the board one time

                    checkNeighbors(tileList, test); //updates the vector of neighbors

                    if (test.minesCount > 9) {
                        tensPlaceInt = stoi(digitString.substr(0, 1));
                        onesPlaceInt = stoi(digitString.substr(1, 2));
                    }
                    else {
                        tensPlaceInt = 0;
                        onesPlaceInt = test.minesCount;
                    }

                    signPlaceInt = 0; 

                    numberTiles(tileList, test);
                }
            }

        }
       
        if (event.type == sf::Event::MouseButtonPressed) { //if the type of event is the player pressing a mouse button, go into this

            if (event.mouseButton.button == sf::Mouse::Right) { //if the button the person clicked is the right mouse button, go into this

                int mouseX = Mouse::getPosition(window).x; //represent the x of the mouse's coordinates
                int mouseY = Mouse::getPosition(window).y; //represents the y of the mouse's coordinates

                for (unsigned int i = 0; i < test.boardWidth; i++) {
                    for (unsigned int j = 0; j < test.boardHeight; j++) {
                        Tile* currentTile = tileList[i][j]; //represents the current tile under investigation

                        if ((mouseX >= currentTile->tileSprite.getPosition().x && mouseX <= (currentTile->tileSprite.getPosition().x + currentTile->tileSprite.getTextureRect().width))) { //if the mouse is clicked within the dimensions of a box, go into this if 
                            if ((mouseY >= currentTile->tileSprite.getPosition().y && mouseY <= (currentTile->tileSprite.getPosition().y + currentTile->tileSprite.getTextureRect().height))) { //if the mouse is clicked within the dimensions of a box, go into this if 

                                if (tileList[i][j]->isFlagged) { //if the tile is already flagged, unflag it and incriment the counter 
                                    tileList[i][j]->isFlagged = false;

                                    tileList[i][j]->tileSprite.setTexture(textures["hiddenTile"]); //texture will be hidden tile after the flag is removed

                                    if (negativeCounter) { //if the counter is negative
                                        if (onesPlaceInt == 0) { //count down code 
                                            tensPlaceInt--; 
                                            onesPlaceInt = 9;
                                        }
                                        else {
                                            onesPlaceInt--; 
                                        }
                                    }
                                    else { //if the counter is still positive
                                        if (onesPlaceInt == 9) { //count up code 
                                            tensPlaceInt++;
                                            onesPlaceInt = 0;
                                        }
                                        else {
                                            onesPlaceInt++;
                                        }
                                    }


                                    

                                }
                                else { //if the tile is not already flagged, add a flag and decriment the counter 
                                    Sprite flag; //create a sprite for the flag 
                                    flag.setTexture(textures["flag"]); //sets the flag texture on the space 
                                    flag.setPosition(currentTile->tileSprite.getPosition()); //gets the position of the tile as the position of the flag

                                    currentTile->isFlagged = true; //states that the current tile has been flagged 

                                    if (negativeCounter) { //if the counter is negative, use count up code because it is negative 
                                        if (onesPlaceInt == 9) {
                                            tensPlaceInt++;
                                            onesPlaceInt = 0;
                                        }
                                        else {
                                            onesPlaceInt++;
                                        }
                                    }
                                    else { //if the counter is not negative, decriment the counter 
                                        if (onesPlaceInt == 0) {
                                            if (tensPlaceInt == 0) {
                                                signPlaceInt = -1;
                                                negativeCounter = true;
                                            }
                                            else {
                                                tensPlaceInt--;
                                                onesPlaceInt = 9;
                                            }
                                        }
                                        else {
                                            onesPlaceInt--;
                                        }
                                    }

                                    


                                    window.draw(flag);
                                }


                            }
                        }
                    }
                }
            }
            
        }
        
        

        window.display(); //displays the window
    }

	return 0; 
};

void checkNeighbors(vector<vector<Tile*>>& tileList, Board& test) { //fills the neighbors array in every tile to have them know who their neighbors are 
    for (unsigned int i = 0; i < test.boardWidth; i++) {
        for (unsigned int j = 0; j < test.boardHeight; j++) {
            Tile* currentTile = tileList[i][j]; //represents the current tile under investigation

            //uses try catch to see if there is a tile in the area that it is checking and increments based on how many neighbors it has
            try {
                currentTile->neighbors[0] = tileList.at(i - 1).at(j + 1); //checks the tile to its top left

                currentTile->numNeighbors++;
            }
            catch (const out_of_range& e) { //if the vetcor goes out of bounds, it is caught by this exception
                currentTile->neighbors[0] = nullptr;
            }

            try {
                currentTile->neighbors[1] = tileList.at(i).at(j + 1); //checks the top middle tile

                currentTile->numNeighbors++;
            }
            catch (const out_of_range& e) {
                currentTile->neighbors[1] = nullptr;
            }

            try {
                currentTile->neighbors[2] = tileList.at(i + 1).at(j + 1); //checks the top right tile 

                currentTile->numNeighbors++;
            }
            catch (const out_of_range& e) {
                currentTile->neighbors[2] = nullptr;
            }

            try {
                currentTile->neighbors[3] = tileList.at(i - 1).at(j); //checks the left tile

                currentTile->numNeighbors++;
            }
            catch (const out_of_range& e) {
                currentTile->neighbors[3] = nullptr;
            }

            try {
                currentTile->neighbors[4] = tileList.at(i + 1).at(j); //checks the right tile

                currentTile->numNeighbors++;
            }
            catch (const out_of_range& e) {
                currentTile->neighbors[4] = nullptr;
            }

            try {
                currentTile->neighbors[5] = tileList.at(i - 1).at(j - 1); //checks the bottom left tile

                currentTile->numNeighbors++;
            }
            catch (const out_of_range& e) {
                currentTile->neighbors[5] = nullptr;
            }

            try {
                currentTile->neighbors[6] = tileList.at(i).at(j - 1); //checks the bottom middle tile

                currentTile->numNeighbors++;
            }
            catch (const out_of_range& e) {
                currentTile->neighbors[6] = nullptr;
            }

            try {
                currentTile->neighbors[7] = tileList.at(i + 1).at(j - 1); //checks the bottom right tile 

                currentTile->numNeighbors++;
            }
            catch (const out_of_range& e) {
                currentTile->neighbors[7] = nullptr;
            }
        }
    }
}

bool checkForWin(vector<vector<Tile*>>& tileList, Board& test) { //method to see if all the mines have been flagged, if they have, the user has won the game
    int counter = 0;

    for (unsigned int i = 0; i < test.boardWidth; i++) {
        for (unsigned int j = 0; j < test.boardHeight; j++) {
            Tile* currentTile = tileList[i][j]; //represents the current tile under investigation

            if (currentTile->hasMine && currentTile->isFlagged) {
                counter++;
            }
            
        }
    }

    if (counter == test.minesCount) {
        return true; 
    }
    else {
        return false; 
    }
}

void numberTiles(vector<vector<Tile*>>& tileList, Board& test) { //numbers every tile based on if there is a mine in one of its neighbors

    for (unsigned int i = 0; i < test.boardWidth; i++) { //go through every tile 
        for (unsigned int j = 0; j < test.boardHeight; j++) {
            Tile* currentTile = tileList[i][j]; //representation of current tile 

            currentTile->numberOnTile = 0; //resets the value on the tile back to 0 if this is not the first time this function has been run

            for (int w = 0; w < currentTile->numNeighbors; w++) { //goes through all of the tile's neighbors
                if (currentTile->neighbors[w] != nullptr && currentTile->neighbors[w]->hasMine) { //if the tile's neighbor exists and there is a mine adjacent to it, incriment the number on the tile
                    currentTile->numberOnTile++; 
                }
            }


        }
    }
}

void revealTile(Tile* tile) { //method to be used to remove groups of tiles at once that are not mines 
    if (tile->isRevealed || tile->hasMine ) { //if the current tile has already been revealed or it has a mine on it, do not continue 
        return;

    }
    
    else { //if the tile does not have a mine and has not been revealed, reveal it
        tile->isRevealed = true;
    }

    for (int i = 0; i < 8; i++) { //goes through all of a tile's neighbors
        if (tile->neighbors[i] != nullptr) { //if there is a neighbor for a tile, look into it
            if (tile->neighbors[i]->numberOnTile == 0) { //if there is a tile that has no number on it, run recursion
                revealTile(tile->neighbors[i]);
            }
            else if(tile->neighbors[i]->numberOnTile > 0 && !tile->neighbors[i]->hasMine){ //if the tile does have a number on it, reveal it but stop there
              tile->neighbors[i]->isRevealed = true; 
              
           }
        }
    }
}