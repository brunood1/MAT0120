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
            
original, height, width, P = scanImage("adam.ppm")

# do quadrado unitário para o tamanho da imagem
u4 = np.array([height, width, 1])
U = np.array([[0,height,0],[0,0,width],[1,1,1]])
abg = np.dot(np.linalg.inv(U),u4)
psi = np.zeros((3,3))
psi[0,0] = -abg[0]
psi[1,1] =  abg[1]
psi[2,2] =  abg[2]
W = np.array([[0,1,0],[0,0,1],[1,1,1]])
T1 = np.dot(U, np.dot(psi, np.linalg.inv(W)))

# do quadrado unitario para a imagem projetada
v1 = np.array([2,2,1])
v2 = np.array([270,50,1])
v3 = np.array([60,170,1])
v4 = np.array([200,130,1])
V = np.zeros((3,3))
V[:,0] = v1
V[:,1] = v2
V[:,2] = v3
abg = np.dot(np.linalg.inv(V),v4)
psi = np.zeros((3,3))
psi[0,0] = -abg[0]
psi[1,1] =  abg[1]
psi[2,2] =  abg[2]
W = np.array([[0,1,0],[0,0,1],[1,1,1]])
T2 = np.dot(V, np.dot(psi, np.linalg.inv(W)))

T = np.dot(T2,np.linalg.inv(T1))
Tinv = np.linalg.inv(T)

m = [v1[0], v2[0], v3[0], v4[0]]
n = [v1[1], v2[1], v3[1], v4[1]]

H = max(m)
L = max(n)

B = np.zeros((H,L,3))
for i in range(H):
    for j in range(L):
        v = np.array([[i],[j],[1]])
        w = Tinv@v
        w = w/w[2]
        I = math.floor(w[0])
        J = math.floor(w[1])
        if I >= 0 and I < height and J >= 0 and J < width:
            B[i,j,0] = original[I,J,0]
            B[i,j,1] = original[I,J,1]
            B[i,j,2] = original[I,J,2]



file_path = "transformed.ppm"

with open(file_path, 'w') as file:
    file.write(f'P{P}\n')
    file.write(f'{L} {H}\n255\n')
    for i in range(H):
        for j in range(L):
            for k in range(3):
                file.write(f"{int(B[i,j,k])}\n")