import sys
import pylightxl
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
        self.block_width = list()  # irregular floors
        self.bound = []  # [4, 9] means a strap starts in line 4 to line
        # 9
    """ strget: read and write file, start points, strip dir, strip path, end
     points , strip amounts, list of length in the block, 2 more commands
    """

    def strget(self, rd_file, wt_file, ledrd):
        n = 0
        for line in rd_file.readlines():
            if n > 0:
                print(line)
                pat = line.split('|')
                self.c1(pat[5])
                self.c2(pat[3])
                self.c3(pat[6])
                self.c4(pat[2])
                self.col_bound(pat[0], pat[1])
                self.str_proc(pat[4])
                self.bfs_on_port()
                self.strap_dfs(wt_file, ledrd, 80, 0)
            n += 1

    def c1(self, mystr):  # string mystr converted to list start
        ind = mystr.split(', ')
        self.start = [int(ind[0]), int(ind[1])]

    def c2(self, mystr):  # string mystr converted to length of straps
        self.port_num = int(mystr)
        self.block_width.append(self.port_num)

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
    def col_bound(self, str_b, str_e):
        begin = int(str_b)
        end = int(str_e)
        self.bound = [begin, end]

    def bfs_on_port(self):
        buff = self.start
        self.PLlist = []
        for ii in range(self.port_num):
            # print(buff)
            self.PLlist.append(buff)
            buff = [buff[0] + self.now_dir[0], buff[1] + self.now_dir[1]]

