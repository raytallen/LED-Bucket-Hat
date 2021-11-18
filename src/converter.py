from PIL import Image
import numpy as np

im = Image.open("C:\\Users\\rallen\\Downloads\\download.bmp")
p = np.array(im)

string = "uint8_t image[256][3] = {"

for y in range(0, 8):
    for x in range(0, 32):
        string += "{"
        for rgb in range (0, 3):
            string += hex(p[y][x][rgb])
            string += ", "
        string = string[:-2]
        string += "}, "
    string += "\n"
string = string[:-3]
string += "};"

print(string)

f = open("myfile.txt", "w")
f.write(string)
f.close()

