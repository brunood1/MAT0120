import numpy as np

def d(x,y,z):
    X = np.zeros((2,2))
    X[0,0] = y[0] - x[0]
    X[0,1] = y[1] - x[1]
    X[1,0] = z[0] - x[0]
    X[1,1] = z[1] - x[1]
    
    return X[0,0]*X[1,1] - X[0,1]*X[1,0]
    
A = np.zeros((100,100,3))
x = np.array([55,60])
y = np.array([31,22])
z = np.array([71,11])

for i in range(100):
    for j in range(100):
        p = np.array([i,j])
        if d(x,y,p) > 0 and d(z,x,p) > 0 and d(y,z,p) > 0:
            A[i][j][0] = 182
            A[i][j][1] = 9
            A[i][j][2] = 88
        else:
            A[i][j][0] = 21
            A[i][j][1] = 59
            A[i][j][2] = 89            

file_path = "triangulo_py.ppm"

with open(file_path, 'w') as file:
    file.write('P3\n')
    file.write('100 100\n255\n')
    for i in range(100):
        for j in range(100):
            for k in range(3):
                # Write each coordinate to a new line in the file
                file.write(f"{int(A[i,j,k])}\n")
