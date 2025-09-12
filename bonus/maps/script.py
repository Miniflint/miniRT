import random

def generate_spheres(
    count=10,
    position_range=(-200, 200),
    size_range=(2, 10),
    height_range=(2, 60),
    vec_range=(-1, 1),
    colors=[(255, 255, 255), (255, 255, 255)]
):
    spheres = []
    for _ in range(count):
        x = round(random.uniform(*position_range), 2)
        y = round(random.uniform(*position_range), 2)
        z = round(random.uniform(*position_range), 2)
        size = random.randint(*size_range)
        height = random.randint(*height_range)
        v_x = round(random.uniform(*vec_range), 2)
        v_y = round(random.uniform(*vec_range), 2)
        v_z = round(random.uniform(*vec_range), 2)
        color = random.choice(colors)
        sphere_line = f"cy {x},{y},{z} {v_x},{v_y},{v_z} {size} {height} {color[0]},{color[1]},{color[2]}"
        spheres.append(sphere_line)
    return spheres

if __name__ == "__main__":
    spheres = generate_spheres(count=800)
    for sphere in spheres:
        print(sphere)