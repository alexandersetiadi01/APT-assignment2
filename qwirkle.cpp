#include "LinkedList.h"
#include "TileCodes.h"
#include "Player.h"
#include "Tile.h"
#include "TileBag.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define MAX_TILEBAG_SIZE 108
#define MAX_HAND_SIZE 6

#define MAX_SIZE_BOARD 26
#define EMPTY_TILE "|  |"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

using namespace std;

//2D tile vector
vector<vector<Tile>> board(27);

void playGame(std::string TileBagFile, TileBag *tilebag, Player *playerOne, Player *playerTwo, bool enhancement);
//void playTheGame(Board *board, Player *playerOne);
//void cleanupGame(Board *board, Player *playerOne);
void printBoard();
void placeInitialTile(TileBag *tilebag, bool enhancement);
void placeTile(TileBag *tilebag);
void refreshHand(TileBag *tilebag, TileBag *hand);
bool validLocation(Tile *playedTile, std::string boardLocation);
void help();
bool readOneTile(std::ifstream &file, Colour *colour, Shape *shape);

std::string player1name;
std::string player2name;
string tileToPlace;
string boardPos;

// Function loads a game
void loadGame()
{
  std::fstream fin;
  std::string filename;
  std::cout << "Enter the filename you want to load " << std::endl;
  std::cout << ">"; cin >> filename;
  fin.open(filename, std::ios::in);
  if (fin.fail())
    std::cout << "Could not open file \n";
  else
  {
    std::string value;
    getline(fin, value);
    std::cout << "Value read from file " << value;
  }
  fin.close();
}

// Function starts new game
void newGame()
{
  bool isNameOneSet = false;
  bool isNameTwoSet = false;
  
  std::cout << "Enter player 1 name (uppercase only)" << std::endl;
  while (isNameOneSet == false)
  {
    bool isInvalid = true;
    std::cout << ">"; cin >> player1name;
    std::cout << std::endl;
    for (size_t i = 0; i < player1name.length(); i++)
    {
      if (!isupper(static_cast<unsigned char>(player1name[i])))
      {
        isInvalid = false;
      }
    }
    if (isInvalid == false)
    {
      std::cout << "isInvalid -- Please enter your name in UPPERCASE" << std::endl;
    }
    isNameOneSet = isInvalid;
  }

  std::cout << "Enter player 2 name (uppercase only)" << std::endl;
  while (isNameTwoSet == false)
  {
    bool isInvalid = true;
    std::cout << ">"; cin >> player2name;
    std::cout << std::endl;
    for (size_t i = 0; i < player2name.length(); i++)
    {
      if (!isupper(static_cast<unsigned char>(player2name[i])))
      {
        isInvalid = false;
      }
    }
    if (isInvalid == false)
    {
      std::cout << "isInvalid -- Please enter your name in UPPERCASE" << std::endl;
    }
    isNameTwoSet = isInvalid;
  }
}

int selectMenuOption(bool enhancement)
{
  int option;
  if(enhancement == true){
    std::cout << "Menu" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load game" << std::endl;
    std::cout << "3. Credits (Show student information)" << std::endl;
    std::cout << "4. Help" << endl;
    std::cout << "5. Back to version menu" << std::endl;
    std::cout << ">"; cin >> option;
    fflush(stdin);
  
  }
  if(enhancement == false){
    std::cout << "Menu" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load game" << std::endl;
    std::cout << "3. Credits (Show student information)" << std::endl;
    std::cout << "4. Back to version menu" << std::endl;
    std::cout << ">"; cin >> option;
    fflush(stdin);
  }
  return option;
}
void showCredits()
{
  std::cout << "-----------------------------------" << std::endl;
  std::cout << "Name: Jamaine George" << std::endl;
  std::cout << "Student ID: s3660962" << std::endl;
  std::cout << "Email: s3660962@student.rmit.edu.au" << std::endl;
  std::cout << "-----------------------------------" << std::endl;

  std::cout << "Name: William Bossen" << std::endl;
  std::cout << "Student ID: s3658961" << std::endl;
  std::cout << "Email: s3658961@student.rmit.edu.au" << std::endl;
  std::cout << "-----------------------------------" << std::endl;

  std::cout << "Name: Ellery Alexander Setiadi" << std::endl;
  std::cout << "Student ID: s3886701" << std::endl;
  std::cout << "Email: s3886701@student.rmit.edu.au" << std::endl;
  std::cout << "-----------------------------------" << std::endl;

  std::cout << "Name: Arjun Sharma" << std::endl;
  std::cout << "Student ID: s3604973" << std::endl;
  std::cout << "Email: s3604973@student.rmit.edu.au" << std::endl;
  std::cout << "-----------------------------------" << std::endl;
}

