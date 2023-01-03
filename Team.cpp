//
// Created by Meitar Basson on 02/01/2023.
//

#include "Team.h"

Team::Team(int teamId, UnionFind<std::shared_ptr<Player>>& players) :
    m_id(teamId),
    m_players(&players)
    {}

int Team::getId() const {
    return m_id;
}

int Team::getSpirit() const {
    return m_teamSpirit;
}

bool Team::isValid() const {
    return m_numOfGoalKeepers > 0 && m_teamSize > 0;
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

void Team::updateRepresentative(UFNode<std::shared_ptr<Player>> *representativePlayer) {
    if(m_representativePlayer == nullptr) {
        m_representativePlayer = representativePlayer;
    } else {
        m_players->unify(*m_representativePlayer, *representativePlayer);
    }
}

StatusType Team::addNewPlayer(std::shared_ptr<Player>& player) {
    auto& p_node = m_players->insert(player->get_id(), player);
    increaseTeamSize();
    if(player->isGoalKeeper())
        addGoalKeeper();

    updateRepresentative(&p_node);
    
    return StatusType::SUCCESS;
}

UFNode<std::shared_ptr<Player>>& Team::get_representative() const {
    return *m_representativePlayer;
}

int Team::getAbility() const {
    return m_ability;
}

void Team::updateTeamStatus() {
    if(m_representativePlayer != nullptr) {
        m_representativePlayer->val->changePlayerStatus();
    }
}
