import numpy as np

# A   X   1     ROCK
# B   Y   2     PAPER
# C   Z   3     SCISSOR

# A <<< B <<< C <<< A


def removeLastN(str, n):
    str = str[: len(str) - n]
    return str


def opp_choice(letter):
    if letter == "A":
        return np.array([[1, 0, 0]])
    elif letter == "B":
        return np.array([[0, 1, 0]])
    elif letter == "C":
        return np.array([[0, 0, 1]])


def own_choice(letter):
    if letter == "X":
        return opp_choice("A").transpose()
    elif letter == "Y":
        return opp_choice("B").transpose()
    elif letter == "Z":
        return opp_choice("C").transpose()


# input_file_path = r"./day2/input_test.txt"
input_file_path = r"./day2/input.txt"
file_object = open(input_file_path, "r")

lines = file_object.readlines()
lines = [removeLastN(line, 1) for line in lines]
print(lines)

choice_score = np.array([[1, 2, 3], [1, 2, 3], [1, 2, 3]])
win_score = np.array([[3, 6, 0], [0, 3, 6], [6, 0, 3]])
total_score = choice_score + win_score

score = 0
for line in lines:
    opp_input = line[0]
    own_input = line[2]
    score_this_round = np.dot(opp_choice(opp_input), total_score)
    score_this_round = np.dot(score_this_round, own_choice(own_input))
    score += score_this_round
print(score)
