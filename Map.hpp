#include <utility>
#include <initializer_list>
#include <iostream>
#include <cmath>
#include <ctime>
#include <stdexcept>
#include <typeinfo>

#define MAX_HEIGHT 32

namespace cs540{  
  
  template <typename Key_T, typename Mapped_T> class Map {
    
  private:
    // Member Type
    typedef std::pair<const Key_T, Mapped_T> ValueType;
    
    // Node definition
    typedef struct Node{
      ValueType kv;
      Node* forwards[MAX_HEIGHT];
      Node* backwards[MAX_HEIGHT];
      Node(ValueType keyValue) : kv(keyValue){
	for(int i = 0; i < MAX_HEIGHT; i++){
	  forwards[i] = nullptr;
	  backwards[i] = nullptr;
	}
      }
      ~Node(){
      }
      
    }Node;

    // Skip list head
    Node* head[MAX_HEIGHT];
    
    // Current max level 
    size_t max_level;

    // Helper functions for obtaining random height to insert node
    float frand() {
      return (float) rand() / RAND_MAX;
    }
    int randomLevel(){
      static bool seeded = false;
      if(!seeded){
	srand((unsigned)time(NULL));
	seeded = true;
      }
      int newLevel = (int)(log(frand())/log(1.-.5));
      if(newLevel < MAX_HEIGHT-1){
	return newLevel;
      }
      else{
	return MAX_HEIGHT-1;
      }
    }

    Node* findNode(const Key_T &k) const{
      Node* current = head[max_level];
      for(int i = max_level; i >= 0; i--){
	while(current->forwards[i] != nullptr && (current->forwards[i]->kv.first < k || current->forwards[i]->kv.first == k)){
	  current = current->forwards[i];
	}
      }
      return current;
    }


  public:
    // Forward declare nested class for visibility in free funcitons
    class Iterator;
    class ConstIterator;
    class ReverseIterator;
    // Define nested classes

    class Iterator{
      friend class Map;
      friend class ConstIterator;
      friend class ReverseIterator;
    private:
      Node* nPtr;
    public:
      Iterator(){}
      Iterator(Node* n) : nPtr(n){}
      Iterator(const Iterator &i){}
      ~Iterator(){}
      Iterator& operator=(const Iterator &){}
      Iterator &operator++(){
	nPtr = nPtr->forwards[0];
	return *this;
      }
      Iterator operator++(int){
	Iterator temp = Iterator(nPtr);
	nPtr = nPtr->forwards[0];
	return temp;
      }
      Iterator &operator--(){
	nPtr = nPtr->backwards[0];
	return *this;
      }
      Iterator operator--(int){
	Iterator temp(nPtr);
	nPtr = nPtr->backwards[0];
	return temp;
      }
      ValueType &operator*() const{
	return nPtr->kv;
      }
      ValueType *operator->() const{
	return &(nPtr->kv);
      }
      bool operator==(const Iterator &i){
	return (nPtr == i.nPtr);
      }
      bool operator!=(const Iterator &i){
	return (nPtr != i.nPtr);
      }
      bool operator==(const ConstIterator &i){
	return (nPtr == i.nPtr);
      }
      bool operator!=(const ConstIterator &i){
	return (nPtr != i.nPtr);
      }
      bool operator==(const ReverseIterator &i){
	return (nPtr == i.nPtr);
      }
      bool operator!=(const ReverseIterator &i){
	return (nPtr != i.nPtr);
      }
    };
    
    class ConstIterator{
      friend class Iterator;
      friend class ReverseIterator;
    private:
      Node* nPtr;
    public:
      ConstIterator(Node* n) : nPtr(n){}
      const ValueType &operator*() const{
	return nPtr->kv;
      }
      const ValueType *operator->() const{
	return &(nPtr->kv);
      }
      bool operator==(const Iterator &i){
	return (nPtr == i.nPtr);
      }
      bool operator!=(const Iterator &i){
	return (nPtr != i.nPtr);
      }
      bool operator==(const ConstIterator &i){
	return (nPtr == i.nPtr);
      }
      bool operator!=(const ConstIterator &i){
	return (nPtr != i.nPtr);
      }
      bool operator==(const ReverseIterator &i){
	return (nPtr == i.nPtr);
      }
      bool operator!=(const ReverseIterator &i){
	return (nPtr != i.nPtr);
      }
    };
    
    class ReverseIterator{
      friend class Iterator;
      friend class ConstIterator;
    private:
      Node* nPtr;
    public:
      ReverseIterator(Node* n) : nPtr(n){}
      ReverseIterator &operator++(){
	nPtr = nPtr->backwards[0];
	return *this;
      }
      ReverseIterator operator++(int){
	ReverseIterator temp(nPtr);
	nPtr = nPtr->backwards[0];
	return temp;
      }
      ReverseIterator &operator--(){
	nPtr = nPtr->forwards[0];
	return *this;
      }
      ReverseIterator operator--(int){
	ReverseIterator temp(nPtr);
	nPtr = nPtr->forwards[0];
	return temp;
      }
      ValueType *operator->() const{
	return &(nPtr->kv);
      }
      bool operator==(const Iterator &i){
	return (nPtr == i.nPtr);
      }
      bool operator!=(const Iterator &i){
	return (nPtr != i.nPtr);
      }
      bool operator==(const ConstIterator &i){
	return (nPtr == i.nPtr);
      }
      bool operator!=(const ConstIterator &i){
	return (nPtr != i.nPtr);
      }
      bool operator==(const ReverseIterator &i){
	return (nPtr == i.nPtr);
      }
      bool operator!=(const ReverseIterator &i){
	return (nPtr != i.nPtr);
      }
    };
    
    // Constructor & Assingment Operator
    Map(){
      max_level = 0;
      for(int i = 0; i < MAX_HEIGHT; i++){
	head[i] = nullptr;
      }
    }
    Map(const Map &m){
      max_level = m.max_level;
      Node* current = m.head[0];
      for(int i = 0; i < MAX_HEIGHT; i++){
	while(current != nullptr && current->forwards[i] != nullptr){
	  head[i];
	}
      }
    }
    Map &operator=(const Map&){

    }
    Map(std::initializer_list<std::pair<const Key_T, Mapped_T> > lst){
      max_level = 0;
      for(int i = 0; i < MAX_HEIGHT; i++){
	head[i] = nullptr;
      }
      for(auto it = lst.begin(); it != lst.end(); it++){
	insert(*it);
      }
    }
    ~Map(){
      Node* current = head[0];
      while(current != nullptr){
	Node* temp = current;
	current = current->forwards[0];
	delete temp;
      }
    }
    void print(){
      for(Iterator it = begin(); it != end(); it++){
	std::cout << it->first << std::endl;
      }
    }

    void rprint(){
      Node* current = head[0];
      while(current->forwards[0] != nullptr){
	current = current->forwards[0];
      }
      while(current != nullptr){
	std::cout<< current->kv.first<<std::endl;
	current = current->backwards[0];
      }
    }
    // Size
    size_t size() const{
      int count = 0;
      Node* current = head[0];
      while(current != nullptr){
	count++;
	current = current->forwards[0];
      }
      return count;
    }
    bool empty() const{
      return head[0] == nullptr;
    }
    
    // Iterators
    Iterator begin(){
      Iterator b(head[0]);
      return b;
    }
    Iterator end(){
      Iterator e(nullptr);
      return e;
    }
    ConstIterator begin() const{
      ConstIterator b(head[0]);
      return b;
    }
    ConstIterator end() const{
      ConstIterator e(nullptr);
      return e;
    }
    ReverseIterator rbegin(){
      Node* current = head[0];
      while(current->forwards[0] != nullptr){
	current = current->forwards[0];
      }
      ReverseIterator rb(current);
      return rb;
    }
    ReverseIterator rend(){
      ReverseIterator re(nullptr);
      return re;
    }
    
    // Element Access
    Iterator find(const Key_T &kIn){
      Node* current = head[max_level];
      if(current == nullptr){
	std::cout<<"NOT FOUND-EMPTY" <<std::endl;
	return end();
      }
      else{
	std::cout<<"SEARCHING"<<std::endl;
	for(int i = max_level; i >=0; i--){
	  while(current->forwards[i] != nullptr && (current->forwards[i]->kv.first < kIn || current->forwards[i]->kv.first == kIn)){
	    current = current->forwards[i];
	  } 
	}
      
	if(current->kv.first == kIn){
	  Iterator found(current);
	  std::cout<<"FOUND"<<std::endl;
	  return found;
	}
	else{
	  std::cout<<"NOT FOUND"<<std::endl;
	  return end();
	}
      }
    }
    ConstIterator find(const Key_T& k) const{
      Node* n = findNode(k);
      ConstIterator ci(n);
      return ci;
    }
    Mapped_T &at(const Key_T &k){
      Node* n = findNode(k);
      if(n->kv.first == k){
	return n->kv.second;
      }
      else{
	throw std::out_of_range("Key Not Found");
      }
    }
    const Mapped_T &at(const Key_T &k) const{
      Node* n =findNode(k);
      if(n->kv.first ==k){
	return n->kv.second;
      } 
      else{
        throw std::out_of_range("Key Not Found");
      }
    }
    Mapped_T &operator[](const Key_T &k){
      Node* update[MAX_HEIGHT];
      Node* current = head[max_level];
      std::pair<Key_T,Mapped_T> kv;
      kv.first = k;
      if(current == nullptr){
	current = new Node(kv);
	std::cout<<"Inserting new Node at head["<<max_level<<"]"<<std::endl;
	for(int i = 0; i < MAX_HEIGHT; i++){
	  head[i] = current;
	}
      }
      else{
	for(int i = max_level; i >= 0; i--){
	  while(current->forwards[i] != nullptr && (current->forwards[i]->kv.first < k || current->forwards[i]->kv.first == k)){
	    current = current->forwards[i];
	  }
	  update[i] = current;
	}
	
	if(current->kv.first == k){
	  return current->kv.second;
	}
	else if(current->kv.first > k){
	  // for the case when inserted key is smaller than current smallest
	  current = new Node(kv);
	  for(int i = 0; i < MAX_HEIGHT; i++){
	    update[i] = head[i];
	    head[i] = current;
	    current->forwards[i] = update[i];
	    if(update[i] != nullptr){
	      update[i]->backwards[i] = current;
	    }
	  }
	}
	else{
	  current = new Node(kv);
	  int insertLevel = randomLevel();
	  if(insertLevel > max_level){
	    for(int i = max_level+1; i <= insertLevel; i++){
	      update[i] = head[i];
	    }
	    max_level = insertLevel;
	  }
	  for(int i = 0; i <= max_level; i++){
	    if(update[i] == nullptr){
	      current->forwards[i] = nullptr;
	      current->backwards[i] = nullptr;
	      head[i] = current;
	    }
	    else{
	      current->forwards[i] = update[i]->forwards[i];
	      current->backwards[i] = update[i];
	      update[i]->forwards[i] = current;
	    }
	  }
	}
      }
      return current->kv.second;
    }
    
    // Modifiers
    std::pair<Iterator, bool> insert(const ValueType &kvIn){
      std::cout<<"INSERTING"<<std::endl;
      std::pair<Iterator, bool> p;
      bool inserted;
      Node* update[MAX_HEIGHT];
    
      Node* current = head[max_level];
      if(current == nullptr){
	current = new Node(kvIn);
	std::cout<<"Inserting new Node at head["<<max_level<<"]"<<std::endl;
	for(int i = 0; i < MAX_HEIGHT; i++){
	  head[i] = current;
	}
	inserted = true;
      }
      else{
	for(int i = max_level; i >= 0; i--){
	  std::cout<<"level: "<<i<<std::endl;
	  while(current->forwards[i] != nullptr && (current->forwards[i]->kv.first < kvIn.first || current->forwards[i]->kv.first == kvIn.first)){
	    current = current->forwards[i];
	  }
	  update[i] = current;
	}

	if(current->kv.first == kvIn.first){
	  inserted = false;
	  Iterator it(current);	  
	  std::cout<<"NOT INSERTED: ALREADY EXISTS"<<std::endl;
	}
	else if(current->kv.first > kvIn.first){
	  // for the case when inserted key is smaller than current smallest
	  current = new Node(kvIn);
	  for(int i = 0; i < MAX_HEIGHT; i++){
	    update[i] = head[i];
	    head[i] = current;
	    current->forwards[i] = update[i];
	    if(update[i] != nullptr){
	      update[i]->backwards[i] = current;
	    }
	  }
	}
	else{
	  current = new Node(kvIn);
	  int insertLevel = randomLevel();
	  std::cout<<"NEW LEVEL: " << insertLevel <<std::endl;
	  if(insertLevel > max_level){
	    for(int i = max_level+1; i <= insertLevel; i++){
	      update[i] = head[i];
	    }
	    max_level = insertLevel;
	  }
	  for(int i = 0; i <= max_level; i++){
	    if(update[i] == nullptr){
	      current->forwards[i] = nullptr;
	      current->backwards[i] = nullptr;
	      head[i] = current;
	    }
	    else{
	      current->forwards[i] = update[i]->forwards[i];
	      current->backwards[i] = update[i];
	      update[i]->forwards[i] = current;
	    }
	  }
	  inserted = true;
	}
	Iterator it(current);
	p = std::make_pair(it,inserted);
	return p;
      }
    }
    template <typename IT_T>
    void insert(IT_T range_beg, IT_T range_end){}
    void erase(Iterator &pos){
      Node* toDelete = pos.nPtr;
      for(int i = 0; i <= max_level; i++){
	(toDelete->forwards[i])->backwards[i] = toDelete->backwards[i];
	(toDelete->backwards[i])->forwards[i] = toDelete->forwards[i];
      }
      delete toDelete;
    }
    void erase(const Key_T &k){
      Node* toDelete = findNode(k);
      if(toDelete->kv.first != k){
	throw std::out_of_range("Key Not Found");
      }
      else{
	for(int i = 0; i <= max_level; i++){
	  (toDelete->forwards[i])->backwards[i] = toDelete->backwards[i];
	  (toDelete->backwards[i])->forwards[i] = toDelete->forwards[i];
	}
	delete toDelete;
      }
    }
    void clear(){
      Node* current = head[0];
      while(current != nullptr){
	Node* temp = current;
	current = current->forwards[0];
	delete temp;
      }
      for(int i = 0; i < MAX_HEIGHT; i++){
	head[i] = nullptr;
      }
      max_level = 0;
    }
    
    // Comparison
    bool operator==(const Map &m){
      bool retVal = true;
      if(size() != m.size()){
	retVal = false;
      }
      else{
	for(Iterator it = begin(); it != end(); it++){
	  ConstIterator it2 = m.find(it->first);
	  if(it2 == end() || it2->second != it->second){
	    retVal = false;
	    break;
	  }
	}
      }
      return retVal;
    }
    bool operator!=(const Map &m){
      bool retVal = false;
      if(size() != m.size()){
	retVal = true;
      }
      else{
	for(Iterator it = begin(); it != end(); it++){
	  ConstIterator it2 = m.find(it->first);
	  if(it2 == end() || it2->second != it->second){
	    retVal = true;
	    break;
	  }
	}
      }
      return retVal;
    }
    bool operator<(const Map &){

    }
  };
}
