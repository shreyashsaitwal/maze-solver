import os
from maze import Maze
from utils import Utils

def main():
    print("--- Welcome to Maze Solver! ---")
    print("Select which maze you want to solve: ")
    print("1. Maze 1")
    print("2. Maze 2")
    print("3. Maze 3")
    print("4. Your own maze!")
    choice = int(input("Enter your choice: "))

    maze_str = ""
    maze_path = ""
    if choice == 1:
        maze_str = Utils.read_file(os.path.join("mazes", "maze1.txt"))
    elif choice == 2:
        maze_str = Utils.read_file(os.path.join("mazes", "maze2.txt"))
    elif choice == 3:
        maze_str = Utils.read_file(os.path.join("mazes", "maze3.txt"))
    elif choice == 4:
        maze_path = input("Enter path to your maze.txt file: ")
        maze_str = Utils.read_file(maze_path)
    else:
        print("Invalid choice!")
        return

    maze = Maze(maze_str)
    maze.solve()
    maze.print_solution()

if __name__ == "__main__":
    main()
