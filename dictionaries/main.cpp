#include <iostream>
#include <chrono>
#include <utility>
#include <memory>

/*!
 *  Narzedzie do zliczania czasu
 *
 *  Sposob uzycia:
 *
 *  {
 *    Benchmark<std::chrono::nanoseconds> b;
 *    // kod do zbadania
 *    size_t elapsed = b.elapsed();
 *  }
 *
 *  lub
 *
 *  {
 *    Benchmark<std::chrono::milliseconds> b(true);
 *    // kod do zbadania
 *  } // obiekt wypisze wartosc czasu w podanych jednostkach na stderr
 */
template<typename D = std::chrono::microseconds>
class Benchmark {
public:

    Benchmark(bool printOnExit = false) : m_print(printOnExit) {
        start = std::chrono::high_resolution_clock::now();
    }
    typename D::rep elapsed() const {
        auto end = std::chrono::high_resolution_clock::now();
        auto result = std::chrono::duration_cast<D>(end-start);
        return result.count();
    }
    ~Benchmark() {
        auto result = elapsed();
        if (m_print)
        {
            std::cerr << "Czas: " << result << "\n";
        }
    }
private:
    std::chrono::high_resolution_clock::time_point start;
    bool m_print = true;
};




/*
 * Slownik
 *
 */
template<typename KeyType, typename ValueType>
class TreeMap
{
public:
    using key_type = KeyType;
    using mapped_type = ValueType;
    using value_type = std::pair<const key_type, mapped_type>;

    TreeMap() : root(nullptr) {}

    ~TreeMap() = default;   // destruktor trywialny

    /*!
     * true jezeli slownik jest pusty
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /*!
     * dodaje wpis do slownika
     */
    void insert(const key_type& key, const mapped_type& value)
    {
        if (isEmpty())
        	root = new Node<key_type, mapped_type>(key, value);
        else
            root->addNode(new Node<key_type, mapped_type>(key, value));

        this->balance();
        
    }

    /*!
     * dodaje wpis do slownika przez podanie pary klucz-wartosc
     */
    void insert(const value_type &key_value)
    {
        throw std::runtime_error("TODO: insert");
    }

    /*!
     * zwraca referencje na wartosc dla podanego klucza
     *
     * jezeli elementu nie ma w slowniku, dodaje go
     */
    mapped_type& operator[](const key_type& key)
    {
        throw std::runtime_error("TODO: operator[]");
    }

    /*!
     * zwraca wartosc dla podanego klucza
     */
    const mapped_type& value(const key_type& key) const
    {
        throw std::runtime_error("TODO: value");
    }

    /*!
     * zwraca informacje, czy istnieje w slowniku podany klucz
     */
    bool contains(const key_type& key) const {
        return doesItContainIt(key, root);
    }

    /*!
     * zwraca liczbe wpisow w slowniku
     */
    size_t size() const {
        return getSizeLookup(root);
    }

private:

	/*
	 * aggregated class representing nodes in tree structure
	 */
	template<typename key_type, typename mapped_type>
	class Node{
	public:

		Node() = default;
		Node(key_type key, mapped_type value) : key(key), value(value), left(nullptr), right(nullptr){}

		~Node(){
    		if(left)
    			delete(left);
    		if(right)
    			delete(right);
    	}


		// recursive function for adding nodes to BST tree structure
		void addNode(Node* node){
			if(node->getKey() <= key){
				if(left)
					left->addNode(node);
				else
					this->setLeft(node);
			}
			else {
				if(right)
					right->addNode(node);
				else
					this->setRight(node);
			}
		}

		Node* getLeft() const {
			return left;
		}

		Node* getRight() const {
			return right;
		}

		key_type getKey() const {
			return key;
		}

		value_type getValue() const {
			return value;
		}


	private:
    	Node* left;				// left child node
		Node* right;			// right child node
		key_type key;
		mapped_type value;

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


	};

	/*
	 * regressive function calculating the number of nodes in (sub)tree structure, starting from parentNode
	 */
	const size_t getSizeLookup(const Node<key_type, mapped_type> *parentNode) const{
		if(!parentNode)
			return 0;
		else{
			size_t nLeft = getSizeLookup(parentNode->getLeft());
			size_t nRight = getSizeLookup(parentNode->getRight());
			return nLeft + nRight + 1;
		}
	}

	/*
	 * function executing right rotation
	 *      X           Y
	 *     / \         / \
	 *    Y  RX   ->  LY  X
	 *   / \             / \
 	 *  LY RY           RY RX
	 */

	void rightRotation(const Node<key_type, value_type> **childNode) const{
        Node<key_type , value_type >* nodeX, nodeY;
        nodeX = *childNode;
        nodeY = nodeX->getLeft();
        nodeX->setLeft(nodeY.getRight());
        nodeY.setRight(nodeX);
        *childNode = nodeY;
    }
    /*
	 * function executing left rotation
     * symmetrical to above function
     */

    void leftRotation(const Node<key_type, value_type> **childNode) const{
        Node<key_type , value_type >* nodeX, nodeY;
        nodeX = *childNode;
        nodeY = nodeX->getRight();
        nodeX->setRight(nodeY.getLeft());
        nodeY.setLeft(nodeX);
        *childNode = nodeY;
    }

	/*
	 * regressive function looking for desiredKey in (sub)tree structure, starting from parentNode
	 */
	bool doesItContainIt(const key_type &desiredKey, const Node<key_type, mapped_type> *parentNode) const {
		// finish looking for a key if function used on dead-end
		if(this->getSizeLookup(parentNode) <= 0)
			return false;
		else{
			key_type parentKey = parentNode->getKey();

			if( desiredKey == parentKey )
				return true;
			// decide on which branch look for recursively
			// according to binary tree theory
			else if( desiredKey < parentKey )
				return doesItContainIt(desiredKey, parentNode->getLeft());
			else
				return doesItContainIt(desiredKey, parentNode->getRight());
		}
	}

	/*
	 * make this BST balanced <=> restores AVL tree structure
	 */
	void balance(){
		// TODO complete it

	}


	Node<key_type, mapped_type>* root;
};



#include "tests.h"

int main()
{
	insert_test();
	unit_test();

    return 0;
}
