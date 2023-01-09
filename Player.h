//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_PLAYER_H
#define WET2_PLAYER_H

#include "wet2util.h"
#include "UnionFind.h"
#include "wet2util.h"

class Player {

public:
    Player(int id, const permutation_t& spirit, int numOfGames, int ability,
           int numOfCards, bool goalKeeper);

    int get_id() const;
    permutation_t get_spirit();
    int get_numOfGames() const;
    int get_ability() const;
    int get_numOfCards() const;
    bool isGoalKeeper() const;
    bool isPlayerActive() const;

    void updateNumOfCards(int numOfCards);
    void updateNumOfGames(int by);
    void changePlayerStatus();
    void updateSpirit(permutation_t const& teamSpirit);

    UFNode<std::shared_ptr<Player>> &getRepresentative();
    void updateRepresentative(UFNode<std::shared_ptr<Player>> &new_representative);

private:
    int m_id;
    int m_numOfGames;
    int m_ability;
    int m_numOfCards;
    bool m_goalKeeper;
    bool m_isActive = true;
    permutation_t m_spirit;

    UFNode<std::shared_ptr<Player>> *m_representative = nullptr;
};


#endif //WET2_PLAYER_H
