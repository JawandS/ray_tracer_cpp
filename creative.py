# generate a scene file for the creative project
import math

SPHERE_RAD = 0.025

def create_sphere(f, center, color, radius=SPHERE_RAD):
    return f.write(f"s\n{center}\n{radius}\n{color}\n\n")

def create_plane(f, normal, distance, color_one, color_two):
    return f.write(f"p\n{normal}\n{distance}\n{color_one}\n{color_two}\n\n")

def create_light(f, center):
    return f.write(f"l\n{center}\n")

# main method
with open("creative.txt", "w") as f:
    # create bakcground plane
    create_plane(f, "0 0 -1", 30, "0 0 0", "0 0 0")
    
    # colors of the rainbow
    colors = ["1 0 0", "1 0.5 0", "1 1 0", "0 1 0", "0 0 1", "0.29 0 0.51", "0.56 0 1"]
    
    # radius of the circle and spheres
    circle_radius = 5
    
    # recursively generate rings of spheres 
    def gen_spheres(counter, center_X, center_Y, circle_radius, values):
        if counter == 1:
            for i in range(7):
                angle = 2 * math.pi * i / 7
                x = circle_radius * math.cos(angle)
                z = circle_radius * math.sin(angle)
                center = f"{center_X + x} {center_Y + z} 2.5"
                values.append((center, colors[i]))
        else:
            for i in range(7):
                angle = 2 * math.pi * i / 7
                x = circle_radius * math.cos(angle)
                z = circle_radius * math.sin(angle)
                gen_spheres(counter - 1, center_X + x, center_Y + z, circle_radius / 3, values)

    values = []
    gen_spheres(7, 0, 0, circle_radius, values)
    # print(values)
    for center, color in values:
        create_sphere(f, center, color)

    # add light
    create_light(f, "0 0 -5")