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
        self.self = op.OpticalSystem(str(filename))

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


jpype.startJVM(classpath = ['../Java/optisim_java.jar'])

import optisim_java

OpS = OpticalSystem()

proxy = JProxy(optisim_java.OpticalSystem, inst = OpS)

optisim_java.OpticalSimulatorGUI(proxy)

jpype.shutdownJVM()
