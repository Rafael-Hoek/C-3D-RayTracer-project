import sys
from mesh_reader import read_file
from mesh_writer import write_to_file
from mesh_optimizer import optimize_mesh

#The biggest fucking tism that ever was
filename = input('Enter input file name: ')
outputname = input('Enter desired output file (does not have to be existing file): ')
print('Reading file...')
read_output = read_file(filename)
vertices = read_output[0]
stack = read_output[1]
print('File read complete.')
print('Enter the maximum number of triangles per box')
print('Hint: a smaller maximum means a more optimized result, but if your mesh is too big a maximum that is too small might crash the process (thank you recursion)')
triangles_per_box = int(input('Maximum number of triangles per box:'))
print('Optimizing mesh...')
optimized = optimize_mesh(stack , vertices, triangles_per_box)
print('Optimization complete.')
print('Writing to new file...')
write_to_file(outputname, optimized , vertices)
print('File write complete, please check the file ' + outputname + ' for your optimized mesh')