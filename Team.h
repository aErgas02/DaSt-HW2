//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_TEAM_H
#define WET2_TEAM_H

#include "UnionFind.h"
#include "Player.h"

class Team {

public:
    Team(int teamId, UnionFind<Player>& players);

    int getId() const;
    int getSpirit() const;
    bool isValid() const;
    int getScore() const;
    int getSize() const;

    void updateScore(int byAmount);

    StatusType addNewPlayer(Player &player);


private:
    int m_id;
    int m_teamSpirit = 0;
    int m_numOfGoalKeepers = 0;
    int m_score = 0;
    int m_teamSize = 0;

    void increaseTeamSize();
    void addGoalKeeper();
    void updateRepresentative(UFNode<Player> &representativePlayer);

    UnionFind<Player>& m_players;
    UFNode<Player>* m_representativePlayer = nullptr;
};


#endif //WET2_TEAM_H
