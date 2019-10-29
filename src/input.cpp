#include <iostream>
#include <string>
#include <vector>
#include "CXBOT.h"

int main( int arg, char *argv[] ){
	const std::string PubBasePath("/Volumes/datavolumn_bmkserver_Pub"); 
	const std::string PFbasePath1("/Volumes/datavolumn_bmkserver_Pub/新做稿/未开始"); 
	const std::string PFbasePath2("/Volumes/datavolumn_bmkserver_Pub/新做稿/进行中"); 
	const char * job;
	if (!is_exist(PubBasePath)){
		std::cout << "Please check if the server is connected." << '\n';
		return 1;
	}

	if (arg == 2){
		job = argv[1]; // need to check the length of digits.
	}else{
		std::cout << "please input the job#" << '\n';
		return 1;
	}

	struct tm_path timepath;
	PathConstruct(timepath);
	std::string jb_path;

	get_jb_folder(timepath.today, timepath.yesterday, job, jb_path);

	if(jb_path.length() == 0) {
		std::cout << "can't locate the job in today and yesterday." << '\n';
		return 1;
	}

	std::vector<std::string> txtFiles;
	get_txt_files(jb_path, txtFiles);

	std::vector<struct txts *> bodies;

	if(txtFiles.size() != 0) {
		multiTxtContainer(txtFiles, bodies);
	}else{
		std::cout << "can't locate the txt in the job folder." << '\n';
		get_pdf_files(jb_path, txtFiles);
		if(txtFiles.size() == 0){ std::cout << "no .pdf either!" << '\n'; return 1 ;}
		pdfContainer(txtFiles,bodies);
	}

	std::string PFpath;
	get_pf_path(PFbasePath1, PFbasePath2, job, PFpath);
	if (PFpath.length() == 0) {return 1;};
	std::string *txttail = get_tail(PFpath);

	std::string combiner;

	for (unsigned long i = 0; i < bodies.size(); i++){
		combiner += get_head(bodies.at(i)->length);
		combiner += *(bodies.at(i)->files);
        combiner += "\n";
		combiner += *txttail;
	}

	std::cout << combiner;
	
}
