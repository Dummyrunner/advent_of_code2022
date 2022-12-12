from ipdb import set_trace


class Direction:
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
    return int(grid[point_x][point_y])


def is_visible(grid, point_x, point_y, directions):
    for dir in directions:
        print(
            "point (", point_x, ",", point_y, ")", " is visible in direction ", dir.name
        )
        if is_visible_in_direction_rec(grid, point_x, point_y, dir):
            return True
    return False


# def visualize_interior_binary(grid):
#     NUM_OF_ROWS = len(grid)
#     NUM_OF_COLS = len(grid[0])
#     binary_grid = [[] for i in range(NUM_OF_ROWS)]
#     for irow in range(1, NUM_OF_ROWS):
#             if is_visible(grid, irow, icol, directions):
#                 binary_grid.append(1)
#             else:
#                 binary_grid.append(0)
#     print(binary_grid)


def is_visible_in_direction_rec(grid, point_x, point_y, direction):
    NUM_OF_ROWS = len(grid)
    NUM_OF_COLS = len(grid[0])
    point_val = get_val_from_point(grid, point_x, point_y)
    incr_x = direction.increment_x
    incr_y = direction.increment_y
    curr_pos_x = point_x
    curr_pos_y = point_y
    new_pos_x = curr_pos_x + incr_x
    new_pos_y = curr_pos_y + incr_y
    new_pos_out_of_bound = (
        new_pos_x < 0
        or curr_pos_x > NUM_OF_COLS - 1
        or curr_pos_y < 0
        or curr_pos_y > NUM_OF_ROWS - 1
    )
    if new_pos_out_of_bound:
        return True
    elif get_val_from_point(grid, new_pos_x, new_pos_y) >= point_val:
        return False
    else:
        # print("dir\t", direction.name)
        # print("curr pos x: ", curr_pos_x, "curr pos y: ", curr_pos_y, "\n")
        # print("new pos x: ", new_pos_x, "curr pos y: ", new_pos_y, "\n")
        print(
            "Current position: ",
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
        return is_visible_in_direction_rec(grid, new_pos_x, new_pos_y, direction)


# dirs = [North(), West(), South(), East()]
NORTH = 0
EAST = 1
SOUTH = 2
WEST = 3
directions = [
    Direction("north"),
    Direction("east"),
    Direction("south"),
    Direction("west"),
]


input_file_path = r"./day8/input_test.txt"
# input_file_path = r"./day8/input.txt"
file_object = open(input_file_path, "r")
grid = [x.strip() for x in file_object.readlines()]
NUM_OF_ROWS = len(grid)
NUM_OF_COLS = len(grid[0])
# set_trace()
zero_line = [0 for i in range(NUM_OF_COLS - 2)]
zero_grid = [zero_line for i in range(NUM_OF_ROWS - 2)]
print(zero_grid)
point_x = 1
point_y = 1
visibile_ctr = 2 * (NUM_OF_ROWS - 1) + 2 * (NUM_OF_COLS - 1)
for irow in range(1, NUM_OF_ROWS - 1):
    for icol in range(1, NUM_OF_COLS - 1):
        if is_visible(grid, icol, irow, directions):
            visibile_ctr += 1
            # INDEXING WRONG??
            # print("icol, irow = ", icol, ", ", irow)
            zero_grid[icol - 1][irow - 1] = 1

    # print("in ", dir.name, "visible is", vis)
    # visibilities.append(vis)
print("interior:\n", zero_grid)
print("EXC 8A: visible trees\t", visibile_ctr)
set_trace()
