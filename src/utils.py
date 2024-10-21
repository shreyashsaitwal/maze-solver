class Utils:
    @staticmethod
    def read_file(file_path):
        with open(file_path, 'r') as file:
            return file.read()

    @staticmethod
    def split_str(input_str, delimiter):
        if delimiter == "":
            return list(input_str)
        return input_str.split(delimiter)

    @staticmethod
    def move_up_by(n):
        print(f"\033[{n}A", end="")
