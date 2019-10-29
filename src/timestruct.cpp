#include <iostream>
#include <string>
#include <ctime>

inline std::string itoa(int t){
	std::string temp;
	temp = std::to_string(t);
	if (t < 10) {
		temp = '0' + temp;
	}
	return temp;
}


class timePath {
	std::string y, m, d;
	std::string basePath = "/Volumes/datavolumn_bmkserver_Pub/";
	public:
	timePath();
	timePath(const std::tm *now);
	std::string get_path();
};

timePath::timePath(const std::tm *now){
	this->y = itoa(now->tm_year - 100 +2000);
	this->m = itoa(now->tm_mon+1);
	this -> d = itoa(now->tm_mday);
}

std::string  timePath::get_path(){
	std::string temp;
	temp = this->basePath + this->y + this->m + '/' + this->m + this->d;
	return temp;
}

inline void get_tm_struct(std::tm &td, std::tm &yd){
	time_t now = time(0);
	td = *std::localtime(&now);
	td.tm_mday-=1;
	std::time_t next = std::mktime(&td);
	yd = *std::localtime(&next);
	td.tm_mday+=1;
}

struct tm_path {
	std::string today;
	std::string yesterday;
};

void PathConstruct(tm_path &path){
	std::tm td;
	std::tm yd;
	get_tm_struct(td,yd);
	timePath today(&td);
	timePath yesterday(&yd);
	path.today = today.get_path();
	path.yesterday = yesterday.get_path();
}

// int main(){
// 	struct tm_path timepath;
// 	PathConstruct(timepath);
// 	std::cout << timepath.today << std::endl;
// 	std::cout << timepath.yesterday << std::endl;
// }






