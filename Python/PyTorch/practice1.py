# This illustrates working with autograd directly in PyTorch

import torch

dtype = torch.float # Use floating point
# device = torch.device('cpu') # Use CPU 
device = torch.device('cuda:0') # Use GPU 

N, Din, H, Dout = 64, 1000, 100, 10 

# These are PyTorch Tensor (multidimensional array)
# Similar to Numpy array, doesn't know about computational graph or gradients
# However, PyTorch Tensor can run on GPU 


# Create random input and random output data
x = torch.randn(N, Din, device=device, dtype=dtype) 
y = torch.randn(N, Dout, device=device, dtype=dtype) 

# Randomly initialize the weights using normal distribution with mean 0 and variance 1
# Requires_Grad indicate this is a parameter that needs to compute gradients for
# whenever you end up calculating lossTensorVariable.backward()
w1 = torch.randn(Din, H, device=device, dtype=dtype, requires_grad=True)
w2 = torch.randn(H, Dout, device=device, dtype=dtype, requires_grad=True)

# Training parameters
learningRate = 1e-6
numEpoch = 300

for currEpochIndex in range(numEpoch):
    # Forward pass
    # mm = matrix multiply
    z = x.mm(w1)
    # Relu Non-linearity 
    h = z.clamp(min=0)
    yPred = h.mm(w2)

    # Compute the loss
    # Everything in torch returns a torch tensor
    loss = (yPred - y).pow(2).sum()
    # To convert into actual numpy array, use item()
    print(currEpochIndex, loss.item())

    # Backward pass
    loss.backward()

    # Need update weights but not update gradients when using them in calculations
    with torch.no_grad():
        # Update weights manually
        w1 -= learningRate * w1.grad
        w2 -= learningRate * w2.grad
        # Pytorch doesn't zero the grads automatically
        # as the gradients may add up additively in parallel
        # so you have to decide when to zero the gradients
        # Manually zero the gradients
        w1.grad.zero_()
        w2.grad.zero_()
    # Backward pass
    #gradY = 2.0*(ypred - y)
    # TODO: 
