import optisim as op # import optisim library components

def test_LightSource():
    print("\n\nTesting LightSource:\n\n")
    LS = op.LightSource(10, 5)

    if LS.getX() == 10:
        print("\tLightSource -> getX() : works properly (same for Image)\n")
    else:
        print("\tLightSource -> getX() : works faulty (same for Image)\n")
    if LS.getY() == 5:
        print("\tLightSource -> getY() : works properly (same for Image)\n")
    else:
        print("\tLightSource -> getY() : works faulty (same for Image)\n")

    LS.setX(15)
    LS.setY(10)

    if LS.getX() == 15:
        print("\tLightSource -> setX(double) : works properly (same for Image)\n")
    else:
        print("\tLightSource -> setX(double) : works faulty (same for Image)\n")
    if LS.getY() == 10:
        print("\tLightSource -> setY(double) : works properly (same for Image)\n")
    else:
        print("\tLightSource -> setY(double) : works faulty (same for Image)\n")

def test_ThinLens():
    print("\n\nTesting ThinLens:\n\n")
    ThinL = op.ThinLens(10, 5)

    if ThinL.getX() == 10:
        print("\tThinLens -> getX() : works properly\n")
    else:
        print("\tThinLens -> getX() : works faulty\n")
    if ThinL.getF() == 5:
        print("\tThinLens -> getF() : works properly\n")
    else:
        print("\tThinLens -> getF() : works faulty\n")

    ThinL.setX(15)
    ThinL.setF(10)

    if ThinL.getX() == 15:
        print("\tThinLens -> setX() : works properly\n")
    else:
        print("\tThinLens -> setX() : works faulty\n")
    if ThinL.getF() == 10:
        print("\tThinLens -> setF() : works properly\n")
    else:
        print("\tThinLens -> setF() : works faulty\n")

def test_ThickLens():
    print("\n\nTesting ThickLens:\n\n")
    ThickL = op.ThickLens(10, 1.5, 5, -20, 25)

    if ThickL.getX() == 10:
        print("\tThickLens -> getX() : works properly\n")
    else:
        print("\tThickLens -> getX() : works faulty\n")
    if ThickL.getN() == 1.5: 
        print("\tThickLens -> getN() : works properly\n")
    else:
        print("\tThickLens -> getN() : works faulty\n")
    if ThickL.getD() == 5:
        print("\tThickLens -> getD() : works properly\n")
    else:
        print("\tThickLens -> getD() : works faulty\n")
    if ThickL.getR_left() == -20:
        print("\tThickLens -> getR_left() : works properly\n")
    else:
        print("\tThickLens -> getR_left() : works faulty\n")
    if ThickL.getR_right() == 25:
        print("\tThickLens -> getR_right() : works properly\n")
    else:
        print("\tThickLens -> getR_right() : works faulty\n")

    ThickL.setX(20)
    ThickL.setN(1.7)
    ThickL.setD(3)
    ThickL.setR_left(15)
    ThickL.setR_right(10)

    if  ThickL.getX() == 20: 
        print("\tThickLens -> setX(double) : works properly\n")
    else:
        print("\tThickLens -> setX(double) : works faulty\n")
    if ThickL.getN() == 1.7:
        print("\tThickLens -> setN(double) : works properly\n")
    else: 
        print("\tThickLens -> setN(double) : works faulty\n")
    if ThickL.getD() == 3: 
        print("\tThickLens -> setD(double) : works properly\n")
    else:
        print("\tThickLens -> setD(double) : works faulty\n")
    if ThickL.getR_left() == 15: 
        print("\tThickLens -> setR_left(double) : works properly\n")
    else: 
        print("\tThickLens -> setR_left(double) : works faulty\n")
    if ThickL.getR_right() == 10: 
        print("\tThickLens -> setR_right(double) : works properly\n")
    else: 
        print("\tThickLens -> setR_right(double) : works faulty\n")

    ThickL.setN(1.5)
    ThickL.setD(3)
    ThickL.setR_left(10)
    ThickL.setR_right(10)

    if ThickL.getF() == 200: 
        print("\tThickLens -> getF() : works properly\n")
    else: 
        print("\tThickLens -> getF() : works faulty\n")

