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


def get_choice_for_opp_choice_and_outcome(opp_letter, outcome_letter):
    # Aim: X -> lose, Y -> draw, Z -> win
    # lose: +1, win: -1, draw: +-0
    # outcome_as_ABC = convert_XYZ_to_ABC(outcome_letter)
    ASCII_OF_X = 88
    ASCII_OF_A = 65
    outcome_letter_to_increment = {"X": -1, "Y": 0, "Z": 1}
    normed_opp_nr = ord(opp_letter) - ASCII_OF_A  # X, Y; Z -> 0,1,2
    increment = outcome_letter_to_increment.get(outcome_letter)
    choice_nr = (normed_opp_nr + increment) % 3
    choice_letter_XYZ = chr(choice_nr + ASCII_OF_X)
    return choice_letter_XYZ


def convert_XYZ_to_ABC(letter):
    return chr(ord(letter) - 23)


def convert_ABC_to_XYZ(letter):
    return chr(ord(letter) + 23)


input_file_path = r"./day2/input_test.txt"
input_file_path = r"./day2/input.txt"
file_object = open(input_file_path, "r")
lines = file_object.readlines()
lines = [removeLastN(line, 1) for line in lines]

score_A = 0
score_B = 0
# For Exc A
for line in lines:
    letters_tuple = parse_letters_from_line(line)
    first_letter = letters_tuple[0]
    second_letter = letters_tuple[1]
    score_this_round_A = score_from_choices(first_letter, second_letter)
    # set_trace()
    score_this_round_B = score_from_choices(
        first_letter, get_choice_for_opp_choice_and_outcome(first_letter, second_letter)
    )
    score_B += score_this_round_B
    score_A += score_this_round_A
print("EXC A: ", score_A)
print("EXC B: ", score_B)
# For Exc B
