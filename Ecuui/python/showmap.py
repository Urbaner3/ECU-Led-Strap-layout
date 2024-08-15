import numpy as np
import matplotlib.pyplot as plt


def strget(rd_file):
    linnum = 0
    count = 0
    xx = []
    yy = []
    for line in rd_file.readlines():
        if line[0] == '[':
            line = line[1:-2]
            pat = line.split(', ')
            # print('strget', int(pat[0]), int(pat[1]), pat[0], pat[1])
            xx.append(int(pat[0]))
            yy.append(int(pat[1]))
        # gather data of xx and yy and print format

            count += 1
        # if count == 100000:
        #     break

    # print([xx, yy])
    return [xx, yy]


def getIntegers(string):
    numbs = [int(x) for x in string.split() if x.isnumeric()]
    return numbs


def d3read(rd_file) -> list:
    linnum = 0
    count = 0
    xx = []
    yy = []
    sigs = ['0', '333333', '555555']
    cuts = ['777777']
    cnt_cut = 0
    for line in rd_file.readlines():
        pat = line.split()
        if line[0] == '*':
            continue
        elif pat[0] in sigs:
            continue
        elif pat[0] in cuts:
            print("sig passed")
            continue

        else:
            # print(line)
            xx.append(int(pat[0]))
            yy.append(int(pat[1]))

        # if count > 10:
        #     break
        count += 1

    return [xx, yy]


def main():
    rd = open("east_led.txt", "r")
    # adding option here, to different rd file the precess function is chossen
    # the following plt asset is adopted
    # ans = d3read(rd)
    ans = strget(rd)
    x, y = (ans[0], ans[1])
    rd.close()

    # plot details
    # x = [5, 7, 8, 7, 2, 17, 2, 9, 4, 11, 12, 9, 6]
    # y = [99, 86, 87, 88, 111, 86, 103, 87, 94, 78, 77, 85, 86]
    # x = np.array(x)
    # y = np.array(y)
    plt.plot(x, y, 'r,')
    # plt.axis([0, 1000, 0, 2000])
    ax = plt.gca()
    ax.set_aspect('equal', adjustable='box')
    plt.show()


if __name__ == '__main__':
    main()
