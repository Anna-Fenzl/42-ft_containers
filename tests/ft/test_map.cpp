/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:20:12 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/03 17:51:26 by afenzl           ###   ########.fr       */
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
		empty.print(); NEWLINE

		empty.insert(ft::make_pair(1, "one"));
		empty.insert(ft::make_pair(7, "seven"));
		empty.insert(ft::make_pair(4, "four"));
		empty.insert(ft::make_pair(2, "two"));
		empty.insert(ft::make_pair(5, "five"));

		ft::map<int, std::string> copy(empty);
		BOLD std::cout << "--> COPIED MAP:"; RESET 
		copy.print(); NEWLINE

		ft::map<int, std::string> range(empty.begin(), empty.end());
		BOLD std::cout << "--> RANGE MAP:"; RESET 
		range.print(); NEWLINE
	}

	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<< ELEMENT ACCESS >>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		
		ft::map<int, char> access;
		access.insert(ft::make_pair(4, 'k'));
		access.insert(ft::make_pair(0, 't'));
		
		BOLD std::cout << "[] OPERATOR:\t\t\t\t(inserts if not found)"; RESET
		std::cout << "[0]: " << access[0] << "\t(previouseliy inserted)" << std::endl;
		std::cout << "[1]: " << access[1] << std::endl;
		std::cout << "[2]: " << access[2] << std::endl;
		std::cout << "[3]: " << access[3] << std::endl;
		std::cout << "[4]: " << access[4] << "\t(previousliy inserted)" << std::endl;
		NEWLINE

		access.print();

		BOLD std::cout << "AT():\t\t\t\t(throws when not found))"; RESET
		std::cout << "at(2) " << access.at(10) << std::endl;
	}
}