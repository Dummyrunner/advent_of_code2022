from ipdb import set_trace


class North:
    name = "north"
    increment_x = 0
    increment_y = 1


class West:
    name = "west"
    increment_x = 1
    increment_y = 0


class South:
    name = "south"
    increment_x = 0
    increment_y = -1


class East:
    name = "east"
    increment_x = -1
    increment_y = 0


def get_val_from_point(grid, point_x, point_y):
    return grid[point_x][point_y]


def is_visible_in_direction(grid, point_x, point_y, direction):
    point_val = get_val_from_point(grid, point_x, point_y)
    incr_x = direction.increment_x
    incr_y = direction.increment_y
    curr_pos = TODO


dirs = [North(), West(), South(), East()]

input_file_path = r"./day8/input_test.txt"
# input_file_path = r"./day8/input.txt"
file_object = open(input_file_path, "r")
grid = [x.strip() for x in file_object.readlines()]
set_trace()

print(grid)
