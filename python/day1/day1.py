from utils import removeLastN

# input_file_path = r"./day1/input_test.txt"
input_file_path = r"./day1/input.txt"
file_object = open(input_file_path, "r")

lines = file_object.readlines()
lines = [removeLastN(line, 1) for line in lines]
print("converted lines :", lines)
lines.append("")

parted_list = []
print(lines)
print([lines[: lines.index("")] for x in lines if x == ""])
for x in lines:
    if x == "":
        empty_index = lines.index("")
        parted_list.append(lines[:empty_index])
        lines = lines[empty_index:]
        del lines[0]
        print("parted list:  ", parted_list)
        print("lines:  ", lines)
        # ipdb.set_trace()
print(parted_list)
sums = []
for part in parted_list:
    part = [eval(num) for num in part]
    sums.append(sum(part))
print("sums   ", sums)
maximum = max(sums)
print("Max ", maximum)

# EXC B
sums.sort()
print("sums   ", sums)
three_largest = sums[-3:]
sum_of_three_largest = sum(three_largest)
print("sum of 3 largest: ", sum_of_three_largest)
