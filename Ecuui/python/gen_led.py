import sys
# with open("output.txt", 'w') as sys.stdout:
#
#


class strap:
    def __init__(self):
        self.start = [1, -9]
        self.flr_h = 11  # height for each strap
        self.port_num = 3
        self.now_dir = [1, 0]  # moving port direction
        self.v_ang = [-1, 1]  # vector angle
        self.Flr_list = [1, 2, 3]
        self.PLlist = []
        self.pport = []
        self.floor_height = [1, 3, 3, 4, 4, 4, 4, 4, 4, 2]  # irregular floors

    # strget: read and write file, start points, strip dir, strip path, end points, strip amounts, list of length in the block, 2 more commands
    def strget(self, rd_file, wt_file):
        n = 0
        for line in rd_file.readlines():
            if n > 0:
                print(line)
                pat = line.split('|')
                self.c1(pat[1])
                self.c2(pat[5])
                self.c3(pat[2])
                self.c4(pat[3])
                self.str_proc(pat[6])
                self.bfs_on_port()
                self.strap_dfs(wt_file, 80, 1)
            n += 1

    def c1(self, mystr):  # string mystr converted to list start
        ind = mystr.split(', ')
        self.start = [int(ind[0]), int(ind[1])]

    def c2(self, mystr):  # string mystr converted to length of straps
        self.port_num = int(mystr)

    def c3(self, mystr):  # string mystr converted to direction of strap
        ind = mystr.split(', ')
        self.v_ang = [int(ind[0]), int(ind[1])]

    def c4(self, mystr):  # string mystr converted to list start
        ind = mystr.split(', ')
        case = ind[0].strip()
        if case == 'N/A':
            self.now_dir = [0, 0]
        else:
            self.now_dir = [int(ind[0]), int(ind[1])]

    # def cont_proc(self, #continuous processing function

    def bfs_on_port(self):
        buff = self.start
        self.PLlist = []
        for ii in range(self.port_num):
            # print(buff)
            self.PLlist.append(buff)
            buff = [buff[0] + self.now_dir[0], buff[1] + self.now_dir[1]]

    def str_proc(self, mystr):  # string mystr converted to length
        ind = mystr.split(', ')  # dividing into 3 cases
        self.Flr_list = []
        t_list = []
        for ii in range(len(ind)):
            if ind[ii].find('*') != -1:
                ind2 = ind[ii].split('*')
                self.seqre(int(ind2[0]), int(ind2[1]))
                # self.port_num = int(ind2[1])
                # self.strap_cord()
                # self.port_num -= int(ind2[1])
            elif ind[ii].find(':') != -1:
                ind2 = ind[ii].split(':')
                sta = int(ind2[0])
                edd = int(ind2[1])
                t_list = self.seq(
                    sta, edd) if sta < edd else self.seqbak(sta, edd)
                # self.strap_cord()
            else:
                ind2 = int(ind[ii])
                self.seqre(ind2, 1)
                # self.port_num = ind2
                # self.strap_cord()

    def seq(self, st, ed):
        # self.Flr_list = []
        for ii in range(st, ed+1):
            self.Flr_list.append(ii)

    def seqbak(self, st, ed):  # sequence backward
        # self.Flr_list = []
        for ii in range(st, ed-1, -1):
            self.Flr_list.append(ii)

    def seqre(self, ele, tm):  # sequence repeated
        # self.Flr_list = []
        for ii in range(tm):
            self.Flr_list.append(ele)

    # direction deg -45

    def strap_cord(self):  # start nodes
        # print("----------------")

        for jj in range(self.port_num):
            # global PLlist, pport
            self.PLlist.append(self.start)
            buff = self.start
            self.pport = self.start
            for ii in range(self.Flr_list[jj]):  # flr_h):
                # print(buff)
                buff = [buff[0]+self.v_ang[0], buff[1]+self.v_ang[1]]

            self.pport = [self.pport[0]+self.now_dir[0],
                          self.pport[1]+self.now_dir[1]]

    def strap_dfs(self, wt_file, block_size, option: int):
        # here block_merge is to print the led coordinate in the strap
        # option 0 is to initialize, option 1 is to read led file
        for jj in range(self.port_num):  # total num of ports in a block
            startup = self.PLlist[jj]
            # port_n is exact num of ports in jj-th port
            port_n = self.Flr_list[jj]
            Nled = 76
            print("----------------")
            scl_buff = []
            linetext = str(jj) + ','
            buff = startup
            scl_list = []

            # scaled coordinates and list of amount to leds in strip is
            # processed here
            for ii in range(port_n):  # flr_h):
                scl_buff = [buff[0]*block_size, buff[1]*block_size]  # scaling
                print(scl_buff)
                scl_list.append(scl_buff)
                buff = [buff[0]+self.v_ang[0], buff[1]+self.v_ang[1]]
                # if option > 0 :
                linetext = linetext + str(Nled) + ','
                # else :

            # grep amount of led bulbs and precess it
            self.block_merge(linetext, scl_list, block_size)
            linetext += '\n'
            print(linetext)
            wt_file.write(linetext)

    def block_merge(self, led_line, scl_list, block_size):
        # leng is length in "line of length" ,len_lin
        leng = led_line.split(',')
        for ii in range(len(leng)-2):  # first component and the one in the end doesn't count
            stt = scl_list[ii]
            vec = self.v_ang
            buff = stt
            for jj in range(int(leng[ii+1])):
                buff = [buff[0]+vec[0], buff[1]+vec[1]]
                print(buff)

        #

        # def str_scaling(self, block_size):
        #     for np in range(self.port_num):
        #         for cs in range(self.PLlist[np]):
        # self.start =

        # def str_test(self):

        # the end


def main():
    xx = strap()
    wd = open("east_led.txt", "w")
    rd = open("east_port.txt", "r")
    # rd2 = open("north_led.csv", "r")
    original = sys.stdout
    sys.stdout = open("myout.txt", 'w')
    xx.strget(rd, wd)
    sys.stdout = original
    rd.close()
    wd.close()
    # xx.str_proc();
    # Flr_list = seqre(Flr_list, flr_h, port_num)
    # Flr_list = seqbak(Flr_list, 10, 1)
    # xx.strap_cord()
    # port_num = port_num + 11
    # port_num = 29
    # Flr_list = seqre(Flr_list, 21, 7)
    # Flr_list = seqbak(Flr_list, 29,1)
    # strap_cord(Flr_list, port_num)


if __name__ == '__main__':
    main()

# direction deg 135
# Flr_list = range(1,9)
# for jj in range(port_num):
#    PLlist = [PLlist, pport]
#    buff = pport
#    for ii in range(flr_h):
#        print(buff)
#        buff = [buff[0]-1, buff[1]+1]
#
#    pport = [pport[0]+1, pport[1]]
#
# third wire pattern 135 deg, go up
# for jj in range(port_num):
#    PLlist = [PLlist, pport]
#    buff = pport
#    for ii in range(flr_h):
#        print(buff)
#        buff = [buff[0]-1, buff[1]+1]
#
#    pport = [pport[0], pport[1]-1]
#
#
