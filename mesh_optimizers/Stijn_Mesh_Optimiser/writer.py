def create_file(name):
    return open(f'optimized-{name}', 'w')

def write_vertices(file, vertices):
    file.write(f'{len(vertices)} 0\n')   
    for i in range(len(vertices)):
        file.write(f'{vertices[i][0]} {vertices[i][1]} {vertices[i][2]}\n')

def write_hierarchy(file, hierarchy):
    file.write(hierarchy)

def close_file(file):
    file.write(f'end')
    file.close()