#  put the starts in PLlist

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

    # corresponds to row  in meta
    def read_strap_change(self, wt_file, ledrd, block_size, row_in_meta):
        # here I would read and check all length of straps
        # that is not 76, and then print the coordinates
        read_count = 1
        modified_straps_inblock = []
        for lines in ledrd.readlines():
            # jump to those rows in led file
            if read_count < row_in_meta[0]:
                read_count += 1
                continue
            elif read_count > row_in_meta[1]:
                break
            else:
                pat = lines.split(',')
                temp = []
                r_ct = read_count - row_in_meta[0]
                for items in range(len(pat)):
                    if items == 0:
                        temp.append(pat[items])
                    elif items == self.Flr_list[r_ct] + 1:
                        continue
                        # temp.append(pat[items])
                    elif pat[items]:
                        temp.append(pat[items])
                    else:
                        break

                pat = temp
                temp = []  # save the data in the line
                for items in range(len(pat)):
                    if items == 0:
                        continue
                    elif items > self.Flr_list[r_ct]:
                        continue
                    elif pat[items] != "76":
                        # return place
                        print(items, "th strip modified")
                        Nled = int(pat[items])
                        temp.append(Nled)
                    elif pat[items] == "76":
                        Nled = int(pat[items])
                        temp.append(Nled)
                        # modified_straps_inblock.append(Nled)
                    else:
                        print("row case overhead")
                        break

                modified_straps_inblock.append(temp)
                read_count += 1

        # for jj in range(self.port_num):  # total num of ports in a block
        #     startup = self.PLlist[jj]
        #     # port_n is exact num of ports in jj-th port
        #     port_n = self.Flr_list[jj]
        #     # else:
        #     #     # according to list, set Nled to corresponding value.
        #     #     for line in ledrd.readlines():
        #     #         print("line
        #
        #     print("----------------")
        #     scl_buff = []
        #     linetext = str(jj) + ','
        #     buff = startup
        #     scl_list = []
        #
        #     # scaled coordinates and list of amount to leds in strip is
        #     # processed here
        #     for ii in range(port_n):  # flr_h):
        #         Nled = stp_ls[ii]
        #         scl_buff = [buff[0]*block_size, buff[1]*block_size]  # scalin
        # g
        #         print(str(scl_buff[0])+' | '+str(scl_buff[1]))
        #         scl_list.append(scl_buff)
        #         buff = [buff[0]+self.v_ang[0], buff[1]+self.v_ang[1]]
        #         # if option > 0 :
        #         linetext = linetext + str(Nled) + ','
        #         # else :
        #
        #     # grep amount of led bulbs and precess it
        #     self.block_merge(linetext, scl_list, block_size)
        #     linetext += '\n'
        #     print(linetext)
        #     wt_file.write(linetext)

        return modified_straps_inblock

    def strap_dfs(self, wt_file, ledrd, block_size, option: int):
        # here block_merge is to print the led coordinate in the strap
        # option 0 is to initialize, option 1 is to read led file
        stp_ls = []
        # if option == 0:
        #     Nled = 76 # use 23 lines below instead
        if option == 1:
            # stp_ls is list of modified straps in length
            block_list = open("east_led_update.csv", "r")
            stp_ls = self.read_strap_change(
                wt_file, block_list, block_size, self.bound)
            block_list.close()
        for jj in range(self.port_num):  # total num of ports in a block
            startup = self.PLlist[jj]
            # port_n is exact num of ports in jj-th port
            port_n = self.Flr_list[jj]

            # end here
            print("----------------")
            scl_buff = []
            linetext = str(jj) + ','
            buff = startup
            scl_list = []

            # scaled coordinates and list of amount to leds in strip is
            # processed here
            for ii in range(port_n):  # flr_h):
                if option == 1 and stp_ls:
                    Nled = (stp_ls[jj])[ii]
                else:  # mainly option =1
                    Nled = 76

                scl_buff = [buff[0]*block_size, buff[1]*block_size]  # scaling
                # print(str(scl_buff[0])+' | '+str(scl_buff[1]))
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

    def get_strap_index(self, line: int, NthStrip: int):
        port_count = 0
        for it in range(len(self.block_width)):
            if port_count + self.block_width(it) > line:
                break  # break when the block contains the port
            else:
                port_count += self.block_width(it)

        # list data of block, port, strap
        return list((it+1), (line-port_count), NthStrip)

    def block_merge(self, led_line, scl_list, block_size):
        # leng is length in "line of length" ,len_lin
        leng = led_line.split(',')
        for ii in range(len(leng)-2):  # first component and the one in the end
            # doesn't count
            # mere block index and empty style type
            stt = scl_list[ii]
            vec = self.v_ang
            buff = stt
            for jj in range(int(leng[ii+1])):
                buff = [buff[0]+vec[0], buff[1]+vec[1]]
                # print(str(buff[0]) + ' | ' + str(buff[1]))
                print(buff)

        #

        # def str_scaling(self, block_size):
        #     for np in range(self.port_num):
        #         for cs in range(self.PLlist[np]):
        # self.start =

        # def str_test(self):

        # the end

    def modify(self):
        rd = open("east_port.txt", "r")
        wd = open("null.txt", "w")
        ledrd = open("east_led_update.csv", "r")
        original = sys.stdout
        sys.stdout = open("myout.txt", 'w')

        # read meta file and do the modification
        n = 0
        for line in rd.readlines():
            if n > 0:
                print(line)
                pat = line.split('|')
                self.c1(pat[5])
                self.c2(pat[3])
                self.c3(pat[6])
                self.c4(pat[2])
                self.col_bound(pat[0], pat[1])
                self.str_proc(pat[4])
                self.bfs_on_port()
                self.strap_dfs(wd, ledrd, 80, 1)
            n += 1

        # n += 1
        sys.stdout.close()
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


def main():
    xx = strap()
    wd = open("east_led.csv", "w")
    rd = open("east_port.txt", "r")
    ledrd = open("east_led.csv", "r")
    # rd2 = open("north_led.csv", "r")
    original = sys.stdout
    sys.stdout = open("myout.txt", 'w')
    xx.strget(rd, wd, ledrd)
    sys.stdout.close()
    sys.stdout = original
    rd.close()
    wd.close()
    ledrd.close()
    # xx.str_proc();
    # Flr_list = seqre(Flr_list, flr_h, port_num)
    # Flr_list = seqbak(Flr_list, 10, 1)
    # xx.strap_cord()
    # port_num = port_num + 11
    # port_num = 29
    # Flr_list = seqre(Flr_list, 21, 7)
    # Flr_list = seqbak(Flr_list, 29,1)
    # strap_cord(Flr_list, port_num)
    # xx = strap()
    # wait = input("Press Enter to continue.")
    xx.modify()


if __name__ == '__main__':
    main()
# elif __name__ == 'led_mod':

    # modify()

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
