#include <string.h>

#include "interface.hpp"
//#include "tool.h"
//#include "rec.h"
//#include "mix.h"

using namespace std;

int interface::Addition(int x, int y){
   return (x + y);
}
 
int interface::Multiply(int x, int y){
   return (x * y);
}

//void interface :: checkArgs(){
//    while(argc > 0){
//        if(argv[1][0]=='-'){
//	    if(argv[1][1] == 'r')
//		cout << "rec!";
//	    else if(argv[1][1] == 'm')
//		cout << "mix!";
//	    else {
//		printf("error: unrecognisedd option %s\n", argv[1]);
//		return 1;
//	    }
//	    argc--;
//	    argv++;
//	}
//    }
//}

//void interface :: setOptions(string op){
	t.getCs(op).
//}
