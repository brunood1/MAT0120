import numpy as np

def d(x,y):
    return ((x[0] - y[0])**2 + (x[1] - y[1])**2)**0.5
    
A = np.zeros((100,100,3))
CENTRO = np.array([40,60])
RAIO = 15

for i in range(100):
    for j in range(100):
        p = np.array([i,j])
        if d(CENTRO, p) <= RAIO:
            A[i][j][0] = 182
            A[i][j][1] = 9
            A[i][j][2] = 88
        else:
            A[i][j][0] = 21
            A[i][j][1] = 59
            A[i][j][2] = 89
            

file_path = "circulo_py.ppm"

with open(file_path, 'w') as file:
    file.write('P3\n')
    file.write('100 100\n255\n')
    for i in range(100):
        for j in range(100):
            for k in range(3):
                # Write each coordinate to a new line in the file
                file.write(f"{int(A[i,j,k])}\n")
