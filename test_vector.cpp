/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:14:51 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/06 18:05:15 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define NEWLINE std::cout << std::endl;
# define BORDER std::cout << "------------------------------------------------------------------" << std::endl;

# include "include/containers.hpp"
# include <string>

void test_vector()
{
	std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<< CONSTRUCTORS >>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
	{
		ft::vector<std::string> empty;								// -> default constructor
		std::cout << "--> EMPTY VECTOR:" << std::endl;
		for (size_t i = 0; i < empty.size(); i++)
			std::cout << "EMPTY[" << i << "] = " << empty[i] << ", ";
		NEWLINE BORDER

		ft::vector<char> fill(5, 'X'); 								// -> fill constructor
		std::cout << "--> FILL VECTOR:" << std::endl; 
		for (size_t i = 0; i < fill.size(); i++)
			std::cout << "FILL[" << i << "] = " << fill[i] << ", ";
		NEWLINE BORDER
		
		// ft::vector<int> range(fill.begin(), fill.end());			// -> range constructor
		// std::cout << "--> RANGE VECTOR:" << std::endl();
		// for (size_t i = 0; i < range.size(); i++)
		// 	std::cout << "RANGE[" << i << "] = " << range[i] << ", ";
		// NEWLINE BORDER
		
		ft::vector<char> copy(fill);								// -> copy constructor
		std::cout << "--> COPIED VECTOR: (from fill)" << std::endl; 
		for (size_t i = 0; i < copy.size(); i++)
			std::cout << "COPY[" << i << "] = " << copy[i] << ", ";
		NEWLINE NEWLINE
	}
	
	std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<< ITERATORS >>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
	{
		ft::vector<int> vec(5, 6);
		vec[0] = 0;
		vec[1] = 1;
		vec[2] = 2;
		vec[3] = 3;
		vec[4] = 4;

		std::cout << "NO ITERATOR:" << std::endl;
		std::cout << "for ( INT I = 0; I < SIZE; I++ ) :" << std::endl;
		for (size_t i = 0; i < vec.size(); i++)
			std::cout << vec[i] << ", ";
		NEWLINE NEWLINE

		std::cout << "PRE-INCREMENT ITERATOR:" << std::endl;
		std::cout << "for ( it = VEC.BEGIN(); it != VEC.END() && ++IT ) :" << std::endl;
		for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout  << *it << ", ";
		NEWLINE NEWLINE

		// std::cout << "POST-INCREMENT ITERATOR:" << std::endl;
		// std::cout << "for ( it = VEC.BEGIN(); it != VEC.END() && IT++ ) :" << std::endl;
		// for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		// 	std::cout  << *it << ", ";
		// NEWLINE NEWLINE 

		std::cout << "PRE-DECREMENT ITERATOR:" << std::endl;
		std::cout << "for ( it = --VEC.END(); it != --VEC.BEGIN() && --IT ) :" << std::endl;
		for (ft::vector<int>::iterator it = --vec.end(); it != --vec.begin(); --it)
			std::cout  << *it << ", ";
		NEWLINE NEWLINE

		// std::cout << "POST-DECREMENT ITERATOR:" << std::endl;
		// std::cout << "for ( it = --VEC.END(); it != --VEC.BEGIN() && IT-- ) :" << std::endl;
		// for (ft::vector<int>::iterator it = --vec.end(); it != --vec.begin(); it--)
		// 	std::cout  << *it << ", ";
		// NEWLINE NEWLINE
	
		std::cout << "[] OPERATOR:" << std::endl;
		ft::vector<int>::iterator it0(vec.begin());
		std::cout << "it(vec.begin());       print it[3]: \'" << it0[3] << "\'" << std::endl;
		ft::vector<int>::iterator it1(&vec[1]);
		std::cout << "it(&vec[1]);           print it[3]: \'" << it1[3] << "\'" << std::endl;

		NEWLINE NEWLINE NEWLINE


	}
	
	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<< CAPACITY >>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
	{
		// change size
		// reserve

		ft::vector<char> cap(5, '!');
		std::cout << "--> DEFAULT VECTOR:" << std::endl;
		for (size_t i = 0; i < cap.size(); i++)
			std::cout << "D[" << i << "] = \'" << cap[i] << "\', ";
		NEWLINE

		std::cout << "size()     = " << cap.size() << std::endl;
		std::cout << "max_size() = " << cap.max_size() << std::endl;
		std::cout << "capacity() = " << cap.capacity() << std::endl;
		std::cout << "empty()    = " << cap.empty() << std::endl;
		NEWLINE BORDER

		ft::vector<char> empty;
		std::cout << "--> EMPTY VECTOR:" << std::endl << std::endl;
		std::cout << "size()     = " << empty.size() << std::endl;
		std::cout << "max_size() = " << empty.max_size() << std::endl;
		std::cout << "capacity() = " << empty.capacity() << std::endl;
		std::cout << "empty()    = " << empty.empty() << std::endl;
		NEWLINE NEWLINE
	}

	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<< ELEMENT ACCESS >>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
	{
		ft::vector<std::string> def(3, "DEFAULT STRING");
		std::cout << "--> DEFAULT VECTOR:" << std::endl;
		for (size_t i = 0; i < def.size(); i++)
			std::cout << "DEF[" << i << "] = \"" << def[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> mod(def);
		std::cout << "--> []OPERATOR:\t\t\t\t(undefined behavior when out of bounds)" << std::endl;
		mod[1] = "-> mod[i]";
		for (size_t i = 0; i < mod.size(); i++)
			std::cout << "MOD[" << i << "] = \"" << mod[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> op(def);
		std::cout << "--> .AT():\t\t\t\t(throws when out of bounds)" << std::endl;
		op.at(1) = "-> mod.at(i)";
		for (size_t i = 0; i < op.size(); i++)
			std::cout << "MOD[" << i << "] = \"" << op.at(i) << "\"" << std::endl;
		NEWLINE
		try
		{
			op.at(op.size());
			// op.at(-1);
		}
		catch(const std::exception& e)
		{
			std::cerr << "CATCHED EXCEPTION: "<<  e.what() << std::endl;
		}
		NEWLINE BORDER

		ft::vector<std::string> ends(def);
		ends[0] = "first string";
		ends[2] = "last string";

		std::cout << "--> .FRONT():\t\t\t\t(undefined behavior when out of bounds)" << std::endl;
		std::cout << "MOD[0] == MOD.FRONT() is " << (ends[0] == ends.front()) << std::endl;
		std::cout << "MOD[1] == MOD.FRONT() is " << (ends[1] == ends.front()) << std::endl;
		NEWLINE BORDER

		std::cout << "--> .BACK():\t\t\t\t(undefined behavior when out of bounds)" << std::endl;
		std::cout << "MOD[2] == MOD.BACK() is " << (ends[2] == ends.back()) << std::endl;
		std::cout << "MOD[1] == MOD.BACK() is " << (ends[1] == ends.back()) << std::endl;
		NEWLINE NEWLINE
	}
}