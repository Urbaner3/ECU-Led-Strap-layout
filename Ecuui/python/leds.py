a = [80, -720]  # start point
b = [1, -1]
c = a
for ii in range(37):
    c = [c[0]+b[0], c[1]+b[1]]
    print(c)
