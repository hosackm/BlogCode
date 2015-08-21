class Stack(object):
    def __init__(self):
        self.elems = list()

    def push(self, x):
        self.elems.append(x)

    def pop(self):
        return self.elems.pop()

    def __len__(self):
        return len(self.elems)

    def __repr__(self):
        return 'Stack({})'.format(', '.join(map(str, self.elems)))

    def __str__(self):
        return self.__repr__()

    def empty(self):
        return len(self) == 0