//storing placeholder value
void storePlaceholder()
{
  for (auto &row : board)
  {
    row.resize(26);
    for (auto &val : row)
    {
      val.shape = 80;
      val.colour = 'X';
    }
  }
}
//to help player know what commands they can execute
void help()
{
  cout << "1. how to choose tile" << endl;
  cout << "2. how to place tile" << endl;
  cout << "3. how to quit in the middle of the game" << endl;
  cout << "4. back" << endl;
  bool needHelp = true;
  int userInput;
  cout << "> "; cin >> userInput;
  
  while(needHelp == true){
    if(userInput == 1){
      cout << "to choose the tile that you want to put by typing one of the tile's name in your hand" << endl;
      cout << "when 'which tile would you place?' show up" << endl;
      cout << "type <tile's color><tile's number>" << endl;
      cout << "example: " << endl;
      cout << "your hand is P4 P5 Q5 R6 B4 X7 \n which tile would you place? "<< endl; 
      cout << "> R6 (color: red, number: 6)" << endl;
      cout << "note: color must be UPPERCASE" << endl << endl;
      break;
    }
      
    if(userInput == 2){
      cout << "to choose where the tile will be placed, you have to type the location on the board" << endl;
      cout << "when 'where would you like to place this tile?' show up" << endl;
      cout << "type <row><column>" << endl;
      cout << "example: \nyour hand is P4 P5 Q5 R6 B4 X7 \nwhich tile would you place? "<< endl; 
      cout << " |1|2|3|4|5|" << endl;
      cout << "A| | | | | |" << endl;
      cout << "B| | | | | |" << endl;
      cout << "C| | | | | |" << endl;
      cout << "where would you like to place the tile" << endl;
      cout << "> A1 (row: A, column: 1)" << endl;
      cout << "note: row must be UPPERCASE" << endl << endl;
      break;
    }
      
    if(userInput == 3){
      cout << "type 'quit' or 'QUIT' to back to the main menu when in game" << endl << endl;
      break;
    }
      
    if(userInput == 4){
      cout << endl << endl;
      needHelp = false;
      break;
    }
     
  }

  
  
}
void printBoard()
{
  for (unsigned int i = 0; i < board.size(); i++)
  {

    //Numbered top index of board
    if (i == 0)
    {
      cout << "    0"
           << "   1"
           << "   2"
           << "   3"
           << "   4"
           << "   5"
           << "   6"
           << "   7"
           << "   8"
           << "   9"
           << "  10"
           << "  11"
           << "  12"
           << "  13"
           << "  14"
           << "  15"
           << "  16"
           << "  17"
           << "  18"
           << "  19"
           << "  20"
           << "  21"
           << "  22"
           << "  23"
           << "  24"
           << "  25\n";
      cout << "   ---------------------------------------------------"
           << "----------------------------------------------------";
    }

    //Lettered side index of board
    if (i == 1)
    {
      cout << "A ";
    }
    if (i == 2)
    {
      cout << "B ";
    }
    if (i == 3)
    {
      cout << "C ";
    }
    if (i == 4)
    {
      cout << "D ";
    }
    if (i == 5)
    {
      cout << "E ";
    }
    if (i == 6)
    {
      cout << "F ";
    }
    if (i == 7)
    {
      cout << "G ";
    }
    if (i == 8)
    {
      cout << "H ";
    }
    if (i == 9)
    {
      cout << "I ";
    }
    if (i == 10)
    {
      cout << "J ";
    }
    if (i == 11)
    {
      cout << "K ";
    }
    if (i == 12)
    {
      cout << "L ";
    }
    if (i == 13)
    {
      cout << "M ";
    }
    if (i == 14)
    {
      cout << "N ";
    }
    if (i == 15)
    {
      cout << "O ";
    }
    if (i == 16)
    {
      cout << "P ";
    }
    if (i == 17)
    {
      cout << "Q ";
    }
    if (i == 18)
    {
      cout << "R ";
    }
    if (i == 19)
    {
      cout << "S ";
    }
    if (i == 20)
    {
      cout << "T ";
    }
    if (i == 21)
    {
      cout << "U ";
    }
    if (i == 22)
    {
      cout << "V ";
    }
    if (i == 23)
    {
      cout << "W ";
    }
    if (i == 24)
    {
      cout << "X ";
    }
    if (i == 25)
    {
      cout << "Y ";
    }
    if (i == 26)
    {
      cout << "Z ";
    }

    for (unsigned int j = 0; j < board[i].size(); j++)
    {
      //doesnt print top row of vector where the index is
      if (i == 0)
      {
        //do nothing
      }
      else
      {
        //replace placeholder with empty board space
        if (board[i][j].shape == 80 && board[i][j].colour == 'X')
        {
          cout << "|  |";
        }
        else
        {
          //if board space is not placeholder then print it on the board
          cout << "|" << board[i][j].colour << board[i][j].shape << "|";
        }
      }
    }
    cout << endl;
  }
}

