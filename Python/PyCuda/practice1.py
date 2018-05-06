# Working with CUDA using PyCuda 
# Note: skcuda (scikit-cuda) builds on top of pycuda to work with additional CUDA libraries that pycuda doesn't include

import pycuda.driver as cuda
import pycuda.autoinit
from pycuda.compiler import SourceModule

import numpy as np

arr = np.ones((3,3))

# Most GPU's only support single precision, whereas numpy's default is double precision
arr = arr.astype(np.float32)

# Allocate memory on the gpu
arrInGpu = cuda.mem_alloc(arr.nbytes)

# Cody the data from host (CPU's main memory) to device (GPU)
cuda.memcpy_htod(arrInGpu, arr)

# Now, the data is in GPU, we can execute code in the GPU
# CUDA is written in C code, so you need to compile it
mod = SourceModule("""
    // Takes in a  
    __global__ void doublify(float *a)
    {
        int idx = threadIdx.x + threadIdx.y*4;
        a[idx] *= 2;
    }
    """)

# Get the GPU kernel function that was compiled
func = mod.get_function("doublify")

# Execute the Gpu kernel function
func(arrInGpu, block=(4,4,1))

# Create memory to store output back in host
arrDoubled = np.empty_like(arr)
cuda.memcpy_dtoh(arrDoubled, arrInGpu)

# Print the original result
print(arr)
# Print the result
print(arrDoubled)
