#include <xlnt/xlnt.hpp>
#include <string>
//#include "openpf.h"


std::string * Oputxlsx(const std::string &path)
{
    std::string *ptxt = new std::string();
    xlnt::workbook wb;
    wb.load(path);
    xlnt::worksheet ws = wb.active_sheet();
    xlnt::column_t A = "H";
    xlnt::row_t R;
    for(int i = 5; i<=12; ++i){
        R = i;
        *ptxt = *ptxt + ws.cell(A,R).to_string();
        *ptxt += "\n";
    }
    return ptxt;
}

