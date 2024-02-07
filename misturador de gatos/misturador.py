import numpy as np
import math



def scanImage(file_name):
    ppm = []
    RGB = []    

    with open(file_name, 'r') as file: 
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
    
    return ppm, height, width, P
    

def f(A, B):
    C = np.zeros(np.shape(A))
    x = math.floor(len(A)/3)
    y = 2*x
    n = len(A)
    C[0:x,:] = A[0:x,:]
    C[y:n,:] = B[y:n,:]
    for i in range(x,y):
        
        C[i,:] = (2- i/x)*A[i,:] + (i/x - 1)*B[i,:]
        
    return C
            
white_cat, height, width, P = scanImage("gatobranco.ppm")
reverse_cat = 255 - white_cat

mixed_cat = f(white_cat, reverse_cat)

for i in range(height):
    for j in range(width):
        for k in range(3):
            mixed_cat[i][j][k] = math.floor(mixed_cat[i][j][k])

file_path = "gato_misturado.ppm"

with open(file_path, 'w') as file:
    file.write(f'P{P}\n')
    file.write(f'{width} {height}\n255\n')
    for i in range(height):
        for j in range(width):
            for k in range(3):
                file.write(f"{int(mixed_cat[i,j,k])}\n")