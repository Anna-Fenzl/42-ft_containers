/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:20:12 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/25 16:09:39 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define NEWLINE std::cout << std::endl;
# define BORDER std::cout << "------------------------------------------------------------------" << std::endl;
# define HEADLINE std::cout << "\033[35;5;81m";
# define BOLD std::cout << "\033[0;1m";
# define RESET std::cout << "\033[0m" << std::endl;

# include "../../include/map.hpp"
# include "../../include/utils/rbt_node.hpp"
# include "../../include/iterators/rbt_iterator.hpp"
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

void	test_map()
{
	std::cout << std::boolalpha << std::endl;
	HEADLINE
	std::cout << "------------------------------------------------------------------\n";
	std::cout << "|                                MAP                             |\n";
	std::cout << "------------------------------------------------------------------";
	RESET
	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<< CONSTRUCTORS >>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		
		ft::map<int, std::string> empty;
		BOLD std::cout << "--> EMPTY MAP:"; RESET 
		// empty.print(); NEWLINE BORDER

		empty.insert(ft::make_pair(1, "one"));
		empty.insert(ft::make_pair(7, "seven"));
		empty.insert(ft::make_pair(4, "four"));
		empty.insert(ft::make_pair(2, "two"));
		empty.insert(ft::make_pair(5, "five"));

		ft::map<int, std::string> copy(empty);
		BOLD std::cout << "--> COPIED MAP:"; RESET 
		// copy.print(); NEWLINE BORDER

		ft::map<int, std::string> range(empty.begin(), empty.end());
		BOLD std::cout << "--> RANGE MAP:"; RESET 
		// range.print(); NEWLINE BORDER
	}

		{
		HEADLINE
		std::cout <<  "\n<<<<<<<<<<<<<<<<<<<<<<<<<< ITERATORS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		ft::map<char, int> iter;
		iter.insert(ft::make_pair('F', 0));
		iter.insert(ft::make_pair('S', 0));
		iter.insert(ft::make_pair('K', 0));
		iter.insert(ft::make_pair('D', 0));
		iter.insert(ft::make_pair('A', 0));
		iter.insert(ft::make_pair('P', 0));
		iter.insert(ft::make_pair('W', 0));

		BOLD std::cout << "DEFAULT:" << std::endl; RESET
		// iter.print(); NEWLINE BORDER
		
		BOLD std::cout << "BEGIN() TO END()"; RESET
		for (ft::map<char, int>::iterator it = iter.begin(); it != iter.end(); ++it )
		{
			std::cout << it->first << ", ";
		} NEWLINE BORDER

		BOLD std::cout << "RBEGIN() TO REND()"; RESET
		for (ft::map<char, int>::reverse_iterator it = iter.rbegin(); it != iter.rend(); ++it )
		{
			std::cout << it->first << ", ";
		} NEWLINE BORDER
	}

	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<< ELEMENT ACCESS >>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		
		ft::map<int, char> access;
		access.insert(ft::make_pair(4, 'k'));
		access.insert(ft::make_pair(0, 't'));
		
		BOLD std::cout << "[] OPERATOR:\t\t\t\t(inserts if not found)"; RESET
		std::cout << "[0]: " << access[0] << "\t(previouseliy inserted)" << std::endl;
		std::cout << "[1]: " << access[1] << std::endl;
		std::cout << "[2]: " << access[2] << std::endl;
		std::cout << "[3]: " << access[3] << std::endl;
		std::cout << "[4]: " << access[4] << "\t(previousliy inserted)" << std::endl;
		NEWLINE BORDER

		// access.print();
		NEWLINE BORDER

		BOLD std::cout << "AT():\t\t\t\t\t(throws when not found))"; RESET
		try
		{
			std::cout << "at(2) " << access.at(2) << std::endl;
			std::cout << "at(10) " << access.at(10) << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << "CATCHED EXCEPTION: "<<  e.what() << std::endl;
		}
	}

	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<< MODIFIERS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		ft::map<char, bool> def;
		def.insert(ft::make_pair('a', false));
		def.insert(ft::make_pair('k', true));
		def.insert(ft::make_pair('o', true));
		def.insert(ft::make_pair('s', false));
		def.insert(ft::make_pair('f', true));

		BOLD std::cout << "DEFAULT:" << std::endl; RESET
		// def.print(); NEWLINE BORDER

		BOLD std::cout << "CLEAR()"; RESET
		ft::map<char, bool> clear(def);
		clear.clear();
		// clear.print(); NEWLINE BORDER
		
		ft::map<char, bool> insert;
		BOLD std::cout << "INSERT(ft::pair('l', true))\t\t\t(single element)"; RESET
		insert.insert(ft::make_pair('l', true));
		// insert.print(); NEWLINE BORDER

		BOLD std::cout << "INSERT(def.begin(), def.end())\t\t\t(range)"; RESET
		insert.insert(def.begin(), def.end());
		// insert.print(); NEWLINE BORDER

		BOLD std::cout << "ERASE('l')\t\t\t\t\t(single element, compare object could throw exeptions)"; RESET
		insert.erase('l');
		// insert.print(); NEWLINE BORDER

		BOLD std::cout << "ERASE(begin())\t\t\t\t\t(single element)"; RESET
		insert.erase(insert.begin());
		// insert.print(); NEWLINE BORDER

		BOLD std::cout << "ERASE(++begin(); end())\t\t\t\t(range)"; RESET
		insert.erase((++insert.begin()), insert.end());
		// insert.print(); NEWLINE BORDER

		BOLD std::cout << "SWAP(def)"; RESET
		insert.swap(def);
		std::cout << "other:\n";
		// def.print(); NEWLINE
		std::cout << "default:\n";
		// insert.print(); NEWLINE BORDER
	}

	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<< LOOKUP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		ft::map<int, int> look;
		look.insert(ft::make_pair(1, 1));
		look.insert(ft::make_pair(7, 1));
		look.insert(ft::make_pair(3, 1));
		look.insert(ft::make_pair(2, 1));
		look.insert(ft::make_pair(9, 1));
		BOLD std::cout << "DEFAULT:" << std::endl; RESET
		// look.print(); NEWLINE BORDER

		BOLD std::cout << "COUNT(), Amount of times key is found"; RESET
		std::cout << "key found     = " << look.count(1) << std::endl;
		std::cout << "key not found = " << look.count(10) << std::endl;
		NEWLINE BORDER
		
		BOLD std::cout << "LOWER_BOUND()"; RESET
		std::cout << "Iterator pointing to the first element that is not less than\n";
		std::cout << "key(3) :" << look.lower_bound(3)->first << std::endl; 
		std::cout << "key(5) :" << look.lower_bound(5)->first << std::endl; NEWLINE BORDER

		BOLD std::cout << "UPPER_BOUND()"; RESET
		std::cout << "Iterator pointing to the first element that is greater than\n";
		std::cout << "key(3) :" << look.upper_bound(3)->first << std::endl;
		std::cout << "key(5) :" << look.upper_bound(5)->first << std::endl; NEWLINE BORDER

		BOLD std::cout << "EQUAL_RANGE()"; RESET
		std::cout << "returns a pair, first element that is not less than key and another pointing to the first element greater than key" << std::endl;
		std::cout << "key(3) :" << (look.equal_range(3).first)->first << ", " << (look.equal_range(3).second)->first << std::endl;
		std::cout << "key(5) :" << (look.equal_range(5).first)->first << ", " << (look.equal_range(5).second)->first << std::endl;
	}

	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<< ITERATOR INVALIDATION >>>>>>>>>>>>>>>>>>>>"; RESET

		ft::map<int, int> look;
		look.insert(ft::make_pair(1, 1));
		look.insert(ft::make_pair(7, 1));
		look.insert(ft::make_pair(3, 1));
		look.insert(ft::make_pair(2, 1));
		look.insert(ft::make_pair(9, 1));

		ft::map<int, int>::iterator it = look.begin();
		look.erase(7);
		look.erase(2);

		std::cout << "iterator after erase: " << (*it).first << "/" << (*it).second << std::endl;
	}

	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<< TEST CONST >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET

		ft::map<int, std::string> coins;
		coins.insert(ft::make_pair(100, "dollar"));
		coins.insert(ft::make_pair(25, "quarter"));
		coins.insert(ft::make_pair(5, "nickel"));
		coins.insert(ft::make_pair(1, "penny"));

		const ft::map<int, std::string> money(coins);
		// money.print(); NEWLINE
	
		ft::map<int, std::string>::const_iterator it = money.find(100);
		std::cout << it->first << std::endl;

		// // shouldn't compile
		// {
			// money.clear();
			// money.insert(ft::make_pair(50, "half dollar"));
			// it->first = 56;
		// }
	}

	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<< OPERATOR OVERLOAD >>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		
		ft::map<std::string, bool> extinct;
		extinct.insert(ft::make_pair("Dodo", true));
		
		ft::map<std::string, bool> other;

		std::cout << "DEF == DEF\t-> " << ( extinct == extinct) << std::endl;
		std::cout << "OTH == DEF\t-> " << ( extinct == other) << std::endl;
		NEWLINE
		std::cout << "DEF < DEF\t-> " << ( extinct < extinct) << std::endl;
		std::cout << "DEF < OTH\t-> " << ( extinct < extinct) << std::endl;
		std::cout << "OTH < DEF\t-> " << ( other < extinct) << std::endl;
		NEWLINE BORDER
	}

	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<< BIG SIZE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		ft::map<int, int> size;

		std::cout << "~5000000 insertions" << std::endl;
		srand(2745896);
		for (size_t i = 0; i < 5000000; i++)
		{
			size.insert(ft::make_pair(rand() % (50000000 + 1), rand() % 14));
		}
		// size.print();
		
		std::cout << "size: " << size.size() << std::endl;
		std::cout << "find()" << size.begin()->first << ": " << size.at(size.begin()->first) << std::endl;
		NEWLINE BORDER
	}
}