/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:20:12 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/05 14:28:01 by afenzl           ###   ########.fr       */
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
	# include <map>
	# include <stdio.h>


void	test_map()
{
	std::cout << std::boolalpha << std::endl;
	HEADLINE
	std::cout << "----------------------------------------------------------------------\n";
	std::cout << "|                                MAP                                 |\n";
	std::cout << "----------------------------------------------------------------------";
	RESET
	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<< CONSTRUCTORS >>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		
		ft::map<int, std::string> empty;
		BOLD std::cout << "--> EMPTY MAP:"; RESET 
		empty.print(); NEWLINE BORDER

		empty.insert(ft::make_pair(1, "one"));
		empty.insert(ft::make_pair(7, "seven"));
		empty.insert(ft::make_pair(4, "four"));
		empty.insert(ft::make_pair(2, "two"));
		empty.insert(ft::make_pair(5, "five"));

		ft::map<int, std::string> copy(empty);
		BOLD std::cout << "--> COPIED MAP:"; RESET 
		copy.print(); NEWLINE BORDER

		ft::map<int, std::string> range(empty.begin(), empty.end());
		BOLD std::cout << "--> RANGE MAP:"; RESET 
		range.print(); NEWLINE BORDER
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

		access.print();
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
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<< MODIFIERS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		ft::map<char, bool> def;
		def.insert(ft::make_pair('a', false));
		def.insert(ft::make_pair('k', true));
		def.insert(ft::make_pair('o', true));
		def.insert(ft::make_pair('s', false));
		def.insert(ft::make_pair('f', true));
		def.print();
		
		NEWLINE
		def.erase(++def.begin(), def.end());
		std::cout << "def is empty: " << def.empty() << std::endl;
		def.print();

		std::map<char, bool> comp;
		comp.insert(std::make_pair('a', false));
		comp.insert(std::make_pair('k', true));
		comp.insert(std::make_pair('o', true));
		comp.insert(std::make_pair('s', false));
		comp.insert(std::make_pair('f', true));

		comp.erase(++comp.begin(), comp.end());
		std::cout << "comp is empty: " << comp.empty() << std::endl;


		// BOLD std::cout << "DEFAULT:" << std::endl; RESET
		// def.print(); NEWLINE BORDER

		// BOLD std::cout << "CLEAR()"; RESET
		// ft::map<char, bool> clear(def);
		// clear.clear();
		// clear.print(); NEWLINE BORDER
		
		// ft::map<char, bool> insert;
		// BOLD std::cout << "INSERT(ft::pair('l', true))\t\t\t(single element)"; RESET
		// insert.insert(ft::make_pair('l', true));
		// insert.print(); NEWLINE BORDER

		// BOLD std::cout << "INSERT(def.begin(), def.end())\t\t\t(range)"; RESET
		// insert.insert(def.begin(), def.end());
		// insert.print(); NEWLINE BORDER

		// BOLD std::cout << "ERASE('l')\t\t\t\t\t(single element, compare object could throw exeptions)"; RESET
		// insert.erase('l');
		// insert.print(); NEWLINE BORDER

		// BOLD std::cout << "ERASE(begin())\t\t\t\t\t(single element)"; RESET
		// insert.erase(insert.begin());
		// insert.print(); NEWLINE

		// BOLD std::cout << "ERASE(begin(); end())\t\t\t\t(range)"; RESET
		// std::cout << "(++insert.begin() is " << *(++insert.begin()) << std::endl;
		// insert.erase((++insert.begin()), insert.end());
		// insert.print(); NEWLINE
		
	}
}