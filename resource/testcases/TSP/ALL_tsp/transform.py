import os


def name_kind(filename: str) -> list:
    return filename.split('.')[:2]


if __name__ == "__main__":
    cwd = r"D:\_Files\_Lessons\ALGORITHM\Project\resource\testcases\TSP\ALL_tsp"
    files = os.listdir(cwd)
    for file in files:
        splits = name_kind(file)
        if splits[1] == "tsp":
            n = 20
            begin = False
            nodes = []
            with open(file, 'r') as f:
                while line := f.readline().strip():
                    if line == "EOF":
                        break
                    print(line)
                    if line.startswith("DIMENSION"):
                        n = int(line.replace(" ", "").split(":")[1])
                    if line == "NODE_COORD_SECTION":
                        begin = True
                        continue
                    if begin:
                        info = line.split(" ")
                        i = 0
                        while i < len(info):
                            if info[i] == "":
                                info.remove(info[i])
                            else:
                                i += 1
                        print(info)
                        nodes.append((int(info[1]), int(info[2])))

            distance = [[0 for i in range(n)] for j in range(n)]
            for i in range(n):
                for j in range(0, i):
                    distance[i][j] = int(((nodes[i][0] - nodes[j][0]) ** 2 + (nodes[i][1] - nodes[j][1]) ** 2) ** 0.5)
                    distance[j][i] = distance[i][j]

            with open(f"{splits[0]}.txt", 'w') as f:
                f.write(str(n) + "\n")
                for i in range(n):
                    for j in range(n):
                        f.write(str(distance[i][j]) + " ")
                    f.write("\n")


