#ifndef OPENPF_H
#define OPENPF_H

#include "string"

extern "C" {
#include "myxls.h"
}

//void Oputxlsx(const std::string &path, std::string &txt);
std::string * Oputxlsx(const std::string &path);

class Tails {
public:
    std::string *tail;
    Tails(const std::string &path);
};

Tails::Tails(const std::string &path){
    if (path.find(".xlsx") != std::string::npos){
        this->tail = Oputxlsx(path);
	}else{
		char buf[256] = {0};
		Oputxls(path.c_str(),buf);
		this->tail = new std::string(buf);
	}
}



#endif