void placeInitialTile(TileBag *tilebag, bool enhancement)
{
  cout << "Which tile would you like to place? (use UPPERCASE only)" << endl;

  bool tileExists = false;
  char placedColour = 'X';

  //input tile
  do
  {
    cout << "> "; cin >> tileToPlace;
    if(enhancement == true){
      if (tileToPlace == "help" || tileToPlace == "HELP"){
        help();
        cout << "Which tile would you like to place? (use UPPERCASE only)" << endl;
      }
      else if(tileToPlace == "QUIT" || tileToPlace == "quit"){
        cout << "are you sure to quit the game now? (y/n)" << endl;
        string validation;
        cout << "> ";cin >> validation;
        
        if(validation == "y" || validation == "Y"){
          cout << "goodbye" << endl << endl;
          exit(0);
        }
        else if(validation == "n" || validation == "N"){
          
          cout << "Which tile would you like to place? (use UPPERCASE only)" << endl;
          continue;
        }
      }
    
    }
    //copy tile string
    std::string temp = "temp string";
    string tile = tileToPlace;
    temp = tileToPlace;

    //take int value of the string for the shape
    size_t i = 0;
    for (; i < tileToPlace.length(); i++)
    {
      if (isdigit(tileToPlace[i]))
        break;
    }

    tileToPlace = tileToPlace.substr(i, tileToPlace.length() - i);

    int placedShape = atoi(tileToPlace.c_str());

    //set colour to string index 0
    placedColour = temp[0];

    //check if tile is in the hand...TODO
    int k = 0;

    while (k < MAX_HAND_SIZE)
    {
      //move from tilebag to player
      Tile *tile = new Tile(*tilebag->get(k));
      //cout << tile->colour << endl;

      if (tile->colour == placedColour && tile->shape == placedShape)
      {
        tileExists = true;
        tilebag->remove(k);
        break;
      }
      else
      {
        tileExists = false;
      }

      ++k;
    }
    if (tileExists == false)
    {
      cout << "you don't have tile " << tile << " in your hand" << endl;
      cout << "Try again" << endl;
    }
    
      
  } while (tileExists == false);
  int placedShape = atoi(tileToPlace.c_str());
  //printHand(tilebag);

  cout << "Where would you like to place this tile? (use UPPERCASE only)" << endl;
  //input board position
  cout << "> "; cin >> boardPos;
  std::string temp2 = "temp string";
  temp2 = boardPos;

  char row = 'Z';

  //take int value of the string for the col position
  size_t j = 0;
  for (; j < boardPos.length(); j++)
  {
    if (isdigit(boardPos[j]))
      break;
  }

  boardPos = boardPos.substr(j, boardPos.length() - j);

  int col = atoi(boardPos.c_str());

  //set row to be index 0 of input
  row = temp2[0];

  int rowIndex = 444;

  //convert row letter to a number
  if (row == 'A')
  {
    rowIndex = 1;
  }
  if (row == 'B')
  {
    rowIndex = 2;
  }
  if (row == 'C')
  {
    rowIndex = 3;
  }
  if (row == 'D')
  {
    rowIndex = 4;
  }
  if (row == 'E')
  {
    rowIndex = 5;
  }
  if (row == 'F')
  {
    rowIndex = 6;
  }
  if (row == 'G')
  {
    rowIndex = 7;
  }
  if (row == 'H')
  {
    rowIndex = 8;
  }
  if (row == 'I')
  {
    rowIndex = 9;
  }
  if (row == 'J')
  {
    rowIndex = 10;
  }
  if (row == 'K')
  {
    rowIndex = 11;
  }
  if (row == 'L')
  {
    rowIndex = 12;
  }
  if (row == 'M')
  {
    rowIndex = 13;
  }
  if (row == 'N')
  {
    rowIndex = 14;
  }
  if (row == 'O')
  {
    rowIndex = 15;
  }
  if (row == 'P')
  {
    rowIndex = 16;
  }
  if (row == 'Q')
  {
    rowIndex = 17;
  }
  if (row == 'R')
  {
    rowIndex = 18;
  }
  if (row == 'S')
  {
    rowIndex = 19;
  }
  if (row == 'T')
  {
    rowIndex = 20;
  }
  if (row == 'U')
  {
    rowIndex = 21;
  }
  if (row == 'V')
  {
    rowIndex = 22;
  }
  if (row == 'W')
  {
    rowIndex = 23;
  }
  if (row == 'X')
  {
    rowIndex = 24;
  }
  if (row == 'Y')
  {
    rowIndex = 25;
  }
  if (row == 'Z')
  {
    rowIndex = 26;
  }

  //check if location is valid
  //Tile *tileCheck = new Tile(placedColour, placedShape);

  //validLocation(tileCheck, temp2);
  //place tile on the board
  
  board[rowIndex][col].shape = placedShape;
  board[rowIndex][col].colour = placedColour;

  //refresh the players hand
}

