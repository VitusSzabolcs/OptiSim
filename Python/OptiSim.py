import jpype
import jpype.imports
import jpype.types
from jpype import JProxy
import optisim as op

class OpticalSystem(object):
    def initialize(self):
        system = op.OpticalSystem()
        ls = op.LightSource(0, 8)
        system.add(ls)
        system.toString()    
        

jpype.startJVM(classpath = ['../Java/optisim_java.jar'])

import optisim_java

OpS = OpticalSystem()

proxy = JProxy(optisim_java.OpticalSystem, inst = OpS)

optisim_java.OptiSim(proxy)

jpype.shutdownJVM()