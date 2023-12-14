import numpy as np
import random

def d(x,y):
    return ((x[0] - y[0])**2 + (x[1] - y[1])**2)**0.5
    
A = np.zeros((500,500,3))
for i in range(500):
    for j in range (500):
        A[i][j][0] = 21
        A[i][j][1] = 59
        A[i][j][2] = 89

CENTRO = np.zeros(2)
RAIO = 0
COR = np.zeros(3)

for x in range(100):
    CENTRO[0] = int(random.randint(0, 500))
    CENTRO[1] = int(random.randint(0, 500))
    
    RAIO = int(random.randint(0, 100))
    
    COR[0] = int(random.randint(0, 255))
    COR[1] = int(random.randint(0, 255))
    COR[2] = int(random.randint(0, 255))
    
    for i in range(500):
        for j in range(500):
            p = np.array([i,j])
            if d(CENTRO, p) <= RAIO:
                A[i][j][0] = COR[0]
                A[i][j][1] = COR[1]
                A[i][j][2] = COR[2]

file_path = "circulos_py.ppm"

with open(file_path, 'w') as file:
    file.write('P3\n')
    file.write('500 500\n255\n')
    for i in range(500):
        for j in range(500):
            for k in range(3):
                # Write each coordinate to a new line in the file
                file.write(f"{int(A[i,j,k])}\n")
