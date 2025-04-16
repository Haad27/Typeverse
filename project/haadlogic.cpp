#include<iostream>
#include<sstream>
using namespace std;
int correct{0},wrong{0};
void check(string a, string b){
	if(a==b){
		correct++;}
	else{
		wrong++;
	}
	
}


int main(){
	string type;
	string a="KIA HALL HAI";
	istringstream word(a);
	string save;
	while(word>>save){
		string input;
		char c;
		while ((c = getchar()) != ' ' && c != '\n') {
			input += c;
		}
		
		
		check(save,input);
	}
	cout<<"The correct are: "<<correct<<endl;
	cout<<"The wrong  are: " <<wrong;
}