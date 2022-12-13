from MeshClasses import Triangle, Box
from mesh_reader import read_file

def optimize_mesh(stack, vertices, triangles_per_box) :

    #Go go big brain algorithm
    stack = [smooth_brain_algorithm(stack[0], vertices, triangles_per_box)]
    
    #return optimized stack
    return stack
    
def smooth_brain_algorithm(x, vertices, triangles_per_box) :
    if len(x.children) > triangles_per_box :
        xmin = vertices[x.children[0].vertices[0]][0]
        ymin = vertices[x.children[0].vertices[0]][1]
        zmin = vertices[x.children[0].vertices[0]][2]
        xmax = xmin
        ymax = ymin
        zmax = zmin
        for triangle in x.children :
            xmin = min(xmin, vertices[triangle.vertices[0]][0])
            ymin = min(ymin, vertices[triangle.vertices[0]][1])
            zmin = min(zmin, vertices[triangle.vertices[0]][2])
            xmax = max(xmax, vertices[triangle.vertices[0]][0])
            ymax = max(ymax, vertices[triangle.vertices[0]][1])
            zmax = max(zmax, vertices[triangle.vertices[0]][2])
        
        xdiff = xmax - xmin
        ydiff = ymax - ymin
        zdiff = zmax - zmin
        
        box1 = Box([])
        box2 = Box([])

        for triangle in x.children :
            if xdiff >= ydiff and xdiff >= zdiff :
                bound = xmin + (xdiff / 2)
                if vertices[triangle.vertices[0]][0] >= bound :
                    box1.children.append(triangle)
                else :
                    box2.children.append(triangle)
            elif ydiff >= xdiff and ydiff >= zdiff :
                bound = ymin + (ydiff / 2)
                if vertices[triangle.vertices[0]][1] >= bound :
                    box1.children.append(triangle)
                else :
                    box2.children.append(triangle)
            else :
                bound = zmin + (zdiff / 2)
                if vertices[triangle.vertices[0]][2] >= bound :
                    box1.children.append(triangle)
                else :
                    box2.children.append(triangle)

        box1 = smooth_brain_algorithm(box1, vertices, triangles_per_box)
        box2 = smooth_brain_algorithm(box2, vertices, triangles_per_box)
        return Box([box1, box2])
    else :
        return x