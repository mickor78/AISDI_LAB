#include <iostream>

/*
 * Slownik
 *
 */
template<typename KeyType, typename ValueType>
class TreeMap {
public:
    using key_type = KeyType;
    using mapped_type = ValueType;
    using value_type = std::pair<const key_type, mapped_type>;


    TreeMap() : root(nullptr) {}

    ~TreeMap() {
        delete (root);
    }

    /*!
     * true jezeli slownik jest pusty
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /*!
     * dodaje wpis do slownika
     */
    void insert(const key_type &key, const mapped_type &value) {
        if (this->isEmpty()) {
            root = new Node<key_type, mapped_type>(key, value);
            return;
        }

        auto new_root = splay(root, key);
        Node <key_type, mapped_type> *child = nullptr;
        Node <key_type, mapped_type> *new_element = new Node<key_type, mapped_type>(key, value);

        if (new_root->getKey() != key) {
            if (new_root->getKey() < key) {

                child = new_root->getRight();
                if (child != nullptr) {
                    new_element->setRight(child);
                    new_root->unsafeDeleteRightChild();
                    new_root->setRight(new_element);
                } else {
                    new_root->setRight(new_element);
                }
            } else {
                child = new_root->getLeft();
                if (child != nullptr) {
                    new_element->setLeft(child);
                    new_root->unsafeDeleteLeftChild();
                    new_root->setLeft(new_element);
                } else {
                    new_root->setLeft(new_element);
                }
            }


        } else
            new_root->setValue(value);

        root = splay(root, key);
    }

    /*!
     * dodaje wpis do slownika przez podanie pary klucz-wartosc
     */
    void insert(const value_type &key_value) {
        this->insert(key_value.first, key_value.second);
    }

    /*!
     * zwraca referencje na wartosc dla podanego klucza
     *
     * jezeli elementu nie ma w slowniku, dodaje go
     */
    mapped_type &operator[](const key_type &key) {
        root = splay(root, key);

        if (root and root->getKey() == key)
            return const_cast<mapped_type &>(root->getValue());

        else {
            mapped_type dummyVal{};

            this->insert(key, dummyVal);
            return const_cast<mapped_type &>(splay(root, key)->getValue());
        }
    }

    /*!
     * zwraca wartosc dla podanego klucza
     */
    const mapped_type &value(const key_type &key) {
        root = splay(root, key);
        if (root->getKey() == key)
            return root->getValue();
        else {
            throw -1;
        }
    }

    /*!
     * zwraca informacje, czy istnieje w slowniku podany klucz
     */
    bool contains(const key_type& desiredKey) {
		if(isEmpty())
			return false;

    	root = splay(root,desiredKey);
    	return root->getKey() == desiredKey;
    }

    /*!
     * zwraca liczbe wpisow w slowniku
     */
    size_t size() const {
        return getSizeLookup(root);
    }

private:

    template<typename key_type, typename mapped_type>
    class Node {
    public:

        Node() : key(), value(), left(nullptr), right(nullptr) {}

        Node(key_type key, mapped_type value) : key(key), value(value), left(nullptr), right(nullptr) {}

        ~Node() {
            if (left)
                delete (left);
            if (right)
                delete (right);
        }


		Node* getLeft() const {
			return left;
		}

		Node* getRight() const {
			return right;
		}

		Node** getAppropriateChildSuperPtr(Node *node){
			if(right == node)
				return &right;
			else if(left == node)
				return &left;
			else
				throw -1;
		}

		const mapped_type& getValue() const{
			return value;
		}

        const key_type getKey() const {
            return key;
        }

		void setValue(const mapped_type& newValue){
			value = newValue;
		}

		void setLeft(Node* node){
			if(!left)
				delete(left);
			left = node;
		}

		void setRight(Node* node){
			if(!right)
				delete(right);
			right = node;
		}

		void unsafeDeleteRightChild(){
			right = nullptr;
		}

		void unsafeDeleteLeftChild(){
			left = nullptr;
		}

