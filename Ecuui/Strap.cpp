//---------------------------------------------------------------------------

#pragma hdrstop

#include "typeForm.h"
#include "Strap.h"
#include <System.IOUtils.hpp>
#include <System.Classes.hpp>//StreamReader

//---------------------------------------------------------------------------
#pragma package(smart_init)
 // Strap constructor and destructor
Strap::Strap()
{
	int start[2] = { 0, 0 }, flr_h = 0, port_num = 0, now_dir[2] = { 0, 0 }, v_ang[2] = { 0, 0 };
	std::vector<int> Flr_list = { 1, 2, 3 }, PLlist, floor_height = { 0 };
//	struct myvec{
//      int size;
//		TList *ind = new TList;
//		ind = SplitString(mystr, ',');
//		String* togopts[2];
//		for (int k = 0; k < 2; k++) {
//			togopts[k] = (String*)(ind->Items[k]);
//		}
//	};
//	start = { StrToInt(String(*(togopts[0]))), StrToInt(String(*(togopts[1]))) };
}
Strap::~Strap() {}

TList *Strap::SplitString(const String &str, char delimiter)
{
	TList* result = new TList; // Dynamic array to hold the substrings
	int start = 1; // Start from the first character in VCL Strings
	int end = 0; // To find the end of the substring
	int count = 0;
	String opr = String(str);
	// Loop until we reach the end of the string
	while (1) {
		end = opr.SubString(start, str.Length() - count).Pos(delimiter);
		if (end == 0) {
			break;
		}
		//else
		// Extract substring and add to result
		result = Append(result, opr.SubString(start, end - 1));
		count += end;
		start = count + 1; // Move start index past the delimiter
		//		opr = opr.SubString(start, opr.Length() - end);
	};

	// Add the last substring if any
	if (start <= str.Length()) {
		result = Append(result, str.SubString(start, str.Length() - start + 1));
	}

	return result;
}

TList *Strap::Append(TList *arr, const String &value)
{
	String* addstr1 = new String(value);
	arr->Add(addstr1); // Add new value at the end
	return arr;
}



void Strap::strget(std::ifstream &rd_file, std::ofstream &wt_file)
{
	String line;
	int n = 0;
	TStreamReader* Reader = new TStreamReader(new TFileStream("file.txt", fmCreate));
	while ((line = Reader->ReadLine()) != Null) {
		if (n > 0) {
			std::cout << line.c_str() << std::endl;
			TList *pat = new TList;
			pat = SplitString(line, '|');
			String* togopts[10];
			for (int k = 0; k < 10; k++) {
				togopts[k] = (String*)(pat->Items[k]);
			}
			start_read(String(*(togopts[1])));
			colnum_read(String(*(togopts[5])));
			vec_read(String(*(togopts[2])));
			dir_read(String(*(togopts[3])));
			str_proc(String(*(togopts[6])));
			bfs_on_port();
			strap_dfs(wt_file, 80, 1);
		}
		n++;
	}
	delete Reader; // Clean up the reader
}

void Strap::start_read(const String &mystr)
{
	TList *ind = new TList;
	ind = SplitString(mystr, ',');
	String* togopts[2];
	for (int k = 0; k < 2; k++) {
		togopts[k] = (String*)(ind->Items[k]);
	}
	start = { StrToInt(String(*(togopts[0]))), StrToInt(String(*(togopts[1]))) };
}

void Strap::colnum_read(const String &mystr)
{
	port_num = StrToInt(mystr.c_str());
}

void Strap::vec_read(const String &mystr)
{
	TList *ind = new TList;
	ind = SplitString(mystr, ',');
	String* togopts[2];
	for (int k = 0; k < 2; k++) {
		togopts[k] = (String*)(ind->Items[k]);
	}
	v_ang = { StrToInt(String(*(togopts[0]))), StrToInt(String(*(togopts[1]))) };
}

void Strap::dir_read(const String &mystr)
{
	TList *ind = new TList;
	ind = SplitString(mystr, ',');
	String* togopts[2];
	for (int k = 0; k < 2; k++) {
		togopts[k] = (String*)(ind->Items[k]);
	}
	String case_str = String(*(togopts[0])).Trim();
	if (case_str == "N/A") {
		now_dir = { 0, 0 };
	} else {
		now_dir = { StrToInt(String(*(togopts[0]))), StrToInt(String(*(togopts[1]))) };
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
	TList *ind = SplitString(mystr, ',');
	Flr_list.clear();

	for (const auto &item : ind) {
		if (item.Pos('*') != 0) {
			TStringDynArray ind2 = SplitString(item, '*');
			seqre(StrToInt(ind2[0]), StrToInt(ind2[1]));
		} else if (item.Pos(':') != 0) {
			TStringDynArray ind2 = SplitString(item, ':');
            int sta = StrToInt(ind2[0]);
            int edd = StrToInt(ind2[1]);
            if (sta < edd) {
				seq(sta, edd);
            } else {
                seqbak(sta, edd);
            }
        } else {
            int ind2 = StrToInt(item);
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
//    for (int jj = 0; jj < port_num; ++jj) {
//        std::vector<int> startup = PLlist[jj];
//        int port_n = Flr_list[jj];
//        int Nled = 76;
//        OutMemo->Lines->Add("----------------");
//		std::vector<int> scl_buff;
//		String linetext = IntToStr(jj) + ",";
//		std::vector<int> buff = startup;
//		std::vector<std::vector<int> > scl_list;
//
//		for (int ii = 0; ii < port_n; ++ii) {
//			scl_buff = { buff[0] * block_size, buff[1] * block_size };
//			OutMemo->Lines->Add(scl_buff[0] + " " + scl_buff[1]);
//			scl_list.push_back(scl_buff);
//			buff = { buff[0] + xx.v_ang[0], buff[1] + xx.v_ang[1] };
//			linetext += IntToStr(Nled);
//			linetext += ",";
//		}
//
//		xx.block_merge(linetext, scl_list, block_size);
//		linetext += "\n";
//		OutMemo->Lines->Add(linetext);
//        wt_file << linetext;
//    }
}

void Strap::block_merge(const String &led_line, const std::vector<std::vector<int>> &scl_list, int block_size)
{
	TStringDynArray leng = SplitString(led_line, ',');
    for (size_t ii = 0; ii < leng.size() - 2; ++ii) {
		std::vector<int> stt = scl_list[ii];
		std::vector<int> vec = v_ang;
        std::vector<int> buff = stt;
        for (int jj = 0; jj < StrToInt(leng[ii + 1].c_str()); ++jj) {
            buff = { buff[0] + vec[0], buff[1] + vec[1] };
            std::cout << buff[0] << " " << buff[1] << std::endl;
        }
    }
}


int main()
{
//	Strap xx;
////    std::ofstream wd("east_led.txt");
////    std::ifstream rd("east_port.txt");
//	std::ofstream myout("myout.txt");
//
//	TFileStream("file.txt", fmCreate);
//
//	// Redirect stdout to myout.txt
//	std::streambuf* coutbuf = std::cout.rdbuf();
//	std::cout.rdbuf(myout.rdbuf());
//
//	xx.strget(rd, wd);
//
//	// Restore stdout
//	std::cout.rdbuf(coutbuf);
//
//	rd.close();
//	wd.close();
//	myout.close();
//
//    return 0;
}
