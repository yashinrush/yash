'''For given set of elements create skip list. Find the element in the set that is closest to some given value.
(note: Decide the level of element in the list Randomly with some upper limit)'''
import random

MAX_LEVEL = 4  # maximum level height

class Node:
    def __init__(self, value, level):
        self.value = value
        self.forward = [None] * (level + 1)  # forward pointers for each level

class SkipList:
    def __init__(self):
        self.header = Node(None, MAX_LEVEL)
        self.level = 0

    def random_level(self):
        lvl = 0
        while random.random() < 0.5 and lvl < MAX_LEVEL:
            lvl += 1
        return lvl

    def insert(self, value):
        update = [None] * (MAX_LEVEL + 1)
        current = self.header

        for i in reversed(range(self.level + 1)):
            while current.forward[i] and current.forward[i].value < value:
                current = current.forward[i]
            update[i] = current

        lvl = self.random_level()
        if lvl > self.level:
            for i in range(self.level + 1, lvl + 1):
                update[i] = self.header
            self.level = lvl

        new_node = Node(value, lvl)
        for i in range(lvl + 1):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node

    def find_closest(self, target):
        current = self.header
        closest = None

        for i in reversed(range(self.level + 1)):
            while current.forward[i] and current.forward[i].value < target:
                current = current.forward[i]

        if current.forward[0]:
            next_val = current.forward[0].value
            if abs(next_val - target) < abs(current.value - target if current.value else float('inf')):
                closest = next_val
            else:
                closest = current.value
        else:
            closest = current.value

        return closest

    def display(self):
        print("Skip List:")
        for i in range(self.level + 1):
            node = self.header.forward[i]
            line = f"Level {i}: "
            while node:
                line += str(node.value) + " -> "
                node = node.forward[i]
            print(line + "None")

# Example Usage

elements = [3, 6, 7, 9, 12, 19, 21, 25, 26, 30]
skiplist = SkipList()

for elem in elements:
    skiplist.insert(elem)

skiplist.display()

target = 20
closest = skiplist.find_closest(target)
print(f"\nClosest element to {target} is {closest}")
