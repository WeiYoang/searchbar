//
//  TestForFileStream.hpp
//  DS
//
//  Created by WeiYoang on 3/2/19.
//  Copyright © 2019 WeiYoang. All rights reserved.
//

#ifndef TestForFileStream_hpp
#define TestForFileStream_hpp

#include<iostream>
#include<cstring>
class WordNode{
    public:
        enum Color { red, black };
        WordNode* wordsLeftptr;
        WordNode* wordsRightptr;
        WordNode* samewordsPtr;
        WordNode* treeLeftptr;
        WordNode* treeRightptr;
        WordNode* treeParentptr;
        int color;
        std::string str;
    
        WordNode(std::string str=" ");
        ~WordNode();
        bool operator=(std::string str);
        bool operator<(std::string str);
        bool operator>(std::string str);
        friend std::ostream& operator<<(std::ostream& os,WordNode* clause);
};
class DoubleList{
    private:
        WordNode* RBheader;
        WordNode* NIL;
        WordNode* Dataheader;
        WordNode* Datatail;
        int count;
    public:
        DoubleList();
        ~DoubleList();
        int Count();
        bool isnull();
        WordNode* getRBheader();
        WordNode* getNIL();
        WordNode* getDataheader();
        WordNode* getdatatail();
        friend std::ostream& operator << (std::ostream& os,DoubleList& list);   
        friend void RBinsertFixup(DoubleList& list,WordNode* ptr);
        friend void RBstructure(std::ifstream& fin,DoubleList& list,std::string location); 
};


#endif /* TestForFileStream_hpp */
