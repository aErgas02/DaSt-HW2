#include "worldcup23a2.h"

int compT_func(std::shared_ptr<Team> *a, std::shared_ptr<Team> *b) {
    return (*a)->getId() == (*b)->getId() ? 0 : (*a)->getId() < (*b)->getId() ? -1 : 1;
}

int runSimulation(TreeNode<std::shared_ptr<Team>> &team1, TreeNode<std::shared_ptr<Team>> &team2) {
    team1.val->get_representative().val.updateNumOfGames();
    team2.val->get_representative().val.updateNumOfGames();

    if(team1.val->getAbility() > team2.val->getAbility()) {
        team1.val->updateScore(3);
        return 1;
    } else if(team1.val->getAbility() < team2.val->getAbility()) {
        team2.val->updateScore(3);
        return 3;
    } else if (team1.val->getSpirit() > team2.val->getSpirit()) {
        team1.val->updateScore(3);
        return 2;
    }else if (team1.val->getSpirit() < team2.val->getSpirit()) {
        team2.val->updateScore(3);
        return 4;
    } else {
        team1.val->updateScore(1);
        team2.val->updateScore(1);
        return 0;
    }
}

world_cup_t::world_cup_t() : m_players{}
{
    // TODO: Your code goes here
    m_teams = new AVLTree<std::shared_ptr<Team>>(compT_func);
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
    delete m_teams;
}

StatusType world_cup_t::add_team(int teamId)
{
	// TODO: Your code goes here
    try {
        if(teamId <= 0) {
            return StatusType::INVALID_INPUT;
        } else {
            auto new_team = std::make_shared<Team>(teamId, m_players);
            if(m_teams->object_exists(new_team)) {
                return StatusType::FAILURE;
            } else {
                m_teams->insert(new_team);
                return StatusType::SUCCESS;
            }
        }
    } catch (std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::remove_team(int teamId)
{
	// TODO: Your code goes here
    try {
        if(teamId <= 0) {
            return StatusType::INVALID_INPUT;
        } else {
            auto team = std::make_shared<Team>(teamId, m_players);
            if(m_teams->object_exists(team)) {
                m_teams->find_object(team)->val->updateTeamStatus();
                m_teams->delete_node(team);
                return StatusType::SUCCESS;
            } else {
                return StatusType::FAILURE;
            }
        }
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here

    // TODO: Check what happens if team is not active anymore
    try {
        if (playerId <= 0 || teamId <= 0 || !spirit.isvalid() || gamesPlayed < 0 || cards < 0) {
            return StatusType::INVALID_INPUT;
        } else {
            // Player params are valid.
            auto team = std::make_shared<Team>(teamId, m_players);
            if (m_teams->object_exists(team)) {
                // Add to team
                auto team_node = m_teams->find_object(team);
                auto player = Player(playerId, spirit, gamesPlayed, ability, cards, goalKeeper, m_players);
                return team_node->val->addNewPlayer(player);
            } else {
                return StatusType::FAILURE;
            }
        }
    } catch(std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
    try {
        if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
            return StatusType::INVALID_INPUT;
        } else {
            auto team1 = std::make_shared<Team>(teamId1, m_players);
            auto team2 = std::make_shared<Team>(teamId2, m_players);

            if(m_teams->object_exists(team1) && m_teams->object_exists(team2)) {
                auto team1_node = m_teams->find_object(team1);
                auto team2_node = m_teams->find_object(team2);

                if(team1_node->val->isValid() == 0 || team2_node->val->isValid() == 0) {
                    return StatusType::FAILURE;
                }
                return runSimulation(*team1_node, *team2_node);
            } else {
                return StatusType::FAILURE;
            }
        }
        return StatusType::SUCCESS;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
    try {
        if(playerId <= 0) {
            return StatusType::INVALID_INPUT;
        } else {
            auto res = m_players.find(playerId);
            if(res == nullptr) {
                return StatusType::FAILURE;
            }
            return res->val.get_numOfGames();
        }
    } catch(std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
    try {
        if(playerId <= 0 || cards < 0) {
            return StatusType::INVALID_INPUT;
        }
        auto res = m_players.find(playerId);
        if(res == nullptr) {
            return StatusType::FAILURE;
        }
        if(res->val.updateNumOfCards(cards))
            return StatusType::SUCCESS;
        return StatusType::FAILURE;
    } catch(std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
    try {
        if(playerId <= 0) {
            return StatusType::INVALID_INPUT;
        } else {
            auto res = m_players.find(playerId);
            if(res == nullptr) {
                return StatusType::FAILURE;
            }
            return res->val.get_numOfCards();
        }
    } catch(std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
    try {
        if(teamId <= 0) {
            return StatusType::INVALID_INPUT;
        } else {
            auto team = std::make_shared<Team>(teamId, m_players);
            if(m_teams->object_exists(team)) {
                return m_teams->find_object(team)->val->getScore();
            } else {
                return StatusType::FAILURE;
            }
        }
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
