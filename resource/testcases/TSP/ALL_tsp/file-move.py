import os
import shutil

if __name__ == "__main__":
    src = os.path.join(os.getcwd(), r"resource\testcases\TSP\ALL_tsp")
    dst = os.path.join(os.getcwd(), r"resource\testcases\TSP")
    files = os.listdir(src)
    for file in files:
        file_type = file.split(".")[-1]
        if file_type == "txt":
            src_file = os.path.join(src, file)
            dst_file = os.path.join(dst, file)
            shutil.copy(src_file, dst_file)
            print(f"{src_file} -> {dst_file}")
