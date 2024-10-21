class Maze:
    def __init__(self, maze_str):
        self.start = None
        self.goal = None
        self.dimensions = None
        self.walls = []
        self.explored_states = []
        self.solution = None

        lines = maze_str.split("\n")
        for i, line in enumerate(lines):
            row = []
            for j, char in enumerate(line):
                if char == "A":
                    self.start = (i, j)
                elif char == "B":
                    self.goal = (i, j)
                row.append(char == "#")
            self.walls.append(row)

        self.dimensions = (len(lines), len(lines[0]))

    def solve(self):
        frontier = [Node(self.start)]

        while frontier:
            if len(frontier) > 1:
                frontier.sort(key=lambda node: self.manhattan_distance(self.goal, node.position))

            node = frontier.pop()

            if node.position == self.goal:
                self.solution = node
                return

            self.explored_states.append(node)

            for pos in self.possible_moves(node.position):
                neighbour = Node(pos, node)
                if not any(n.position == neighbour.position for n in self.explored_states) and \
                   not any(n.position == neighbour.position for n in frontier):
                    frontier.append(neighbour)

    def print_solution(self):
        sol_pos = []
        if self.solution:
            node = self.solution
            while node.parent:
                sol_pos.append(node.position)
                node = node.parent

        expl_pos = [node.position for node in self.explored_states]

        count = 0
        while count < len(expl_pos):
            self.print_maze([], expl_pos[:count])
            Utils.move_up_by(self.dimensions[0])
            count += 1

        if self.solution:
            count = 0
            while count < len(sol_pos):
                self.print_maze(sol_pos[:count], expl_pos)
                Utils.move_up_by(self.dimensions[0])
                count += 1

        self.print_maze(sol_pos, expl_pos)
        print()

        if self.solution:
            print(f"Path length:     {len(sol_pos)}")
        else:
            print("No solution found")
        print(f"Explored states: {len(self.explored_states)}")

    def print_maze(self, solution_pos, explored_pos):
        for i, row in enumerate(self.walls):
            for j, is_wall in enumerate(row):
                pos = (i, j)
                if pos == self.start:
                    print(" A ", end="")
                elif pos == self.goal:
                    print(" B ", end="")
                elif is_wall:
                    print("▓▓▓", end="")
                elif pos in solution_pos:
                    print(" • ", end="")
                elif pos in explored_pos:
                    print(" · ", end="")
                else:
                    print(" · ", end="")
            print()

    @staticmethod
    def manhattan_distance(pos1, pos2):
        return abs(pos1[0] - pos2[0]) + abs(pos1[1] - pos2[1])

    def possible_moves(self, pos):
        result = []
        row, col = pos

        if row > 0 and not self.walls[row - 1][col]:
            result.append((row - 1, col))
        if row < self.dimensions[0] - 1 and not self.walls[row + 1][col]:
            result.append((row + 1, col))
        if col > 0 and not self.walls[row][col - 1]:
            result.append((row, col - 1))
        if col < self.dimensions[1] - 1 and not self.walls[row][col + 1]:
            result.append((row, col + 1))

        return result

class Node:
    def __init__(self, position, parent=None):
        self.position = position
        self.parent = parent
