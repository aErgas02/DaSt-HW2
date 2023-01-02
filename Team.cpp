//
// Created by Meitar Basson on 02/01/2023.
//

#include "Team.h"

Team::Team(int teamId) :
    m_id(teamId)
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
