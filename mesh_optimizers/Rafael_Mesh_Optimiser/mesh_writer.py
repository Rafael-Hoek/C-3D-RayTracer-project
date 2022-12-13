from MeshClasses import Triangle, Box

def write_to_file(filename, stack, vertices) :
    file = open(filename, 'w')
    write_mesh(file, stack, vertices)
    file.close()

def write_mesh(file, stack, vertices) :
    vertices = write_vertices(file, vertices)
    write_stack(file, stack)
    file.write('end')

def write_vertices(file, vertices) :
    file.write(str(len(vertices)) + ' 0\n')
    for vertex in vertices :
        file.write(str(vertex[0]) + ' ' + str(vertex[1]) +  ' ' + str(vertex[2]) + '\n') 
    return vertices

def write_stack(file, stack) :
    while len(stack) != 0 :
        x = stack.pop()
        write_item(file, x)

def write_item(file, x) :
    if isinstance(x, Box) :
        for y in x.children :
            write_item(file, y)
        file.write('b ' + str(len(x.children)) + '\n')
    elif isinstance(x, Triangle) :
        file.write('t')
        for v in x.vertices :
            file.write(' ' + str(v))
        file.write('\n')