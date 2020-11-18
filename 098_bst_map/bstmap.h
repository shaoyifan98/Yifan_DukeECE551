#include <stdexcept>
#include <iostream>
#include "map.h"
using namespace std;

template<typename K, typename V>
class BstMap:public Map<K, V> {
private:
    class Node{
    public:
        K key;
        V value;
        Node *left;
        Node *right;
        Node(const K & k, const V & v):key(k), value(v), left(NULL), right(NULL){}
    };
    Node *root;

public:
    BstMap():root(NULL){}
 BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }
   
 Node * copy(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * root = new Node(current->key, current->value);
    root->left = copy(current->left);
    root->right = copy(current->right);
    return root;
  }
   BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy(rhs.root);
    }
    return *this;
  }

  

     virtual void add(const K & key, const V & value) {
    Node ** current = &root;
    while (*current != NULL) {
      //key exists: replace its value
      if (key == (*current)->key) {
        (*current)->value = value;
        return;
      }
      //no such key
      else if (key < (*current)->key) {
        current = &((*current)->left);
      }
      else {
        current = &((*current)->right);
      }
    }
    *current = new Node(key, value);
  }
    virtual const V & lookup(const K& key) const throw (std::invalid_argument){
        Node *cur = root;
        while(cur != NULL){
            if(key == cur->key){
                return cur->value;
            }else if(key < cur->key){
                cur = cur->left;
            }else{
                cur = cur->right;
            }
        }
        throw std::invalid_argument("error");
    }
    virtual void remove(const K& key){
        if(key == root->key){
            root = remove(root);
            return;
        }
        Node *cur = root;
        while(cur != NULL){
            if(key < cur->key){
                if(cur->left == NULL){
                    return;
                }else if(key == cur->left->key){
                    cur->left = remove(cur->left);
                    return;
                }else{
                    cur = cur->left;
                }
            }else if(key > cur->key){
                if(cur->right == NULL){
                    return;
                }else if(key == cur->right->key){
                    cur->right = remove(cur->right);
                    //cout << "find" >> endl;
                    return;
                }else{
                    cur = cur->right;
                }
            }
        }
    }

    Node * remove(Node * target){
        //cout << "remove node" << target->data.first << endl;
        if(target->left == NULL){
            Node * temp = target->right;
            delete target;
            return temp;
        }else if(target->right == NULL){
            Node * temp = target->left;
            delete target;
            return temp;
        }else{
            Node *temp = target->right;
            if(temp->left == NULL){
                target->key = temp->key;
                target->value = temp->value;
                delete temp;
                target->right = NULL;
                return target;
            }else{
                while(temp->left->left != NULL){
                    temp = temp->left;
                    
                }
                target->key = temp->left->key;
                target->value = temp->left->value;

                delete temp->left;
                temp->left = NULL;
                return target;
            }
        }
    }

   

    void destroy(Node * node){
        if(node != NULL){
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
    virtual ~BstMap<K,V>() {
        destroy(root);
    }

    void in(){
        inOrderTraverse(root);
    }
    void inOrderTraverse(Node * node){
        if(node != NULL){
            inOrderTraverse(node->left);
            cout << node->key << endl;
            inOrderTraverse(node->right);
        }
    }
};