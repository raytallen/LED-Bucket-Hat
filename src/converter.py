from PIL import Image
import numpy as np

im = Image.open("C:\\Users\\rallen\\Downloads\\pixil-frame-0 (1).png")
p = np.array(im)

string = "extern char image[8][32][3] = {"

for y in range(0, 8):
    string += "{"
    for x in range(0, 32):
        string += "{"
        for rgb in range (0, 3):
            string += hex(p[y][x][rgb])
            string += ", "
        string = string[:-2]
        string += "}, "
    string = string[:-2]
    string += "},"
    string += "\n"
string = string[:-2]
string += "};"

print(string)

f = open("myfile.txt", "w")
f.write(string)
f.close()

