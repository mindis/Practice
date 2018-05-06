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
    __global__ void doublify(float *arr)
    {
        // There will be a separate thread index for each thread
        // The index of the array is determined by the id's of executing thread
        int idx = threadIdx.x + threadIdx.y*3;
        // Since there is no overlap, can just double each arr index
        arr[idx] *= 2;
    }
    """)

# Get the GPU kernel function that was compiled
func = mod.get_function("doublify")

# Execute the GPU kernel function
# and give it a block size of (x,y,z) = (3,3,1),
# which mean's there will be (3*3*1) = 9 threads
# with id's ((0,0,0), (0,1,0), (0,2,0), (1,0,0), (1,1,0), (1,2,0), (2,0,0), (2,1,0), (2,2,0)
func(arrInGpu, block=(3,3,1))

# Create memory to store output back in host
results = np.empty_like(arr)

# Copy back from the executed GPU func to the created array on host
cuda.memcpy_dtoh(results, arrInGpu)

# Print the original result
print(arr)

# Print the result
print(results)
