#include<iostream>
#include<sstream>
using namespace std;
int main(){
	int w=0 ,i=0;
	int correct{0},wrong{0};
	string type,temp;
	string a;
	a="The quick movement of technology has transformed the way we live, work, and communicate.";
	cout<<a<<endl;
	cout<<"start your test"<<endl;
	getline(cin,type);
	istringstream iss(a);
	istringstream ss(type);
	istringstream count(type);
	while(count>>temp){
		w++;
	}
	cout<<w<<endl;
	string token;
	string shoken;
	
	while(iss>>token){
		i++;
		if(ss>>shoken){
	if (token==shoken){
		correct++;
	}
	else{
		wrong++;
	}
}
if(i==w){
	break;
}
}
	cout<<"mistakes: "<<wrong<<endl;
	cout<<"correct: "<<correct;
}
