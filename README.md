# pybind11_helloworld

An example helloworld conda package that contains a submodule that is a pybind11 extension.

For example:
```
>>> from pybind11_helloworld.submodule import hello
>>> import numpy as np
>>> arr = np.arange(12).reshape((3, 4))
>>> hello(arr)
hello world! Got an array with 12 total elements
>>> exit()
```
