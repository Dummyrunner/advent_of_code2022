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
    # print("check direction\t", direction.name, "now (recursive)")

    NUM_OF_ROWS = len(grid)
    NUM_OF_COLS = len(grid[0])
    incr_x = direction.increment_x
    incr_y = direction.increment_y
    point_val = get_val_from_point(grid, curr_pos_x, curr_pos_y)

    new_pos_x = curr_pos_x + incr_x
    new_pos_y = curr_pos_y + incr_y

    new_pos_x_out_of_bound = new_pos_x < 0 or new_pos_x > NUM_OF_COLS - 1
    new_pos_y_out_of_bound = new_pos_y < 0 or new_pos_y > NUM_OF_ROWS - 1

    # print(
    #     "curr: (",
    #     curr_pos_x,
    #     ",",
    #     curr_pos_y,
    #     ")\t new: (",
    #     new_pos_x,
    #     ",",
    #     new_pos_y,
    #     ")\t",
    #     "posx out of b:",
    #     new_pos_x_out_of_bound,
    #     "; posy out of b:",
    #     new_pos_y_out_of_bound,
    # )
    # set_trace()
    if new_pos_x_out_of_bound or new_pos_y_out_of_bound:
        return True
    else:
        new_point_val = get_val_from_point(grid, new_pos_x, new_pos_y)

        if new_point_val >= start_val:
            # print(
            #     "point (",
            #     curr_pos_x,
            #     ",",
            #     curr_pos_y,
            #     ") NOT visible in dir ",
            #     direction.name,
            #     "due to higher tree",
            # )
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
print("number of boundary trees:\t", visibile_ctr)

# Iterate over interior points of grid
for irow in range(1, NUM_OF_ROWS - 1):
    for icol in range(1, NUM_OF_COLS - 1):
        print(
            "Current Point:\t(",
            icol,
            ",",
            irow,
            "), Value: ",
            get_val_from_point(grid, icol, irow),
        )
        if is_visible(grid, icol, irow, directions_NESW):
            visibile_ctr += 1
print("EXC 8A: visible trees\t", visibile_ctr)
# set_trace()
