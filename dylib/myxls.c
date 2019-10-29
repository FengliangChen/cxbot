
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <xls.h>

void Oputxls(const char *path, char *rt)
{
    xlsWorkBook* pWB;
    xlsWorkSheet* pWS;
    unsigned char buf[256] = {0};
    const char *linebreak = "\n";
    
    struct st_row_data* row;
    WORD t,tt;
    pWB=xls_open(path, "UTF-8");
    
    if (pWB!=NULL)
    {
        pWS=xls_getWorkSheet(pWB, 0); // first sheet
        xls_parseWorkSheet(pWS);
        
        for (t=5;t<=13;t++)
        {
            row=&pWS->rows.row[t];

                xlsCell *cell = &row->cells.cell[7];
                if(cell->id == 0x201) continue;
                //xls_showCell(cell);
            //printf("%s\n",cell->str);
            
            strcat(buf,cell->str);
            strcat(buf,linebreak);
        }
        strcpy(rt, buf);
        //printf("%s\n",buf);
        
        xls_close_WS(pWS); // close every sheet you open
        xls_close_WB(pWB); // close the sheet - can use xls_close(pWB) too
    } else {
        printf("pWB == NULL\n");
    }
    return ;
}

// int main(){
//     const char* path = "/Users/imac-6/Desktop/U191010_IMP_DetailList_W.xls";
//     char buf[255] = {0};
//     Oputxls(path, buf);
//     printf("%s\n",buf);
//     return 0;
// }
