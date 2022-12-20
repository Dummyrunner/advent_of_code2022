# ipdb Debugger. add line set_trace() to enter debugger there
from ipdb import set_trace


class Direction:
    """Class for directions, with increments to add on a coordinate to move in this direction"""

    def __init__(self, name):
        if name == "north":
            self.name = name
            self.increment_x = 0
            self.increment_y = -1
        elif name == "west":
            self.name = name
            self.increment_x = -1
            self.increment_y = 0
        elif name == "south":
            self.name = name
            self.increment_x = 0
            self.increment_y = 1
        elif name == "east":
            self.name = name
            self.increment_x = 1
            self.increment_y = 0


def get_val_from_point(grid, point_x, point_y):
    """evaluate grid value at given coordinates"""
    return int(grid[point_y][point_x])


def is_on_boundary(grid, point_x, point_y):
    NUM_OF_ROWS = len(grid)
    NUM_OF_COLS = len(grid[0])
    on_boundary = (
        point_x == 0
        or point_x == NUM_OF_COLS - 1
        or point_y == 0
        or point_y == NUM_OF_ROWS - 1
    )
    return on_boundary


def is_out_of_bound(grid, point_x, point_y):  #
    NUM_OF_ROWS = len(grid)
    NUM_OF_COLS = len(grid[0])
    out_of_bound = (
        point_x < 0
        or point_x > NUM_OF_COLS - 1
        or point_y < 0
        or point_y > NUM_OF_ROWS - 1
    )
    return out_of_bound


def is_visible(grid, point_x, point_y, directions):
    """Check whether point given by coordinates point_x, point_y is visible in grid"""
    for dir in directions:
        start_val = get_val_from_point(grid, point_x, point_y)
        if is_visible_in_direction_rec(grid, point_x, point_y, start_val, dir):
            print(
                "---- VIS: point (",
                point_x,
                ",",
                point_y,
                ")",
                " is visible in direction ",
                dir.name,
            )
            return True
    print(
        "---- VIS: point (",
        point_x,
        ",",
        point_y,
        ")",
        " is  NOT visible",
    )
    return False


def is_visible_in_direction_rec(grid, curr_pos_x, curr_pos_y, start_val, direction):
    """Check recursively, whether point given by curr_pos is visible in direction "direction" """
    incr_x = direction.increment_x
    incr_y = direction.increment_y

    new_pos_x = curr_pos_x + incr_x
    new_pos_y = curr_pos_y + incr_y

    if is_out_of_bound(grid, new_pos_x, new_pos_y):
        return True
    else:
        new_point_val = get_val_from_point(grid, new_pos_x, new_pos_y)

        if new_point_val >= start_val:
            return False
        else:
            print(
                "-- Current position: ",
                curr_pos_x,
                ",",
                curr_pos_y,
                "check next point\t",
                new_pos_x,
                ", ",
                new_pos_y,
                " for checking dir: ",
                direction.name,
            )
            return is_visible_in_direction_rec(
                grid, new_pos_x, new_pos_y, start_val, direction
            )


def vis_range_in_dir(grid, point_x, point_y, dir):
    vis_ctr = 0
    considered_tree_val = get_val_from_point(grid, point_x, point_y)
    next_x = point_x + dir.increment_x
    next_y = point_y + dir.increment_y
    while (
        not is_out_of_bound(grid, next_x, next_y)
        and get_val_from_point(grid, next_x, next_y) < considered_tree_val
    ):
        vis_ctr += 1
        next_x += dir.increment_x
        next_y += dir.increment_y

    # blocking trees are counted as visible tree
    if is_out_of_bound(grid, next_x, next_y):
        return vis_ctr
    else:
        return vis_ctr + 1


def scenic_score(grid, point_x, point_y, directions):
    score = 1
    for dir in directions:
        if is_on_boundary(grid, point_x, point_y):
            score = 0
        else:
            print(
                "\tvis-range point (",
                point_x,
                ",",
                point_y,
                ") in dir ",
                dir.name,
                "is:  ",
                vis_range_in_dir(grid, point_x, point_y, dir),
            )
            score *= vis_range_in_dir(grid, point_x, point_y, dir)

    return score


directions_NESW = [
    Direction("north"),
    Direction("east"),
    Direction("south"),
    Direction("west"),
]


input_file_path = r"./day8/input_test.txt"
input_file_path = r"./day8/input.txt"

# Parse Input file
file_object = open(input_file_path, "r")
# remove \n from strings with strip()
grid = [x.strip() for x in file_object.readlines()]
NUM_OF_ROWS = len(grid)
NUM_OF_COLS = len(grid[0])
# trees on boundary are visible
visibile_ctr = 2 * (NUM_OF_ROWS - 1) + 2 * (NUM_OF_COLS - 1)
scenic_score_max = 0
print("number of boundary trees:\t", visibile_ctr)

# Iterate over interior points of grid, sum up visible trees (EXC A)
for irow in range(1, NUM_OF_ROWS - 1):
    for icol in range(1, NUM_OF_COLS - 1):
        # EXC A
        # print(
        #     "Current Point:\t(",
        #     icol,
        #     ",",
        #     irow,
        #     "), Value: ",
        #     get_val_from_point(grid, icol, irow),
        # )
        if is_visible(grid, icol, irow, directions_NESW):
            visibile_ctr += 1


# set_trace()
# # EXC B
# for irow in range(NUM_OF_ROWS - 1):
#     for icol in range(NUM_OF_COLS - 1):
#         curr_scenic_score = scenic_score(grid, icol, irow, directions_NESW)
#         print("Point (", icol, ",", irow, ") curr scenic score:\t", curr_scenic_score)
#         # set_trace()
#         if scenic_score_max < curr_scenic_score:
#             scenic_score_max = curr_scenic_score
for irow in range(1, NUM_OF_ROWS - 1):
    for icol in range(1, NUM_OF_COLS - 1):
        curr_scenic_score = scenic_score(grid, icol, irow, directions_NESW)
        print(
            ">> Point (", icol, ",", irow, ") curr scenic score:\t", curr_scenic_score
        )
        # set_trace()
        if scenic_score_max < curr_scenic_score:
            scenic_score_max = curr_scenic_score

print("EXC 8A: visible trees\t", visibile_ctr)
print("EXC 8B: max scenic score over all trees\t", scenic_score_max)
