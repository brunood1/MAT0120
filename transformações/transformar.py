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
            
original, height, width, P = scanImage("adam.ppm")

A = np.array([[3,1],[0.5,2]])
Ainv = np.linalg.inv(A)

X = np.zeros(4)
Y = np.zeros(4)
Z = np.zeros((2,1))
U0 = Ainv@Z

print(np.shape(original))
print("")

print(Z)
print(U0)
print("")

X[0] = U0[0][0]
Y[0] = U0[1][0]

Z[0][0] = height
U1 = Ainv@Z
X[1] = U1[0][0]
Y[1] = U1[1][0]

print(Z)
print(U1)
print("")

Z[0][0] = 0
Z[1][0] = width
U2 = Ainv@Z
X[2] = U2[0][0]
Y[2] = U2[1][0]

print(Z)
print(U2)
print("")

Z[0][0] = height
Z[1][0] = width
U3 = Ainv@Z
X[3] = U3[0][0]
Y[3] = U3[1][0]

print(Z)
print(U3)

xm = min(X)
ym = min(Y)
xM = max(X)
yM = max(Y)

print(X)
print(Y)

H = math.floor(xM - xm)
L = math.floor(yM - ym)

B = np.zeros((H, L, 3))
print(np.shape(B))
for i in range(height-5):
    for j in range(width-5):
        I = math.floor(Ainv[0,0]*i + Ainv[0,1]*j) - math.floor(xm)
        J = math.floor(Ainv[1,0]*i + Ainv[1,1]*j) - math.floor(ym)
        B[I,J,0] = original[i,j,0]
        B[I,J,1] = original[i,j,1]
        B[I,J,2] = original[i,j,2]

file_path = "transformed.ppm"

with open(file_path, 'w') as file:
    file.write(f'P{P}\n')
    file.write(f'{L} {H}\n255\n')
    for i in range(H):
        for j in range(L):
            for k in range(3):
                file.write(f"{int(B[i,j,k])}\n")