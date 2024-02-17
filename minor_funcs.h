//compare content to find one end of the set in pole


void find_diff(void)
{
// in Ls2txt3.cpp, variables, be careful!!!!
    if (cntnt.Compare(prev_cnt) == 0) {
        Form1->RichEdit->Lines->Add("not yet start");
        end_flag = 0;
    } else {
        Form1->RichEdit->Lines->Add("found the end");
        end_flag = 1;
        end_col_ind = ii;
    }
}

