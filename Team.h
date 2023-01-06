//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_TEAM_H
#define WET2_TEAM_H

#include "UnionFind.h"
#include "Player.h"

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
    UFNode<std::shared_ptr<Player>>& get_representative() const;
    UFNode<std::shared_ptr<Player>>& getLastNode();

    void updateTeamStatus();
    void updateTeamSpirit(permutation_t spirit);
    void updateTeamAbility(int ability);
    void updatePlayerNumGames(std::shared_ptr<Player>& player);
    void updateRepresentative(UFNode<std::shared_ptr<Player>> *representativePlayer);
    StatusType addNewPlayer(std::shared_ptr<Player>& player);

private:
    int m_id;
    permutation_t m_teamSpirit;
    int m_numOfGoalKeepers = 0;
    int m_score = 0;
    int m_teamSize = 0;
    int m_ability = 0;

    void increaseTeamSize();
    void addGoalKeeper();

    UnionFind<std::shared_ptr<Player>>* m_players;
    UFNode<std::shared_ptr<Player>>* m_representativePlayer;
    UFNode<std::shared_ptr<Player>>* m_lastNode;
};


#endif //WET2_TEAM_H
