//---------------------------------------------------------------------------

#pragma hdrstop

#include "Strap_bak.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <sysdyn.h>    //DynamicArray
#include <System.IOUtils.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>//TStringDynArray


Strap::Strap()
{
	int start[2] = { 0, 0 }, flr_h = 0, port_num= 0, now_dir[2] = { 0, 0 },
	v_ang[2] = { 0, 0 };
	std::vector<int> Flr_list = { 1, 2, 3 }, PLlist,
	floor_height = { 0 };

}
Strap::~Strap() {

}

void Strap::strget(std::ifstream &rd_file, std::ofstream &wt_file)
{
	String line;
	int n = 0;
	TStreamReader* Reader = new TStreamReader(rd_file);
	while (line = Reader->ReadLine() !=Null) {
        if (n > 0) {
			std::cout << line << std::endl;
			DynamicArray<String> *pat = new DynamicArray<String>();
			pat = SplitString(line, '|');
			start_read(pat->Strings[1]);
			colnum_read(pat->Strings[5]);
			vec_read(pat->Strings[2]);
			dir_read(pat->Strings[3]);
			str_proc(pat->Strings[6]);
			bfs_on_port();
			strap_dfs(wt_file, 80, 1);
        }
        n++;
    }
}

void Strap::start_read(const String &mystr)
{
	TStringList *ind = new TStringList();
	ind = split(mystr, ',');
	start = { std::stoi(ind[0]), std::stoi(ind[1]) };
}

void Strap::colnum_read(const String &mystr)
{
	port_num = std::stoi(mystr);
}

void Strap::vec_read(const String &mystr)
{
	TStringList *ind = new TStringList();
	ind = split(mystr, ',');
	v_ang = { std::stoi(ind[0]), std::stoi(ind[1]) };
}

void Strap::dir_read(const String &mystr)
{
	TStringList *ind = new TStringList();
	ind = split(mystr, ',');
	std::string case_str = trim(ind[0]);
	if (case_str == "N/A") {
        now_dir = { 0, 0 };
	} else {
        now_dir = { std::stoi(ind[0]), std::stoi(ind[1]) };
	}
}

void Strap::bfs_on_port()
{
	std::vector<int> buff = start;
	PLlist.clear();
	for (int ii = 0; ii < port_num; ++ii) {
		PLlist.push_back(buff);
		buff = { buff[0] + now_dir[0], buff[1] + now_dir[1] };
	}
}

void Strap::str_proc(const String &mystr)
{
	TStringList *ind = new TStringList();
	ind = split(mystr, ',');
	Flr_list.clear();
	int pc_fd;
    for (const auto &item : ind) {
		if (item.Find('*', &pc_fd) != std::string::npos) {
			TStringList *ind2 = new TStringList();
			ind2 = split(item, '*');
            seqre(std::stoi(ind2[0]), std::stoi(ind2[1]));
		} else if (item.Find(':', &pc_fd) != std::string::npos) {
			TStringList *ind2 = new TStringList();
			ind2 = split(item, ':');
            int sta = std::stoi(ind2[0]);
			int edd = std::stoi(ind2[1]);
            if (sta < edd) {
                seq(sta, edd);
            } else {
                seqbak(sta, edd);
            }
        } else {
            int ind2 = std::stoi(item);
            seqre(ind2, 1);
        }
    }
}

void Strap::seq(int st, int ed)
{
    for (int ii = st; ii <= ed; ++ii) {
        Flr_list.push_back(ii);
    }
}

void Strap::seqbak(int st, int ed)
{
    for (int ii = st; ii >= ed; --ii) {
        Flr_list.push_back(ii);
	}
}

void Strap::seqre(int ele, int tm)
{
	for (int ii = 0; ii < tm; ++ii) {
        Flr_list.push_back(ele);
    }
}

void Strap::strap_dfs(std::ofstream &wt_file, int block_size, int option)
{
	for (int jj = 0; jj < port_num; ++jj) {
		std::vector<int> startup = PLlist[jj];
		int port_n = Flr_list[jj];
		int Nled = 76;
		std::cout << "----------------" << std::endl;
		std::vector<int> scl_buff;
		std::string linetext = std::to_string(jj) + ",";
		std::vector<int> buff = startup;
		std::vector<std::vector<int> > scl_list;

		for (int ii = 0; ii < port_n; ++ii) {
			scl_buff = { buff[0] * block_size, buff[1] * block_size };
			std::cout << scl_buff[0] << " " << scl_buff[1] << std::endl;
			scl_list.push_back(scl_buff);
			buff = { buff[0] + v_ang[0], buff[1] + v_ang[1] };
			linetext += std::to_string(Nled) + ",";
		}

		block_merge(linetext, scl_list, block_size);
		linetext += "\n";
		std::cout << linetext;
		wt_file << linetext;
	}
}

void Strap::block_merge(const std::string &led_line,
    const std::vector<std::vector<int> > &scl_list, int block_size)
{
    TStringList *leng = new TStringList();
	TStringList leng = split(led_line, ',');
	for (size_t ii = 0; ii < leng.size() - 2; ++ii) {
		std::vector<int> stt = scl_list[ii];
		std::vector<int> vec = v_ang;
		std::vector<int> buff = stt;
        for (int jj = 0; jj < std::stoi(leng[ii + 1]); ++jj) {
            buff = { buff[0] + vec[0], buff[1] + vec[1] };
			std::cout << buff[0] << " " << buff[1] << std::endl;
        }
    }
}
TStringList *Strap::split(const std::string &s, char delimiter)
{

//	TStringList *tokens=new TStringList();
//	String token;
//	std::istringstream tokenStream;
//	tokenStream.str(s);
//	while (std::getline(tokenStream, token, delimiter)) {
//		tokens->Add(token);
//	}
//	return tokens;
}

std::string Strap::trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

int main()
{
    Strap xx;
    std::ofstream wd("east_led.txt");
    std::ifstream rd("east_port.txt");
    std::ofstream myout("myout.txt");

    // Redirect stdout to myout.txt
    std::streambuf* coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(myout.rdbuf());

	xx.strget(rd, wd);

    // Restore stdout
    std::cout.rdbuf(coutbuf);

	rd.close();
    wd.close();
    myout.close();

    return 0;
}

