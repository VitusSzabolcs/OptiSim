import jpype
import jpype.imports
import jpype.types
from jpype import JProxy
import optisim as op

class OpticalSystem(object):
    system = op.OpticalSystem()
    def initialize(self):
        ls = op.LightSource(0, 8)
        self.system.add(ls)
        self.system.toString()
        

jpype.startJVM(classpath = ['../Java/optisim_java.jar'])

import optisim_java

OpS = OpticalSystem()

proxy = JProxy(optisim_java.OpticalSystem, inst = OpS)

optisim_java.OpticalSimulatorGUI(proxy)

jpype.shutdownJVM()