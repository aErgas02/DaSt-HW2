#include "worldcup23a2.h"

#define TIE 0
#define FIRST_TEAM_BY_ABILITY 1
#define FIRST_TEAM_BY_SPIRIT 2
#define SECOND_TEAM_BY_ABILITY 3
#define SECOND_TEAM_BY_SPIRIT 4

void blackBox(UFNode<std::shared_ptr<Player>> &set, UFNode<std::shared_ptr<Player>> &parent) {
    set.val->updateNumOfGames(-parent.parent->val->get_numOfGames() + parent.val->get_numOfGames());
    set.val->updateSpirit(  parent.parent->val->get_spirit().inv() * parent.val->get_spirit());
    set.val->updateRepresentative(parent.val->getRepresentative());
}

int compT_func(std::shared_ptr<Team> *a, std::shared_ptr<Team> *b) {
    return (*a)->getId() == (*b)->getId() ? 0 : (*a)->getId() < (*b)->getId() ? -1 : 1;
}

int comp_ability_func(std::shared_ptr<Team> *a, std::shared_ptr<Team> *b){
    if((*a)->getId() == (*b)->getId()) return 0;
    if((*a)->getAbility() < (*b)->getAbility()) return -1;
    if((*a)->getAbility() > (*b)->getAbility()) return 1;

    return ((*a)->getId() < (*b)->getId()) ? -1 : 1;
}

bool comp_player_func(std::shared_ptr<Player> * player, int id){
    if((*player)->get_id() == id) return true;
    return false;
}

int runSimulation(TreeNode<std::shared_ptr<Team>> &team1, TreeNode<std::shared_ptr<Team>> &team2) {
    team1.val->get_representative()->val->updateNumOfGames(1);
    team2.val->get_representative()->val->updateNumOfGames(1);

    if(team1.val->fightAbility() > team2.val->fightAbility()) {
        team1.val->updateScore(3);
        return FIRST_TEAM_BY_ABILITY;
    } else if(team1.val->fightAbility() < team2.val->fightAbility()) {
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
    m_playersNodes.blackBox = blackBox;
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
            auto team_node = m_teams->find_object(team);
            if(team_node->val->getSize() > 0) {
                auto representative = team_node->val->get_representative();
                representative->val->changePlayerStatus();
            }
            m_teamsAbility->delete_node(team_node->val);
            m_teams->delete_node(team_node->val);
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

    try {
        // Player params are valid.
        auto team = std::make_shared<Team>(teamId, m_playersNodes);
        if (m_teams->object_exists(team)) {
            // Add to team
            auto team_node = m_teams->find_object(team);
            auto player = std::make_shared<Player>(playerId, spirit, gamesPlayed, ability, cards, goalKeeper);
            if(m_playersHash.find(playerId) == m_playersHash.end()) {
                std::pair<int, std::shared_ptr<Player>> po(playerId, player);
                m_teamsAbility->delete_node(team_node->val); // FIX ability tree
                team_node->val->addNewPlayer(player);
                m_teamsAbility->insert(team_node->val);
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
        return (*res_player).second->get_numOfGames();
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
        m_playersNodes.find(playerId);
        auto res = m_playersHash.find(playerId);
        if(res == m_playersHash.end()) {
            return StatusType::FAILURE;
        }
        if(res->second->getRepresentative().val->isPlayerActive()) {
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
        auto player = *res; //todo: check why no use of player?
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
    if( i < 0 || i >= m_teamsAbility->get_size() || m_teamsAbility->get_size() == 0){
        return StatusType::FAILURE;
    }
    try{
        auto node = m_teamsAbility->select(i);
        return node->val->getId();
    } catch (std::bad_alloc &e){
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
        if(res_parent == nullptr || res_player == m_playersHash.end()) {
            return StatusType::FAILURE;
        }
        if(res_parent->val->isPlayerActive()) {
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
            auto team1_rep = m_teams->find_object(team1);
            auto team2_rep = m_teams->find_object(team2);
            m_teamsAbility->delete_node(team2_rep->val);
            m_teamsAbility->delete_node(team1_rep->val);
            team1_rep->val->buyTeam(team2_rep->val);
            m_teamsAbility->insert(team1_rep->val);
            m_teams->delete_node(team2_rep->val);
            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}
