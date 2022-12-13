import sys
from reader import read
from writer import create_file, write_vertices, close_file, write_hierarchy
from boxes import Box
from os.path import exists

def optimise():
    print(f'Optimizing {sys.argv[1]}...')

    # Read
    k = int(sys.argv[2]) 
    (vertices, triangles) = read(open(sys.argv[1], "r"))

    # Write
    optimized_file = create_file(sys.argv[1])
    print(f'Created optimized-{sys.argv[1]}')
    print(f'Writing vertices...')
    write_vertices(optimized_file, vertices)

    print(f'Optimizing mesh...')
    # Optimise
    box = Box(triangles)
    box.subdivide(vertices, k)
    hierarchy = box.get_hierarchy()

    print(f'Optimizing mesh done')

    print(f'Writing mesh to optimized-{sys.argv[1]}...')
    write_hierarchy(optimized_file, hierarchy)
    close_file(optimized_file)
    print(f'Writing done')
    print(f'Optimization complete')

if (len(sys.argv) != 3):
    print(f'Command must be of format: py mesh-optimizer.py <input_file> <max_triangles_per_box>')
else:
    if (exists(sys.argv[1]) == False):
        print(f'Input file does not exist')  
    elif (sys.argv[2].isdigit() == False):
        print(f'Max triangles per box is not an integer')  
    else: 
        optimise()