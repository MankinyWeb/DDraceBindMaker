#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
inline void Clear(){
	system("cls");
}
struct Item{
	string info;
	string English, Chinese;
	int Count(){
		int argc = 0;
		for(size_t i=0;i<info.size();i++){
			if(i != 0 && info[i] == '&' && info[i-1] != '|'){
				argc ++;
			}
		}
		return argc;
	}
	vector <string> operator -(){
		vector <string> ret;
		for(int i=1;i<=Count();i++){
			string c;
			cout << "Parameter " << i << " : ";
			cin >> c;
			ret.push_back(c);
		}
		return ret;
	}
	string operator +(vector <string> getAsk){
		int asked = 0;
		string ret = info;
		for(size_t i=0;i<ret.size();i++){
			if(i != 0 && ret[i] == '&' && ret[i-1] != '|'){
				ret = ret.substr(0, i) + getAsk[asked] + ret.substr(i + 1);
				asked ++;
			}
		}
		return ret;
	}
	void show(){
		cout << English << " \n   " << Chinese << " \n   { ";
		int argc = 1;
		for(size_t i=0;i<info.size();i++){
			if(info[i] == '|'){
				continue;
			}
			if(info[i] == '&' && info[i-1] != '|'){	
				cout << "[Parameter " << argc << " ]";
				argc ++;
			}else{
				if(info[i] == '&' && info[i-1] == '|'){
					continue;
				}else cout << info[i];
			}
		}
		cout << "}\n";
	}
	string showedStr(){
		string ret;
		for(size_t i=0;i<info.size();i++){
			if(info[i] == '|'){
				continue;
			}
			if(info[i] == '&'){	
				continue;
			}
			ret += info[i];
		}
		return ret;
	}
} items[100000];
class Bind{
	public:
		string bind;
		void operator =(string str){
			bind = str;
		}
		void operator +=(Item item){
			string info = ( item + ( - item ) );
			for(size_t i=0;i<bind.size();i++){
				if(bind[i] == '&' && bind[i-1] != '|'){
					bind = bind.substr(0, i) + info + bind.substr(i + 1);
				}
				if(bind[i] == '&' && bind[i-1] == '|'){
					bind[i-1] = ' ';
				}
			}
		}	
		string showedStr(){
			string ret;
			for(size_t i=0;i<bind.size();i++){
				if(bind[i] == '|'){
					continue;
				}
				if(bind[i] == '&'){	
					continue;
				}
				ret += bind[i];
			}
			return ret;
		}
};
void Print(Bind bind){		
	for(size_t i=0;i<bind.bind.size();i++){
		if(bind.bind[i] != '&'){
			cout << bind.bind[i];
		}
	}
	return ;
}
void PutInPath(string bindy){
	string appdata_path = getenv("APPDATA");
	string file_path = appdata_path + "\\DDNet\\settings_ddnet.cfg";
    fstream file;
    file.open(file_path.c_str(), ios::app | ios::out);
    cout << "Opening " << file_path << ".\n";
    if (file.is_open()) {
        cout << "File opened successfully!" << endl;
        file << "\necho Welcome To Use BindMaker by Manki.\n";
        file << bindy << "\n";
        cout << "Import Successfully.\n";
    }
    else {
        cout << "Failed to open file." << endl;
    }
}
void Color(int a){
    if(a==0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    if(a==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
    if(a==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
    if(a==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
    if(a==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
    if(a==5) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
    if(a==6) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
}
string NextPage, Finish;
int main(int argc, char* argv[]){
	ios::sync_with_stdio(false);
	cout << argc;
	if(argc > 1){
		cout << argv[1];
		getchar();
		fstream file2;
		file2.open(argv[0], ios::app | ios::out);
		string newbind;
		getline(file2, newbind);
		cout << newbind << "?";
		PutInPath(newbind);
		getchar();
		return 0;
	}
	Bind bind;
	bind = "&";
	
	string now;
	fstream file;
	file.open("Binds_BindMaker.binds", ios::in | ios::out);
	int line;
	file >> line;
	getline(file, items[0].info);
	getline(file, NextPage);
	getline(file, Finish);
	for(int i=0;i<line;i++){
		getline(file, items[i].info);
		getline(file, items[i].Chinese);
		getline(file, items[i].English);
	}
	system("C:\\Windows\\system32\\chcp 65001");
	int page = 1;
	while(1){
		Clear();
		Color(6);
		cout << "[ "; 
		Print(bind);
		cout << " ]\n\n";
		Color(0);
		cout << "Page " << page << " of " << ceil(line/5.0) << "\n\n";
		for(int i=(page-1)*5;i<((page-1)*5+min(5,line-((page-1)*5)));i++){
			cout << i+1 << ". ";
			items[i].show();
		}
		cout << "\n\n" << NextPage << "\nPress N Next Page, B Back.\n\n";
		cout << Finish << "\nFinish? Press F Import Bind Into Rhe Game.\n";
		char c;
		cin >> c;
		if(c == 'N' || c == 'n'){
			if(page < ceil(line/5.0)){
				page++;
			}
		}else if(c == 'B' || c == 'b'){
			if(page > 1){
				page--;
			}
		}else if(c == 'F' || c == 'f'){
			PutInPath(bind.showedStr());
		}else bind += items[c-1-'0'];
	}
	return 0;
}
