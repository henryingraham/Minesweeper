//
// Created by Henry Ingraham on 4/13/22.
//

#include "Tile.h"

Tile::Tile(){
    _isRevealed = false;
    _isFlagged = false;
    _isMine = false;
    _isDigit = true;
    numAdjacentMines = 0;
    hiddenTile.setTexture(TextureManager::GetTexture("tile_hidden"));
    revealedTile.setTexture(TextureManager::GetTexture("tile_revealed"));
    flag.setTexture(TextureManager::GetTexture("flag"));
    mine.setTexture(TextureManager::GetTexture("mine"));
    one.setTexture(TextureManager::GetTexture("number_1"));
    two.setTexture(TextureManager::GetTexture("number_2"));
    three.setTexture(TextureManager::GetTexture("number_3"));
    four.setTexture(TextureManager::GetTexture("number_4"));
    five.setTexture(TextureManager::GetTexture("number_5"));
    six.setTexture(TextureManager::GetTexture("number_6"));
    seven.setTexture(TextureManager::GetTexture("number_7"));
    eight.setTexture(TextureManager::GetTexture("number_8"));

}

sf::Sprite Tile::GetSprite() {
    if (!_isRevealed)
        return hiddenTile;
    else
        return revealedTile;
}

void Tile::Uncover() {
    if (!isFlagged())
        _isRevealed = true;
}

sf::Sprite Tile::GetMines() {
    return mine;
}

void Tile::setPosition(float x, float y) {
    hiddenTile.setPosition(x,y);
    revealedTile.setPosition(x,y);
    flag.setPosition(x,y);
    mine.setPosition(x,y);
    one.setPosition(x,y);
    two.setPosition(x,y);
    three.setPosition(x,y);
    four.setPosition(x,y);
    five.setPosition(x,y);
    six.setPosition(x,y);
    seven.setPosition(x,y);
    eight.setPosition(x,y);

}

bool Tile::isFlagged() {
    return _isFlagged;
}

void Tile::setFlag() {
    _isFlagged = !_isFlagged;
}

sf::Sprite Tile::GetFlag() {
    return flag;
}

bool Tile::hasMine() {
    return _isMine;
}

void Tile::setMine() {
    _isMine = true;
    _isDigit = false;
}

bool Tile::isRevealed() {
    return _isRevealed;
}

sf::Sprite Tile::GetNumber() {
    switch (numAdjacentMines) {
        case 0:
            return revealedTile;
        case 1:
            return one;
        case 2:
            return two;
        case 3:
            return three;
        case 4:
            return four;
        case 5:
            return five;
        case 6:
            return six;
        case 7:
            return seven;
        case 8:
            return eight;

    }
}

bool Tile::hasNumber() {
    return _isDigit;
}

void Tile::removeFlag() {
    _isFlagged = false;
}