def test_OpticalSystem():
    print("\n\nTesting OpticalSystem:\n\n")

    # Create optical system and OpticalObjects
    OS = op.OpticalSystem()
    LS = op.LightSource(0, 5)
    ThinL = op.ThinLens(10, 5)
    ThickL = op.ThickLens(30, 1.5, 5, -20, 25)

    # Add LightSource to the OpticalSystem & get LightSource from OpticalSystem & check identity
    OS.add(LS)
    LS_get = OS.getLightSource()
    if LS_get.getX() == LS.getX() and LS_get.getY() == LS.getY():
        print("\tOpticalSystem -> add(LightSource) & getLightSource() : works properly\n")
    else: 
        print("\tOpticalSystem -> add(LightSource) || getLightSource() : works faulty\n")

    # Add Lenses to the OpticalSystem & get Lenses from OpticalSystem & check identity
    OS.add(ThinL, "Lens1")
    OS.add(ThickL, "Lens2")
    OOList = OS.getSystemElements()
    ThinL_get = OOList["Lens1"]
    ThickL_get = OOList["Lens2"]
    if ThinL_get.getX() == ThinL.getX() and ThinL_get.getF() == ThinL.getF() and ThickL_get.getX() == ThickL.getX() and ThickL_get.getN() == ThickL.getN() and ThickL_get.getD() == ThickL.getD() and ThickL_get.getR_left() == ThickL.getR_left() and ThickL_get.getR_right() == ThickL.getR_right():
        print("\tOpticalSystem -> add(OpticalObject&, string) & getSystemElements() : works properly\n")
    else: 
        print("\tOpticalSystem -> add(OpticalObject&, string) || getSystemElements() : works faulty\n")

    # Modify LightSource & get LightSource from OpticalSystem & check whether the modification was successful
    OS.modifyLightSource("x",-20)
    OS.modifyLightSource("y",10)
    LS_get = OS.getLightSource()
    if LS_get.getX() == -20 and LS_get.getY() == 10:
        print("\tOpticalSystem -> modifyLightSource(string, double) : works properly\n")
    else:
        print("\tOpticalSystem -> modifyLightSource(string, double) : works faulty\n")

    # Modify Lenses & get Lenses from OpticalSystem & check whether the modification was successful
    OS.modifyOpticalObject("Lens1", "x", 0)
    OS.modifyOpticalObject("Lens1", "f", 10)
    OS.modifyOpticalObject("Lens2", "x", 30)
    OS.modifyOpticalObject("Lens2", "n", 1.7)
    OS.modifyOpticalObject("Lens2", "d", 3)
    OS.modifyOpticalObject("Lens2", "r_left", 35)
    OS.modifyOpticalObject("Lens2", "r_right", 40)

    OOList = OS.getSystemElements()
    ThinL_get = OOList["Lens1"]
    ThickL_get = OOList["Lens2"]

    if ThinL_get.getX() == 0 and ThinL_get.getF() == 10 and ThickL_get.getX() == 30 and ThickL_get.getN() == 1.7 and ThickL_get.getD() == 3 and ThickL_get.getR_left() == 35 and ThickL_get.getR_right() == 40:
        print("\tOpticalSystem -> modifyOpticalObject(string, string, double) : works properly\n")
    else:
        print("\tOpticalSystem -> modifyOpticalObject(string, string, double) : works faulty\n")

    # Remove Lens & get Lenses from OpticalSystem & check whether the remove was successful
    OS.remove("Lens2")
    OOList = OS.getSystemElements()
    ThinL_get = OOList["Lens1"]

    if ThinL_get.getX() == 0 and ThinL_get.getF() == 10 and len(OOList) == 1: # check if we still have Lens1 & if we have only one lens
        print("\tOpticalSystem -> remove(string) : works properly\n")
    else:
        print("\tOpticalSystem -> remove(string) : works faulty\n")

    # Calculate image formation & get image sequence & check for proper image formation
    OS.Calculate()
    IS =  OS.getImageSequence()
    FinalI = IS[-1]

    if FinalI.getX() == 20 and FinalI.getY() == -10 and FinalI.getReal() == 1:
        print("\tOpticalSystem -> Calculate() &  getImageSequence(): works properly\n")
    else: 
        print("\tOpticalSystem -> Calculate() &  getImageSequence() : works faulty\n")

    # Get rays & check if they are correct
    Rays =  OS.getRays()
    if Rays["ray_1"].x[0] == -20 and Rays["ray_1"].x[1] == 0 and Rays["ray_1"].x[2] == 20 and Rays["ray_1"].y[0] == 10 and Rays["ray_1"].y[1] == 10 and Rays["ray_1"].y[2] == -10 and Rays["ray_2"].x[0] == -20 and Rays["ray_2"].x[1] == 0 and Rays["ray_2"].x[2] == 20 and Rays["ray_2"].y[0] == 10 and Rays["ray_2"].y[1] == 0 and Rays["ray_2"].y[2] == -10:
        print("\tOpticalSystem -> getRays(): works properly\n")
    else:
        print("\tOpticalSystem -> getRays() : works faulty\n")

    # Save the OpticalSystem into file & relaod it from file & check if we get the same OpticalSystem
    OS.save("saved_system.json")
    OS2 = op.OpticalSystem("saved_system.json")

    LS_get = OS.getLightSource()
    OOList = OS.getSystemElements()
    ThinL_get = OOList["Lens1"]

    if LS_get.getX() == -20 and LS_get.getY() == 10 and ThinL_get.getX() == 0 and ThinL_get.getF() == 10:
        print("\tOpticalSystem -> save(string) & OpticalSystem(string) : works properly\n")
    else:
        print("\tOpticalSystem -> save(string) & OpticalSystem(string) : works faulty\n")


test_LightSource()
test_ThinLens()
test_ThickLens()
test_OpticalSystem()