//
// Created by Meitar Basson on 02/01/2023.
//

#include "Team.h"

Team::Team(int teamId, UnionFind<std::shared_ptr<Player>>& players) :
    m_id(teamId),
    m_teamSpirit(permutation_t().neutral()),
    m_numOfGoalKeepers(0),
    m_score(0),
    m_teamSize(0),
    m_ability(0),
    m_players(&players)
    {}

int Team::getId() const {
    return m_id;
}

permutation_t Team::getSpirit() {
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

void Team::updateRepresentative(UFNode<std::shared_ptr<Player>> *player) {
    if(player == nullptr) return;
    else if(m_representativePlayer == nullptr) {
        m_representativePlayer = player;
    } else {
        m_players->unify(*m_representativePlayer, *player);
        player->val->updateSpirit(m_representativePlayer->val->get_spirit().inv() * m_teamSpirit);
        updatePlayerNumGames(player->val);
    }
    player->val->updateRepresentative(*m_representativePlayer);
}

StatusType Team::addNewPlayer(std::shared_ptr<Player>& player) {
    auto& p_node = m_players->insert(player->get_id(), player);
    permutation_t init_spirit = player->get_spirit();
    increaseTeamSize();
    if(player->isGoalKeeper())
        addGoalKeeper();

    updateRepresentative(&p_node);
    updateTeamAbility(player->get_ability());
    updateTeamSpirit(init_spirit);

    return StatusType::SUCCESS;
}

UFNode<std::shared_ptr<Player>>* Team::get_representative() const {
    return m_representativePlayer;
}

int Team::getAbility() const {
    return m_ability;
}

void Team::updateTeamSpirit(permutation_t spirit) {
    m_teamSpirit = m_teamSpirit * spirit;
}

void Team::updateTeamAbility(int ability) {
    m_ability += ability;
}

void Team::updatePlayerNumGames(std::shared_ptr<Player>& player) {
    player->updateNumOfGames(-m_representativePlayer->val->get_numOfGames());
}

void Team::buyTeam(std::shared_ptr<Team>& team2) {
    // Update score
    m_score += team2->m_score;

    if(team2->getSize() == 0) return; // Team2 is empty
    else if(m_teamSize == 0) {
        // Team1 is empty
        update_team(team2);
    } else if(m_representativePlayer->height >= team2->m_representativePlayer->height) {
        // Team1 is bigger
        team2->m_representativePlayer->val->updateSpirit(m_representativePlayer->val->get_spirit().inv() * m_teamSpirit);
        team2->m_representativePlayer->val->updateNumOfGames(-m_representativePlayer->val->get_numOfGames());
        team2->m_representativePlayer->val->updateRepresentative(*m_representativePlayer);
        updateTeamSpirit(team2->m_teamSpirit);
        m_ability += team2->m_ability;
        m_numOfGoalKeepers += team2->m_numOfGoalKeepers;
        m_players->unify(*m_representativePlayer, *team2->m_representativePlayer);
    } else {
        // Team2 is bigger
        m_representativePlayer->val->updateNumOfGames(-team2->m_representativePlayer->val->get_numOfGames());
        team2->m_representativePlayer->val->updateSpirit(m_teamSpirit);
        m_representativePlayer->val->updateSpirit(team2->m_representativePlayer->val->get_spirit().inv());
        m_representativePlayer->val->updateRepresentative(*team2->m_representativePlayer);
        updateTeamSpirit(team2->m_teamSpirit);
        team2->m_ability += m_ability;
        team2->m_numOfGoalKeepers += m_numOfGoalKeepers;
        m_players->unify(*team2->m_representativePlayer, *m_representativePlayer);
    }
}

void Team::update_team(std::shared_ptr<Team>& team) {
    m_teamSpirit = team->m_teamSpirit;
    m_numOfGoalKeepers = team->m_numOfGoalKeepers;
    m_score = team->m_score;
    m_teamSize = team->m_teamSize;
    m_ability = team->m_ability;
    m_representativePlayer = team->m_representativePlayer;
    m_players = team->m_players;
}
