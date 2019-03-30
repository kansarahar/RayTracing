#include "surface.h"

Surface_List::Surface_List(){
  slist = new Surface*[1];
  length_ = 0;
  capacity_ = 1;
  // head = nullptr;
  // length = 0;
}

Surface_List::~Surface_List(){
  for (int i = 0; i < capacity_; i++){
    if (slist[i] != nullptr){
      delete slist[i];
      slist[i] = nullptr;
    }
    //delete[] slist;
  }

  // while (head != nullptr){
  //   ListNode* temp = head->next;
  //   delete head;
  //   head->next = nullptr;
  //   head = temp;
  // }
}

Surface& Surface_List::operator[](int i){
  return *(slist[i]);
  // ListNode* temp = head;
  // for (int j = 0; j < i; j++){
  //   temp = temp->next;
  // }
  // return temp->s_;
}

void Surface_List::addSurface(Surface* s){
  if (capacity_ < length_+1){
    Surface** newslist = new Surface*[capacity_*2];
    capacity_*=2;
    for (int i = 0; i < capacity_; i++){
      if (i < length_){
        newslist[i] = slist[i];
        slist[i] = nullptr;
      }
      else{newslist[i] = nullptr;}
    }
    delete[] slist;
    slist = newslist;
  }
  slist[length_] = s;
  length_++;
  empty_ = false;
  // ListNode* temp = head;
  // head = new ListNode(s);
  // head->next = temp;
  // length++;
}

int Surface_List::size(){return length_;}
int Surface_List::capacity(){return capacity_;}
bool Surface_List::empty(){return empty_;}

// Surface_List::ListNode::ListNode(const Surface& s) : s_(s), next(nullptr){
//
// }
//
// Surface_List::ListNode::~ListNode(){
//
// }
