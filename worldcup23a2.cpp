#include "worldcup23a2.h"

int compT_func(std::shared_ptr<Team> *a, std::shared_ptr<Team> *b) {
    return (*a)->getId() == (*b)->getId() ? 0 : (*a)->getId() < (*b)->getId() ? -1 : 1;
}

world_cup_t::world_cup_t()
{
	// TODO: Your code goes here
    m_teams = new AVLTree<std::shared_ptr<Team>>(compT_func);
    m_players = UnionFind<Player>();
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
            auto new_team = std::make_shared<Team>(teamId);
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
            auto team = std::make_shared<Team>(teamId);
            if(m_teams->object_exists(team)) {
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
    try {
        if (playerId <= 0 || teamId <= 0 || !spirit.isvalid() || gamesPlayed < 0 || cards < 0) {
            return StatusType::INVALID_INPUT;
        } else {
            // Player params are valid.
            auto team = std::make_shared<Team>(teamId);
            auto team_node = TreeNode<std::shared_ptr<Team>>(std::make_shared<Team>(teamId));
            if (m_teams->object_exists(team)) {
                // Add to team
                auto player = Player(playerId, spirit, gamesPlayed, ability, cards, goalKeeper);
                if (m_players.isPlayerExist(playerId)) {
                    return StatusType::FAILURE;
                }
                m_players.insert(playerId, player);
                return StatusType::SUCCESS;
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
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
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
