#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TextureManager.h"
#include "Random.h"
#include "Tile.h"
#include <vector>
#include "math.h"

using namespace std;

vector<vector<Tile>> newBoard(string fileName, int width, int length){
    vector<vector<Tile>> board;
    ifstream inFileBoard(fileName);
    if (inFileBoard.is_open()){
        for(int i = 0; i < length; ++i){
            string rowDigits;
            getline(inFileBoard,rowDigits);
            istringstream stream(rowDigits);
            vector<Tile> row;
            for(int j = 0; j < width; ++j){
                char mine;
                stream.get(mine);
                Tile t;
                if (mine == '1'){
                    t.setMine();
                }
                t.setPosition(j*32.f, i*32.f);
                row.push_back(t);
            }
            board.push_back(row);
        }
        for(int i = 0; i < length; ++i) {
            for (int j = 0; j < width; ++j) {
                if ((i-1) >=0 && (i-1) < length && (j-1) >=0 && (j-1) < width && board[i - 1][j - 1].hasMine())
                    board[i][j].numAdjacentMines++;
                if ((i-1) >=0 && (i-1) < length && (j) >=0 && (j) < width && board[i - 1][j].hasMine())
                    board[i][j].numAdjacentMines++;
                if ((i-1) >=0 && (i-1) < length && (j+1) >=0 && (j+1) < width && board[i - 1][j + 1].hasMine())
                    board[i][j].numAdjacentMines++;
                if ((i) >=0 && (i) < length && (j-1) >=0 && (j-1) < width && board[i][j - 1].hasMine())
                    board[i][j].numAdjacentMines++;
                if ((i) >=0 && (i) < length && (j+1) >=0 && (j+1) < width && board[i][j + 1].hasMine())
                    board[i][j].numAdjacentMines++;
                if ((i+1) >=0 && (i+1) < length && (j-1) >=0 && (j-1) < width && board[i + 1][j - 1].hasMine())
                    board[i][j].numAdjacentMines++;
                if ((i+1) >=0 && (i+1) < length && (j) >=0 && (j) < width && board[i + 1][j].hasMine())
                    board[i][j].numAdjacentMines++;
                if ((i+1) >=0 && (i+1) < length && (j+1) >=0 && (j+1) < width && board[i + 1][j + 1].hasMine())
                    board[i][j].numAdjacentMines++;
            }
        }

    }
        else{
            cout << "file not open" << endl;
        }
    return board;
}
vector<vector<Tile>> randomBoard(const int mineCount , int width, int length){
    Random random;
    int randomX;
    int randomY;
    vector<vector<Tile>> board;
    for(int i = 0; i < length; ++i){
        vector<Tile> row;
        for(int j = 0; j < width; ++j){
            Tile t;
            t.setPosition(j*32.f, i*32.f);
            row.push_back(t);
        }
        board.push_back(row);
    }
    int i = 0;
    while( i < mineCount){
        randomX = random.Int(0,width-1);
        randomY = random.Int(0,length-1);
        if (!board.at(randomY).at(randomX).hasMine()){
            board.at(randomY).at(randomX).setMine();
            i++;
        }

    }

    for(int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            if ((i-1) >=0 && (i-1) < length && (j-1) >=0 && (j-1) < width && board[i - 1][j - 1].hasMine())
                board[i][j].numAdjacentMines++;
            if ((i-1) >=0 && (i-1) < length && (j) >=0 && (j) < width && board[i - 1][j].hasMine())
                board[i][j].numAdjacentMines++;
            if ((i-1) >=0 && (i-1) < length && (j+1) >=0 && (j+1) < width && board[i - 1][j + 1].hasMine())
                board[i][j].numAdjacentMines++;
            if ((i) >=0 && (i) < length && (j-1) >=0 && (j-1) < width && board[i][j - 1].hasMine())
                board[i][j].numAdjacentMines++;
            if ((i) >=0 && (i) < length && (j+1) >=0 && (j+1) < width && board[i][j + 1].hasMine())
                board[i][j].numAdjacentMines++;
            if ((i+1) >=0 && (i+1) < length && (j-1) >=0 && (j-1) < width && board[i + 1][j - 1].hasMine())
                board[i][j].numAdjacentMines++;
            if ((i+1) >=0 && (i+1) < length && (j) >=0 && (j) < width && board[i + 1][j].hasMine())
                board[i][j].numAdjacentMines++;
            if ((i+1) >=0 && (i+1) < length && (j+1) >=0 && (j+1) < width && board[i + 1][j + 1].hasMine())
                board[i][j].numAdjacentMines++;
        }
    }
    return board;
}
void uncover(vector<vector<Tile>> &board, int i, int j, int width, int length){
        board[i][j].Uncover();

        if (board[i][j].isRevealed() && board[i][j].numAdjacentMines == 0) {
            if ((i - 1) >= 0 && (i - 1) < length && (j - 1) >= 0 && (j - 1) < width && !board[i-1][j-1].isRevealed()) {
                uncover(board, (i - 1), (j - 1), width, length);
            }
            if ((i - 1) >= 0 && (i - 1) < length && (j) >= 0 && (j) < width && !board[i-1][j].isRevealed()) {
                uncover(board, (i - 1), (j), width, length);
            }
            if ((i - 1) >= 0 && (i - 1) < length && (j + 1) >= 0 && (j + 1) < width && !board[i-1][j+1].isRevealed()) {
              uncover(board, (i - 1), (j + 1), width, length);
            }
            if ((i) >= 0 && (i) < length && (j - 1) >= 0 && (j - 1) < width && !board[i][j-1].isRevealed()) {
               uncover(board, (i), (j - 1), width, length);
            }
            if ((i) >= 0 && (i) < length && (j + 1) >= 0 && (j + 1) < width && !board[i][j+1].isRevealed()) {
                uncover(board, (i), (j + 1), width, length);
            }
            if ((i + 1) >= 0 && (i + 1) < length && (j - 1) >= 0 && (j - 1) < width && !board[i+1][j-1].isRevealed()) {
                uncover(board, (i + 1), (j - 1), width, length);
            }
            if ((i + 1) >= 0 && (i + 1) < length && (j) >= 0 && (j) < width && !board[i+1][j].isRevealed()) {
                uncover(board, (i + 1), (j), width, length);
            }
            if ((i + 1) >= 0 && (i + 1) < length && (j + 1) >= 0 && (j + 1) < width && !board[i+1][j+1].isRevealed()) {
                uncover(board, (i + 1), (j + 1), width, length);
            }
        }

}


