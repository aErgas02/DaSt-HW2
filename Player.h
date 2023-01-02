//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_PLAYER_H
#define WET2_PLAYER_H

#include "wet2util.h"
#include "UnionFind.h"

class Player {

public:
    Player(int id, const permutation_t& spirit, int numOfGames, int ability,
           int numOfCards, bool goalKeeper, UnionFind<Player>& team);

    int get_id() const;
    int get_spirit();
    int get_numOfGames();
    int get_ability();
    int get_numOfCards() const;
    bool isGoalKeeper() const;

private:
    int m_id;
    int m_numOfGames;
    int m_ability;
    int m_numOfCards;
    int m_initialTeamGames;
    bool m_goalKeeper;
    permutation_t m_spirit;

    UnionFind<Player>& m_team;

};


#endif //WET2_PLAYER_H
