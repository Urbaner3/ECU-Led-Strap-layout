//---------------------------------------------------------------------------

#ifndef StrapH
#define StrapH
//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <sysdyn.h>    //DynamicArray
#include <System.Types.hpp> //TStringDynArray
#include <System.StrUtils.hpp> //SplitString
#include <System.SysUtils.hpp> //TList

class Strap {
private:
    std::vector<int> start;
    int flr_h;
    std::vector<int> pport;
	std::vector<int> floor_height;

public:
	Strap();
	~Strap();
	TList *SplitString(const String& str, char delimiter);
	TList *Append(TList *arr, const String& value);
	void strget(std::ifstream& rd_file, std::ofstream& wt_file);

	void start_read(const String& mystr);
	void colnum_read(const String& mystr);
	void vec_read(const String& mystr);
	void dir_read(const String& mystr);
   void bfs_on_port();
	void str_proc(const String& mystr);
	void seq(int st, int ed);
	void seqbak(int st, int ed);
	void seqre(int ele, int tm);
	void strap_dfs(std::ofstream& wt_file, int block_size, int option);

	void block_merge(const String &led_line, const std::vector<std::vector<int>>& scl_list, int block_size);
    std::vector<int> v_ang;
    std::vector<int> Flr_list;
	std::vector<std::vector<int>> PLlist;
    int port_num;
    std::vector<int> now_dir;
};

int main();

#endif
