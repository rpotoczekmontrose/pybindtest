from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        "fastlib",
        ["fastlib/src/bindings.cpp", 
         "fastlib/src/computations.cpp",],
        include_dirs=[pybind11.get_include(),
                      "fastlib/include"],
        language='c++',
        extra_compile_args=["/std:c++20", "/MDd"]
    ),
]

setup(
    name="fastlib",
    ext_modules=ext_modules,
)