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
    int getSpirit() const;
    bool isValid() const;
    int getScore() const;
    int getSize() const;
    int getAbility() const;

    void updateScore(int byAmount);
    UFNode<std::shared_ptr<Player>>& get_representative() const;

    void updateTeamStatus();
    StatusType addNewPlayer(std::shared_ptr<Player> player);


private:
    int m_id;
    int m_teamSpirit = 0;
    int m_numOfGoalKeepers = 0;
    int m_score = 0;
    int m_teamSize = 0;
    int m_ability = 0;

    void increaseTeamSize();
    void addGoalKeeper();

    void updateRepresentative(UFNode<std::shared_ptr<Player>> &representativePlayer);

    UnionFind<std::shared_ptr<Player>>* m_players;
    UFNode<std::shared_ptr<Player>>* m_representativePlayer;
};


#endif //WET2_TEAM_H
