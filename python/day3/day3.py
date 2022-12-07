from ipdb import set_trace


def priority_for_letter(item):
    ASCII_A = ord("A")
    ASCII_a = ord("a")
    ASCII_Z = ord("Z")
    ascii_nr = ord(item)
    if ascii_nr > ASCII_Z:  # lower case
        prio = ascii_nr - ASCII_a + 1
    else:
        prio = ascii_nr - ASCII_A + 27
    return prio


def common_chars_2sets(set1, set2):
    common_chars = set1.intersection(set2)
    return common_chars


def common_chars_3sets(set1, set2, set3):
    common_chars = set1.intersection(set2).intersection(set3)
    return common_chars


# input_file_path = r"./day3/input_test.txt"
input_file_path = r"./day3/input.txt"

file_object = open(input_file_path, "r")
lines = file_object.readlines()
lines = [line.split() for line in lines]
common_chars_list = []
prios = []
for line in lines:
    line = line[0]
    len_line = len(line)
    len_halfline = int(len(line) / 2)
    line_half1 = line[:len_halfline]
    line_half2 = line[(len_halfline):]
    common_chars_in_this_line = list(
        common_chars_2sets(set(line_half1), set(line_half2))
    )
    common_chars_list.append(common_chars_in_this_line[0])
    prios.append(priority_for_letter(common_chars_in_this_line[0]))
print("day3A: ", sum(prios))

badge_prios = 0
for idx in range(len(lines)):
    if idx % 3 == 0:
        string1 = lines[idx][0]
        string2 = lines[idx + 1][0]
        string3 = lines[idx + 2][0]
        badge_this_triplet = list(
            common_chars_3sets(set(string1), set(string2), set(string3))
        )
        badge_prios += priority_for_letter(badge_this_triplet[0])
print("day3B: ", badge_prios)
