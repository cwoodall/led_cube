import serial
s = serial.Serial('/dev/tty.usbserial-A900aevi', baudrate=9600)

def transformToFrame(cube):
    transform = []
    for layer in cube:
        for row in range(0,len(layer),2):
            num1 = 0
            num2 = 0
            for el in range(0, len(layer[row])):
                num1 += (2**el)*layer[row][el]
            for el in range(0, len(layer[row+1])):
                num2 += ((2**el)*layer[row+1][el])
                    
            num = num1 + (num2<<4)
            transform.append(num)

    return transform
                    
cube = [[[1,0,1,0],
         [0,1,0,1],
         [1,0,1,0],
         [0,1,0,1]],
        [[0,1,0,1],
         [1,0,1,0],
         [0,1,0,1],
         [1,0,1,0]],
        [[1,0,1,0],
         [0,1,0,1],
         [1,0,1,0],
         [0,1,0,1]],
        [[0,1,0,1],
         [1,0,1,0],
         [0,1,0,1],
         [1,0,1,0]]]

transform = transformToFrame(cube)


print "uint8_t frame[8] = {"
for a in range(0, len(transform),2):
    print "\t%s, %s," % (hex(transform[a]), hex(transform[a+1]))
print "};"
