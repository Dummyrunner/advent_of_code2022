import numpy as np
from ipdb import set_trace

# A   X   1     ROCK
# B   Y   2     PAPER
# C   Z   3     SCISSOR

# A <<< B <<< C <<< A


def removeLastN(string_to_reduce, n):
    string_to_reduce = string_to_reduce[: len(string_to_reduce) - n]
    return string_to_reduce


def opp_choice(letter):
    if letter == "A":
        return np.array([[1, 0, 0]])
    elif letter == "B":
        return np.array([[0, 1, 0]])
    elif letter == "C":
        return np.array([[0, 0, 1]])


def own_choice(letter):
    if letter == "X":
        return np.array([[1, 0, 0]])
    elif letter == "Y":
        return np.array([[0, 1, 0]])
    elif letter == "Z":
        return np.array([[0, 0, 1]])


def score_from_choices(opponent, own):
    choice_score_matrix = np.array([[1, 2, 3], [1, 2, 3], [1, 2, 3]])
    win_score_matrix = np.array([[3, 6, 0], [0, 3, 6], [6, 0, 3]])
    total_score_matrix = choice_score_matrix + win_score_matrix
    return opp_choice(opponent).dot(total_score_matrix).dot(own_choice(own).transpose())


def parse_letters_from_line(line):
    return (line[0], line[2])


input_file_path = r"./day2/input_test.txt"
# input_file_path = r"./day2/input.txt"
file_object = open(input_file_path, "r")
lines = file_object.readlines()
lines = [removeLastN(line, 1) for line in lines]

score = 0
for line in lines:
    letters_tuple = parse_letters_from_line(line)
    opp_letter = letters_tuple[0]
    own_letter = letters_tuple[1]
    score_this_round = score_from_choices(opp_letter, own_letter)
    score += score_this_round
print(score)
