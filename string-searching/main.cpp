#include <iostream>
#include "tests.h"
#include "test.h"
#include "find_str_util.h"
#include "find_str_util2.h"

int main()
{
    boundary_test();

    std::cout << "\n" << "Hello World!" << std::endl;
    random_case_test();
//    board_case_test();

	return 0;
}