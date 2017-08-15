/// @author Arin Arjani
/// @file pa16.cpp
/// @version 2017-04-21
/// @brief This program utilizes a few well known sort algorithms and 
///        one search algorithm. The program then outputs the sorting
///        times for 100,000 items.  Another time the program outputs
///        is the time it takes for the algorithm to find the searched
///        item.

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <cstdint>
#include <climits>
#include <iomanip>
#include <ios>

/// -----------------------------------------------------------------------
/// Sorts a list
/// @param list The list of integers to sort
///
/// @param length The length of the list.
///
/// -----------------------------------------------------------------------
void bubble_sort(std::vector<int>& list, int length);

/// -----------------------------------------------------------------------
/// Sorts a list
///
/// @param list The list of integers to sort
///
/// @param length The length of the list.
///
/// -----------------------------------------------------------------------
void selection_sort(std::vector<int>& list, int length);

/// -----------------------------------------------------------------------
/// Sorts a list
///
/// @param list The list of integers to sort
///
/// @param length The length of the list.
///
/// -----------------------------------------------------------------------
void insertion_sort(std::vector<int>& list, int length);

/// -----------------------------------------------------------------------
/// Searchs list for an item specified by user
///
/// @param list The list of integers to sort.
///
/// @param length The length of the list.
///
/// @param item The item to search the list for.
///
/// @return Returns the item searched for in the list or -1 for not found.
///
/// -----------------------------------------------------------------------
int binary_search(std::vector<int>& list, int length, int item); // only call once list is sorted
static const int TEST_SIZE = 100000;
static const int NUM_INTERATIONS = 3;

int main() {
	std::clock_t start;
	std::clock_t end;
	double seconds_find;
	double seconds_bubble_so;
	double seconds_binary_se;
	double seconds_selection_so;
	double seconds_insertion_so;
	double seconds_sort_so;

	for (size_t i = 0; i < NUM_INTERATIONS; ++i) {
		// Part 1 - seed and generate
		std::srand(0);  // seed with 0

		//std::vector<int> v(5)
		std::vector<int> v( TEST_SIZE );
		std::generate(v.begin(), v.end(), std::rand); 

		// Part 2 - use std::find

		start = clock();

		auto part_2_find = std::find( std::begin(v), std::end(v), INT_MAX / 2 ); // INT_MAX / 2
		
		end = clock();

		seconds_find += static_cast<double>( end - start ) / CLOCKS_PER_SEC;


		// if ( part_2_find == std::end( v ) || part_2_find != std::end( v ) ) {
		// 	std::cout << "vector \"v\" contains: " << 10 << "." << std::endl;
		// } else {
		// 	std::cout << "vector \"v\" does not contain: " << 10  
		// 	          << "." << std::endl;
		// }

		// Part 3 - sort with bubble sort
		
		start = clock();
		bubble_sort(v, v.size());
		end = clock();
		seconds_bubble_so += double( end - start ) / CLOCKS_PER_SEC;

		// Part 4 - search with binary search
		start = clock();
		auto part_4_search = binary_search( v, v.size(), INT_MAX / 2 );
		end = clock();
		seconds_binary_se += double( end - start ) / CLOCKS_PER_SEC;
		//std::cout << "Binary Search took " << seconds << "s." << std::endl;
		// if ( part_4_search != -1 ) {
		// 	std::cout << "binary search found stuff!!!" << std::endl;
		// } else {
		// 	std::cout << "binary search did not find stuff!!!" << std::endl;
		// }

		// Part 5 - seed & generate
		std::srand(0);

		std::vector<int> a( TEST_SIZE );
		std::generate(a.begin(), a.end(), std::rand);

		// Part 6 - sort with selection sort

		start = clock();
		selection_sort(a, a.size());
		end = clock();
		seconds_selection_so += double( end - start ) / CLOCKS_PER_SEC;

		// Part 7 - seed & generate
		std::srand(0);

		std::vector<int> b( TEST_SIZE );
		std::generate(b.begin(), b.end(), std::rand);

		// Part 8 - sort with insertion sort

		start = clock();
		insertion_sort(b, b.size());
		end = clock();
		seconds_insertion_so += double( end - start ) / CLOCKS_PER_SEC;


		// Part 9 - seed & generate
		std::srand(0);

		//std::vector<int> v(5)
		std::vector<int> c( TEST_SIZE );
		std::generate(c.begin(), c.end(), std::rand);

		// Part 10 - sort with std::sort

		start = clock();
		std::sort( std::begin(c), std::end(c) );
		end = clock();
		seconds_sort_so += double( end - start ) / CLOCKS_PER_SEC;
	}

	std::cout << "Average CPU times with 10,000 elements:" << std::endl;
	std::cout << "Find:               " << std::fixed
										<< std::setw(10) 
										<< seconds_find / 3 
										<< " secs" << std::endl;

	std::cout << "Bubble Sort:        " << std::setw(10) 
										<< seconds_bubble_so / 3 
										<< " secs" << std::endl;

	std::cout << "Binary Search:      " << std::setw(10) 
										<< seconds_binary_se / 3 
										<< " secs" << std::endl;

	std::cout << "Selection Sort:     " << std::setw(10) 
										<< seconds_selection_so / 3 
										<< " secs" << std::endl;

	std::cout << "Insertion Sort:     " << std::setw(10) 
										<< seconds_insertion_so / 3 
										<< " secs" << std::endl;

	std::cout << "std::sort:          " << std::setw(10) 
										<< seconds_sort_so / 3 
										<< " secs" << std::endl;



    return 0;
}

void bubble_sort(std::vector<int>& list, int length) {
	int temp;
	int iterator;
	int index;
	for( iterator = 1; iterator < length; iterator++ ) {
		for ( index = 0; index < length - iterator; index++ ) {
			if ( list[index] > list[index + 1] ) {
				temp = list[index];
			    list[index] = list[index + 1];
			    list[index + 1] = temp;
			}
		}
	}
}

void insertion_sort(std::vector<int>& list, int length) {
	int first_out_of_order;
	int location;
	int temp;
	for ( first_out_of_order = 1; first_out_of_order < length; first_out_of_order++ ) {
		temp = list[first_out_of_order];
		location = first_out_of_order;
		do {
			list[location] = list[location - 1];
			location--;
		} while ( location > 0 && list[location - 1] > temp );

		list[location] = temp;
	}
}

void selection_sort(std::vector<int>& list, int length) {
	int index;
	int smallest_index;
	int location;
	int temp;

	for ( index = 0; index < length- 1; index++ ) {
		smallest_index = index;
		for ( location = index + 1; location < length; location++ ) {
			if ( list[location] < list[smallest_index] ) {
				smallest_index = location;
			}
		}
		temp = list[smallest_index];
		list[smallest_index] = list[index];
		list[index] = temp;
	}	
}

int binary_search(std::vector<int>& list, int length, int search_item) {
	int first = 0;
	int last = length - 1;
	int mid;

	bool found = false;

	while ( first <= last && !found ) {
		mid = (first + last) / 2;
		if ( list[mid] == search_item ) {
			found = true;
		} else if ( list[mid] > search_item ) {
			last = mid - 1;
		} else {
			first = mid + 1;
		}
	}

	return found ? mid : -1;

}