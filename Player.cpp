//
// Created by Meitar Basson on 02/01/2023.
//

#include "Player.h"

Player::Player(int id, const permutation_t& spirit, int numOfGames, int ability,
               int numOfCards, bool goalKeeper, UnionFind<std::shared_ptr<Player>> &team) :
    m_id(id),
    m_spirit(spirit),
    m_numOfGames(numOfGames),
    m_ability(ability),
    m_numOfCards(numOfCards),
    m_goalKeeper(goalKeeper),
    m_team(&team)
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

int Player::get_numOfGames() const {
    return m_numOfGames;
}

void Player::updateNumOfGames(int by) {
    m_numOfGames += by;
}

void Player::updateNumOfCards(int numOfCards) {
    m_numOfCards += numOfCards;
}

void Player::changePlayerStatus() {
    m_isActive = false;
}

UnionFind<std::shared_ptr<Player>> &Player::getTeam() {
    return *m_team;
}

bool Player::isPlayerActive() const {
    return m_isActive;
}

const permutation_t &Player::get_spirit() {
    return m_spirit;
}

void Player::updateSpirit(permutation_t const teamSpirit) {
    m_spirit = teamSpirit * m_spirit;
}

int Player::get_ability() const {
    return m_ability;
}
