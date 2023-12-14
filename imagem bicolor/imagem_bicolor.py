import numpy as np

A = np.zeros((100,100,3))

for i in range(100):
    for j in range(100):
        if (42*(i-42) - 31*(j-31)) > 0:
            A[i][j][0] = 255
            A[i][j][1] = 0
            A[i][j][2] = 0
        elif (42*(i-42) - 31*(j-31)) < 0:
            A[i][j][0] = 0
            A[i][j][1] = 0
            A[i][j][2] = 255
            

file_path = "imagem_bicolor_py.ppm"

with open(file_path, 'w') as file:
    file.write('P3\n')
    file.write('100 100\n255\n')
    for i in range(100):
        for j in range(100):
            for k in range(3):
                # Write each coordinate to a new line in the file
                file.write(f"{int(A[i,j,k])}\n")