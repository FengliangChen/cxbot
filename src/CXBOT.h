#ifndef CXBOT_H
#define CXBOT_H

extern inline bool is_exist(const std::string & path);

class timePath {
	std::string y, m, d;
	std::string basePath = "/Volumes/datavolumn_bmkserver_Pub/";
	public:
	timePath();
	timePath(const std::tm *now);
	std::string get_path();
};

struct tm_path {
	std::string today;
	std::string yesterday;
};

struct txts {
	int length;
	std::string *files;
	~txts(){delete (files); delete this; }
};

void PathConstruct(tm_path &path);

void get_jb_folder(const std::string &path1, const std::string &path2, const std::string &jobcode, std::string &rtpath);

void get_pf_path(const std::string &path1, const std::string &path2, const std::string &job,std::string &rtpath);

void get_pdf_files(const std::string &path, std::vector<std::string> &rt);

void get_txt_files(const std::string &path, std::vector<std::string> &rt);

void multiTxtContainer( std::vector<std::string> &paths, std::vector<struct txts *> &contain);

void pdfContainer(std::vector<std::string> &pdf, std::vector<struct txts *> &contain);

std::string get_head(int a);
std::string* get_tail(const std::string &path);

#endif
