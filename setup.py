"""
Python setuptools config to package this repository.
"""
from setuptools import setup, find_namespace_packages
from pybind11.setup_helpers import ParallelCompile, naive_recompile, Pybind11Extension, build_ext

ParallelCompile("NPY_NUM_BUILD_JOBS", needs_recompile=naive_recompile).install()

ext_modules = [
    Pybind11Extension("pybind11_helloworld.submodule",
                      sources=["src/pybind11_helloworld/submodule/main.cpp"]),
]

setup(
    name="pybind11_helloworld",
    version="0.0.0",
    package_dir={"": "lib"},
    packages=find_namespace_packages(where="lib"),
    install_requires=["pybind11"],
    cmdclass={"build_ext": build_ext},
    ext_modules=ext_modules,
    zip_safe=False,
)
