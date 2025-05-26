import os
import numpy as np

def read_node_coordinates(filename):
    """读取节点坐标文件，返回一个字典，键为节点序号，值为(x, y)坐标"""
    node_coords = {}
    try:
        with open(filename, 'r') as file:
            lines = file.readlines()
            # 查找坐标部分开始位置
            start_idx = 0
            for i, line in enumerate(lines):
                if "NODE_COORD_SECTION" in line or (len(line.strip().split()) == 3 and line.strip().split()[0].isdigit()):
                    start_idx = i + 1 if "NODE_COORD_SECTION" in line else i
                    break
            
            # 读取所有节点坐标
            for line in lines[start_idx:]:
                parts = line.strip().split()
                if len(parts) == 3:
                    try:
                        node_id = int(parts[0])
                        x = float(parts[1])
                        y = float(parts[2])
                        node_coords[node_id] = (x, y)
                    except ValueError:
                        continue  # 跳过格式错误的行
                
                # 遇到文件结束标记则停止
                if line.strip() in ("-1", "EOF"):
                    break
                    
    except FileNotFoundError:
        print(f"错误：无法找到文件 {filename}")
        return None
    
    print(f"成功读取 {len(node_coords)} 个节点坐标")
    return node_coords

def read_path_sequence(filename):
    """读取路径序列文件，返回一个列表，包含路径上的节点序号"""
    try:
        with open(filename, 'r') as file:
            lines = file.readlines()
            # 查找路径部分开始位置
            start_idx = 0
            for i, line in enumerate(lines):
                if "TOUR_SECTION" in line or (line.strip().isdigit() and not line.startswith(("NAME", "TYPE", "DIMENSION"))):
                    start_idx = i + 1 if "TOUR_SECTION" in line else i
                    break
            
            path = []
            for line in lines[start_idx:]:
                num = line.strip()
                if num.isdigit():
                    path.append(int(num))
                elif num in ("-1", "EOF"):  # 常见的路径结束标记
                    break
                    
    except FileNotFoundError:
        print(f"错误：无法找到文件 {filename}")
        return None
    
    print(f"路径包含 {len(path)} 个节点")
    return path

def calculate_distance(coord1, coord2):
    """计算两个坐标之间的欧几里得距离"""
    x1, y1 = coord1
    x2, y2 = coord2
    return ((x2 - x1)**2 + (y2 - y1)**2)**0.5

def calculate_path_length(path, node_coords):
    """计算环路路径总长度，包括回到起点(1号节点)的距离"""
    if not path or not node_coords:
        return 0.0
    
    total_distance = 0.0
    
    # 计算路径中相邻节点之间的距离
    for i in range(len(path) - 1):
        node1 = path[i]
        node2 = path[i+1]
        if node1 in node_coords and node2 in node_coords:
            total_distance += calculate_distance(node_coords[node1], node_coords[node2])
        else:
            print(f"警告：节点 {node1} 或 {node2} 坐标缺失")
    
    # 加上最后一个节点回到起点(1号节点)的距离
    last_node = path[-1]
    start_node = 1  # 原点固定为1号节点
    if last_node in node_coords and start_node in node_coords:
        total_distance += calculate_distance(node_coords[last_node], node_coords[start_node])
    else:
        print(f"警告：节点 {last_node} 或 {start_node} 坐标缺失")
    
    return total_distance

def generate_distance_matrix(node_coords, output_filename):
    """生成距离矩阵并保存到文件"""
    if not node_coords:
        print("错误：没有可用的节点坐标数据")
        return
    
    # 获取节点列表并按序号排序
    nodes = sorted(node_coords.keys())
    n = len(nodes)
    
    # 创建距离矩阵
    dist_matrix = np.zeros((n, n))
    
    # 填充距离矩阵
    for i in range(n):
        for j in range(n):
            if i != j:
                dist_matrix[i][j] = calculate_distance(node_coords[nodes[i]], node_coords[nodes[j]])
    
    # 确定数字对齐的最大宽度
    max_distance = np.max(dist_matrix)
    max_width = len(f"{max_distance:.2f}") + 2  # 保留2位小数，加2个空格
    
    # 写入文件
    try:
        with open(output_filename, 'w') as f:
            # 第一行写入节点个数
            f.write(f"{n}\n")
            
            # 第二行开始写入距离矩阵
            for row in dist_matrix:
                # 格式化每个数字为右对齐
                formatted_row = [f"{x:>{max_width}.2f}" for x in row]
                f.write(" ".join(formatted_row) + "\n")
        
        print(f"成功生成距离矩阵并保存到 {output_filename}")
    except IOError:
        print(f"错误：无法写入文件 {output_filename}")

def export_shortest_path(path, path_length, output_filename):
    """导出最短路径到文件"""
    if not path:
        print("错误：没有可用的路径数据")
        return
    
    try:
        with open(output_filename, 'w') as f:
            # 第一行写入节点个数和最短路径长度
            f.write(f"{len(path)} {path_length:.2f}\n")
            
            # 写入路径节点（不重复结尾的1号节点）
            for node in path:
                f.write(f"{node}\n")
        
        print(f"成功导出最短路径到 {output_filename}")
    except IOError:
        print(f"错误：无法写入文件 {output_filename}")

def main():
    # 获取当前脚本所在目录
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    # 定义输入输出文件名
    path_file = os.path.join(script_dir, 'ulysses22.opt.tour')  # 路径序列文件
    coord_file = os.path.join(script_dir, 'ulysses22.tsp')      # 节点坐标文件
    dist_matrix_file = os.path.join(script_dir, 'ulysses22.txt')  # 距离矩阵文件
    shortest_path_file = os.path.join(script_dir, 'ulysses22-ans.txt')  # 最短路径文件
    
    # 读取数据
    node_coords = read_node_coordinates(coord_file)
    path = read_path_sequence(path_file)
    
    # 验证数据
    if node_coords is None or path is None:
        return
    
    # 检查路径中所有节点是否都有坐标
    missing_nodes = [node for node in path if node not in node_coords]
    if missing_nodes:
        print(f"错误：以下节点在坐标文件中缺失：{missing_nodes}")
        return
    
    # 计算路径长度
    path_length = calculate_path_length(path, node_coords)
    print(f"最短环路路径长度为: {path_length:.2f}")
    
    # 生成距离矩阵文件
    generate_distance_matrix(node_coords, 'ulysses22.txt')
    
    # 导出最短路径文件
    export_shortest_path(path, path_length, 'ulysses22-ans.txt')

if __name__ == "__main__":
    main()