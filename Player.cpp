//
// Created by Meitar Basson on 02/01/2023.
//

#include "Player.h"

Player::Player(int id, const permutation_t& spirit, int numOfGames, int ability,
               int numOfCards, bool goalKeeper, UnionFind<Player>& team) :
    m_id(id),
    m_spirit(spirit),
    m_numOfGames(numOfGames),
    m_ability(ability),
    m_numOfCards(numOfCards),
    m_goalKeeper(goalKeeper),
    m_team(team)
{}

int Player::get_id() const {
    return m_id;
}

bool Player::isGoalKeeper() const {
    return m_goalKeeper;
}

int Player::get_numOfCards() const {
    return m_numOfCards;
}