int main()
{
    ifstream inFile("boards/config.cfg");
    int width;
    int length;
    int numMines;
    int numMinesConfig;
    int flagCount;
    if (inFile.is_open()) {
        string tempWidth;
        getline(inFile,tempWidth);
        width = stoi(tempWidth);

        string tempLength;
        getline(inFile,tempLength);
        length = stoi(tempLength);

        string tempMines;
        getline(inFile,tempMines);
        numMinesConfig = stoi(tempMines);
        flagCount = stoi(tempMines);

    }
    else{
        cout << "file not open" << endl;
    }

    sf::RenderWindow window(sf::VideoMode(width*32, length*32+100), "Minesweeper");
    sf::Sprite debug(TextureManager::GetTexture("debug"));
    sf::Sprite happyFace(TextureManager::GetTexture("face_happy"));
    sf::Sprite loseFace(TextureManager::GetTexture("face_lose"));
    sf::Sprite winFace(TextureManager::GetTexture("face_win"));
    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    sf::Sprite test3(TextureManager::GetTexture("test_3"));
    sf::Sprite digitSign(TextureManager::GetTexture("digits"));
    sf::Sprite digit1(TextureManager::GetTexture("digits"));
    sf::Sprite digit2(TextureManager::GetTexture("digits"));
    sf::Sprite digit3(TextureManager::GetTexture("digits"));



    bool debugMode = false;
    bool gameOver = false;
    bool win = false;
    string boardNumber;

    vector<vector<Tile>> board = randomBoard(numMinesConfig , width, length);


    happyFace.setPosition(window.getSize().x/2.f, length*32.f);
    winFace.setPosition(window.getSize().x/2.f, length*32.f);
    loseFace.setPosition(window.getSize().x/2.f, length*32.f);
    digitSign.setPosition(0, length * 32.f);
    digit1.setPosition(21, length * 32.f);
    digit2.setPosition(42, length * 32.f);
    digit3.setPosition(63, length * 32.f);
    debug.setPosition(happyFace.getPosition().x+64*2,happyFace.getPosition().y);
    test1.setPosition(happyFace.getPosition().x+64*3,happyFace.getPosition().y);
    test2.setPosition(happyFace.getPosition().x+64*4,happyFace.getPosition().y);
    test3.setPosition(happyFace.getPosition().x+64*5,happyFace.getPosition().y);




    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (!gameOver) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    for (int i = 0; i < board.size(); ++i) {
                        for (int j = 0; j < board[i].size(); ++j) {
                            sf::FloatRect rectangle = board[i][j].GetSprite().getGlobalBounds();
                            if (rectangle.contains(mousePosition.x, mousePosition.y)) {
                                if (!board[i][j].isRevealed()) {
                                    if (board[i][j].isFlagged())
                                        flagCount++;
                                    else
                                        flagCount--;
                                    board[i][j].setFlag();
                                }
                            }
                        }
                    }
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    for (int i = 0; i < board.size(); ++i) {
                        for (int j = 0; j < board[i].size(); ++j) {
                            sf::FloatRect rectangle = board[i][j].GetSprite().getGlobalBounds();
                            if (rectangle.contains(mousePosition.x, mousePosition.y)) {
                                if (board[i][j].hasMine() && !board[i][j].isFlagged()) {
                                    board[i][j].Uncover();
                                    gameOver = true;
                                }
                                else {
                                    uncover(board, i, j, width, length);
                                    int tilesLeft = 0;
                                    for (int a = 0; a < board.size(); ++a) {
                                        for (int b = 0; b < board[a].size(); ++b) {
                                            if (!board[a][b].isRevealed())
                                                tilesLeft++;
                                        }
                                    }
                                    if (tilesLeft == numMines) {
                                        win = true;
                                        gameOver = true;
                                    }
                                }

                            }
                        }
                    }
                    sf::FloatRect debugPos = debug.getGlobalBounds();
                    sf::FloatRect test1Pos = test1.getGlobalBounds();
                    sf::FloatRect test2Pos = test2.getGlobalBounds();
                    sf::FloatRect test3Pos = test3.getGlobalBounds();
                    sf::FloatRect facePos = loseFace.getGlobalBounds();


                    if (debugPos.contains(mousePosition.x, mousePosition.y)) {
                        debugMode = !debugMode;
                    }
                    if (test1Pos.contains(mousePosition.x, mousePosition.y)) {
                        boardNumber = "1";
                        board = newBoard("boards/testboard" + boardNumber + ".brd", width, length);
                        flagCount = 0;
                        numMines = 0;
                        for (int i = 0; i < board.size(); ++i) {
                            for (int j = 0; j < board[i].size(); ++j) {
                                if (board[i][j].hasMine())
                                    numMines++;
                            }
                        }
                        flagCount = numMines;
                    }
                    if (test2Pos.contains(mousePosition.x, mousePosition.y)) {
                        boardNumber = "2";
                        board = newBoard("boards/testboard" + boardNumber + ".brd", width, length);
                        flagCount = 0;
                        numMines = 0;
                        for (int i = 0; i < board.size(); ++i) {
                            for (int j = 0; j < board[i].size(); ++j) {
                                if (board[i][j].hasMine())
                                    numMines++;
                            }
                        }
                        flagCount = numMines;
                    }
                    if (test3Pos.contains(mousePosition.x, mousePosition.y)) {
                        boardNumber = "3";
                        board = newBoard("boards/testboard" + boardNumber + ".brd", width, length);
                        flagCount = 0;
                        numMines = 0;
                        for (int i = 0; i < board.size(); ++i) {
                            for (int j = 0; j < board[i].size(); ++j) {
                                if (board[i][j].hasMine())
                                    numMines++;
                            }
                        }
                        flagCount = numMines;
                    }
                    if (facePos.contains(mousePosition.x, mousePosition.y)){
                        board = randomBoard(numMinesConfig, width, length);
                        flagCount = 0;
                        numMines = 0;
                        for (int i = 0; i < board.size(); ++i) {
                            for (int j = 0; j < board[i].size(); ++j) {
                                if (board[i][j].hasMine())
                                    numMines++;
                            }
                        }
                        flagCount = numMines;
                    }


                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                sf::FloatRect facePos = loseFace.getGlobalBounds();
                if (facePos.contains(mousePosition.x, mousePosition.y)) {
                    gameOver = false;
                    win = false;
                    board = randomBoard(numMinesConfig, width, length);
                    flagCount = numMinesConfig;

                }
                sf::FloatRect test1Pos = test1.getGlobalBounds();
                sf::FloatRect test2Pos = test2.getGlobalBounds();
                sf::FloatRect test3Pos = test3.getGlobalBounds();
                if (test1Pos.contains(mousePosition.x, mousePosition.y)) {
                    gameOver = false;
                    win = false;
                    boardNumber = "1";
                    board = newBoard("boards/testboard" + boardNumber + ".brd", width, length);
                    flagCount = 0;
                    numMines = 0;
                    for (int i = 0; i < board.size(); ++i) {
                        for (int j = 0; j < board[i].size(); ++j) {
                            if (board[i][j].hasMine())
                                numMines++;
                        }
                    }
                    flagCount = numMines;
                }
                if (test2Pos.contains(mousePosition.x, mousePosition.y)) {
                    gameOver = false;
                    win = false;
                    boardNumber = "2";
                    board = newBoard("boards/testboard" + boardNumber + ".brd", width, length);
                    flagCount = 0;
                    numMines = 0;
                    for (int i = 0; i < board.size(); ++i) {
                        for (int j = 0; j < board[i].size(); ++j) {
                            if (board[i][j].hasMine())
                                numMines++;
                        }
                    }
                    flagCount = numMines;
                }
                if (test3Pos.contains(mousePosition.x, mousePosition.y)) {
                    gameOver = false;
                    win = false;
                    boardNumber = "3";
                    board = newBoard("boards/testboard" + boardNumber + ".brd", width, length);
                    flagCount = 0;
                    numMines = 0;
                    for (int i = 0; i < board.size(); ++i) {
                        for (int j = 0; j < board[i].size(); ++j) {
                            if (board[i][j].hasMine())
                                numMines++;
                        }
                    }
                    flagCount = numMines;
                }

            }

        }

        window.clear();



        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                window.draw(board[i][j].GetSprite());
                if (board[i][j].isRevealed()){
                    if (board[i][j].hasMine()) {
                        window.draw(board[i][j].GetMines());
                    }
                    else{
                        window.draw(board[i][j].GetNumber());
                    }
                }
                if (board[i][j].isFlagged()) {
                    window.draw(board[i][j].GetFlag());
                }
                if (debugMode) {
                    if (board[i][j].hasMine()) {
                        window.draw(board[i][j].GetMines());
                    }
                }

            }
        }



        if (!gameOver){
            window.draw(happyFace);
        }
        else if (win){
            window.draw(winFace);
            for (int i = 0; i < board.size(); ++i) {
                for (int j = 0; j < board[i].size(); ++j) {
                    if (board[i][j].hasMine())
                        board[i][j]._isFlagged = true;
                }
            }
            flagCount = 0;
        }
        else{
            window.draw(loseFace);
            for (int i = 0; i < board.size(); ++i) {
                for (int j = 0; j < board[i].size(); ++j) {
                    if (board[i][j].hasMine())
                        board[i][j].Uncover();
                }
            }
            flagCount = 0;
        }
        window.draw(test3);
        window.draw(test2);
        window.draw(test1);
        window.draw(debug);
        int absCount = flagCount;
        if (flagCount < 0) {
            window.draw(digitSign);
            absCount = abs(flagCount);
        }

        int digitF;
        int digitS;
        int digitT;
        digitT = absCount % 10;
        digitS = (absCount / 10) % 10;
        digitF = (absCount / 100) % 10;
        digit1.setTextureRect(sf::IntRect(21 * digitF, 0, 21, 32));
        digit2.setTextureRect(sf::IntRect(21 * digitS, 0, 21, 32));
        digit3.setTextureRect(sf::IntRect(21 * digitT, 0, 21, 32));
        digitSign.setTextureRect(sf::IntRect(210, 0, 21, 32));


        window.draw(digit1);
        window.draw(digit2);
        window.draw(digit3);
        window.display();
    }

    return 0;
}