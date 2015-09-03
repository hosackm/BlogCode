from __future__ import print_function


class Node(object):
    def __init__(self, val):
        """
        Represents a node in a tree.  Contains a value and a reference
        to it's left and right children

        :param val: the value to be stored in the node
        """
        self.left = None
        self.right = None
        self.val = val

    def __str__(self):
        return "Node({}, left:{}, right:{})".format(
            self.val, self.left, self.right)


class Tree(object):
    def __init__(self):
        self.root = None

    def add(self, val):
        """
        Add a node to the tree.  This will attempt to insert at the root
        if it does not already exist.  If it does, it will call the recursive
        addToNode() using starting at the root.

        :param val: the value of the node to be added
        """
        if self.root is None:
            self.root = Node(val)
        else:
            self.addToNode(val, self.root)

    def addToNode(self, val, node):
        """
        Recursively add a node to a tree.

        :param val: the value of the node to be added
        :param node: the node that this value should be appended to
        """
        if val < node.val:
            if node.left is None:
                node.left = Node(val)
            else:
                self.addToNode(val, node.left)
        else:
            if node.right is None:
                node.right = Node(val)
            else:
                self.addToNode(val, node.right)

    def __str__(self):
        if self.root is None:
            return "Tree()"
        return str(self.root)


def main():
    t = Tree()
    t.add(8)
    t.add(6)
    t.add(9)
    t.add(2)
    t.add(5)
    t.add(3)
    t.add(1)
    print(t)

if __name__ == "__main__":
    main()
