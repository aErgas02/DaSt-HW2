//
// Created by Meitar Basson on 02/01/2023.
//

#include "Player.h"

Player::Player(int id, int spirit, int numOfGames, int ability, int numOfCards, bool goalKeeper) :
    m_id(id),
    m_spirit(spirit),
    m_numOfGames(numOfGames),
    m_ability(ability),
    m_numOfCards(numOfCards),
    m_goalKeeper(goalKeeper)
{}

int Player::get_id() const {
    return m_id;
}

bool Player::isGoalKeeper() const {
    return m_goalKeeper;
}
