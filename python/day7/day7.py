# ipdb Debugger. add line set_trace() to enter debugger there
from ipdb import set_trace


class Node:
    def __init__(self, name):
        self.name = name


class RootNode(Node):
    def __init__(self):
        self.children = []

    name = "/"


class NodeDirectory(RootNode):
    def __init__(self, parent, name):
        self.children = []
        self.name = name
        self.parent = parent


class NodeFile(RootNode):
    def __init__(self, parent, name, file_size):
        super().__init__(parent, name)
        self.file_size = file_size


class CLI:
    def __init__(self, root):
        self.root_node = root
        self.current_dir = root


class NodeDirectory:
    def __init__(self, parent, name):
        self.children = []
        self.name = name
        self.parent = parent


class NodeFile:
    def __init__(self, parent, name, file_size):
        self.children = []
        self.file_size = file_size


class CLI:
    def __init__(self, root):
        self.root_node = root
        self.current_dir = self.root


def parse_command7(command_string):
    # remove leading $
    command_string = command_string[2:]


input_file_path = r"./day7/input_test.txt"
# input_file_path = r"./day7/input.txt"


def parseCommand(command_string):
    # remove leading $
    command_string = command_string[2:]
    if command_string[0:2] == "cd":
        cmd = "cd"
    elif command_string[0:2] == "ls":
        cmd = "ls"
    else:
        print("ERROR UNKNOWN COMMAND")
    return (cmd, command_string[3:])


def change_dir(destination):
    pass


input_file_path = r"./day7/input_test.txt"
# input_file_path = r"./day7/input.txt"

# Parse Input file
file_object = open(input_file_path, "r")
# remove \n from strings with strip()
command_list = [x.strip() for x in file_object.readlines()]

# print(command_list)
first_command = command_list[0]
print(parseCommand(first_command))
