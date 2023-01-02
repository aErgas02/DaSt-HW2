cmake_minimum_required(VERSION 3.20)
project(wet2)

set(CMAKE_CXX_STANDARD 11)

include_directories("segelfiles")
set(PROJECT_FILES "worldcup23a2.cpp" "team.cpp" "player.cpp") # "team_info.cpp"
set(TESTS "tests/treeTests.cpp" "tests/addTeamTests.cpp" "tests/removeTeamTests.cpp" "tests/addPlayerTests.cpp" "tests/playMatchTests.cpp" "tests/testNumPlayedGames.cpp" "tests/testAddPlayerCards.cpp" "tests/testGetPlayerCards.cpp" "tests/testGetTeamPoints.cpp" "tests/testGetIthPointlessAbility.cpp" "tests/testGetPartialTeamSpirit.cpp" "tests/testBuyTeam.cpp")
add_executable(our tests/main.cpp ${PROJECT_FILES} ${TESTS})
add_executable(segel_tests segelfiles/main23a2.cpp ${PROJECT_FILES})


add_executable(test main.cpp Player.cpp Player.h Team.cpp Team.h AVLTree.h TreeNode.h exceptions.h Array.h)
add_executable(wet2 main23a2.cpp Player.cpp Player.h Team.cpp Team.h AVLTree.h TreeNode.h exceptions.h Array.h)