bool validLocation(Tile *playedTile, std::string boardLocation)
{
  int row, column;
  bool result = false;

  column = boardLocation[0] - 65;
  row = stoi(boardLocation.substr(1));

  std::string board[column][row];

  if (row >= MAX_SIZE_BOARD || column >= MAX_SIZE_BOARD)
    std::cout << "Invalid location";
  else if (row % 2 != column % 2)
    std::cout << "Invalid locaiton" << std::endl;
  else if (board[column][row].compare(EMPTY_TILE) != 0)
  {
    std::cout << "There is a tile already in that location" << std::endl;
  }
  else
  {
    int newRow, newCol;

    bool invalidLocation = false;
    bool validLocation = false;

    for (int dir = 1; dir <= 4 && !invalidLocation; dir++)
    {
      newRow = row;
      newCol = column;

      if (dir == UP)
      {
        newCol--;
      }
      else if (dir == DOWN)
      {
        newCol++;
      }
      else if (dir == LEFT)
      {
        newRow--;
      }
      else if (dir == RIGHT)
      {
        newRow++;
      }

      if (newRow >= 0 && newRow < MAX_SIZE_BOARD && newCol >= 0 && newCol < MAX_SIZE_BOARD)
      {
        if (board[newCol][newRow].compare(EMPTY_TILE) != 0)
        {
          if (board[newCol][newRow].compare(playedTile->getTile()) != 0)
          {
            if (playedTile->getTile()[0] == board[newCol][newRow][0])
            {

              int offsetRow = newRow - row;
              int offsetCol = newCol - column;

              newRow += offsetRow;
              newCol += offsetCol;

              while (newRow >= 0 && newRow < MAX_SIZE_BOARD &&
                     newCol >= 0 && newCol < MAX_SIZE_BOARD &&
                     board[newCol][newRow].compare(EMPTY_TILE) != 0 &&
                     !invalidLocation)
              {

                if (playedTile->getTile().compare(board[newCol][newRow]) == 0)
                {
                  std::cout << "Tile already in the line" << std::endl;
                  invalidLocation = true;
                }
                else if (playedTile->getTile()[0] != board[newCol][newRow][0])
                {
                  invalidLocation = true;
                  std::cout << "Each line must share a common shape or colour" << std::endl;
                }

                newRow += offsetRow;
                newCol += offsetCol;
              }
              validLocation = true;
            }

            else if (playedTile->getTile()[1] == board[newCol][newRow][1])
            {
              int offsetRow = newRow - row;
              int offsetCol = newCol - column;

              newRow += offsetRow;
              newCol += offsetCol;

              while (newRow >= 0 && newRow < MAX_SIZE_BOARD &&
                     newCol >= 0 && newCol < MAX_SIZE_BOARD &&
                     board[newCol][newRow].compare(EMPTY_TILE) != 0 &&
                     !invalidLocation)
              {

                if (playedTile->getTile().compare(board[newCol][newRow]) == 0)
                {
                  std::cout << "Tile already in the line" << std::endl;
                  invalidLocation = true;
                }
                else if (playedTile->getTile()[1] != board[newCol][newRow][1])
                {
                  invalidLocation = true;
                  std::cout << "Each line must share a common shape or colour" << std::endl;
                }

                newRow += offsetRow;
                newCol += offsetCol;
              }
              validLocation = true;
            }
            else
            {
              std::cout << "Each line must share a common shape or colour" << std::endl;
              invalidLocation = true;
            }
          }
          else
          {
            std::cout << "Tile already in the line" << std::endl;
            invalidLocation = true;
          }
        }
      }
    }

    if (!invalidLocation)
    {
      if (validLocation)
        result = true;
      else
        std::cout << "Each line must share a common shape or colour" << std::endl;
    }
  }
  return result;
}


