//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_TEAM_H
#define WET2_TEAM_H

#include "UnionFind.h"
#include "Player.h"
#include "wet2util.h"
#include <memory>

class Team {

public:
    Team(int teamId, UnionFind<std::shared_ptr<Player>>& players);

    int getId() const;
    permutation_t getSpirit();
    bool isValid() const;
    int getScore() const;
    int getSize() const;
    int getAbility() const;

    void updateScore(int byAmount);
    UFNode<std::shared_ptr<Player>>* get_representative() const;

    void updateTeamSpirit(permutation_t spirit);
    void updateTeamAbility(int ability);
    void updatePlayerNumGames(std::shared_ptr<Player>& player);
    void updateRepresentative(UFNode<std::shared_ptr<Player>> *player);
    void buyTeam(std::shared_ptr<Team> &team2);
    StatusType addNewPlayer(std::shared_ptr<Player>& player);

private:
    int m_id;
    permutation_t m_teamSpirit = permutation_t().neutral();
    int m_numOfGoalKeepers;
    int m_score;
    int m_teamSize;
    int m_ability;

    void increaseTeamSize();
    void addGoalKeeper();

    UnionFind<std::shared_ptr<Player>>* m_players = nullptr;
    UFNode<std::shared_ptr<Player>>* m_representativePlayer = nullptr;

    void update_team(std::shared_ptr<Team>& team);
};


#endif //WET2_TEAM_H
