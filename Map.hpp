#include <utility>
#include <initializer_list>
#include <iostream>

#define MAX_HEIGHT 32

namespace cs540{  

  // Forward declare nested class for visibility in free funcitons
  class Iterator;
  class ConstIterator;
  class ReverseIterator;
  
  template <typename Key_T, typename Mapped_T> class Map {
    
  private:
    // Member Type
    typedef std::pair<const Key_T, Mapped_T> ValueType;

    // Node definition
    typedef struct Node{
      ValueType kv;
      Node* next;
      Node* down;
      Node(ValueType keyValue) : kv(keyValue), next(nullptr), down(nullptr){}
    }Node;

    // Skip list heads
    Node* heads[MAX_HEIGHT];
    
    size_t max_level;

  public:
    // Define nested classes
    class Iterator{
    private:

    public:
      Iterator(){}
      Iterator(const Iterator &i){}
      ~Iterator(){}
      Iterator& operator=(const Iterator &){}
      virtual Iterator &operator++(){}
      virtual Iterator operator++(int){}
      virtual Iterator &operator--(){}
      virtual Iterator operator--(int){}
      virtual ValueType &operator*() const{}
      virtual ValueType *operator->() const{}
    };
    
    class ConstIterator: public Iterator{
    public:
      const ValueType &operator*() const{}
      const ValueType *operator->() const{}
    };
    
    class ReverseIterator: public Iterator{
    public:
      ReverseIterator &operator++(){}
      ReverseIterator operator++(int){}
      ReverseIterator &operator--(){}
      ReverseIterator operator--(int){}
    };
    
    // Constructor & Assingment Operator
    Map(){
      max_level = 0;
      for(int i = 0; i < MAX_HEIGHT; i++){
	heads[i] = nullptr;
      }
    }
    Map(const Map&){}
    Map &operator=(const Map&){}
    Map(std::initializer_list<std::pair<const Key_T, Mapped_T>>){}
    ~Map(){
      for(int i = 0; i < MAX_HEIGHT; i++){
	Node* current = heads[i];
	while(current != nullptr){
	  Node* temp = current;
	  current = current -> next;
	  delete temp;
	}
      }
    }
    
    // Size
    size_t size() const{
      int count = 0;
      Node* current = heads[0];
      while(current != nullptr){
	count++;
	current = current->next;
      }
      return count;
    }
    bool empty() const{
      return heads[0] == nullptr;
    }
    
    // Iterators
    Iterator begin(){}
    Iterator end(){Iterator end; return end;}
    ConstIterator begin() const{}
    ConstIterator end() const{}
    ReverseIterator rbegin(){}
    ReverseIterator rend(){}
    
    // Element Access
    Iterator find(const Key_T &k){
      Node* current = heads[max_level];
      int current_level = max_level;
      if(current != nullptr){
	while(current_level >= 0){
	  while(current->next != nullptr && current->next->kv.first <= k){
	    current = current->next;
	  }
	  if(current->kv.first == k){
	    Iterator found;
	    std::cout << "FOUND" << std::endl;
	    return found;
	  }
	  else{
	    current = current->down;
	    current_level--;
	  }
	}
      }
      
      Iterator notFound = end();
      std::cout << "NOT FOUND" << std::endl;
      return notFound;
    }
    ConstIterator find(const Key_T& k) const{
      Node* current = heads[max_level];
      int current_level = max_level;
      if(current != nullptr){
	while(current_level >= 0){
	  while(current->next != nullptr && current->next->kv.first <= k){
	    current = current->next;
	  }
	  if(current->kv.first == k){
	    ConstIterator found;
	    std::cout << "FOUND" << std::endl;
	    return found;
	  }
	  else{
	    current = current->down;
	    current_level--;
	  }
	}
      }
      
      ConstIterator notFound = end();
      std::cout << "NOT FOUND" << std::endl;
      return notFound;
    }
    Mapped_T &at(const Key_T &){}
    const Mapped_T &at(const Key_T &) const{}
    Mapped_T &operator[](const Key_T &){}
    
    // Modifiers
    std::pair<Iterator, bool> insert(const ValueType &kv){
      Node* newNode = new Node(kv);
      if(heads[0] == nullptr){
	heads[0] = newNode;
      }
      std::cout << heads[0]->kv.first << ":" << heads[0]->kv.second << std::endl;
     
      std::pair<Iterator, bool> p;
     
      return p;
    }
    template <typename IT_T>
    void insert(IT_T range_beg, IT_T range_end){}
    void erase(Iterator pos){}
    void erase(const Key_T &){}
    void clear(){}
    
    // Comparison
    bool operator==(const Map &){}
    bool operator!=(const Map &){}
    bool operator<(const Map &){}
  };

  bool operator==(const Iterator &, const Iterator &){return true;}
  bool operator==(const ConstIterator &, const ConstIterator &){return true;}
  bool operator==(const Iterator &, const ConstIterator &){return true;}
  bool operator==(const ConstIterator &, const Iterator &){return true;}
  bool operator!=(const Iterator &, const Iterator &){return true;}
  bool operator!=(const ConstIterator &, const ConstIterator &){return true;}
  bool operator!=(const Iterator &, const ConstIterator &){return true;}
  bool operator!=(const ConstIterator &, const Iterator &){return true;}
  bool operator==(const ReverseIterator &, const ReverseIterator &){return true;}
  bool operator!=(const ReverseIterator &, const ReverseIterator &){return true;}
}