	private:
    	Node* left;				// left child node
		Node* right;			// right child node
		key_type key;
		mapped_type value;


    };

    Node<key_type, mapped_type>* splay(Node<key_type, mapped_type>* root, const key_type& key) {

    	auto child = getNodeSplay(root,key);
    	auto parent = getNodeSplayParent(root,child);
    	auto superParent = getNodeSplayParent(root, parent);
		Node<key_type, mapped_type>** parentPtr = nullptr;


    	if(parent)
    	{
			if(parent->getKey() < child->getKey())
			{
				if(superParent)
					parentPtr = superParent->getAppropriateChildSuperPtr(parent);
				else
					parentPtr = &root;

				leftRotation(parentPtr);
			}
			else
			{
				if(superParent)
					parentPtr = superParent->getAppropriateChildSuperPtr(parent);
				else
					parentPtr = &root;

				rightRotation(parentPtr);
			}

			return splay(root,key);
    	}
    	else
    		return child;

    }

	Node<key_type, mapped_type>* root;

	Node<key_type, mapped_type>* getNodeSplayParent(Node<key_type, mapped_type>* root, Node<key_type, mapped_type>* desiredChild) {

    	if(!desiredChild)
    		return nullptr;

		key_type key = desiredChild->getKey();
    	Node<key_type, mapped_type>* child;

    	if(!root)
			return nullptr;
    	else if(key == root->getKey())
    		return nullptr;
    	else{
			if(key < root->getKey()){
				if(root->getLeft()){
					if(key == (root->getLeft())->getKey())
						return root;
					else
						return getNodeSplayParent(root->getLeft(), desiredChild);
					}
				else
					return nullptr;
			}
			else{
				if(root->getRight()){
					if(key == (root->getRight())->getKey())
						return root;
					else
						return getNodeSplayParent(root->getRight(), desiredChild);
					}
				else
					return nullptr;
			}
    	}
	}

	Node<key_type, mapped_type>* getNodeSplay(Node<key_type, mapped_type>* root, const key_type& key) {

    	Node<key_type, mapped_type>* child;

    	if(!root)
			return nullptr;

    	else{
			if(key == root->getKey())
				return root;

			else if(key < root->getKey()){

				child = getNodeSplay(root->getLeft(), key);

				if( !child )
					return root;
				//asymmetric condition for stopping infinite splaying
				else if( key > child->getKey() and child->getRight() == nullptr )
					return root;
				else
					return child;
			}
			else{

				child = getNodeSplay(root->getRight(), key);

				if( !child )
					return root;
				else
					return child;
			}
		}

    }

    void rightRotation(Node<key_type, mapped_type> **childNode) const {
        Node<key_type, mapped_type> *nodeX, *nodeY;
        nodeX = *childNode;
        nodeY = nodeX->getLeft();
        nodeX->unsafeDeleteLeftChild();
        nodeX->setLeft(nodeY->getRight());
        nodeY->unsafeDeleteRightChild();
        nodeY->setRight(nodeX);
        *childNode = nodeY;
    }

    void leftRotation(Node<key_type, mapped_type> **childNode) const {
        Node<key_type, mapped_type> *nodeX, *nodeY;
        nodeX = *childNode;
        nodeY = nodeX->getRight();
        nodeX->unsafeDeleteRightChild();
        nodeX->setRight(nodeY->getLeft());
        nodeY->unsafeDeleteLeftChild();
        nodeY->setLeft(nodeX);
        *childNode = nodeY;
    }

    const size_t getSizeLookup(const Node<key_type, mapped_type> *parentNode) const {
        if (!parentNode)
            return 0;
        else {
            size_t nLeft = getSizeLookup(parentNode->getLeft());
            size_t nRight = getSizeLookup(parentNode->getRight());
            return nLeft + nRight + 1;
        }
    }

};

#include "tests.h"

int main() {
    unit_test();
    insert_test2();
    insert_test3();

    compare_test_num_as_key_set();
    compare_test_word_as_key_set();
    return 0;
}
