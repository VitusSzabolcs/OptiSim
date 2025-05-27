import optisim as op

ls = op.LightSource(-10, 2)

lens1 = op.ThinLens(0, 10)
lens2 = op.ThickLens(20, 1.5, 2.0, 15.0, -15.0)

my_system = op.OpticalSystem()

my_system.add(lens1, "L1")
my_system.add(lens2, "L2")

my_system.add(ls)

my_system.modifyOpticalObject("L1", "x", 1)

img = my_system.Calculate()

my_system.toString()

my_second_system = op.OpticalSystem("json_files/input.json")
my_second_system.Calculate()
my_second_system.toString()