int main(int argc, char **argv)
{
  //LinkedList* list = new LinkedList();
  //delete list;

  //std::cout << "TODO: Implement Qwirkle!" << std::endl;

  std::cout << "Welcome to Qwirkle!" << std::endl;
  std::cout << "-------------------" << std::endl;
  int option = 0;
  bool enhancement = false;
  int choose;
  
  while(true){
    cout << "1. milestone 2 version" << endl;
    cout << "2. individual enhancement version" << endl;
    cout << "3. exit" << endl;
    cout << "> ";
    cin >> choose;
    if(choose == 1){
      enhancement = false;
      while (option != 4)
      {
        option = selectMenuOption(enhancement);

        if (option == 1)
        {
          newGame();
          std::string TileBagFile = "tileBag.txt";
          if (argc >= 2)
          {
            TileBagFile = argv[1];
          }

          TileBag *tilebag = new TileBag();
          Player *playerOne = new Player(1);
          Player *playerTwo = new Player(2);
          storePlaceholder();
          playGame(TileBagFile, tilebag, playerOne, playerTwo, enhancement);
        }
        else if (option == 2)
          loadGame();
        else if (option == 3)
          showCredits();
        else if (option == 4){
          std::cout << "Goodbye!" << std::endl;
          break;
        }
          
      }
    }
    else if(choose == 2){
      enhancement = true;
      while (option != 5)
      {
        option = selectMenuOption(enhancement);
        if (option == 1)
        {
          newGame();
          std::string TileBagFile = "tileBag.txt";
          if (argc >= 2)
          {
            TileBagFile = argv[1];
          }

          TileBag *tilebag = new TileBag();
          Player *playerOne = new Player(1);
          Player *playerTwo = new Player(2);
          storePlaceholder();
          playGame(TileBagFile, tilebag, playerOne, playerTwo, enhancement);
        }
        else if (option == 2)
          loadGame();
        else if (option == 3)
          showCredits();
        else if(option == 4)
          help();
        else if (option == 5){
          std::cout << "Goodbye!" << std::endl;
          break;
        }
      }
    }
    else if(choose == 3){
      exit(0);
    }
  }
  
  return EXIT_SUCCESS;
}

