# pybind11_helloworld

An example helloworld conda package that contains a submodule that is a pybind11 extension.

For example:

```
>>> from pybind11_helloworld.submodule import sometime
>>> sometime()
numpy.datetime64('2021-06-28T18:36:23.956765909')
```
