import optisim as op

# create new empty system
my_system = op.OpticalSystem()

# create new light source at x = 0 and height = 8
LS = op.LightSource(0, 8)

# add light source to system
my_system.add(LS)

# create new thin lens at x = 20 with f = 10
L1 = op.ThinLens(20, 10)

# add light source to system
my_system.add(L1, "Lens_1")

# calculate image formation
my_system.Calculate()

# print informations about system and image formation
my_system.toString()

#-----------------------------------------------------
# create new system from json
my_second_system = op.OpticalSystem("./json_files/presentation2.json")

# calculate image formation
my_second_system.Calculate()

# print informations about system and image formation
my_second_system.toString()

# remove a lens
my_second_system.remove("Lens_1")

# recalculate the image formation
my_second_system.Calculate()

# print informations about system and image formation
my_second_system.toString()

my_second_system.save("./json_files/presentation2_modified.json")




