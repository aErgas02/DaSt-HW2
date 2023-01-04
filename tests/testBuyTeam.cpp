#include "catch.hpp"
#include "common.h"

constexpr const int teamA = 1;
constexpr const int teamB = 2;
constexpr const int teamC = 3;
constexpr const int teamD = 4;

TEST_CASE("buyTeam sanity", "[buyTeam]") {
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamA));
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamA, teamB));
}

TEST_CASE("buyTeam input", "[buyTeam]") {
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamA));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.buy_team(-1, teamB));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.buy_team(0, teamB));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.buy_team(teamA, -1));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.buy_team(teamA, 0));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.buy_team(teamA, teamA));
}

TEST_CASE("buyTeam team not exist", "[buyTeam]") {
    world_cup_t worldCup;
    REQUIRE(StatusType::FAILURE == worldCup.buy_team(teamA, teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamA));
    REQUIRE(StatusType::FAILURE == worldCup.buy_team(teamA, teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamA, teamB));
}

TEST_CASE("buy team gamesPlayed correctness") {

    world_cup_t worldCup;
    auto players_teamA = buildTeam(worldCup, teamA, 10, 1);
    auto players_teamB = buildTeam(worldCup, teamB, 50, 1);
    auto players_teamC = buildTeam(worldCup, teamC, 60, 1);
    auto players_teamD = buildTeam(worldCup, teamD, 60, 1);
    REQUIRE(StatusType::SUCCESS == worldCup.play_match(teamA, teamB).status());
    REQUIRE(StatusType::SUCCESS == worldCup.play_match(teamC, teamD).status());
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamA, teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamD, teamC));
    for (auto player: players_teamA) {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
    for (auto player: players_teamB) {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamD, teamA));
    for (auto player: players_teamA) {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
    for (auto player: players_teamB) {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
    for (auto player: players_teamC) {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
    for (auto player: players_teamD) {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
}

TEST_CASE("buy team points are combined and bought team is gone", "[buyTeam]") {
    world_cup_t worldCup;
    buildTeam(worldCup, teamA, 10, 1);
    buildTeam(worldCup, teamB, 50, 1);
    REQUIRE(StatusType::SUCCESS == worldCup.play_match(teamA, teamB).status());
    REQUIRE(StatusType::FAILURE == worldCup.add_team(teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamA, teamB));
    REQUIRE(2 == worldCup.get_team_points(teamA).ans());
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamB));
}

TEST_CASE("buy team team spirit is correct") {
    world_cup_t worldCup;
    auto players_teamA = buildTeam(worldCup, teamA, 10, 1);
    auto players_teamB = buildTeam(worldCup, teamB, 60, 1);
    auto players_teamC = buildTeam(worldCup, teamC, 30, 1);
    auto players_teamD = buildTeam(worldCup, teamD, 31, 1);
    std::array<int, 5> p{0, 2, 1, 3, 4};
    permutation_t permA{p.__elems_};
    std::next_permutation(p.begin(), p.end());
    permutation_t permAAfter{p.__elems_};
    std::next_permutation(p.begin(), p.end());
    permutation_t permB{p.__elems_};
    std::next_permutation(p.begin(), p.end());
    permutation_t permC{p.__elems_};
    std::next_permutation(p.begin(), p.end());
    permutation_t permD{p.__elems_};
    permutation_t permDAfter{p.__elems_};

    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, teamA, permA, 0, 0, 0, false));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(2, teamB, permB, 0, 0, 0, false));
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamA, teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(3, teamA, permAAfter, 0, 0, 0, false));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(5, teamD, permD, 0, 0, 0, false));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(4, teamC, permC, 0, 0, 0, false));
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamD, teamC));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(6, teamD, permDAfter, 0, 0, 0, false));

    for (auto player: players_teamA) {
        REQUIRE(permutation_t::neutral() == worldCup.get_partial_spirit(player).ans());
    }
    for (auto player: players_teamB) {
        REQUIRE(permA == worldCup.get_partial_spirit(player).ans());
    }

    REQUIRE(permA == worldCup.get_partial_spirit(1).ans());
    REQUIRE((permA * permB) == worldCup.get_partial_spirit(2).ans());
    REQUIRE((permA * permB * permAAfter) == worldCup.get_partial_spirit(3).ans());
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamA, teamD));
    for (auto player: players_teamA) {
        REQUIRE(permutation_t::neutral() == worldCup.get_partial_spirit(player).ans());
    }
    for (auto player: players_teamB) {
        REQUIRE(permA == worldCup.get_partial_spirit(player).ans());
    }
    for (auto player: players_teamC) {
        REQUIRE((permA * permB * permAAfter * permD) == worldCup.get_partial_spirit(player).ans());
    }
    for (auto player: players_teamD) {
        REQUIRE((permA * permB * permAAfter) == worldCup.get_partial_spirit(player).ans());
    }

    REQUIRE((permA * permB * permAAfter * permD) == worldCup.get_partial_spirit(5).ans());
    REQUIRE((permA * permB * permAAfter * permD * permC) == worldCup.get_partial_spirit(4).ans());
    REQUIRE((permA * permB * permAAfter * permD * permC * permDAfter) == worldCup.get_partial_spirit(6).ans());
}

