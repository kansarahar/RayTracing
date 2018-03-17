#include "surface.h"

Surface_List::Surface_List(){
  head = nullptr;
  length = 0;
}

Surface_List::~Surface_List(){
  while (head != nullptr){
    ListNode* temp = head->next;
    delete head;
    head->next = nullptr;
    head = temp;
  }
}

const Surface& Surface_List::operator[](int i) const{
  ListNode* temp = head;
  for (int j = 0; j < i; j++){
    temp = temp->next;
  }
  return temp->s_;
}

void Surface_List::addSurface(const Surface& s){
  ListNode* temp = head;
  head = new ListNode(s);
  head->next = temp;
  length++;
}

int Surface_List::size(){return length;}


Surface_List::ListNode::ListNode(const Surface& s) : s_(s), next(nullptr){

}

Surface_List::ListNode::~ListNode(){

}
