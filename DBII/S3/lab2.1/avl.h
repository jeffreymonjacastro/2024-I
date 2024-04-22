#ifndef AVLTree_H
#define AVLTree_H
#include "node.h"

using namespace std;

template <typename T>
class AVLTree
{
private:
    NodeBT<T> *root;

public:
    AVLTree() : root(nullptr) {}
    void insert(T value)
    {
        insert(this->root, value);
    }
    bool find(T value)
    {
        return find(this->root, value);
    }
    NodeBT<T>* find(T value)
    {
        return find(this->root, value);
    }
    void displayPreOrder()
    {
        displayPreOrder(this->root);
    }
    int height()
    {
        return height(this->root);
    }
    T minValue()
    {
        return minValue(this->root);
    }
    T maxValue()
    {
        return maxValue(this->root);
    }
    bool isBalanced()
    {
        return isBalanced(this->root);
    }
    int size()
    {
        return size(this->root);
    }
    void remove(T value)
    {
        remove(this->root, value);
    }
    void displayPretty()
    {
        displayPretty(this->root, 1);
    }
    ~AVLTree(){
        if(this->root != nullptr){
            this->root->killSelf();
        }
    }

private:
    void displayPreOrder(NodeBT<T> *node);
    bool find(NodeBT<T> *node, T value);
    bool isBalanced(NodeBT<T> *node);
    T minValue(NodeBT<T> *node);
    T maxValue(NodeBT<T> *node);
    int size(NodeBT<T> *node);
    void remove(NodeBT<T> *&node, T value);
    void displayPretty(NodeBT<T> *node, int level);

    /*add for avl*/
    int height(NodeBT<T> *node);
    void updateHeight(NodeBT<T> *node);
    int balancingFactor(NodeBT<T> *node);
    void insert(NodeBT<T> *&node, T value);
    void balance(NodeBT<T> *&node);
    void left_rota(NodeBT<T> *&node); 
    void right_rota(NodeBT<T> *&node); 
};

template <typename T>
bool AVLTree<T>::find(NodeBT<T> *node, T value)
{
    if (node == nullptr)
        return false;
    else if (value < node->data)
        return find(node->left, value);
    else if (value > node->data)
        return find(node->right, value);
    else
        return true;
}




template <typename T>
bool AVLTree<T>::isBalanced(NodeBT<T> *node)
{
    if (node == nullptr)
        return true;
    else
        return abs(height(node->left) - height(node->right)) <= 1 && isBalanced(node->left) && isBalanced(node->right);
}

template <typename T>
void AVLTree<T>::displayPreOrder(NodeBT<T> *node)
{
    if (node == nullptr)
        return;
    cout << node->data << endl;
    displayPreOrder(node->left);
    displayPreOrder(node->right);
}

template <typename T>
T AVLTree<T>::minValue(NodeBT<T> *node)
{
    if (node == nullptr)
        throw("The tree is empty");
    else if (node->left == nullptr)
        return node->data;
    else
        return minValue(node->left);
}

template <typename T>
T AVLTree<T>::maxValue(NodeBT<T> *node)
{
    if (node == nullptr)
        throw("The tree is empty");
    else if (node->right == nullptr)
        return node->data;
    else
        return maxValue(node->right);
}

template <typename T>
int AVLTree<T>::size(NodeBT<T> *node)
{
    if (node == nullptr)
        return 0;
    else
        return 1 + size(node->left) + size(node->right);
}

template <typename T>
void AVLTree<T>::displayPretty(NodeBT<T> *node, int level)
{
    if (node == nullptr)
        return;
    displayPretty(node->right, level + 1);
    cout << endl;
    if (node == this->root)
        cout << "Root->:  ";
    else
    {
        for (int i = 0; i < level; i++)
            cout << "      ";
    }
    cout << node->data <<"("<<node->height<<")";
    displayPretty(node->left, level + 1);
}

/* add for AVL*/
template <typename T>
void AVLTree<T>::insert(NodeBT<T> *&node, T value)
{
    if (node == nullptr){
        node = new NodeBT<T>(value);
        return;
    }
    if (value < node->data) insert(node->left, value);        
    else insert(node->right, value);      
    updateHeight(node);  
    balance(node);
}

template <typename T>
int AVLTree<T>::height(NodeBT<T> *node)
{
    if (node == nullptr)  return -1;
    else return node->height;
}

template <typename T>
int AVLTree<T>::balancingFactor(NodeBT<T> *node){
    return height(node->left) - height(node->right);
}

template <typename T>
void AVLTree<T>::updateHeight(NodeBT<T> *node)
{    
    node->height = max(height(node->left), height(node->right)) + 1;
}


template <typename T>
void AVLTree<T>::balance(NodeBT<T> *&node)
{
    int hb = balancingFactor(node);
    if(hb >= 2){//cargado por la izquierda
        if(balancingFactor(node->left) <= 1) //<=-1, rotacion doble izquierda-derecha
            left_rota(node->left);        
        right_rota(node);        
    }
    else if(hb <= -2){//cargado por la derecha
        if(balancingFactor(node->right) >= 1) //>=1, rotacion doble derecha-izquierda
            right_rota(node->right);        
        left_rota(node);
    }    
}

template <typename T>
void AVLTree<T>::left_rota(NodeBT<T> *&parent){
    NodeBT<T>* temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;    
    updateHeight(parent);
    updateHeight(temp);
    parent = temp;    
}

template <typename T>
void AVLTree<T>::right_rota(NodeBT<T> *&parent){
    NodeBT<T>* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    updateHeight(parent);
    updateHeight(temp);
    parent = temp;
}

template <typename T>
void AVLTree<T>::remove(NodeBT<T> *&node, T value)
{
    if (node == nullptr)
        return;
    else if (value < node->data)
        remove(node->left, value);        
    else if (value > node->data)
        remove(node->right, value);
    else
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node; //free
            node = nullptr;
        }
        else if (node->left == nullptr)
        {
            NodeBT<T> *temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr)
        {
            NodeBT<T> *temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            T temp = maxValue(node->left);
            node->data = temp;
            remove(node->left, temp);            
        }
    }

    if(node != nullptr){
        updateHeight(node);
        balance(node);
    }
}


#endif
