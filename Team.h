//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_TEAM_H
#define WET2_TEAM_H


class Team {

public:
    Team(int teamId);

    int getId() const;
    int getSpirit() const;
    bool isValid() const;
    int getScore() const;
    int getSize() const;

    void addGoalKeeper();
    void updateScore(int byAmount);


private:
    int m_id;
    int m_teamSpirit = 0;
    int m_numOfGoalKeepers = 0;
    int m_score = 0;
    int m_teamSize = 0;
};


#endif //WET2_TEAM_H
