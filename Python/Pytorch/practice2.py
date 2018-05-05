# This illustrates extending PyTorch's Module
import torch

# torch.autograd => Just functions that takes input and computes gradients
# torch.nn => A neural network module that contains 'learnable parameters', anything that contains any weights to learn

# Can extend torch.nn and torch.autograd and write custom C extension for our libraries. 

# Extending torch.autograd => Need forward() and backward()
# has gradcheck() for you to check that your backward gradient implementation is actually correct.

# Extending torch.nn => Need set learnable parameters in init(), as well as forward() that calls an activation function that has backward() implemented
