import optisim as op

my_system = op.OpticalSystem("json_files/input.json")

my_system.toString()

my_system.Calculate()

my_system.toString()

rays = my_system.getRays()

print("Ray 1:", rays["ray_1"].x)
print("Ray 1:", rays["ray_1"].y)
print("Ray 2:", rays["ray_2"].x)
print("Ray 2:", rays["ray_2"].y)

my_system.remove("Lense1")

my_system.Calculate()

my_system.toString()

rays = my_system.getRays()

print("Ray 1:", rays["ray_1"].x)
print("Ray 1:", rays["ray_1"].y)
print("Ray 2:", rays["ray_2"].x)
print("Ray 2:", rays["ray_2"].y)


