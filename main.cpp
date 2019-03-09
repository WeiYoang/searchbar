//
//  main.cpp
//  DS
//
//  Created by WeiYoang on 3/6/19.
//  Copyright © 2018 WeiYoang. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "TestForFileStream.hpp"
WordNode* Search(WordNode* T, WordNode* NIL,std::string str);
void InorderTreeWalk(WordNode* );
int main(int argc,char* argv[]){
    using namespace std;
    if(argc!=3)
       cout<<"please, enter correct numbers of paramenter，file path and word you want to search should be included."<<endl;
    else{
           ifstream fin;
           DoubleList list;
           string str(argv[1]);
           if(str=="-r"){
                RBstructure(fin,list,argv[2]);
                InorderTreeWalk(list.getRBheader());
           } else {
                 RBstructure(fin,list,argv[1]);
                cout<<Search(list.getRBheader(),list.getNIL(),argv[2]);
           }
      }
        return 0;
};
