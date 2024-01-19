import numpy as np
import math

ppm = []
RGB = []

with open('turtle.ppm', 'r') as file: 
    lines = file.readlines()

mod = 2
for line in lines: 
    if line[0] == "#": 
        continue 
    elif line[0] == "P": 
        P = line[1] 
    else:
        try:
            space = line.index(' ')
            width = int(line[0:space])
            height = int(line[space+1:])
        except:
            ppm.append(int(line.strip()))
            RGB.append(mod%3)
            mod = mod + 1
            
ppm = np.array(ppm[1:])
ppm = ppm.reshape((height,width,3))

def convolution(A,B,y,x):
    result = np.zeros(3)
    m = math.floor(len(B)/2)
    h = len(B) - m
    for i in range(y-m,y+h):
        for j in range(x-m,x+h):
            if i >= 0 and i < height and j >= 0 and j < width:
                I = i - (y - m)
                J = j - (x - m)
                result[0] += A[i, j,0] * B[I, J]
                result[1] += A[i, j,1] * B[I, J]
                result[2] += A[i, j,2] * B[I, J]
    
    for i in range(3):
        result[i] = math.floor(result[i])
            
    return result

blur = np.zeros((height,width,3))

gaussian = np.array([ [0.003, 0.013, 0.022, 0.013, 0.003] , [0.013, 0.060, 0.098, 0.060, 0.013] , [0.022, 0.098, 0.162, 0.098, 0.022] , [0.013 , 0.060, 0.098, 0.060, 0.013] , [0.003, 0.013, 0.022, 0.013, 0.003] ])

s = 9
S = s**2
uniform = np.ones((s,s))
uniform = uniform/S

for i in range(height):
    for j in range(width):
        blur[i, j] = convolution(ppm, uniform, i,j)
        
file_path = "blur_py.ppm"

with open(file_path, 'w') as file:
    file.write(f'P{P}\n')
    file.write(f'{width} {height}\n255\n')
    for i in range(height):
        for j in range(width):
            for k in range(3):
                file.write(f"{int(blur[i,j,k])}\n")
            
# edges = abs(ppm - blur)

# file_path = "edges_py.ppm"

# with open(file_path, 'w') as file:
#     file.write(f'P{P}\n')
#     file.write(f'{width} {height}\n255\n')
#     for i in range(height):
#         for j in range(width):
#             for k in range(3):
#                 file.write(f"{int(edges[i, j, k])}\n")
            