#include <cassert>

void unit_test() {
    TreeMap<int,int> dict;

    // slownik jest pusty
    assert(dict.isEmpty() == true);
    assert(dict.size() == 0);
    assert(dict.contains(0) == false);

    // dodanie elementu do slownika
    dict.insert(0, 1);
    assert(dict.isEmpty() == false);
    assert(dict.size() == 1);
    assert(dict.contains(0) == true);
    assert(dict.value(0) == 1);

    // dodanie elementu do slownika jako pary
    dict.insert(std::pair<int,int>(1, 2));
    assert(dict.size() == 2);
    assert(dict.contains(1) == true);
    assert(dict.value(0) == 1);
    assert(dict.value(1) == 2);

    // operator []
    assert(dict[0] == 1);
    assert(dict[1] == 2);

    // operator [] tworzy nowy element
    dict[2] = 3;
    assert(dict.value(2) == 3);
    assert(dict.size() == 3);


    // nadpisanie wartosci dla istniejacego elementu
    dict.insert(2, 4);
    assert(dict.size() == 3);
    assert(dict.value(2) == 4);
}

void insert_test() {
	TreeMap<int,int> dict;

	// slownik jest pusty
	assert(dict.isEmpty() == true);
	assert(dict.size() == 0);
	assert(dict.contains(0) == false);

	// dodanie elementow do slownika
	dict.insert(1, 11);
	dict.insert(2, 12);
	dict.insert(3, 13);
	dict.insert(4, 14);
	dict.insert(5, 15);
	assert(dict.size() == 5);
	assert(dict.contains(0) == false);
	assert(dict.contains(1) == true);
	assert(dict.contains(2) == true);
	assert(dict.contains(3) == true);
	assert(dict.contains(4) == true);
	assert(dict.contains(5) == true);

}
