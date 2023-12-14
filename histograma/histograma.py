import numpy as np
import matplotlib.pyplot as plt

def count(list, count):
    counter = 0
    for i in range(len(list)):
        if list[i] == count:
            counter += 1
    return counter

list_of_words = []
p = 0
rgb = 0

with open('wolverine.pgm', 'r') as file: # imports txt file as a python list
    lines = file.readlines()
    
for line in lines:
    if line[0] == "#":
        continue
    elif line[0] == "P":
        p = line[1] 
    else:
        try:
            space = line.index(' ')
            l = int(line[0:space])
            h = int(line[space+1:])
        except:
            list_of_words.append(int(line.strip()))
            rgb
            
    
# print(list_of_words)

# frequency = np.zeros((256,2))

# for i in range(len(frequency)):
#     frequency[i,1] = i
#     frequency[i,0] = count(list_of_words, i)
    
# # print(frequency)

file_path = 'frequency.dat'
with open(file_path, 'w') as file:
    for row in list_of_words:
        # file.write(' '.join(map(str, map(int, row))) + '\n')
        file.write(str(int(row)) + '\n')

# plt.hist(list_of_words, bins=16)
# plt.savefig('histograma_ppm.pdf')
# plt.show()