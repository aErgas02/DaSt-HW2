#include "worldcup23a2.h"

#define TIE 0
#define FIRST_TEAM_BY_ABILITY 1
#define FIRST_TEAM_BY_SPIRIT 2
#define SECOND_TEAM_BY_ABILITY 3
#define SECOND_TEAM_BY_SPIRIT 4

int compT_func(std::shared_ptr<Team> *a, std::shared_ptr<Team> *b) {
    return (*a)->getId() == (*b)->getId() ? 0 : (*a)->getId() < (*b)->getId() ? -1 : 1;
}

int comp_ability_func(std::shared_ptr<Team> *a, std::shared_ptr<Team> *b){
    if((*a)->getAbility() < (*b)->getAbility()) return -1;
    if((*a)->getAbility() > (*b)->getAbility()) return 1;

    return ((*a)->getId() < (*b)->getId()) ? -1 : 1;
}

int runSimulation(TreeNode<std::shared_ptr<Team>> &team1, TreeNode<std::shared_ptr<Team>> &team2) {
    team1.val->get_representative().val->updateNumOfGames(1);
    team2.val->get_representative().val->updateNumOfGames(1);

    if(team1.val->getAbility() > team2.val->getAbility()) {
        team1.val->updateScore(3);
        return FIRST_TEAM_BY_ABILITY;
    } else if(team1.val->getAbility() < team2.val->getAbility()) {
        team2.val->updateScore(3);
        return SECOND_TEAM_BY_ABILITY;
    } else if (team1.val->getSpirit().strength() > team2.val->getSpirit().strength()) {
        team1.val->updateScore(3);
        return FIRST_TEAM_BY_SPIRIT;
    }else if (team1.val->getSpirit().strength() < team2.val->getSpirit().strength()) {
        team2.val->updateScore(3);
        return SECOND_TEAM_BY_SPIRIT;
    } else {
        team1.val->updateScore(1);
        team2.val->updateScore(1);
        return TIE;
    }
}

world_cup_t::world_cup_t() : m_playersNodes{}, m_playersHash{}
{
    // TODO: Your code goes here
    m_teams = new AVLTree<std::shared_ptr<Team>>(compT_func);
    m_teamsAbility = new AVLTree<std::shared_ptr<Team>>(comp_ability_func);
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
    delete m_teams;
    delete m_teamsAbility;
}

StatusType world_cup_t::add_team(int teamId)
{
	// TODO: Your code goes here
    if(teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        auto new_team = std::make_shared<Team>(teamId, m_playersNodes);
        if(m_teams->object_exists(new_team)) {
            return StatusType::FAILURE;
        } else {
            m_teams->insert(new_team);
            m_teamsAbility->insert(new_team);
            return StatusType::SUCCESS;
        }
    } catch (std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::remove_team(int teamId)
{
	// TODO: Your code goes here
    if(teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        auto team = std::make_shared<Team>(teamId, m_playersNodes);
        if(m_teams->object_exists(team)) {
            if(m_teams->find_object(team)->val->getSize() > 0) {
                auto representative = m_teams->find_object(team)->val->get_representative();
                representative.val->changePlayerStatus();
            }
            m_teams->delete_node(team);
            m_teamsAbility->delete_node(team);
            return StatusType::SUCCESS;
        } else {
            return StatusType::FAILURE;
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
    if (playerId <= 0 || teamId <= 0 || !spirit.isvalid() || gamesPlayed < 0 || cards < 0) {
        return StatusType::INVALID_INPUT;
    }

    // TODO: Check what happens if team is not active anymore
    try {
        // Player params are valid.
        auto team = std::make_shared<Team>(teamId, m_playersNodes);
        if (m_teams->object_exists(team)) {
            // Add to team
            auto team_node = *m_teams->find_object(team);
            auto player = std::make_shared<Player>(playerId, spirit, gamesPlayed, ability, cards, goalKeeper);
            if(m_playersHash.find(playerId) == m_playersHash.end()) {
                std::pair<int, std::shared_ptr<Player>> po(playerId, player);
                m_teamsAbility->delete_node(team); // FIX ability tree
                team_node.val->addNewPlayer(player);
                m_teamsAbility->insert(team);
                m_playersHash.insert(po);
                return StatusType::SUCCESS;
            } else {
                return StatusType::FAILURE;
            }
        } else {
            return StatusType::FAILURE;
        }
    } catch(std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }

    try {
        auto team1 = std::make_shared<Team>(teamId1, m_playersNodes);
        auto team2 = std::make_shared<Team>(teamId2, m_playersNodes);
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
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
    if(playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        auto res_parent = m_playersNodes.find(playerId);
        auto res_player = m_playersHash.find(playerId);
        if(res_parent == nullptr) {
            return StatusType::FAILURE;
        }
        if(res_player->second->get_id() == res_parent->val->get_id())
            return res_parent->val->get_numOfGames();
        return res_parent->val->get_numOfGames() + res_player->second->get_numOfGames();
    } catch(std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
    if(playerId <= 0 || cards < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        auto res = m_playersHash.find(playerId);
        if(res == m_playersHash.end()) {
            return StatusType::FAILURE;
        }
        if(res->second->isPlayerActive()) {
            res->second->updateNumOfCards(cards);
            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    } catch(std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
    if(playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        auto res = m_playersHash.find(playerId);
        if(res == m_playersHash.end()) {
            return StatusType::FAILURE;
        }
        auto player = res->second;
        return res->second->get_numOfCards();
    } catch(std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
    if(teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        auto team = std::make_shared<Team>(teamId, m_playersNodes);
        if(m_teams->object_exists(team)) {
            return m_teams->find_object(team)->val->getScore();
        } else {
            return StatusType::FAILURE;
        }
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    if( i < 0 || i >= m_teams->get_size() || m_teams->get_size() == 0){
        return StatusType::FAILURE;
    }
    try{
        auto node = m_teamsAbility->select(i);
        if(node == nullptr){
            //shouldn't get here but for debugging purposes :)
        }
        else{
            return node->val->getId();
        }
    }
    catch (std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
    if(playerId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    try{
        auto res_parent = m_playersNodes.find(playerId);
        auto res_player = m_playersHash.find(playerId);
        if(res_parent == nullptr) {
            return StatusType::FAILURE;
        }
        if(res_parent->val->isPlayerActive()) {

            // TODO: Change here
            if(res_player->second->get_id() == res_parent->val->get_id())
                return res_parent->val->get_spirit();
            return res_player->second->get_spirit();
        }
        return StatusType::FAILURE;
    } catch(std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2) {
    // TODO: Your code goes here
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }
    try {
        auto team1 = std::make_shared<Team>(teamId1, m_playersNodes);
        auto team2 = std::make_shared<Team>(teamId2, m_playersNodes);

        if(m_teams->object_exists(team1) && m_teams->object_exists(team2)) {
            auto team1_node = m_teams->find_object(team1);
            auto team2_node = m_teams->find_object(team2);


//            m_playersNodes.unify(team1_node->val->get_representative(), team2_rep);
            m_teams->delete_node(team2);
            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}