void playGame(std::string TileBagFile, TileBag *tilebag, Player *playerOne, Player *playerTwo, bool enhancement)
{
  std::ifstream file(TileBagFile);

  int numRead = 0;
  while (!file.eof() && numRead < MAX_TILEBAG_SIZE)
  {
    Colour colour = 'R';
    Shape shape = 0;
    bool readSuccess = false;
    readSuccess = readOneTile(file, &colour, &shape);

    if (!file.eof() && readSuccess)
    {
      // Put the tile in the linked list
      Tile *tile = new Tile(colour, shape);
      // TODO - USE Deck
      tilebag->add(tile);

      // Increment tiles read
      ++numRead;
    }
  }

  // Close the file
  file.close();

  //print the tilebag

  //std::cout << "Tilebag: " << std::endl;
  //printTilebag(tilebag);

  // Create a new temporary tileBag
  TileBag *player1hand = new TileBag();
  TileBag *player2hand = new TileBag();

  // Randomise the players hand
  std::random_device randomSeed;
  std::uniform_int_distribution<int> uniform_dist(0, numRead - 1);
  int i = 0;
  int j = 0;
  while (i < MAX_HAND_SIZE)
  {
    // Pick a random tile from the tilebag
    int randIndex = uniform_dist(randomSeed);

    if (tilebag->get(randIndex) != nullptr)
    {
      //move from tilebag to player
      Tile *tile = new Tile(*tilebag->get(randIndex));
      player1hand->add(tile);
      tilebag->remove(randIndex);

      ++i;
    }
  }
  while (j < MAX_HAND_SIZE)
  {
    // Pick a random tile from the tilebag
    int randIndex1 = uniform_dist(randomSeed);

    if (tilebag->get(randIndex1) != nullptr)
    {
      //move from tilebag to player
      Tile *tile1 = new Tile(*tilebag->get(randIndex1));
      player2hand->add(tile1);
      tilebag->remove(randIndex1);

      ++j;
    }
  }
  for(int l = 0; l < 5; l++){
    // Set the player's initial hand
    playerOne->setInitialHand(player1hand);
    std::cout << player1name << "'s it's your turn: " << std::endl;

    printBoard();
    //Displays the hand of current player
    std::cout << "Your hand is" << std::endl;
    printHand(player1hand);
    std::cout << std::endl;

    //place tile
    placeInitialTile(player1hand, enhancement);
    printBoard();
    refreshHand(tilebag, player1hand);
    //Displays current hand
    std::cout << "Your new hand is" << std::endl;
    printHand(player1hand);
    cout << endl;
    cout << endl;
    //printHand(tilebag);

    //player 2's turn
    playerTwo->setInitialHand(player2hand);
    
    printBoard();
    std::cout << std::endl;
    //Displays the hand of current player
    std::cout << player2name << "'s hand: " << std::endl;
    printHand(player2hand);
    std::cout << std::endl;

    placeInitialTile(player2hand, enhancement);
    refreshHand(tilebag, player2hand);

    std::cout << "Your new hand is" << std::endl;
    printHand(player2hand);

    std::cout << std::endl;
    std::cout << std::endl;

  }
}

void refreshHand(TileBag *tilebag, TileBag *hand)
{
  int numRead = 107;
  std::random_device randomSeed;
  std::uniform_int_distribution<int> uniform_dist(0, numRead - 1);
  // Pick a random tile from the tilebag
  int randIndex1 = uniform_dist(randomSeed);

  if (tilebag->get(randIndex1) != nullptr)
  {
    //move from tilebag to player
    Tile *tile1 = new Tile(*tilebag->get(randIndex1));
    hand->add(tile1);
    tilebag->remove(randIndex1);
  }
}

bool readOneTile(std::ifstream &file, Colour *colour, Shape *shape)
{

  //read colour
  Colour readColour = 'R';
  bool readSuccess = true;
  file >> readColour;

  if (readColour == 'R')
  {
    *colour = 'R';
  }
  else if (readColour == 'O')
  {
    *colour = 'O';
  }
  else if (readColour == 'Y')
  {
    *colour = 'Y';
  }
  else if (readColour == 'G')
  {
    *colour = 'G';
  }
  else if (readColour == 'B')
  {
    *colour = 'B';
  }
  else if (readColour == 'P')
  {
    *colour = 'P';
  }
  else
  {
    readSuccess = false;
    std::cout << "Incorrect color try again!" << std::endl;
  }

  //read shame
  file >> *shape;

  return readSuccess;
}
