# Working with CUDA using PyCuda 
# Note: skcuda (scikit-cuda) builds on top of pycuda to work with additional CUDA libraries that pycuda doesn't include


import pycuda.driver as cuda
import pycuda.autoinit
from pycuda.compiler import SourceModule


