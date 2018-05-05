# Working with CUDA using PyCuda 
# Note: skcuda (scikit-cuda) builds on top of pycuda to work with additional CUDA libraries that pycuda doesn't include

import pycuda.driver as cuda
import pycuda.autoinit
from pycuda.compiler import SourceModule

import numpy as np

arr = np.zeros((3,3))

# Most GPU's only support single precision, whereas numpy's default is double precision
arr = arr.astype(numpy.float32)

# Allocate memory on the gpu
arrInGpu = cuda.mem_alloc(arr.nbytes)

# Cody the data from host (CPU's main memory) to device (GPU)
cuda.memcpy_htd(arrInGpu, arr)

# Now, the data is in GPU, we can execute code in the GPU

