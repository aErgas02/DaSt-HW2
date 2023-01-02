//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_PLAYER_H
#define WET2_PLAYER_H


#include "wet2util.h"

class Player {

public:
    Player(int id, permutation_t spirit, int numOfGames, int ability, int numOfCards, bool goalKeeper);

    int get_id() const;
    int get_spirit();
    int get_numOfGames();
    int get_ability();
    int get_numOfCards();
    bool isGoalKeeper() const;

private:
//    Team &m_team;
    int m_id;
    int m_numOfGames;
    int m_ability;
    int m_numOfCards;
    int m_initialTeamGames;
    bool m_goalKeeper;
    permutation_t m_spirit;
};


#endif //WET2_PLAYER_H
