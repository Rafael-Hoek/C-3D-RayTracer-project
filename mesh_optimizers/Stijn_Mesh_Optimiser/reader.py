import sys

def read_vertices(vertex_count, file):
    vertices = []
    for _ in range(vertex_count):
        v = file.readline().split()
        vertices.append((float(v[0]), float(v[1]), float(v[2])))
    return vertices

def read_triangles(file):
    triangles = []
    line = file.readline().split()
    while line[0] == "t":
        triangles.append((int(line[1]), int(line[2]), int(line[3])))
        line = file.readline().split()
    return triangles

def read(file):
    file = open(sys.argv[1], "r")
    vertex_count = int(file.readline().split()[0])
    vertices = read_vertices(vertex_count, file)
    triangles = read_triangles(file)
    file.close()
    return (vertices, triangles)
