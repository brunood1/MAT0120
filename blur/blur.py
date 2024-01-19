import numpy as np
import math

pgm = []

with open('adam.pgm', 'r') as file: 
    lines = file.readlines()

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
            pgm.append(int(line.strip()))

pgm = np.array(pgm[1:])
pgm = pgm.reshape((height,width)) # swap 

def convolution(A,B,y,x):
    result = 0
    m = math.floor(len(B)/2)
    h = len(B) - m
    for i in range(y-m,y+h):
        for j in range(x-m,x+h):
            if i >= 0 and i < height and j >= 0 and j < width:
                I = i - (y - m)
                J = j - (x - m)
                result += A[i, j] * B[I, J]
            
    return math.floor(result)

blur = np.zeros((height,width))

gaussian = np.array([ [0.003, 0.013, 0.022, 0.013, 0.003] , [0.013, 0.060, 0.098, 0.060, 0.013] , [0.022, 0.098, 0.162, 0.098, 0.022] , [0.013 , 0.060, 0.098, 0.060, 0.013] , [0.003, 0.013, 0.022, 0.013, 0.003] ])

s = 9
S = s**2
uniform = np.ones((s,s))
uniform = uniform/S

for i in range(height):
    for j in range(width):
        blur[i, j] = convolution(pgm, uniform, i,j)
        
file_path = "blur_py.pgm"

with open(file_path, 'w') as file:
    file.write(f'P{P}\n')
    file.write(f'{width} {height}\n255\n')
    for i in range(height):
        for j in range(width):
            file.write(f"{int(blur[i, j])}\n")
            
# edges = abs(pgm - blur)

# file_path = "edges_py.pgm"

# with open(file_path, 'w') as file:
#     file.write(f'P{P}\n')
#     file.write(f'{width} {height}\n255\n')
#     for i in range(height):
#         for j in range(width):
#             file.write(f"{int(edges[i, j])}\n")
            