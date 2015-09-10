from __future__ import print_function
import string
import random


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
            self._add(val, self.root)

    def _add(self, val, node):
        """
        Recursively add a node to a tree.

        :param val: the value of the node to be added
        :param node: the node that this value should be appended to
        """
        if val < node.val:
            if node.left is None:
                node.left = Node(val)
            else:
                self._add(val, node.left)
        else:
            if node.right is None:
                node.right = Node(val)
            else:
                self._add(val, node.right)

    def maxHeight(self):
        if self.root is None:
            return 0
        else:
            return self._maxHeight(self.root)

    def _maxHeight(self, node):
        if node is None:
            return 0
        lheight = self._maxHeight(node.left)
        rheight = self._maxHeight(node.right)
        return lheight + 1 if lheight > rheight else rheight + 1

    def __str__(self):
        if self.root is None:
            return "Tree()"
        return str(self.root)


def getHeight(t):
    return len(t)


def printTree(t):
    """
    List based solution for testing a printing idead I had
    """

    h = getHeight(t)
    width = (2**(h+1)) - 1
    print("Width: {}".format(width))

    for level, row in enumerate(t, 1):
        try:
            nodewidth, space = divmod(width, 2**level)
        except ZeroDivisionError:
            nodewidth, space = width, 0
        finally:
            space = " " if space else ""
        print("".join([s.center(nodewidth) + space for s in row]))


def main2():
    tree = [[random.choice(string.ascii_lowercase)
             for i in range(2**j)] for j in range(5)]
    printTree(tree)


def main():
    t = Tree()
    print("Pre-Height: {}".format(t.maxHeight()))
    t.add(8)
    t.add(6)
    t.add(9)
    t.add(2)
    t.add(5)
    t.add(3)
    t.add(1)
    print(t)
    print("Post-Height: {}".format(t.maxHeight()))

if __name__ == "__main__":
    main2()
