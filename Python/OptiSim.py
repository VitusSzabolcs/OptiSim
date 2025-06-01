import jpype
import jpype.imports
import jpype.types
from jpype import JProxy
import optisim as op

class OpticalSystem(object):
    system = op.OpticalSystem()
    def __init__(self):
        try:
            ls = op.LightSource(0, 8)
            self.system.add(ls)
            self.system.toString()
        except op.OptiSimError as e:
            raise RuntimeException(str(e))

    def initialize(self, filename):
        try:
            self.system = op.OpticalSystem(str(filename))
            self.system.toString()
        except op.OptiSimError as e:
            raise RuntimeException(str(e))

    def add_thin_lens(self, name, x, f):
        try:
            lens = op.ThinLens(x, f)
            self.system.add(lens, str(name))
            self.system.toString()
        except op.OptiSimError as e:
            raise RuntimeException(str(e))

    def add_thick_lens(self, name, x, n, d, r_left, r_right):
        try:
            lens = op.ThickLens(x, n, d, r_left, r_right)
            self.system.add(lens, str(name))
            self.system.toString()
        except op.OptiSimError as e:
            raise RuntimeException(str(e))

    def modify_optical_object(self, name, param, val):
        try:
            self.system.modifyOpticalObject(str(name), str(param), val)
            self.system.toString()
        except op.OptiSimError as e:
            raise RuntimeException(str(e))   

    def modify_light_source(self, param, val):
        try:
            self.system.modifyLightSource(str(param), val)
            self.system.toString()
        except op.OptiSimError as e:
            raise RuntimeException(str(e))

    def calculate(self):
        try:
            img = self.system.Calculate()
            img_map = HashMap()
            img_map.put("x", img.getX())
            img_map.put("y", img.getY())
            img_map.put("real", img.getReal())
            self.system.toString()
        except op.OptiSimError as e:
            raise RuntimeException(str(e))
        return img_map

    def save(self, filename):
        try:
            self.system.save(str(filename))
        except op.OptiSimError as e:
            raise RuntimeException(str(e))

    def getSystemElements(self):
        try:
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
        except op.OptiSimError as e:
            raise RuntimeException(str(e))
        return outer_map

    def getLightSource(self):
        try:
            ls = self.system.getLightSource()
            ls_map = HashMap()
            ls_map.put("x", ls.getX())
            ls_map.put("y", ls.getY())
        except op.OptiSimError as e:
            raise RuntimeException(str(e))
        return ls_map

    def getRays(self):
        try:
            rays = self.system.getRays()
            outer_map = HashMap()
            for key, ray in rays.items():
                inner_map = HashMap()
                x_list = ArrayList()
                y_list = ArrayList()
                
                for i in range(len(ray.x)):
                    x_list.add(ray.x[i])
                    y_list.add(ray.y[i])
                inner_map.put("x", x_list)
                inner_map.put("y", y_list)
                outer_map.put(key, inner_map)
        except op.OptiSimError as e:
            raise RuntimeException(str(e))
        return outer_map

    def remove(self, name):
        try:
            self.system.remove(str(name))
        except op.OptiSimError as e:
            raise RuntimeException(str(e))

jpype.startJVM(classpath = ['../Java/optisim_java.jar'])

from java.util import HashMap, ArrayList
from java.lang import RuntimeException

import optisim_java

OpS = OpticalSystem()

proxy = JProxy(optisim_java.OpticalSystem, inst = OpS)

optisim_java.OpticalSimulatorGUI(proxy)

jpype.shutdownJVM()
