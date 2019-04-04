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

    TreeMap(){
    	root = nullptr;

    }

    ~TreeMap() = default;   // destruktor trywialny

    /*!
     * true jezeli slownik jest pusty
     */
    bool isEmpty() const
    {
        if(!root)
        	return true;
        else
        	return false;
    }

    /*!
     * dodaje wpis do slownika
     */
    void insert(const key_type& key, const mapped_type &value)
    {
        if (isEmpty()) root= new Node<key_type, value_type>(key,value_type(key,value));
        else{
            child = new Node<key_type, value_type>(key,value_type(key,value));
            root->setRight(*child);
        }

        //throw std::runtime_error("TODO: insert");
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
	template<typename key_type, typename value_type>
	class Node{
	public:

		Node() = default;
		Node(key_type key, value_type value) : key(key), value(value){}

		~Node(){
    		if(left)
    			delete(left);
    		if(right)
    			delete(right);
    	}

		void setLeft(const Node& node){
			left = &node;
		}

		void setRight(const Node& node){
			right = &node;
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
		value_type value;

    };

	/*
	 * regressive function calculating the number of nodes in (sub)tree structure, starting from parentNode
	 */
	const size_t getSizeLookup(const Node<key_type, value_type> *parentNode) const{
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
        Node<key_type , value_type >* nodeX = *childNode;
        Node<key_type , value_type >* nodeY = *childNode->getLeft();
        Node<key_type , value_type >* nodeLY = nodeY->getLeft();
        Node<key_type , value_type >* nodeRY = nodeY->getRight();
        Node<key_type , value_type >* nodeRX = nodeX->getRight();


    }

	/*
	 * regressive function looking for desiredKey in (sub)tree structure, starting from parentNode
	 */
	bool doesItContainIt(const key_type &desiredKey, const Node<key_type, value_type> *parentNode) const {
		// finish looking for a key if function used on dead-end
		if(this->getSizeLookup(parentNode) <= 0)
			return false;
		else{
			key_type parentKey = parentNode->getKey();

			if( parentKey == desiredKey)
				return true;
			// decide on which branch look for recursively
			// according to binary tree theory
			else if( parentKey < desiredKey )
				return doesItContainIt(desiredKey, parentNode->getLeft());
			else
				return doesItContainIt(desiredKey, parentNode->getRight());
		}
	}

	Node<key_type, value_type>* root;
    Node<key_type, value_type>* child;

};



#include "tests.h"

int main()
{
    unit_test();

    return 0;
}
