#include "ray.h"

Ray::Ray(){

}

Ray::~Ray(){

}

Ray::Ray(const Vec& o, const Vec& d){
  o_ = o;
  d_ = d;
  hrl = Hit_Record_List();
}

Vec Ray::origin() const{
  return o_;
}

Vec Ray::direction() const{
  return d_;
}

Vec Ray::point_at_t(float t){
  return o_ + d_*t;
}



Hit_Record::Hit_Record(float tval, const Vec& p, const Vec& n, const Vec& c){
  t = tval;
  point = Vec(p);
  normal = Vec(n);
  color = Vec(c);
}

Hit_Record::Hit_Record(const Hit_Record& other){
  t = other.t;
  point = Vec(other.point);
  normal = Vec(other.normal);
  color = Vec(other.color);
}

Hit_Record::~Hit_Record(){
}

Hit_Record_List::Hit_Record_List(){
  head = nullptr;
  length = 0;
}

Hit_Record_List::~Hit_Record_List(){
  while (head != nullptr){
    ListNode* temp = head->next;
    delete head;
    head->next = nullptr;
    head = temp;
  }
}

const Hit_Record& Hit_Record_List::operator[](int i) const{
  ListNode* temp = head;
  for (int j = 0; j < i; j++){
    temp = temp->next;
  }
  return temp->hr_;
}

void Hit_Record_List::addHR(const Hit_Record& hr){
  ListNode* temp = head;
  head = new ListNode(hr);
  head->next = temp;
  length++;
}

const Hit_Record& Hit_Record_List::find_first_hit(){
  ListNode* min = head;
  for (ListNode* i = min; i != nullptr; i=i->next){
    if (min->hr_.t > i->hr_.t){
      min = i;
    }
  }
  return min->hr_;
}

int Hit_Record_List::size(){return length;}


Hit_Record_List::ListNode::ListNode(const Hit_Record& hr) : hr_(hr), next(nullptr){

}

Hit_Record_List::ListNode::~ListNode(){

}
