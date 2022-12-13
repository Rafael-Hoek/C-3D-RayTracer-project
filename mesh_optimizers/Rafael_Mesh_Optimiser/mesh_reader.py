from MeshClasses import Triangle, Box

def read_file(filename) :
    file = open(filename, 'r')
    return [read_vertices(file), read_mesh(file)]

def read_mesh(file) :
    stack = []

    while True:
        line = file.readline()

        if line.startswith('t') :
            vertices = [int(x) for x in line.split(' ')[1:]]
            triangle = Triangle(vertices)
            stack.append(triangle)
        elif line.startswith('b') :
            n_children = int(line.split(' ')[1])
            children = stack[-n_children:]
            stack = stack[:-n_children]
            box = Box(children)
            stack.append(box)
        elif line.startswith('end') :
            return stack

def read_vertices(file) :
    n_vertices = int(file.readline().split(' ')[0])
    return[read_vertex(file) for _ in range(n_vertices)]

def read_vertex(file) :
    return tuple(float(c) for c in file.readline().split(' '))