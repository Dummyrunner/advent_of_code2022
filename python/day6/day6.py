from ipdb import set_trace
from collections import Counter

# input_file_path = r"./day6/input_test.txt"
input_file_path = r"./day6/input.txt"


file_object = open(input_file_path, "r")
message_string = file_object.readlines(1)[0]
CHAIN_LENGTH = 4


def chars_unique(string):
    x = filter(lambda x: string.count(x) >= 2, string)
    duplicates = "".join(set(x))
    if duplicates:
        return False
    else:
        return True


for char_idx in range(len(message_string)):
    str_part = message_string[char_idx : (char_idx + CHAIN_LENGTH)]
    if chars_unique(str_part):
        relevant_idx = char_idx + CHAIN_LENGTH
        print("EXC6A:  ", relevant_idx)
        break

# EXC B
CHAIN_LENGTH_B = 14
for char_idx in range(len(message_string)):
    str_part = message_string[char_idx : (char_idx + CHAIN_LENGTH_B)]
    if chars_unique(str_part):
        relevant_idx = char_idx + CHAIN_LENGTH_B
        print("EXC6B:  ", relevant_idx)
        break
