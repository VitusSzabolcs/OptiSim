import jpype
import jpype.imports
import jpype.types
from jpype import JProxy
import optisim as op

class OpticalSystem(object):
    system = op.OpticalSystem()
    def __init__(self):
        ls = op.LightSource(0, 8)
        self.system.add(ls)

    def initialize(self, filename):
        self.system = op.OpticalSystem(str(filename))

    def add_thin_lens(self, name, x, f):
        lens = op.ThinLens(x, f)
        self.system.add(lens, str(name))

    def add_thick_lens(self, name, x, n, d, r_left, r_right):
        lens = op.ThickLens(x, n, d, r_left, r_right)
        self.system.add(lens, str(name))

    def modify_optical_object(self, name, param, val):
        self.system.modifyOpticalObject(str(name), str(param), val)   

    def modify_light_source(self, param, val):
        self.system.modifyLightSource(str(param), val)

    def calculate(self):
        self.system.Calculate()

    def save(self, filename):
        self.system.save(str(filename))

    def getSystemElements(self):
        name_lens_map = self.system.getSystemElements()
        outer_map = HashMap()
        for name, oo in name_lens_map.items():
            inner_map = HashMap()
            if isinstance(oo, op.ThinLens):
                inner_map.put("type", "ThinLens")
                inner_map.put("x", oo.getX())
                inner_map.put("f", oo.getF())
            elif isinstance(oo, op.ThickLens):
                inner_map.put("type", "ThickLens")
                inner_map.put("x", oo.getX())
                inner_map.put("n", oo.getN())
                inner_map.put("d", oo.getD())
                inner_map.put("r_left", oo.getR_left())
                inner_map.put("r_right", oo.getR_right())
            outer_map.put(name, inner_map)
        return outer_map
    def getLightSource(self):
        ls = self.system.getLightSource()
        ls_map = HashMap()
        ls_map.put("x", ls.getX())
        ls_map.put("y", ls.getY())
        return ls_map

jpype.startJVM(classpath = ['../Java/optisim_java.jar'])

from java.util import HashMap

import optisim_java

OpS = OpticalSystem()

proxy = JProxy(optisim_java.OpticalSystem, inst = OpS)

optisim_java.OpticalSimulatorGUI(proxy)

jpype.shutdownJVM()
