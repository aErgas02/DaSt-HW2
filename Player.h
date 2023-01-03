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
           int numOfCards, bool goalKeeper, UnionFind<std::shared_ptr<Player>> &team);

    int get_id() const;
    int get_spirit();
    int get_numOfGames() const;
    int get_ability();
    int get_numOfCards() const;
    bool isGoalKeeper() const;
    bool isPlayerActive() const;

    void updateNumOfCards(int numOfCards);
    void updateNumOfGames();
    void changePlayerStatus();

    UnionFind<std::shared_ptr<Player>> &getTeam();

private:
    int m_id;
    int m_numOfGames;
    int m_ability;
    int m_numOfCards;
    int m_initialTeamGames = 0;
    bool m_goalKeeper;
    bool m_isActive = true;
    permutation_t m_spirit;

    UnionFind<std::shared_ptr<Player>> *m_team;
};


#endif //WET2_PLAYER_H
