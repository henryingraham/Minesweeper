//
// Created by Henry Ingraham on 4/13/22.
//
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <vector>

class Tile {
    sf::Sprite hiddenTile;
    sf::Sprite revealedTile;
    sf::Sprite flag;
    sf::Sprite mine;
    sf::Sprite one;
    sf::Sprite two;
    sf::Sprite three;
    sf::Sprite four;
    sf::Sprite five;
    sf::Sprite six;
    sf::Sprite seven;
    sf::Sprite eight;

    bool _isRevealed;
    bool _isMine;
    bool _isDigit;


public:
    int numAdjacentMines;
    Tile();
    sf::Sprite GetSprite();
    sf::Sprite GetFlag();
    sf::Sprite GetMines();
    sf::Sprite GetNumber();

    bool isFlagged();
    bool hasMine();
    bool isRevealed();
    bool hasNumber();
    void setPosition(float x, float y);
    void Uncover();
    void setFlag();
    void removeFlag();
    void setMine();

    bool _isFlagged;
};
