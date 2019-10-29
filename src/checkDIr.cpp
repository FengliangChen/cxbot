#include "iostream"
#include "string"
#include "dirent.h"
#include "vector"

inline bool is_exist(const std::string & path){
	return  (opendir(path.c_str()) == NULL)?false:true;
}

inline bool is_hidden(const char *file){
	return (file[0] == '.')?true:false;
}

inline bool searchFile(const std::string& filename, const std::string& jobcode){
	std::size_t found = filename.find(jobcode);
	return (found != std::string::npos)?true:false;
}

std::string searchDir(const std::string &path, const std::string &jobcode){
	DIR *dp;
	struct dirent *dpt;
	dp=opendir(path.c_str());
	while((dpt = readdir(dp)) != NULL)
	{
		if (searchFile(dpt->d_name, jobcode)){
			if (!is_hidden(dpt->d_name))
				return dpt->d_name;
		}
	}
	return "";
}


void searchKind(const std::string &path, const std::string &kind, std::vector<std::string> &rt){
	DIR *dp;
	struct dirent *dpt;
	dp=opendir(path.c_str());
	while((dpt = readdir(dp)) != NULL){
		if (searchFile(dpt->d_name, kind)){
			if (!is_hidden(dpt->d_name))
			rt.push_back(dpt->d_name);
		}
		
	}
	return;
}



void get_jb_folder(const std::string &path1, const std::string &path2, const std::string &jobcode, std::string &rtpath){
	std::string temp;
	if (is_exist(path1)){
		temp = searchDir(path1, jobcode);
		if (temp.length() != 0){
			rtpath = path1 + "/" + temp;
			return;
		}else{
			if (is_exist(path2)) {
				temp = searchDir(path2, jobcode);
				if (temp.length() != 0){
					rtpath = path2 + "/" + temp;
					return;
				}
			}
		}

	}
}

void get_pf_path(const std::string &path1, const std::string &path2, const std::string &job,std::string &rtpath){
	std::string temp;
	std::string base;
	get_jb_folder(path1, path2, job,  base);
	if (base.length() == 0) {std::cout << "Can't not locate PF folder!" << std::endl; return;}
	temp = searchDir(base, ".xls");if(!temp.empty()) { rtpath = base + "/" + temp;return;}	
	temp = searchDir(base, ".xlsx");if (!temp.empty()) { rtpath = base + "/" + temp;return;}
}

void get_pdf_files(const std::string &path, std::vector<std::string> &rt){
	searchKind(path, ".pdf", rt);
}

void get_txt_files(const std::string &path, std::vector<std::string> &rt){
	std::vector<std::string> temp;
	searchKind(path, ".txt", temp);
	if(temp.size() == 0){return;}
	for(unsigned long i = 0; i < temp.size(); i++){
		std::string temps;
		temps = path;
		temps = temps + "/" +temp.at(i);
		rt.push_back(temps);
	}
}

void join_path(const std::string &base, std::vector<std::string> &files){
	for(unsigned long i = 0; i < files.size(); i++){
		files.at(i) = base + files.at(i);
	}
	return;
}

// int main(){
	// std::string path1 = "/Volumes/datavolumn_bmkserver_Pub/201910/1004";
	// std::string path2 = "/Volumes/datavolumn_bmkserver_Pub/201910/1003";
	// std::string filename;
	// std::string jobcode= "191014";
	// get_jb_folder(path1, path2, jobcode, filename);
	// std::cout << filename.length() << std::endl;
	// std::vector<std::string> pdfFiles;
	// searchKind(filename, ".pdf" ,pdfFiles);
	// for(auto i : pdfFiles){
	// 	std::cout << i << std::endl;
	// }
// 	std::string path1 = "/Volumes/datavolumn_bmkserver_Pub/新做稿/未开始";
// 	std::string path2 = "/Volumes/datavolumn_bmkserver_Pub/新做稿/进行中";
// 	std::string path3;
// 	std::string job = "191025";
// 	get_pf_path(path1,path2,job,path3);
// 	std::cout << path3 << std::endl;
// }
