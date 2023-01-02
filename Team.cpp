//
// Created by Meitar Basson on 02/01/2023.
//

#include "Team.h"

Team::Team(int teamId, UnionFind<Player>& players) :
    m_id(teamId),
    m_players(players)
    {}

int Team::getId() const {
    return m_id;
}

int Team::getSpirit() const {
    return m_teamSpirit;
}

bool Team::isValid() const {
    return m_numOfGoalKeepers > 0;
}

int Team::getScore() const {
    return m_score;
}

int Team::getSize() const {
    return m_teamSize;
}

void Team::addGoalKeeper() {
    m_numOfGoalKeepers++;
}

void Team::updateScore(int byAmount) {
    m_score += byAmount;
}

void Team::increaseTeamSize() {
    m_teamSize++;
}

void Team::updateRepresentative(UFNode<Player> &representativePlayer) {
    if(m_representativePlayer == nullptr) {
        m_representativePlayer = &representativePlayer;
    }
}

StatusType Team::addNewPlayer(Player &player) {
    if (m_players.isPlayerExist(player.get_id())) {
        return StatusType::FAILURE;
    }
    m_players.insert(player.get_id(), player);
    increaseTeamSize();

    if(player.isGoalKeeper())
        addGoalKeeper();

    if(m_representativePlayer == nullptr) {

    }
    return StatusType::ALLOCATION_ERROR;
}
