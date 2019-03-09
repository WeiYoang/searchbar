//
//  TestForFileStream.cpp
//  DS
//
//  Created by WeiYoang on 3/6/19.
//  Copyright © 2019 WeiYoang. All rights reserved.
//
#include "TestForFileStream.hpp"
#include <fstream>
WordNode::WordNode(std::string str){
    wordsLeftptr=wordsRightptr=samewordsPtr=nullptr;
    treeLeftptr=treeRightptr=treeParentptr=nullptr;
    color=red;
    this->str=str;
}
WordNode::~WordNode(){
    
}
bool WordNode::operator=(std::string str){
    return this->str==str;
}
bool WordNode::operator<(std::string str){
    return this->str<str;
}
bool WordNode::operator>(std::string str){
    return this->str>str;
}
std::ostream& operator<<(std::ostream& os,WordNode* clause){
    if(clause->str!=" "&&clause!=nullptr){
            WordNode* temp=clause;
            while(clause->wordsLeftptr!=nullptr&&clause->wordsLeftptr->str!=".")
                clause=clause->wordsLeftptr;
            os<<"#:"<<std::endl;
            do{
                if(clause==temp){
                      os<<"@"<<clause->str<<" ";
                } else os<<clause->str<<" ";
                clause=clause->wordsRightptr;
            }while(clause!=nullptr&&clause->str!=".");
            os<<"."<<std::endl;
            if(temp->samewordsPtr!=nullptr)
            os<<temp->samewordsPtr;
    };
    return os;
}
DoubleList::DoubleList(){
    RBheader=Dataheader=Datatail=nullptr;
    NIL=new WordNode;
    NIL->color=WordNode::black;
    count=0;
}
DoubleList::~DoubleList(){
     WordNode* temp;
     while(Dataheader!=nullptr){
        temp=Dataheader;
        Dataheader=Dataheader->wordsRightptr;
        delete temp;
   } 
     delete NIL;
}
int DoubleList::Count(){
    return count;
}
bool DoubleList::isnull(){
    return Dataheader==nullptr;
}
WordNode* DoubleList::getRBheader(){
    return RBheader;
}
WordNode* DoubleList::getNIL(){
    return NIL;
}
WordNode* DoubleList::getDataheader(){
    return Dataheader;
}
WordNode* DoubleList::getdatatail(){
    return Datatail;
}
WordNode* Search(WordNode* T, WordNode* NIL,std::string str){
    if(T->str==str||T==NIL)
       return T; 
    if(T->str<str)
        return Search(T->treeRightptr,NIL,str);
    return Search(T->treeLeftptr,NIL,str);
}
std::ostream& operator<<(std::ostream& os,DoubleList& list){
    WordNode* temp=list.Dataheader;
    while(temp!=nullptr){
        os<<temp->str<<" ";
        temp=temp->wordsRightptr;
    }
    return os;
}
void leftrotate(WordNode** T,WordNode* NIL,WordNode* ptr){
    WordNode* temp=ptr->treeRightptr;
    ptr->treeRightptr=temp->treeLeftptr;
    if(temp->treeLeftptr!=NIL)
        temp->treeLeftptr->treeParentptr=ptr;
    temp->treeParentptr=ptr->treeParentptr;
    if(ptr->treeParentptr==NIL)
        *T=temp;
    else if(ptr==ptr->treeParentptr->treeLeftptr)
        ptr->treeParentptr->treeLeftptr=temp;
    else ptr->treeParentptr->treeRightptr=temp;
    temp->treeLeftptr=ptr;
    ptr->treeParentptr=temp;
}
void rightrotate(WordNode** T,WordNode* NIL,WordNode* ptr){
    WordNode* temp=ptr->treeLeftptr;
    ptr->treeLeftptr=temp->treeRightptr;
    if(temp->treeRightptr!=NIL)
        temp->treeRightptr->treeParentptr=ptr;
    temp->treeParentptr=ptr->treeParentptr;
    if(ptr->treeParentptr==NIL)
        *T=temp;
    else if(ptr==ptr->treeParentptr->treeLeftptr)
        ptr->treeParentptr->treeLeftptr=temp;
    else ptr->treeParentptr->treeRightptr=temp;
    temp->treeRightptr=ptr;
    ptr->treeParentptr=temp;
}
void RBinsertFixup(DoubleList& list,WordNode* ptr){
    while(ptr->treeParentptr->color==WordNode::red){
        WordNode* temp1;
        if(ptr->treeParentptr==ptr->treeParentptr->treeParentptr->treeLeftptr){
            temp1=ptr->treeParentptr->treeParentptr->treeRightptr;
            if(temp1->color==WordNode::red){
                ptr->treeParentptr->color=WordNode::black;
                temp1->color=WordNode::black;
                ptr->treeParentptr->treeParentptr->color=WordNode::red;
                ptr=ptr->treeParentptr->treeParentptr;
            }
            else {
                    if(ptr==ptr->treeParentptr->treeRightptr){
                    ptr=ptr->treeParentptr;
                    leftrotate(&(list.RBheader),list.NIL,ptr);
                   }
               ptr->treeParentptr->color=WordNode::black;
               ptr->treeParentptr->treeParentptr->color=WordNode::red;
               rightrotate(&(list.RBheader),list.NIL,ptr->treeParentptr->treeParentptr);
            }
        } else {
            temp1=ptr->treeParentptr->treeParentptr->treeLeftptr;
            if(temp1->color==WordNode::red){
                ptr->treeParentptr->color=WordNode::black;
                temp1->color=WordNode::black;
                ptr->treeParentptr->treeParentptr->color=WordNode::red;
                ptr=ptr->treeParentptr->treeParentptr;
            }
            else{
                if(ptr==ptr->treeParentptr->treeLeftptr){
                    ptr=ptr->treeParentptr;
                    rightrotate(&(list.RBheader),list.NIL,ptr);
                }
                ptr->treeParentptr->color=WordNode::black;
                ptr->treeParentptr->treeParentptr->color=WordNode::red;
                leftrotate(&(list.RBheader),list.NIL,ptr->treeParentptr->treeParentptr);
            }
        }
    }
    list.RBheader->color=WordNode::black;  
}
void RBstructure(std::ifstream& fin,DoubleList& list,std::string location){
   fin.open(location);
   std::string str;
   WordNode *temp1,*temp2,*temp3=nullptr;
   while(fin>>str){
      temp3=new WordNode(str);
      list.count++;
      if(list.Dataheader==nullptr){
            list.Dataheader=list.Datatail=temp3;
      } else{
            list.Datatail->wordsRightptr=temp3;
            temp3->wordsLeftptr=list.Datatail;
            list.Datatail=temp3;
      }
      if(str!="."&&str!=","&&str!=":"&&str!=";"){
      for(temp1=list.NIL,temp2=list.RBheader;temp2!=list.NIL&&temp2!=nullptr;){
            temp1=temp2;
            if(str==temp2->str) break;
                else  if(str<temp2->str)
                             temp2=temp2->treeLeftptr;
                     else temp2=temp2->treeRightptr;
        }

      if(str==temp1->str){
          while(temp1->samewordsPtr!=nullptr)
                temp1=temp1->samewordsPtr;
            temp1->samewordsPtr=temp3;
          //  continue;
      } else{
          temp3->treeParentptr=temp1;
          if(temp1==list.NIL)
             list.RBheader=temp3;
          else if(str<temp1->str)
              temp1->treeLeftptr=temp3;
          else temp1->treeRightptr=temp3;
          temp3->treeLeftptr=temp3->treeRightptr=list.NIL;
          RBinsertFixup(list,temp3);
      }
       }
   }
   fin.close();
}
void InorderTreeWalk(WordNode* ptr){
    if(ptr!=nullptr&&ptr->str!=" "){
        InorderTreeWalk(ptr->treeLeftptr);
        std::cout<<ptr->str<<" ";
        InorderTreeWalk(ptr->treeRightptr);
    }
}
