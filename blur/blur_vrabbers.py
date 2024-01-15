import numpy as np
import math

pgm = []

with open('alika.pgm', 'r') as file: 
    lines = file.readlines()

for line in lines: 
    if line[0] == "#": 
        continue 
    elif line[0] == "P": 
        P = line[1] 
    else:
        # try:
        #     space = line.index(' ')
        #     width = int(line[0:space])
        #     height = int(line[space+1:])
        # except:
        #     pgm.append(int(line.strip()))
        #
        # i've changed this because using exceptions for control flow is poor practice
        # é lento, e um 'except:' sem restrições em relação ao tipo de exceção tbm nn é mto legal
        # as it can catch any type of exception, even those you probably don't want to ignore
        #
        # string.find does the same thing as string.index, but if it doesn't find the character it will
        # return -1 instead.

        space = line.find(' ')
        if space != -1:
            width = int(line[0:space])
            height = int(line[space+1:])
        else:
            pgm.append(int(line.strip()))

# for now i'll keep mine
# note that this code is not Correct according to what i can gather from the specs of (or well, the wikipedia article on)
# pgm files. notably, the pixel data does not have to be in separate lines, they can all be in one line separated by spaces
# or in separate lines, but multiple by line (see the wikipedia article, has an example pgm which has multiple pixels per line)

pgm = np.array(pgm[1:])
pgm = pgm.reshape((height,width)) # swap 

# debug test for seeing number values of the array. for big images this will spend a lot of time so i've left it out
# for j in range(height):
#     for i in range(width):
#         print(pgm[j, i], end = " ")
#     print()

def convolution(picture,convolution,x,y):
    # i've renamed the variables so I could.. understand the code :sob:
    # except for the x, y, whose functions are somewhat clear, always nicer to have code that scans nicely
    # and whose variables state what they are used for, this is seen as best practice in compsci
    # generally best to keep one letter variable names to mathematics :)
    result = 0
    convHalf = math.floor(len(convolution)/2)
    conv2ndHalf = len(convolution) - convHalf
    for i in range(x-convHalf,x+conv2ndHalf):
        for j in range(y-convHalf,y+conv2ndHalf):
            # c.f. the screenshot i sent you
            if i >= 0 and i < width and j >= 0 and j < height:
                I = i - (x - convHalf)
                J = j - (y - convHalf)
                result += picture[j, i] * convolution[J, I] # this stayed the same just the i-j swap
            
    return math.floor(result)

blur = np.zeros((height,width))

gaussian = np.array([ [0.003, 0.013, 0.022, 0.013, 0.003] , [0.013, 0.060, 0.098, 0.060, 0.013] , [0.022, 0.098, 0.162, 0.098, 0.022] , [0.013 , 0.060, 0.098, 0.060, 0.013] , [0.003, 0.013, 0.022, 0.013, 0.003] ])

s = 9
S = s**2
uniform = np.ones((s,s))
uniform = uniform/S

for i in range(width):
    for j in range(height):
        blur[j, i] = convolution(pgm, uniform, i,j)
        
file_path = "blur_py.pgm"

with open(file_path, 'w') as file:
    file.write(f'P{P}\n')
    file.write(f'{width} {height}\n255\n')

    # notice that we write the rows, and then the columns outside
    # the order here is important! PGM is specified to be like this, so we have to do this
    # what happened is that on square images you'd made the same mistake twice
    # and it happened to look fine
    # but on not square images it was not fine
    for j in range(height):
        for i in range(width):
            file.write(f"{int(blur[j, i])}\n")