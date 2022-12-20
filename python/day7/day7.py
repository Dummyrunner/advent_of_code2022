# ipdb Debugger. add line set_trace() to enter debugger there
from ipdb import set_trace


class RootNode:
    def __init__(self):
        self.children = []


class NodeDirectory(RootNode):
    def __init__(self, parent, name):
        self.children = []
        self.name = name
        self.parent = parent


class NodeFile(NodeDirectory):
    def __init__(self, parent, name, file_size):
        super().__init__(parent, name)
        self.file_size = file_size


class CLI:
    def __init__(self, root):
        self.root_node = root
        self.current_dir = self.root


input_file_path = r"./day7/input_test.txt"
# input_file_path = r"./day7/input.txt"
