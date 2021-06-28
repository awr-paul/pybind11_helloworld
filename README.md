# pybind11_helloworld

An example helloworld conda package that contains a submodule that is a pybind11 extension.

Currently I'm trying to figure out how to stop the pybind11 convertor segfaulting due to a recursive cast:

For example:
>>> from pybind11_helloworld.submodule import sometime
>>> sometime()
Segmentation fault (core dumped)
```
