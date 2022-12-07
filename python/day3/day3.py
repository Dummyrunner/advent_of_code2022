from ipdb import set_trace


def priority_for_letter(item):
    ASCII_A = ord("A")
    ASCII_a = ord("a")
    ASCII_Z = ord("Z")
    ASCII_z = ord("z")
    ascii_nr = ord(item)
    if ascii_nr > ASCII_Z:  # lower case
        prio = ascii_nr - ASCII_a + 1
    else:
        prio = ascii_nr - ASCII_A + 27
    return prio


input_file_path = r"./day3/input_test.txt"
# input_file_path = r"./day3/input.txt"
file_object = open(input_file_path, "r")
lines = file_object.readlines()
lines = [line.split() for line in lines]
common_chars_list = []
prios = []
for line in lines:
    line = line[0]
    len_line = len(line)
    len_halfline = int(len(line) / 2)
    line_half1 = set(line[:len_halfline])
    line_half2 = set(line[(len_halfline):])
    common_chars_in_this_line = list(line_half1.intersection(line_half2))
    common_chars_list.append(common_chars_in_this_line[0])
    prios.append(priority_for_letter(common_chars_in_this_line[0]))
print(prios)
print(sum(prios))
