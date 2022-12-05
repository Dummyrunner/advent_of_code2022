# A   X   1     ROCK
# B   Y   2     PAPER
# C   Z   3     SCISSOR

# A <<< B <<< C <<< A

input_file_path = r"./day2/input_test.txt"
# input_file_path = r"./day2/input.txt"
file_object = open(input_file_path, "r")

lines = file_object.readlines()
print(lines)