TEST_CASE("buy team games played multiple purchases no information is lost", "[buyTeam]") {
    world_cup_t worldCup;
    std::vector<int> players{};
    std::array<int, 6> num_players{1, 1, 2, 4, 8, 16};
    for (int i = 0; i < num_players.size(); ++i) {
        auto players_in_team = buildTeam(worldCup, i + 1, num_players[i], 1);
        players.insert(players.end(), players_in_team.begin(), players_in_team.end());
    }
    for (int i = 0; i < num_players.size(); i += 2) {
        REQUIRE(StatusType::SUCCESS == worldCup.play_match(i + 1, i + 2).status());
    }
    for (auto player: players) {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }

    int buyingTeamId = 104;
    int buyingTeamOpponentId = 103;
    buildTeam(worldCup, buyingTeamId, 100, 1);
    buildTeam(worldCup, buyingTeamOpponentId, 1, 1);
    for (int i = 0; i < 100; ++i) {
        REQUIRE(StatusType::SUCCESS == worldCup.play_match(buyingTeamId, buyingTeamOpponentId).status());
    }

    for (int i = 0; i < num_players.size() - 1; i++) {
        REQUIRE(StatusType::SUCCESS == worldCup.buy_team(i + 2, i + 1));
    }
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(buyingTeamId, 6));
    for (auto player: players) {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
}

TEST_CASE("buy team team spirit multiple purchases no information is lost", "[buyTeam]") {
    world_cup_t worldCup;
    std::vector<int> players{};
    std::vector<permutation_t> partialSpirits{};
    std::array<int, 6> num_players{16, 8, 4, 2, 1, 1};
    std::array<int, 5> p_base{0, 1, 2, 3, 4};
    permutation_t currentTeamSpirit{permutation_t::neutral()};
    for (int i = num_players.size() - 1; i >= 0; --i) {
        auto players_in_team = buildTeam(worldCup, i + 1, num_players[i], 1);
        players.insert(players.end(), players_in_team.begin(), players_in_team.end());
        for (int j = 0; j < num_players[i]; ++j) {
            partialSpirits.push_back(currentTeamSpirit);
        }
        permutation_t p{p_base.__elems_};
        REQUIRE(StatusType::SUCCESS == worldCup.add_player(1000 + i, i + 1, p, 0, 0, 0, false));
        currentTeamSpirit = currentTeamSpirit * p;
        std::next_permutation(p_base.begin(), p_base.end());
    }
    for (int i = 0; i < num_players.size() - 1; i++) {
        REQUIRE(StatusType::SUCCESS == worldCup.buy_team(i + 2, i + 1));
    }

    for (int i =0; i < players.size(); ++i) {
        REQUIRE(partialSpirits[i] == worldCup.get_partial_spirit(players[i]).ans());
    }
}