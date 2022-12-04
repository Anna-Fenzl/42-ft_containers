/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:14:51 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/04 18:46:08 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define NEWLINE std::cout << std::endl;
// # define BORDER std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
# define BORDER std::cout << "------------------------------------------------------------------" << std::endl;

# include "include/containers.hpp"

void test_vector()
{
	// <<<<<<<<<<<<<<<<<<<<< CONSTRUCTORS >>>>>>>>>>>>>>>>>>>>>>>>
	// -> default constructor
	ft::vector<int> empty;

	NEWLINE
	std::cout << "--> EMPTY VECTOR:" << std::endl;
	BORDER
	std::cout << "SIZE: " << empty.size() << ", CAPACITY: " << empty.capacity() << ", MAX_SIZE: " << empty.max_size() << std::endl;
	std::cout << "empty returns: " << empty.empty() << std::endl;
	BORDER NEWLINE

	// -> fill constructor
	int size = 5;
	ft::vector<char> fill(size, 'X');

	std::cout << "--> FILL VECTOR:" << std::endl; 
	BORDER
	std::cout << "SIZE: " << fill.size() << ", CAPACITY: " << fill.capacity() << ", MAX_SIZE: " << fill.max_size() << std::endl;
	std::cout << "empty returns: " << fill.empty() << std::endl; 
	NEWLINE
	for (int i = 0; i < size; i++)
		std::cout << "FILL[" << i << "] = " << fill[i] << ", ";
	NEWLINE BORDER NEWLINE
	
	// -> range constructor
	// -> copy constructor

	// <<<<<<<<<<<<<<<<<<<<< ELEMENT ACCESS >>>>>>>>>>>>>>>>>>>>>>>>
	

	
	
}