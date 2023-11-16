# FIle of search  area py

def mon_chaton(data):
    print(f"[DEBUG] coordonné {data=}")

    Point1 = data[0]
    point1_x = Point1["lat"]
    point1_y = Point1["lng"]

    Point2 = data[1]
    point2_x = Point2["lat"]
    point2_y = Point2["lng"]

    Point3 = data[2]
    point3_x = Point3["lat"]
    point3_y = Point3["lng"]

    Point4 = data[3]
    point4_x = Point4["lat"]
    point4_y = Point4["lng"]


    print(f"[DEBUG] coordonné {Point1=}")
    print(f"[DEBUG] coordonné {Point2=}")
    print(f"[DEBUG] coordonné {Point3=}")

        # Calcul des équations des 4 droites
    droite1 = equation_droite(Point1, Point2)
    droite2 = equation_droite(Point2, Point3)
    droite3 = equation_droite(Point3, Point4)
    droite4 = equation_droite(Point4, Point1)

        # Affichage des équations des droites
    print("Droite 1 : y = {:.4f}x + {:.4f}".format(*droite1))
    print("Droite 2 : y = {:.4f}x + {:.4f}".format(*droite2))
    print("Droite 3 : y = {:.4f}x + {:.4f}".format(*droite3))
    print("Droite 4 : y = {:.4f}x + {:.4f}".format(*droite4))



def equation_droite(coord1, coord2):
    x1, y1 = coord1["lat"], coord1["lng"]
    x2, y2 = coord2["lat"], coord2["lng"]
    m = (y2 - y1) / (x2 - x1)
    b = y1 - m * x1
    
    print(f"[DEBUG] {m=} {b=}"
    return m, b



