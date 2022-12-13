/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:14:51 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/13 16:01:36 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ALSO SWITCHING CONTAINERS

# define NEWLINE std::cout << std::endl;
# define BORDER std::cout << "------------------------------------------------------------------" << std::endl;
# define HEADLINE std::cout << "\033[38;5;81m ";
# define BOLD std::cout << "\033[0;1m";
# define RESET std::cout << "\033[0m" << std::endl;

# include "include/containers.hpp"
# include <string>
# include <vector>

/*
	TO DO:
	RANGE CONSTRUCTOR:
	-> assign
			-> realloc
		-> private _assign_range
			-> ft::distance
	RELATIONAL OPERATORS
		-> ft::equal
		-> ft::lexographical_compare
	REVERSE ITERATORS
	max_size exception
*/

void test_vector()
{
	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<< CONSTRUCTORS >>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET

		ft::vector<std::string> empty;								// -> default constructor
		BOLD std::cout << "--> EMPTY VECTOR:"; RESET
		for (size_t i = 0; i < empty.size(); i++)
			std::cout << "EMPTY[" << i << "] = " << empty[i] << ", ";
		NEWLINE BORDER

		ft::vector<char> fill(5, 'X'); 								// -> fill constructor
		BOLD std::cout << "--> FILL VECTOR:"; RESET 
		for (size_t i = 0; i < fill.size(); i++)
			std::cout << "FILL[" << i << "] = " << fill[i] << ", ";
		NEWLINE BORDER
		
		// ft::vector<int> range(fill.begin(), fill.end());			// -> range constructor
		// BOLD std::cout << "--> RANGE VECTOR:"; RESET
		// for (size_t i = 0; i < range.size(); i++)
		// 	std::cout << "RANGE[" << i << "] = " << range[i] << ", ";
		// NEWLINE BORDER
		
		ft::vector<char> copy(fill);								// -> copy constructor
		BOLD std::cout << "--> COPIED VECTOR: (from fill)"; RESET 
		for (size_t i = 0; i < copy.size(); i++)
			std::cout << "COPY[" << i << "] = " << copy[i] << ", ";
		NEWLINE NEWLINE
	}


	
	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<< ITERATORS >>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET

		ft::vector<int> vec(5, 6);
		vec[0] = 0;
		vec[1] = 1;
		vec[2] = 2;
		vec[3] = 3;
		vec[4] = 4;

		BOLD std::cout << "NO ITERATOR:"; RESET
		std::cout << "for ( INT I = 0; I < SIZE; I++ ) :" << std::endl;
		for (size_t i = 0; i < vec.size(); i++)
			std::cout << vec[i] << ", ";
		NEWLINE NEWLINE

		BOLD std::cout << "PRE-INCREMENT ITERATOR:"; RESET
		std::cout << "for ( it = VEC.BEGIN(); it != VEC.END() && ++IT ) :" << std::endl;
		for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout  << *it << ", ";
		NEWLINE NEWLINE

		BOLD std::cout << "POST-INCREMENT ITERATOR:"; RESET
		std::cout << "for ( it = VEC.BEGIN(); it != VEC.END() && IT++ ) :" << std::endl;
		for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
			std::cout  << *it << ", ";
		NEWLINE NEWLINE 

		BOLD std::cout << "PRE-DECREMENT ITERATOR:"; RESET
		std::cout << "for ( it = --VEC.END(); it != --VEC.BEGIN() && --IT ) :" << std::endl;
		for (ft::vector<int>::iterator it = --vec.end(); it != --vec.begin(); --it)
			std::cout  << *it << ", ";
		NEWLINE NEWLINE

		BOLD std::cout << "POST-DECREMENT ITERATOR:"; RESET
		std::cout << "for ( it = --VEC.END(); it != --VEC.BEGIN() && IT-- ) :" << std::endl;
		for (ft::vector<int>::iterator it = --vec.end(); it != --vec.begin(); it--)
			std::cout  << *it << ", ";
		NEWLINE NEWLINE
	
		BOLD std::cout << "[] OPERATOR:"; RESET
		ft::vector<int>::iterator it0(vec.begin());
		std::cout << "it(vec.begin());       print it[3]: \'" << it0[3] << "\'" << std::endl;
		ft::vector<int>::iterator it1(++vec.begin());
		std::cout << "it(&vec[1]);           print it[3]: \'" << it1[3] << "\'" << std::endl;

		NEWLINE NEWLINE
	}


	
	{
		HEADLINE
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<< CAPACITY >>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET

		ft::vector<char> cap(5, '!');
		BOLD std::cout << "--> DEFAULT VECTOR:"; RESET
		for (size_t i = 0; i < cap.size(); i++)
			std::cout << "D[" << i << "] = \'" << cap[i] << "\', ";
		NEWLINE

		std::cout << "size()     = " << cap.size() << std::endl;
		std::cout << "max_size() = " << cap.max_size() << std::endl;
		std::cout << "capacity() = " << cap.capacity() << std::endl;
		std::cout << "empty()    = " << cap.empty() << std::endl;
		NEWLINE BORDER

		ft::vector<char> empty;
		BOLD std::cout << "--> EMPTY VECTOR:" << std::endl; RESET
		std::cout << "size()     = " << empty.size() << std::endl;
		std::cout << "max_size() = " << empty.max_size() << std::endl;
		std::cout << "capacity() = " << empty.capacity() << std::endl;
		std::cout << "empty()    = " << empty.empty() << std::endl;
		NEWLINE BORDER

		ft::vector<char> resize(cap);
		BOLD std::cout << "--> RESIZE VECTOR:\t\t\t\t()" << std::endl; RESET
		std::cout << "> resize to smaller size (2)" << std::endl;
		resize.resize(2);
		std::cout << "size()     = " << resize.size() << std::endl;
		std::cout << "capacity() = " << resize.capacity() << std::endl;
		for (size_t i = 0; i < resize.size(); i++)
			std::cout << "RES[" << i << "] = \'" << resize[i] << "\', ";
		NEWLINE NEWLINE
		
		std::cout << "> resize to bigger size 9, 'X')" << std::endl;
		resize.resize(9, 'X');
		std::cout << "size()     = " << resize.size() << std::endl;
		std::cout << "capacity() = " << resize.capacity() << std::endl;
		for (size_t i = 0; i < resize.size(); i++)
			std::cout << "RES[" << i << "] = \'" << resize[i] << "\', ";
		NEWLINE NEWLINE BORDER

		ft::vector<char> res(cap);
		BOLD std::cout << "--> RESERVE VECTOR:\t\t\t\t(throws when requested capacity > max_size())" << std::endl; RESET
		std::cout << "reserving 1000 for DEFAULT" << std::endl;
		try
		{
			res.reserve(1000);
			std::cout << "size()     = " << res.size() << std::endl;
			std::cout << "capacity() = " << res.capacity() << std::endl;
			res.reserve(res.max_size() + 2);
		}
		catch(const std::exception& e)
		{
			std::cerr << "CATCHED EXCEPTION: "<<  e.what() << std::endl;
		}
		NEWLINE NEWLINE
	}


	
	{
		HEADLINE
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<< ELEMENT ACCESS >>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET

		ft::vector<std::string> def(3, "DEFAULT STRING");
		BOLD std::cout << "--> DEFAULT VECTOR:"; RESET
		for (size_t i = 0; i < def.size(); i++)
			std::cout << "DEF[" << i << "] = \"" << def[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> mod(def);
		BOLD std::cout << "--> []OPERATOR:\t\t\t\t(undefined behavior when out of bounds)" << std::endl; RESET
		mod[1] = "non default, used: mod[i]";
		for (size_t i = 0; i < mod.size(); i++)
			std::cout << "MOD[" << i << "] = \"" << mod[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> op(def);
		BOLD std::cout << "--> .AT():\t\t\t\t(throws when out of bounds)" << std::endl; RESET
		op.at(1) = "non default, used: mod.at(i)";
		for (size_t i = 0; i < op.size(); i++)
			std::cout << "MOD[" << i << "] = \"" << op.at(i) << "\"" << std::endl;
		NEWLINE
		try
		{
			// op.at(op.size());
			op.at(-1);
		}
		catch(const std::exception& e)
		{
			std::cerr << "CATCHED EXCEPTION: "<<  e.what() << std::endl;
		}
		NEWLINE BORDER

		ft::vector<std::string> ends(def);
		ends[0] = "first string";
		ends[2] = "last string";

		BOLD std::cout << "--> .FRONT():\t\t\t\t(undefined behavior when out of bounds)" << std::endl; RESET
		std::cout << "MOD[0] == MOD.FRONT() is " << (ends[0] == ends.front()) << std::endl;
		std::cout << "MOD[1] == MOD.FRONT() is " << (ends[1] == ends.front()) << std::endl;
		NEWLINE BORDER

		BOLD std::cout << "--> .BACK():\t\t\t\t(undefined behavior when out of bounds)" << std::endl; RESET
		std::cout << "MOD[2] == MOD.BACK() is " << (ends[2] == ends.back()) << std::endl;
		std::cout << "MOD[1] == MOD.BACK() is " << (ends[1] == ends.back());
		NEWLINE NEWLINE
	}


	
	{
		HEADLINE
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<< MODIFIERS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET

		ft::vector<std::string> def(3, "DEFAULT STRING");
		BOLD std::cout << "--> DEFAULT VECTOR:"; RESET
		for (size_t i = 0; i < def.size(); i++)
			std::cout << "DEF[" << i << "] = \"" << def[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> as(def);
		BOLD std::cout << "--> .ASSIGN(4, \"assigned string\"):\t\t\t(fill version)"; RESET
		as.assign(4, "assigned string (fill)");
		for (size_t i = 0; i < as.size(); i++)
			std::cout << "FILL[" << i << "] = \"" << as[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> range(def);
		BOLD std::cout << "--> .ASSIGN(as.begin()+1, as.end()):\t\t\t(range version)"; RESET
		range.assign(as.begin()+1, as.end());
		for (size_t i = 0; i < range.size(); i++)
			std::cout << "RANGE[" << i << "] = \"" << range[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> push(def);
		BOLD std::cout << "--> .PUSH_BACK(\"pushed string\"):"; RESET
		push.push_back("pushed string");
		push.push_back("another pushed string");
		for (size_t i = 0; i < push.size(); i++)
			std::cout << "PUSH[" << i << "] = \"" << push[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> pop(push);
		BOLD std::cout << "--> .POP_BACK():"; RESET
		push.pop_back();
		for (size_t i = 0; i < push.size(); i++)
			std::cout << "POP[" << i << "] = \"" << push[i] << "\"" << std::endl;
		NEWLINE BORDER
		
		ft::vector<std::string> clear(def);
		BOLD std::cout << "--> .CLEAR():"; RESET
		clear.clear();
		for (size_t i = 0; i < clear.size(); i++)
			std::cout << "MOD[" << i << "] = \"" << clear[i] << "\"" << std::endl;
		NEWLINE BORDER

		BOLD std::cout << "--> .SWAP():\t\t\t\t(swapping default && other)"; RESET
		ft::vector<std::string> other(2, "Other stuff");
		BOLD std::cout << "--> OTHER VECTOR:"; RESET
		for (size_t i = 0; i < other.size(); i++)
			std::cout << "OTH[" << i << "] = \"" << other[i] << "\"" << std::endl;
		NEWLINE
		def.swap(other);
		std::cout << "DEFAULT:\n";
		for (size_t i = 0; i < def.size(); i++)
			std::cout << "\tDEF[" << i << "] = \"" << def[i] << "\"" << std::endl;
		std::cout << "OTHER:\n";
		for (size_t i = 0; i < other.size(); i++)
			std::cout << "\tOTH[" << i << "] = \"" << other[i] << "\"" << std::endl;
		NEWLINE BORDER

		// ft::vector<std::string> insert(def);
		// BOLD std::cout << "--> .INSERT(1, \"inserted string\"):\t\t\t\t()"; RESET
		// insert.insert();
		// for (size_t i = 0; i < insert.size(); i++)
		// 	std::cout << "MOD[" << i << "] = \"" << insert[i] << "\"" << std::endl;
		// NEWLINE BORDER
		
	// 	ft::vector<std::string> mod;

		// BOLD std::cout << "--> .ASSIGN:\t\t\t\t(fill version)"; RESET
		// mod.assign(4, "assigned string");
		// for (size_t i = 0; i < def.size(); i++)
		// 	std::cout << "DEF[" << i << "] = \"" << def[i] << "\"" << std::endl;
		// NEWLINE BORDER

		// BOLD std::cout << "--> .ASSIGN:\t\t\t\t(range version)"; RESET
		// mod.assign(def.begin(), def.end());
		// for (size_t i = 0; i < def.size(); i++)
		// 	std::cout << "DEF[" << i << "] = \"" << def[i] << "\"" << std::endl;
		// NEWLINE BORDER

		// BOLD std::cout << "--> .RESERVE():\t\t\t\t(strong exception garantee)"; RESET
		// std::cout << "before reserve: capacity: " << def.capacity() << std::endl;
		// std::cout << "before reserve: max_size: " << def.max_size() << std::endl;
		// mod.reserve();
		// std::cout << "after reserve: capacity: " << def.capacity() << std::endl;;
		// NEWLINE BORDER
	}
	// {
		
	// # include <algorithm>
	// {
	// 	HEADLINE
	// 	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<< ALGORITHM >>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		
	// 	BOLD std::cout << "--> std::transform:\t\t\t\t(adding contents of two vectors)"; RESET
	// 	ft::vector<int> foo(5, 4);
	// 	ft::vector<int> bar(5, 2);
	// 	std::transform(foo.begin(), foo.end(), bar.begin(), foo.begin(), std::plus<int>());
	// 	for (size_t i = 0; i < foo.size(); i++)
	// 		std::cout << "MOD[" << i << "] = \"" << foo[i] << "\"" << std::endl;
	// 	NEWLINE BORDER
	// }
}