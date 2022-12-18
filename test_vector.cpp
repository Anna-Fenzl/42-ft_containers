/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:14:51 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/18 16:56:50 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# define NEWLINE std::cout << std::endl;
# define BORDER std::cout << "------------------------------------------------------------------" << std::endl;
# define HEADLINE std::cout << "\033[38;5;81m ";
# define BOLD std::cout << "\033[0;1m";
# define RESET std::cout << "\033[0m" << std::endl;

# include "./include/vector.hpp"
# include "./include/utils/compare.hpp"
# include "./include/utils/pair.hpp"

# include <string>
# include <vector>

/*
	TO DO:S
	
	==> look over that again
	max_size exception
	const_iterator for insert
	try catch for allocation
	ig *this != other operator=
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
		
		ft::vector<char> range(fill.begin()+1, fill.end());			// -> range constructor
		BOLD std::cout << "--> RANGE VECTOR:\t(fill.begin()+1, fill.end())"; RESET
		for (size_t i = 0; i < range.size(); i++)
			std::cout << "RANGE[" << i << "] = " << range[i] << ", ";
		NEWLINE BORDER
		
		ft::vector<char> copy(fill);								// -> copy constructor
		BOLD std::cout << "--> COPIED VECTOR:\t(from fill)"; RESET 
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

		BOLD std::cout << "INCREMENT ITERATOR:"; RESET
		std::cout << "for ( it = VEC.BEGIN(); it != VEC.END(); ++IT ) :" << std::endl;
		for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout  << *it << ", ";
		NEWLINE NEWLINE

		BOLD std::cout << "DECREMENT ITERATOR:"; RESET
		std::cout << "for ( it = --VEC.END(); it != --VEC.BEGIN(); --IT ) :" << std::endl;
		for (ft::vector<int>::iterator it = --vec.end(); it != --vec.begin(); --it)
			std::cout  << *it << ", ";
		NEWLINE NEWLINE

		BOLD std::cout << "INCREMENT REVERSE ITERATOR:"; RESET
		std::cout << "for ( it = VEC.RBEGIN(); it != VEC.REND(); ++IT ) :" << std::endl;
		for (ft::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
			std::cout  << *it << ", ";
		NEWLINE NEWLINE

		BOLD std::cout << "DECREMENT REVERSE ITERATOR:"; RESET
		std::cout << "for ( it = VEC.REND(); it != VEC.RBEGIN(); --IT ) :" << std::endl;
		for (ft::vector<int>::reverse_iterator it = --vec.rend(); it != --vec.rbegin(); --it)
			std::cout  << *it << ", ";
		NEWLINE NEWLINE
	
		BOLD std::cout << "[] OPERATOR:\t\t\t\t(forward iterator))"; RESET
		ft::vector<int>::iterator it0(vec.begin());
		std::cout << "it(vec.begin());       print it[3]: \'" << it0[3] << "\'" << std::endl;
		ft::vector<int>::iterator it1(++vec.begin());
		std::cout << "it(&vec[1]);           print it[3]: \'" << it1[3] << "\'" << std::endl;
		NEWLINE

		BOLD std::cout << "[] OPERATOR:\t\t\t\t(reverse iterator))"; RESET
		ft::vector<int>::reverse_iterator it2(vec.rbegin());
		std::cout << "it(vec.rbegin());       print it[3]: \'" << it2[3] << "\'" << std::endl;
		ft::vector<int>::reverse_iterator it3(++vec.rbegin());
		std::cout << "it(&vec[1]);           print it[3]: \'" << it3[3] << "\'" << std::endl;
		NEWLINE NEWLINE
	}


	
	{
		HEADLINE
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<< CAPACITY >>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET

		std::cout << std::boolalpha;
		
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
		BOLD std::cout << "--> RESIZE VECTOR:\t\t\t\t" << std::endl; RESET
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
			for (size_t i = 0; i < res.size(); i++)
				std::cout << "RES[" << i << "] = \'" << res[i] << "\', ";
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

		ft::vector<std::string> clear(def);
		BOLD std::cout << "--> .CLEAR():"; RESET
		clear.clear();
		for (size_t i = 0; i < clear.size(); i++)
			std::cout << "MOD[" << i << "] = \"" << clear[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> as(def);
		BOLD std::cout << "--> .ASSIGN(4, \"assigned string\"):\t\t\t(fill version)"; RESET
		as.assign(4, "assigned string (fill)");
		for (size_t i = 0; i < as.size(); i++)
			std::cout << "FILL[" << i << "] = \"" << as[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> range(def);
		BOLD std::cout << "--> .ASSIGN(as.begin()+1, as.end()):\t\t\t(range version)"; RESET
		range.assign(def.begin()+1, def.end());
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
		
		ft::vector<std::string> other(2, "Other stuff");
		BOLD std::cout << "--> OTHER VECTOR:"; RESET
		for (size_t i = 0; i < other.size(); i++)
			std::cout << "OTH[" << i << "] = \"" << other[i] << "\"" << std::endl;
		NEWLINE BORDER
		
		ft::vector<std::string> insert_one(def);
		BOLD std::cout << "--> .INSERT( .BEGIN()+1, \"->inserted string\"):\t\t\t\t(one element)"; RESET
		insert_one.insert(insert_one.begin()+1, " ------ inserted string");
		for (size_t i = 0; i < insert_one.size(); i++)
			std::cout << "MOD[" << i << "] = \"" << insert_one[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> insert_more(def);
		BOLD std::cout << "--> .INSERT( .BEGIN(), 5,\"->inserted string\"):\t\t\t\t(multible elements)"; RESET
		insert_more.insert(insert_more.begin()+1, 5, " ------ inserted string");
		for (size_t i = 0; i < insert_more.size(); i++)
			std::cout << "MOD[" << i << "] = \"" << insert_more[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> insert_range(def);
		BOLD std::cout << "--> .INSERT(BEGIN()+1, OTHER.BEGIN(), OTHER.END()):\t\t\t(range)"; RESET
		insert_range.insert(insert_range.begin()+1, other.begin(), other.end());
		for (size_t i = 0; i < insert_range.size(); i++)
			std::cout << "MOD[" << i << "] = \"" << insert_range[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> erase_one(insert_range);
		BOLD std::cout << "--> .ERASE(ERASE.BEGIN()+1)(from vector above):\t\t\t\t(single element)"; RESET
		ft::vector<std::string>::iterator it0 = erase_one.erase(erase_one.begin()+1);
		std::cout << "returned iterator is \"" << *it0 << "\"\n" << std::endl;
		for (size_t i = 0; i < erase_one.size(); i++)
			std::cout << "MOD[" << i << "] = \"" << erase_one[i] << "\"" << std::endl;
		NEWLINE BORDER

		ft::vector<std::string> erase_more(insert_range);
		BOLD std::cout << "--> .ERASE(ERASE.BEGIN()+2, ERASE.END()-1)(from same vector):\t\t\t\t(range)"; RESET
		ft::vector<std::string>::iterator it1 = erase_more.erase(erase_more.begin()+2, erase_more.end()-1);
		std::cout << "returned iterator is \"" << *it1 << "\"\n" << std::endl;
		for (size_t i = 0; i < erase_more.size(); i++)
			std::cout << "MOD[" << i << "] = \"" << erase_more[i] << "\"" << std::endl;
		NEWLINE BORDER

		BOLD std::cout << "--> .SWAP():\t\t\t\t(swapping default && other)"; RESET
		def.swap(other);
		std::cout << "DEFAULT:\n";
		for (size_t i = 0; i < def.size(); i++)
			std::cout << "\tDEF[" << i << "] = \"" << def[i] << "\"" << std::endl;
		std::cout << "OTHER:\n";
		for (size_t i = 0; i < other.size(); i++)
			std::cout << "\tOTH[" << i << "] = \"" << other[i] << "\"" << std::endl;
		NEWLINE BORDER NEWLINE
	}


	{
		HEADLINE
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<< NON-MEMBER FUNCTIONS >>>>>>>>>>>>>>>>>>>>>>"; RESET
	
		ft::vector<char>	def;
		def.push_back('a');
		def.push_back('b');
		def.push_back('c');
		def.push_back('d');
		def.push_back('e');
		def.push_back('f');
		BOLD std::cout << "--> DEFAULT VECTOR:"; RESET
		for (size_t i = 0; i < def.size(); i++)
			std::cout << "DEF[" << i << "] = \'" << def[i] << "\', ";
		NEWLINE NEWLINE

		ft::vector<char>	oth;
		oth.push_back('a');
		oth.push_back('g');
		BOLD std::cout << "--> OTHER VECTOR:"; RESET
		for (size_t i = 0; i < oth.size(); i++)
			std::cout << "OTH[" << i << "] = \'" << def[i] << "\', ";
		NEWLINE NEWLINE BORDER
		
		BOLD std::cout << "--> OPERATOR==()"; RESET
		std::cout << "DEF == DEF\t-> " << ( def == def) << std::endl;
		std::cout << "DEF == OTH\t-> " << ( def == oth) << std::endl;
		NEWLINE BORDER

		BOLD std::cout << "--> OPERATOR!=()"; RESET
		std::cout << "DEF != DEF\t-> " << ( def != def) << std::endl;
		std::cout << "DEF != OTH\t-> " << ( def != oth) << std::endl;
		NEWLINE BORDER

		BOLD std::cout << "--> OPERATOR<"; RESET
		std::cout << "DEF < DEF\t-> " << ( def < def) << std::endl;
		std::cout << "DEF < OTH\t-> " << ( def < oth) << std::endl;
		NEWLINE BORDER

		BOLD std::cout << "--> SWAP(def, oth)"; RESET
		ft::swap(def, oth);
		for (size_t i = 0; i < def.size(); i++)
			std::cout << "DEF[" << i << "] = \'" << def[i] << "\', ";
		NEWLINE
		for (size_t i = 0; i < oth.size(); i++)
			std::cout << "OTH[" << i << "] = \'" << oth[i] << "\', ";
		NEWLINE NEWLINE BORDER
	}


	{
		HEADLINE
		std::cout << "<<<<<<<<<<<<<<<<<<< LEXICOGRAPHICAL_COMPARE >>>>>>>>>>>>>>>>>>>>>>>"; RESET

		std::cout << "true if the first range is lexicographically less than the second, otherwise false" << std::endl;
		NEWLINE

		char foo[]="abc";
		char bar[]="abc";

		std::cout << "Comparing foo (" << foo <<  ") and bar (" << bar << "):\t";
		std::cout << ft::lexicographical_compare(foo,foo+3,bar,bar+3) << std::endl;
		NEWLINE

		char foo0[] = "ab";
		std::cout << "Comparing foo (" << foo0 <<  ") and bar (" << bar << "):\t";
		std::cout << ft::lexicographical_compare(foo0,foo0+2,bar,bar+3) << std::endl;
		NEWLINE

		char foo1[] = "aXc";
		std::cout << "Comparing foo (" << foo1 <<  ") and bar (" << bar << "):\t";
		std::cout << ft::lexicographical_compare(foo1,foo1+3,bar,bar+3) << std::endl;
		NEWLINE
		
	}


	{
		HEADLINE
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<< EQUAL >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET

		std::cout << "true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), otherwise false" << std::endl;
		NEWLINE
		
		std::string foo = "~<string>~~~~";
		std::string bar = ".......<string>";
		
		std::cout << "Comparing foo \"" << foo <<  "\" and bar \"" << bar << "\":\t";
		std::cout << std::equal(foo.begin(), foo.end(), bar.begin()) << std::endl;
		NEWLINE

		std::cout << "Comparing foo \"" << foo.substr(1,8) <<  "\" and bar \"" << bar.substr(7,15) << "\":\t\t\t";
		std::cout << std::equal(foo.begin()+1, foo.end()-4, bar.begin()+7) << std::endl;
		NEWLINE
	}



	{
		HEADLINE
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PAIR >>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		
		std::cout << "pair is a class template that provides a way to store two heterogeneous objects as a single unit" << std::endl;
		NEWLINE

		std::cout << "testing with string and double:\n" << std::endl;
		ft::pair <std::string,double> product1;
		ft::pair <std::string,double> product2 ("tomatoes",2.30);
		ft::pair <std::string,double> product3 (product2);

		product1 = ft::make_pair(std::string("lightbulbs"),0.99);

		product2.first = "shoes";
		product2.second = 39.90;

		std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
		std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
		std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
		NEWLINE
	}
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
