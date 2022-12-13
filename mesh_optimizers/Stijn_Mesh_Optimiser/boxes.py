import sys

class Box:
    def __init__(self, children) -> None:
        self.children = children

    def subdivide(self, vertices, k):
        if len(self.children) > k:
            (xmin, ymin, zmin) = (float(sys.maxsize), float(sys.maxsize), float(sys.maxsize))
            (xmax, ymax, zmax) = (float(-sys.maxsize),float(-sys.maxsize), float(-sys.maxsize))
            for t in self.children:
                xmin = min(float(xmin), vertices[t[0]][0])
                xmax = max(float(xmax), vertices[t[0]][0])

                ymin = min(float(ymin), vertices[t[0]][1])
                ymax = max(float(ymax), vertices[t[0]][1])

                zmin = min(float(zmin), vertices[t[0]][2])
                zmax = max(float(zmax), vertices[t[0]][2])
            
            xhalf =  xmin + ((xmax - xmin) / 2.0)
            yhalf =  ymin + ((ymax - ymin) / 2.0)
            zhalf =  zmin + ((zmax - zmin) / 2.0)

            # t = top, b = bottom
            # u = up, d = down
            # l = left, r = right
            bottom = ((bdl, bul), (bdr, bur)) = ((Box([]), Box([])), (Box([]), Box([])))
            top = ((tdl, tul),  (tdr, tur)) = ((Box([]), Box([])), (Box([]), Box([])))
            lookup_table = (bottom, top)

            for tri in self.children:
                (t, r, u) = (0, 0, 0)
                if vertices[tri[0]][0] >= xhalf:
                    r = 1 # right 
                if vertices[tri[0]][1] >= yhalf:
                    t = 1 # top
                if vertices[tri[0]][2] >= zhalf:
                    u = 1 # up

                lookup_table[t][r][u].children.append(tri)

            self.children = [bdl, bul, bdr, bur, tdl, tul, tdr, tur]
            self.children = [ele for ele in self.children if ele.children != []]

            for child in self.children:
                child.subdivide(vertices, k)


    def get_hierarchy(self):      
        out = ""
        if len(self.children) == 0:
            return ""

        if isinstance(self.children[0], Box)   :
            for child in self.children:
                out += child.get_hierarchy()
            out += f"b {int(len(self.children))}\n"
        else:
            for i in range(len(self.children)): out += f"t {self.children[i][0]} {self.children[i][1]} {self.children[i][2]}\n"
            out += f"b {int(len(self.children))}\n"
        return out    