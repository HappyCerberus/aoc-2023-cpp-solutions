module;

#include <string_view>

export module input;

export namespace input {
const std::string_view day23_test = R"(#.#####################
#.......#########...###
#######.#########.#.###
###.....#.>.>.###.#.###
###v#####.#v#.###.#.###
###.>...#.#.#.....#...#
###v###.#.#.#########.#
###...#.#.#.......#...#
#####.#.#.#######.#.###
#.....#.#.#.......#...#
#.#####.#.#.#########v#
#.#...#...#...###...>.#
#.#.#v#######v###.###v#
#...#.>.#...>.>.#.###.#
#####v#.#.###v#.#.###.#
#.....#...#...#.#.#...#
#.#########.###.#.#.###
#...###...#...#...#.###
###.###.#.###v#####v###
#...#...#.#.>.>.#.>.###
#.###.###.#.###.#.#v###
#.....###...###...#...#
#####################.#)";
const std::string_view day23 =
    R"(#.###########################################################################################################################################
#.#...###.........#...###...#...#.......#...#...#...#.....###...#.............#...#...#...#.............#...#.......#...###...#...#...#...###
#.#.#.###.#######.#.#.###.#.#.#.#.#####.#.#.#.#.#.#.#.###.###.#.#.###########.#.#.#.#.#.#.#.###########.#.#.#.#####.#.#.###.#.#.#.#.#.#.#.###
#...#...#.#.......#.#.#...#...#.#.....#...#.#.#.#.#.#.#...#...#...#.........#.#.#.#.#.#.#.#.......#...#.#.#.#...#...#.#.....#...#...#...#...#
#######.#.#.#######.#.#.#######.#####.#####.#.#.#.#.#.#.###.#######.#######.#.#.#.#.#.#.#.#######.#.#.#.#.#.###.#.###.#####################.#
#.......#.#.#.....#.#.#.#.......#...#.....#.#.#.#.#.#.#...#...#.....#...###...#.#.#.#.#.#...#...#...#.#.#.#...#.#.###.............#.....#...#
#.#######.#.#.###.#.#.#.#.#######.#.#####.#.#.#.#.#.#.###.###.#.#####.#.#######.#.#.#.#.###.#.#.#####.#.#.###.#.#.###############.#.###.#.###
#.#.....#.#.#.#...#.#.#.#...#...#.#...#...#.#.#.#.#.#.#...#...#.....#.#.#...#...#...#...#...#.#.#.....#.#.#...#.#.###...###...#...#...#...###
#.#.###.#.#.#.#.###.#.#.###.#.#.#.###.#.###.#.#.#.#.#.#.###.#######.#.#.#.#.#.###########.###.#.#.#####.#.#.###.#.###.#.###.#.#.#####.#######
#.#.#...#.#.#.#...#.#...#...#.#.#.#...#...#...#.#.#...#.>.>.#.......#.#...#.#.....#...#...###.#.#.....#...#...#.#.###.#.#...#.#.#.....#.....#
#.#.#.###.#.#.###.#.#####.###.#.#.#.#####.#####.#.#######v###.#######.#####.#####.#.#.#.#####.#.#####.#######.#.#.###.#.#.###.#.#.#####.###.#
#.#.#...#.#.#.#...#.#.....###.#...#.#...#.....#.#.......#...#...#...#...#...#...#.#.#...#...#.#.#...#.#.......#.#...#.#.#...#.#.#.#...#.#...#
#.#.###.#.#.#.#v###.#.#######.#####.#.#.#####.#.#######.###.###.#.#.###.#.###.#.#.#.#####.#.#.#.#.#.#.#.#######.###.#.#.###.#.#.#.#.#.#.#.###
#.#.#...#.#...#.>...#...#...#.....#.#.#.#...#.#.#.......###...#...#.###.#.###.#.#.#.....#.#.#.#.#.#.#.#...#.....#...#.#.#...#.#.#.#.#.#.#.###
#.#.#.###.#####v#######.#.#.#####.#.#.#.#.#.#.#.#.###########.#####.###.#.###.#.#.#####.#.#.#.#.#.#.#.###.#.#####.###.#.#.###.#.#.#.#.#.#.###
#.#.#...#.....#.....###.#.#...#...#...#...#.#.#.#...#.......#.#.....#...#...#.#.#.#.....#.#...#.#.#.#.#...#...#...###.#.#...#.#.#...#...#...#
#.#.###.#####.#####.###.#.###.#.###########.#.#.###.#.#####.#.#.#####.#####.#.#.#.#.#####.#####.#.#.#.#.#####.#.#####.#.###.#.#.###########.#
#.#.###...#...#.....#...#.#...#...........#.#.#.#...#.....#.#.#.#...#.....#.#.#.#.#.#...#.....#.#.#.#.#.#.>.>.#...#...#.#...#...#...#.......#
#.#.#####.#.###.#####.###.#.#############.#.#.#.#.#######.#.#.#.#.#.#####.#.#.#.#.#.#.#.#####.#.#.#.#.#.#.#v#####.#.###.#.#######.#.#.#######
#...#...#.#.###...###...#.#...#.>.>.......#...#.#...#.....#...#...#...#...#...#...#...#.>.>.#.#...#...#...#.....#.#.#...#.#.......#.#.......#
#####.#.#.#.#####.#####.#.###.#.#v#############.###.#.###############.#.#################v#.#.#################.#.#.#.###.#.#######.#######.#
#.....#...#.#...#...###...###.#.#.#...#...#...#.....#.....#...#.....#.#.#.....###...#...#.#.#.......#...........#...#.#...#.......#.#...#...#
#.#########.#.#.###.#########.#.#.#.#.#.#.#.#.###########.#.#.#.###.#.#.#.###.###.#.#.#.#.#.#######.#.###############.#.#########.#.#.#.#.###
#.#...#.....#.#...#.......###...#.#.#...#...#.#...###...#.#.#.#.#...#...#...#.....#...#.#.#.#.......#...#.........#...#.#.........#...#.#.###
#.#.#.#.#####.###.#######.#######.#.#########.#.#.###.#.#.#.#.#.#.#########.###########.#.#.#.#########.#.#######.#.###.#.#############.#.###
#...#...#...#...#.#.......#...#...#.###...#...#.#.###.#.#...#...#.....#...#...........#.#.#.#...###...#...#.......#.....#...#.........#.#...#
#########.#.###.#.#.#######.#.#.###.###.#.#.###.#.###.#.#############.#.#.###########.#.#.#.###.###.#.#####.###############.#.#######.#.###.#
###.......#.#...#...#...###.#.#...#.#...#.#...#.#...#.#...#...#.....#.#.#...###.......#.#.#...#.#...#.#...#.....#...#...###...#.......#.....#
###.#######.#.#######.#.###.#.###.#.#.###.###.#.###.#.###.#.#.#.###.#.#.###.###.#######.#.###.#.#.###.#.#.#####.#.#.#.#.#######.#############
#...#.....#.#.........#.....#.###...#...#.....#...#.#.#...#.#.#...#...#...#...#.......#...###...#...#.#.#.###...#.#.#.#...#...#.....#####...#
#.###.###.#.#################.#########.#########.#.#.#.###.#.###v#######.###.#######.#############.#.#.#.###v###.#.#.###.#.#.#####.#####.#.#
#...#.#...#...........#.....#...###...#.......#...#...#.#...#...>.>.#...#.#...#.......#...#####...#.#.#.#...>.>.#.#.#.#...#.#.#...#.......#.#
###.#.#.#############.#.###.###.###.#.#######.#.#######.#.#######v#.#.#.#.#.###.#######.#.#####.#.#.#.#.#####v#.#.#.#.#.###.#.#v#.#########.#
###...#.....#...#...#...#...#...#...#.........#.......#...#...###.#...#...#.###.......#.#...#...#...#.#.###...#.#.#...#.#...#.>.#...#...#...#
###########.#.#.#.#.#####.###.###.###################.#####.#.###.#########.#########.#.###.#.#######.#.###.###.#.#####.#.#####v###.#.#.#.###
#...........#.#.#.#.#...#.....###.........#...#...#...###...#...#.#.........#.........#.#...#.......#.#.#...#...#.#...#.#.#.....###...#...###
#.###########.#.#.#v#.#.#################.#.#.#.#.#.#####.#####.#.#.#########.#########.#.#########.#.#.#.###.###.#.#.#.#.#.#################
#...........#.#...#.>.#.#...###.......#...#.#.#.#.#.....#.....#.#.#...#.....#.......#...#...###...#.#...#...#...#.#.#.#.#.#.........#.......#
###########.#.#####v###.#.#.###.#####.#.###.#.#.#.#####.#####.#.#.###.#.###.#######.#.#####.###.#.#.#######.###.#.#.#.#.#.#########.#.#####.#
#...#...###...#...#.#...#.#...#.....#...#...#...#.#.....#...#.#.#...#...#...#.......#.#.....#...#.#.#.......#...#...#.#.#.#.........#.#.....#
#.#.#.#.#######.#.#.#.###.###.#####.#####.#######.#.#####.#.#.#.###.#####.###.#######.#.#####.###.#.#.#######.#######.#.#.#.#########.#.#####
#.#.#.#.#...#...#...#.###.#...#...#.....#.......#...#...#.#.#.#.#...#.....###.....#...#...#...###.#.#.......#...#...#.#...#...........#.....#
#.#.#.#.#.#.#.#######.###.#.###.#.#####v#######.#####.#.#.#.#.#.#.###.###########v#.#####.#.#####.#.#######.###.#.#.#.#####################.#
#.#...#...#.#.#.....#...#.#...#.#...#.>.>...#...#.....#...#...#.#.###...#...#...>.>.#.....#...###...#.......###...#...#.....................#
#.#########.#.#.###.###.#.###.#.###.#.#v###.#.###.#############.#.#####.#.#.#.###v###.#######.#######.#################.#####################
#.#.......#.#...#...###...#...#.###...#.#...#.###...........#...#.....#...#.#.###...#.......#.#.......#.....#.......###...............#...###
#.#.#####.#.#####.#########.###.#######.#.###.#############.#.#######.#####.#.#####.#######.#.#.#######.###.#.#####.#################.#.#.###
#.#.#.....#.###...###...###.....#.......#.....#...#.........#.........###...#...###.......#...#.........#...#.#...#.#...............#...#...#
#.#.#.#####.###.#####.#.#########.#############.#.#.#####################.#####.#########.###############.###.#.#.#.#.#############.#######.#
#.#.#.#...#.....###...#.#.....###.......#.....#.#.#.............#...###...#...#...#.......###...#####...#.###.#.#...#.............#.#.......#
#.#.#.#.#.#########.###.#.###.#########.#.###.#.#.#############.#.#.###.###.#.###.#.#########.#.#####.#.#.###.#.#################.#.#.#######
#...#...#.....#...#.#...#.#...#...#.....#.#...#.#.#.........#...#.#...#.....#.....#.......#...#.#.....#...#...#...###.....#...#...#...#.....#
#############.#.#.#.#.###.#.###.#.#v#####.#.###.#.#.#######.#.###.###.###################.#.###.#.#########.#####.###.###.#.#.#.#######.###.#
#.......#.....#.#.#.#...#.#.....#.>.>.....#.....#.#.....###...###...#...#...#...#.........#...#.#.........#.....#...#...#.#.#.#.###.....#...#
#.#####.#v#####.#.#.###.#.#########v#############.#####.###########.###.#.#.#.#.#.###########.#.#########.#####.###.###.#.#.#.#.###.#####.###
#.....#.#.>.....#.#...#.#.###...###...#...........#...#.....#.....#...#...#.#.#.#.......#...#.#...###...#.#...#.#...#...#...#.#.....#.....###
#####.#.#v#######.###.#.#.###.#.#####.#.###########.#.#####.#.###.###.#####.#.#.#######.#.#.#.###.###.#.#.#.#.#.#.###.#######.#######.#######
#.....#...###...#.....#.#.#...#.......#.......#...#.#.#.....#.#...###...#...#.#.#...#...#.#.#.#...#...#...#.#...#...#.......#.#.....#.......#
#.###########.#.#######.#.#.#################.#.#.#.#.#.#####.#.#######.#.###.#.#.#.#v###.#.#.#.###.#######.#######.#######.#.#.###.#######.#
#.....#...#...#.......#.#.#.#.............#...#.#.#.#.#.#...#.#...#...#.#...#.#...#.>.>.#.#.#.#.###...#...#...#.....#...###.#.#.###.........#
#####.#.#.#.#########.#.#.#.#.###########.#.###.#.#.#.#v#.#.#.###.#.#.#.###.#.#######v#.#.#.#.#.#####v#.#.###.#.#####.#.###.#.#v#############
#...#...#.#.#...#...#.#.#.#.#.#...........#.#...#...#.>.>.#.#...#.#.#.#.#...#.#.......#.#.#.#.#.#...>.>.#.....#.#...#.#...#.#.>.#...###.....#
#.#.#####.#.#.#.#.#.#.#.#.#.#.#.###########.#.#########v###.###.#.#.#.#.#.###.#.#######.#.#.#.#.#.###v#########.#.#.#.###.#.###v#.#.###.###.#
#.#.#.....#.#.#...#...#...#...#...........#...###...###...#...#.#.#.#...#.....#.......#...#.#.#...###.........#.#.#.#...#.#.###...#.....#...#
#.#.#.#####.#.###########################.#######.#.#####.###.#.#.#.#################.#####.#.###############.#.#.#.###.#.#.#############.###
#.#...#...#.#...#.......#.....#...#...#...#.......#.....#...#.#.#.#.......#...........#...#.#.....#...........#.#.#.#...#...#...#.........###
#.#####.#.#.###.#.#####.#.###.#.#.#.#.#.###.###########.###.#.#.#.#######.#.###########.#.#.#####.#.###########.#.#.#.#######.#.#.###########
#.#...#.#...###...#...#.#...#...#...#...###.......#...#.#...#...#.#.......#.........#...#...#.....#...#.....#...#.#.#...#.....#...###...#...#
#.#.#.#.###########.#.#.###.#####################.#.#.#.#.#######.#.###############.#.#######.#######.#.###.#.###.#.###.#.###########.#.#.#.#
#.#.#...###...###...#.#.#...#...........#...#####...#.#.#.......#.#.#.........#.....#.....#...#.....#...#...#...#.#.#...#.#...........#...#.#
#.#.#######.#.###.###.#.#.###.#########.#.#.#########.#.#######.#.#.#.#######.#.#########.#.###.###.#####.#####.#.#.#.###.#.###############.#
#.#...#.....#.....###...#.....#.........#.#.#.........#.........#...#.......#...#...#...#...###...#.#...#.....#...#...###...#...#.......#...#
#.###.#.#######################.#########.#.#.#############################.#####.#.#.#.#########.#.#.#.#####.###############.#.#.#####.#.###
#.#...#.....#...#...###...#...#...........#.#.............#.....#.....#...#.......#.#.#.....###...#.#.#...###...#.......#.....#...#####...###
#.#.#######.#.#.#.#.###.#.#.#.#############.#############.#.###.#.###.#.#.#########.#.#####.###.###.#.###.#####.#.#####.#.###################
#.#.#...#...#.#...#...#.#.#.#...#...........#.............#.#...#...#...#.#...#.....#...#...#...#...#...#.....#...#.....#...............#...#
#.#.#.#.#.###.#######.#.#.#.###.#.###########.#############.#.#####.#####.#.#.#v#######.#.###.###.#####.#####.#####.###################.#.#.#
#.#.#.#...#...###.....#.#.#...#.#...........#...............#.....#.#...#.#.#.>.>.#.....#.###...#.#...#.#.....###...###...#.....#.......#.#.#
#.#.#.#####.#####.#####.#.###.#.###########.#####################.#.#.#.#.#.###v#.#.#####.#####.#.#.#.#.#.#######v#####.#.#.###.#.#######.#.#
#...#.......#...#...###.#.###.#.#...........#.....#...............#...#.#.#...#.#.#.#.....#...#.#...#.#.#.#.....>.>.###.#.#.#...#.........#.#
#############.#.###.###.#.###.#.#.###########.###.#.###################.#.###.#.#.#.#.#####.#.#.#####.#.#.#.#####v#.###.#.#.#.#############.#
#.....#...#...#...#.....#...#.#.#...###...###...#.#.........#...#...###.#.#...#.#...#...#...#.#.#.....#.#.#.#.....#...#.#.#.#.#.............#
#.###.#.#.#.#####.#########.#.#.###v###.#.#####.#.#########.#.#.#.#.###.#.#.###.#######.#.###.#.#.#####.#.#.#.#######.#.#.#.#.#.#############
#...#...#...#...#...........#.#.#.>.>.#.#...#...#.#.........#.#.#.#.#...#.#.#...###...#.#.###.#.#.....#.#...#.....###...#.#.#.#...#.........#
###.#########.#.#############.#.#.#v#.#.###.#.###.#.#########.#.#.#.#.###.#.#.#####.#.#.#.###.#.#####.#.#########.#######.#.#.###.#.#######.#
#...#...#.....#.....#...###...#.#.#.#.#.#...#...#.#...#...###.#.#.#...###...#.......#.#.#...#.#.....#.#...#######.....#...#.#...#...#.......#
#.###.#.#.#########.#.#.###.###.#.#.#.#.#.#####.#.###v#.#.###.#.#.###################.#.###.#.#####.#.###.###########.#.###.###.#####.#######
#.....#...#.......#.#.#...#...#...#.#.#.#...#...#.#.>.>.#.#...#.#.........#...........#.#...#.#...#.#.#...#...........#.....#...#...#.......#
###########.#####.#v#.###.###.#####.#.#.###.#.###.#.#v###.#.###.#########.#.###########.#.###.#.#.#.#.#.###.#################.###v#.#######.#
#...........#...#.#.>.###.#...#.....#...###.#.###.#.#.###...#...#...#.....#...........#.#...#...#...#.#.###...........#.......#.>.#.........#
#.###########.#.#.#v#####.#.###.###########.#.###.#.#.#######.###.#.#.###############.#.###.#########.#.#############.#.#######.#v###########
#.............#.#.#.....#.#.###...#...#...#...###.#.#...###...#...#.#...#.............#...#.###...###...###.........#.#.#...#...#...###.....#
###############.#.#####.#.#.#####.#.#.#.#.#######.#.###.###.###.###.###.#.###############.#.###.#.#########.#######.#.#.#.#.#.#####.###.###.#
#...............#.#.....#...#...#...#...#.......#...###...#...#...#.....#.......###.....#...#...#.#...#.....#.....#...#...#.#...###...#.#...#
#.###############.#.#########.#.###############.#########.###.###.#############.###.###.#####.###.#.#.#.#####.###.#########.###.#####.#.#.###
#...............#...#####...#.#...............#...#.......###.....###...###...#.....#...#...#...#...#.#.......###...#.....#.....#...#...#...#
###############.#########.#.#.###############.###.#.#################.#.###.#.#######.###.#.###.#####.#############.#.###.#######.#.#######.#
###...#...#...#.........#.#.#.....#...#...###...#.#...........#.....#.#.....#.....#...#...#.#...#.....#.............#...#.#...###.#.#...#...#
###.#.#.#.#.#.#########.#.#.#####.#.#.#.#.#####.#.###########.#.###.#.###########.#.###.###.#.###.#####.###############.#.#.#.###.#.#v#.#.###
#...#...#.#.#...#.......#.#.#...#...#...#.....#...###.........#...#.#...........#...###.#...#...#.#...#.............#...#...#.....#.>.#.#...#
#.#######.#.###.#.#######.#.#.#.#############.#######.###########.#.###########.#######.#.#####.#.#.#.#############.#.###############v#.###.#
#.......#.#...#...#.....#.#.#.#.###...#.....#.#...#...#.....#.....#...#.......#...#.....#.#...#.#.#.#...#...#...#...#.......#.........#.#...#
#######.#.###.#####.###.#.#.#.#.###.#.#.###.#.#.#.#.###.###.#.#######.#.#####.###.#.#####.#.#.#.#.#.###.#.#.#.#.#.#########.#.#########.#.###
#.......#.....###...#...#.#.#.#.###.#.#...#...#.#.#.....#...#.......#.#.#.....#...#...#...#.#.#.#.#...#.#.#.#.#.#.#...#.....#.........#.#...#
#.###############.###.###.#.#.#.###.#.###v#####.#.#######.#########.#.#.#.#####v#####.#.###.#.#.#.###.#.#.#.#.#.#v#.#.#.#############.#.###.#
#.......#...#...#...#...#.#.#.#.#...#...>.>.###.#.###...#.#...#...#.#.#.#.....>.>.#...#...#.#...#.#...#.#.#...#.>.>.#.#.#...........#.#.#...#
#######.#.#.#.#.###.###.#.#.#.#.#.#######v#.###.#.###.#.#v#.#.#.#.#.#.#.#######v#.#.#####.#.#####.#.###.#.#######v###.#.#.#########.#.#.#.###
#...#...#.#.#.#.#...###.#.#.#.#.#.#.....#.#...#.#...#.#.>.>.#...#.#.#.#...#.....#.#...###.#.....#.#.#...#.#.......###.#.#.#.......#.#.#...###
#.#.#v###.#.#.#.#.#####.#.#.#.#.#.#.###.#.###.#.###.#.###v#######.#.#.###.#.#####.###.###.#####.#.#.#.###.#.#########.#.#.#.#####.#.#.#######
#.#.#.>...#.#.#.#...#...#.#.#.#.#.#...#...#...#.#...#.#...#...###.#.#.....#.....#.#...#...#.....#...#...#.#.........#...#.#.#.....#.#.......#
#.#.#v#####.#.#.###.#.###.#.#.#.#.###.#####.###.#.###.#.###.#.###.#.###########.#.#.###.###.###########.#.#########.#####.#.#.#####.#######.#
#.#.#...#...#.#.#...#...#.#...#...###.....#.#...#.....#.....#...#.#.#...........#...###...#.........###.#.#.........#...#...#.....#.#.......#
#.#.###.#.###.#.#.#####.#.###############.#.#.#################.#.#.#.###################.#########.###.#.#.#########.#.#########.#.#.#######
#.#.....#...#.#.#.#...#.#.#...###.........#...#.........#.....#.#.#.#.#.........#.......#.#...#.....#...#.#...#.....#.#...#...#...#...#...###
#.#########.#.#.#.#.#.#.#.#.#.###.#############.#######.#.###.#.#.#.#.#.#######.#.#####.#.#.#.#.#####.###.###.#.###.#.###.#.#.#.#######.#.###
#.#...###...#.#.#.#.#...#.#.#...#...#...###...#.......#...###...#...#...###...#...#...#.#.#.#...#...#.....#...#.#...#.#...#.#.#.......#.#...#
#.#.#.###.###.#.#.#.#####.#.###.###.#.#.###.#.#######.#####################.#.#####.#.#.#.#.#####.#.#######.###.#.###.#.###.#.#######.#.###.#
#.#.#...#.....#...#.......#...#.###...#.....#.###...#...#.......#...#.......#.......#...#...#...#.#.###...#.....#...#.#...#.#.........#.#...#
#.#.###.#####################.#.#############.###.#.###.#.#####.#.#.#.#######################.#.#.#.###.#.#########.#.###.#.###########.#.###
#...###...........#.......#...#...#.......#...#...#.....#.....#...#.#...........#.....#...#...#.#.#.#...#.#...#...#...#...#...........#.#.###
#################.#.#####.#.#####.#.#####.#.###.#############.#####.###########.#.###.#.#.#.###.#.#.#.###.#.#.#.#.#####.#############.#.#.###
#...#####.........#.....#.#.....#.#.....#...#...#.........###.#.....#...........#...#.#.#.#.#...#.#.#...#...#...#.#.....###...........#.#...#
#.#.#####.#############.#.#####.#.#####v#####.###.#######.###.#.#####.#############.#.#.#.#.#.###.#.###v#########.#.#######.###########.###.#
#.#.......#.....#####...#.#...#.#.#...>.>.###.....###...#.#...#...###...#...#.....#.#...#.#.#...#.#.#.>.>.......#...###.....#...........#...#
#.#########.###.#####.###.#.#.#.#.#.#####.###########.#.#.#.#####.#####.#.#.#.###.#.#####.#.###.#.#.#.#########.#######.#####.###########.###
#.#...#...#...#...#...###...#.#.#.#...###...#...#.....#...#...#...#...#...#.#...#.#...#...#.#...#.#.#.#####.....#.....#.#...#.#.........#...#
#.#.#.#.#.###.###.#.#########.#.#.###.#####.#.#.#.###########.#.###.#.#####v###.#.###.#.###.#.###.#.#.#####.#####.###.#.#.#.#.#.#######.###.#
#...#...#...#...#.#.........#.#.#.#...#.....#.#.#.....###...#.#...#.#...#.>.>.#.#.....#...#.#...#.#.#.#.....#...#...#.#.#.#...#.......#.#...#
###########.###.#.#########.#.#.#.#.###.#####.#.#####v###.#.#.###.#.###.#.###.#.#########.#.###.#.#.#.#.#####.#.###.#.#.#.###########.#.#.###
#...........###.#.#.........#...#.#...#...#...#...#.>.>.#.#.#.#...#...#.#...#.#.#.........#...#.#.#.#.#.#.....#.#...#.#...#...#.......#...###
#.#############.#.#.#############.###.###.#.#####.#.###.#.#.#.#.#####.#.###.#.#.#.###########.#.#.#.#.#.#.#####.#.###.#####.#.#.#############
#.#.......#...#.#.#.............#...#.#...#.#.....#...#.#.#...#.#.....#.....#...#.#.....#.....#.#.#.#.#...#.....#...#.#...#.#.#.#...#...#...#
#.#.#####.#.#.#.#.#############.###.#.#.###.#.#######.#.#.#####.#.###############.#.###.#.#####.#.#.#.#####.#######.#.#.#.#.#.#v#.#.#.#.#.#.#
#...#####.#.#...#.#...#...#...#.#...#.#...#.#.....#...#.#.#.....#...........#.....#.#...#...#...#.#.#...#...#...#...#.#.#.#.#.>.#.#.#.#...#.#
#########.#.#####.#.#.#.#.#.#.#.#.###.###.#.#####.#.###.#.#.###############.#.#####.#.#####.#.###.#.###.#.###.#.#.###.#.#.#.###v#.#.#.#####.#
###...#...#.....#.#.#.#.#.#.#...#.#...#...#.....#.#.###.#.#.....#.....#.....#.....#.#...#...#...#.#.....#...#.#.#...#.#.#...###...#.#.#.....#
###.#.#.#######.#.#.#.#.#.#.#####.#.###.#######.#.#.###.#.#####.#.###.#.#########.#.###.#.#####.#.#########.#.#.###.#.#.###########.#.#.#####
#...#...#.....#.#.#.#.#.#.#.....#.#.#...#...#...#.#...#.#.#.....#...#.#.........#.#.#...#.....#.#.....#.....#.#.#...#.#.....#.......#.#.#...#
#.#######.###.#.#.#.#.#.#.#####.#.#.#.###.#.#.###.###.#.#.#.#######.#.#########.#.#.#.#######.#.#####.#.#####.#.#.###.#####.#.#######.#.#.#.#
#.........###...#...#...#.......#...#.....#...###.....#...#.........#...........#...#.........#.......#.......#...###.......#.........#...#.#
###########################################################################################################################################.#)";
} // namespace input