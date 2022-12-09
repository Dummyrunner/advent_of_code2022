from ipdb import set_trace


def common_chars_2sets(set1, set2):
    common_chars = set1.intersection(set2)
    return common_chars


def line_to_range_pair(line):
    pairs = line.split(",")
    pair0 = pairs[0].split("-")
    pair1 = pairs[1].split("-")
    pair0 = [int(x) for x in pair0]
    pair1 = [int(x) for x in pair1]
    range0 = range(pair0[0], pair0[1] + 1)
    range1 = range(pair1[0], pair1[1] + 1)
    return (range0, range1)


input_file_path = r"./day4/input_test.txt"
# input_file_path = r"./day4/input.txt"
file_object = open(input_file_path, "r")
lines = file_object.readlines()

contains_ctr = 0  # exc A
overlap_ctr = 0  # exc B
for line in lines:
    range_pair = line_to_range_pair(line)
    intersect_set = common_chars_2sets(set(range_pair[0]), set(range_pair[1]))
    if intersect_set == set(range_pair[0]) or intersect_set == set(range_pair[1]):
        contains_ctr += 1
    print(list(range_pair[0]), "\t", list(range_pair[1]))
    print(intersect_set)
    if intersect_set != set():
        overlap_ctr += 1
print("EXC A", contains_ctr)
print("EXC B: ", overlap_ctr)
