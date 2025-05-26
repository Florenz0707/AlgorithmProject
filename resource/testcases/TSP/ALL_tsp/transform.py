import os


def name_kind(filename: str) -> list:
    return filename.split('.')[:2]


if __name__ == "__main__":
    cwd = r"D:\_Files\_Lessons\ALGORITHM\Project\resource\testcases\TSP\ALL_tsp"
    os.chdir(cwd)
    files = os.listdir(cwd)
    generate = False
    for file in files:
        print(file)
        splits = name_kind(file)
        if splits[1] == "tsp":
            n = 20
            begin = False
            nodes = []
            with open(file, 'r') as f:
                while line := f.readline().strip():
                    if line == "EOF":
                        break
                    if line.startswith("DIMENSION"):
                        n = int(line.replace(" ", "").split(":")[1])
                    if line == "NODE_COORD_SECTION" or line == "DISPLAY_DATA_SECTION":
                        begin = True
                        continue
                    if begin:
                        info = line.split(" ")
                        while "" in info:
                            info.remove("")
                        print(info)
                        nodes.append((int(eval(info[1])), int(eval(info[2]))))

            distance = [[0 for i in range(n)] for j in range(n)]
            for i in range(n):
                for j in range(0, i):
                    distance[i][j] = int(((nodes[i][0] - nodes[j][0]) ** 2 + (nodes[i][1] - nodes[j][1]) ** 2) ** 0.5)
                    distance[j][i] = distance[i][j]

            if generate:
                with open(f"{splits[0]}.txt", 'w') as f:
                    f.write(str(n) + "\n")
                    for i in range(n):
                        for j in range(n):
                            f.write(str(distance[i][j]) + " ")
                        f.write("\n")


