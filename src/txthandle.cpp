#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "openpf.h"

struct txts {
	int length;
	std::string *files;
	~txts(){delete (files); delete this; }
};


struct txts * txtContainer(const std::string &path){
	std::streampos size;
	std::string temp;
	std::string alltxt;
	int count =0;
	char * memblock;

	std::ifstream txtfile;
	txtfile.open(path.c_str(), std::ios::binary|std::ios::ate);
	if (!txtfile.is_open()){ std::cout << "Unable to open txt file!" << '\n'; return NULL; }
	size = txtfile.tellg();
	memblock = new char [size];
	txtfile.seekg(0,std::ios::beg);
	txtfile.read(memblock, size);
	txtfile.close();
	for (int i=0; i<=size; i++){
		if (memblock[i] == 0xd){memblock[i] = 0xa;}
	}
	std::stringstream ss(memblock);
	delete[] memblock;

	while(std::getline(ss,temp)){
		temp.erase(temp.end()-4, temp.end());
		alltxt += temp + "\n";
		count++;
		//txt.push_back(temp);
	}
	struct txts *ptxt = new struct txts;
	ptxt -> length = count;
	ptxt -> files = new std::string(alltxt);
	return ptxt;
}

void multiTxtContainer( std::vector<std::string> &paths, std::vector<struct txts *> &contain){ //std::vector<struct txts *> &contain
	for(std::vector<std::string>::iterator it = paths.begin(); it != paths.end(); it++){
		contain.push_back(txtContainer(*it));
	}
	return;
}

void pdfContainer(std::vector<std::string> &pdf, std::vector<struct txts *> &contain){
	std::string temp;
	std::string temp1;
	int count = 0;

	for(std::vector<std::string>::iterator it = pdf.begin(); it != pdf.end(); it++){
		temp1 = (*it);
		temp1.erase(temp1.end()-4, temp1.end());
		temp += temp1 + "\n"; 
		count++;
	}
	struct txts *ptxt = new struct txts;
	ptxt -> length = count;
	ptxt -> files = new std::string(temp);
	contain.push_back(ptxt);
	return;
}

std::string get_head(int a){
	std::string head;
	switch (a)
	{
		case 1:
			head = "Hi Supplier,\n\nThe following 1 file is for your approval:\n\n";
			break;
		default:
			head = "Hi Supplier,\n\nThe following " + std::to_string(a) + " files are for your approval:\n\n";
			break;
	}
	return head;
}

std::string* get_tail(const std::string &path){
	Tails mytails(path);
	return mytails.tail;
}



// int main(){
// 	std::string filename = "/Users/imac-6/Desktop/U191047_FAV.txt";
// 	std::string filename2 = "/Users/imac-6/Desktop/C191059_ATY.txt";

// 	std::vector<std::string> paths;

// 	paths.push_back(filename);
// 	paths.push_back(filename2);


// 	std::vector<struct txts *> ptxts;
// 	pdfContainer( paths, ptxts);





	 
// 	// std::vector<txts> aa;
// 	// struct txts *txt;
// 	//  txt = txtContainer(filename);
	 

// 	std::cout << *(ptxts.at(0)->files) << '\n';
// 	std::cout << ptxts.at(0)->length << '\n';

// }

