# This illustrates working with torch.nn
import torch # autodifferentiation
import torch.nn as nn # neural networks
import torch.nn.functional as F # Relu and maxPool
import torch.optim as optim # SGD

# torch.autograd => Just functions that takes input and computes gradients
# torch.nn => A neural network module that contains 'learnable parameters', anything that contains any weights to learn

# Can extend torch.nn and torch.autograd and write custom C extension for our libraries. 

# Extending torch.autograd => Need forward() and backward()
# has gradcheck() for you to check that your backward gradient implementation is actually correct.

# Extending torch.nn => Need set learnable parameters in init(), as well as forward() that calls an activation function that has backward() implemented
# Also, each module can be an entire NN structure, instead of just a single function
# Need to call parent constructor in extended child class to set up all the dictionaries and private membner variables of parent

class Net(nn.Module):
    '''
    Defining a neural network extends the nn.Module
    '''

    def __init__(self):
        '''
        Define the layers that contains parameters
        '''
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(1, 6, 5) # 1 input image channel (grayscale image), 6 output channels, 5x5 square convolution
        self.conv2 = nn.Conv2d(6, 16, 5)
        self.fc1 = nn.Linear(16 * 5 * 5, 120) # (X, Y) for Y = WX + B, W and B created automatically
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)

    def forward(self, x):
        '''
        Connect the layers in the forward operation with non-linearity which doesn't contain parameters
        '''
        # Convolutional Layers
        x = F.max_pool2d(F.relu(self.conv1(x)), (2, 2)) # Max pooling over a (2, 2) window
        x = F.max_pool2d(F.relu(self.conv2(x)), 2) # Since (2, 2) is square, can specify a single number
        x = x.view(-1, self.num_flat_features(x)) # Flatten the input for fully connected
        # Fully Connected Layers
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x

    def num_flat_features(self, x):
        '''
        Helper method to connect convolutional layers and fully connected layers
        '''
        size = x.size()[1:]  # all dimensions except the batch dimension
        num_features = 1
        for s in size:
            num_features *= s
        return num_features

net = Net()
print(net) # Print the defined network


randomInput = torch.randn(1, 1, 32, 32) # random single (32, 32) input
randomOutput = torch.randn(10)  # random output
randomOutput = randomOutput.view(1, -1)  # 

criterion = nn.MSELoss() # Define loss method

# Forward pass
predictedOutput = net(randomInput)
# Compute loss
loss = criterion(predictedOutput, randomOutput)

print("PredictedOutput", predictedOutput)

net.zero_grad() # Reset the gradients to 0
print("Gradient should be 0 before backward", net.conv1.bias.grad) 

# Backward pass
loss.backward()

print("Gradient should NOT be 0 after backward", net.conv1.bias.grad) 

# SGD with leraning rate of 1
optimizer = optim.SGD(net.parameters(), lr=0.01)

# in your training loop:
optimizer.zero_grad()   # zero the gradient buffers
predictedOutput = net(randomInput)
loss = criterion(predictedOutput, randomOutput)
loss.backward()
optimizer.step()    # Does the update (deduct stepsize of the gradient)


