from ipdb import set_trace


class Direction:
    def __init__(self, name):
        if name == "north":
            self.name = name
            self.increment_x = 0
            self.increment_y = 1
        elif name == "west":
            self.name = name
            self.increment_x = -1
            self.increment_y = 0
        elif name == "south":
            self.name = name
            self.increment_x = 0
            self.increment_y = -1
        elif name == "east":
            self.name = name
            self.increment_x = 1
            self.increment_y = 0


# class North:
#     name = "north"
#     increment_x = 0
#     increment_y = 1


# class West:
#     name = "west"
#     increment_x = -1
#     increment_y = 0


# class South:
#     name = "south"
#     increment_x = 0
#     increment_y = -1


# class East:
#     name = "east"
#     increment_x = 1
#     increment_y = 0


def get_val_from_point(grid, point_x, point_y):
    return grid[point_x][point_y]


def is_visible_in_direction(grid, point_x, point_y, direction):
    point_val = get_val_from_point(grid, point_x, point_y)
    incr_x = direction.increment_x
    incr_y = direction.increment_y
    curr_pos_x = point_x
    curr_pos_y = point_y


def is_visible_in_direction_rec(grid, point_x, point_y, direction):
    NUM_OF_ROWS = len(grid)
    NUM_OF_COLS = len(grid[0])
    point_val = get_val_from_point(grid, point_x, point_y)
    incr_x = direction.increment_x
    incr_y = direction.increment_y
    curr_pos_x = point_x
    curr_pos_y = point_y
    new_pos_x = point_x + incr_x
    new_pos_y = point_y + incr_y
    is_new_pos_boundary = (
        new_pos_x < 0
        or new_pos_x > NUM_OF_COLS - 1
        or new_pos_y < 0
        or new_pos_y > NUM_OF_ROWS - 1
    )
    if is_new_pos_boundary:
        return True
    elif get_val_from_point(grid, new_pos_x, new_pos_y) >= get_val_from_point(
        grid, curr_pos_x, curr_pos_y
    ):
        return False
    else:
        is_visible_in_direction_rec(grid, new_pos_x, new_pos_y, direction)


# dirs = [North(), West(), South(), East()]
NORTH = 0
EAST = 1
SOUTH = 2
WEST = 3
dirs = [Direction("north"), Direction("east"), Direction("south"), Direction("west")]


input_file_path = r"./day8/input_test.txt"
# input_file_path = r"./day8/input.txt"
file_object = open(input_file_path, "r")

grid = [x.strip() for x in file_object.readlines()]
set_trace()

print(grid)
