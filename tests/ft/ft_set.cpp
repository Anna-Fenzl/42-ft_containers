/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:30:17 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/25 15:52:00 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define NEWLINE std::cout << std::endl;
# define BORDER std::cout << "------------------------------------------------------------------" << std::endl;
# define HEADLINE std::cout << "\033[32;5;81m";
# define BOLD std::cout << "\033[0;1m";
# define RESET std::cout << "\033[0m" << std::endl;

# include "../../include/set.hpp"

# include <string>
# include <iostream>

void test_set()
{
	std::cout << std::boolalpha;
	HEADLINE
	std::cout << "------------------------------------------------------------------\n";
	std::cout << "|                                SET                             |\n";
	std::cout << "------------------------------------------------------------------";
	RESET
	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<< CONSTRUCTORS >>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET

		BOLD std::cout << "--> EMPTY SET:"; RESET 
		ft::set<std::string>	empty;
		// empty.print(); NEWLINE BORDER

		empty.insert("clear");
		empty.insert("ls");
		empty.insert("echo");
		empty.insert("chmod");
		empty.insert("cat");

		BOLD std::cout << "--> RANGE SET:"; RESET 
		ft::set<std::string>	range(empty.begin(), empty.end());
		// range.print(); NEWLINE BORDER

		BOLD std::cout << "--> COPY SET:"; RESET 
		ft::set<std::string>	copy(empty);
		// copy.print(); NEWLINE BORDER
	}

	
	{
		HEADLINE
		std::cout <<  "\n<<<<<<<<<<<<<<<<<<<<<<<<<< ITERATORS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		ft::set<char> iter;
		iter.insert('F');
		iter.insert('S');
		iter.insert('K');
		iter.insert('D');
		iter.insert('A');
		iter.insert('P');
		iter.insert('W');

		BOLD std::cout << "DEFAULT:" << std::endl; RESET
		// iter.print(); NEWLINE BORDER
		
		BOLD std::cout << "BEGIN() TO END()"; RESET
		for (ft::set<char>::iterator it = iter.begin(); it != iter.end(); ++it )
		{
			std::cout << *it << ", ";
		} NEWLINE BORDER

		BOLD std::cout << "RBEGIN() TO REND()"; RESET
		for (ft::set<char>::reverse_iterator it = iter.rbegin(); it != iter.rend(); ++it )
		{
			std::cout << *it << ", ";
		} NEWLINE BORDER
	}
		
	

	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<< MODIFIERS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		ft::set<int> def;
		def.insert(3);
		def.insert(7);
		def.insert(19);
		def.insert(1);
		def.insert(5);

		BOLD std::cout << "DEFAULT:" << std::endl; RESET
		// def.print(); NEWLINE BORDER

		BOLD std::cout << "CLEAR()"; RESET
		ft::set<int> clear(def);
		clear.clear();
		// clear.print(); NEWLINE BORDER
		
		ft::set<int> insert;
		BOLD std::cout << "INSERT(ft::pair('l', true))\t\t\t(single element)"; RESET
		insert.insert(8);
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
		ft::set<std::string> look;
		look.insert("-8");
		look.insert("-2");
		look.insert("-0");
		look.insert("-1");
		look.insert("-4");
		BOLD std::cout << "DEFAULT:" << std::endl; RESET
		// look.print(); NEWLINE BORDER

		BOLD std::cout << "COUNT(), Amount of times key is found"; RESET
		std::cout << "key found     = " << look.count("-0") << std::endl;
		std::cout << "key not found = " << look.count("-5876") << std::endl;
		NEWLINE BORDER
		
		BOLD std::cout << "LOWER_BOUND()"; RESET
		std::cout << "Iterator pointing to the first element that is not less than\n";
		std::cout << "key(3) :" << *look.lower_bound("-2") << std::endl; 
		std::cout << "key(5) :" << *look.lower_bound("-5") << std::endl; NEWLINE BORDER

		BOLD std::cout << "UPPER_BOUND()"; RESET
		std::cout << "Iterator pointing to the first element that is greater than\n";
		std::cout << "key(3) :" << *look.upper_bound("-2") << std::endl;
		std::cout << "key(5) :" << *look.upper_bound("-5") << std::endl; NEWLINE BORDER

		BOLD std::cout << "EQUAL_RANGE()"; RESET
		std::cout << "returns a pair, first element that is not less than key and another pointing to the first element greater than key" << std::endl;
		std::cout << "key(3) :" << *look.equal_range("-2").first << ", " << *look.equal_range("-2").second << std::endl;
		std::cout << "key(5) :" << *look.equal_range("-2").first << ", " << *look.equal_range("-5").second << std::endl;
	}

	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<< TEST CONST >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET

		ft::set<int> coins;
		coins.insert(100);
		coins.insert(25);
		coins.insert(10);
		coins.insert(5);

		const ft::set<int> money(coins);
		// money.print(); NEWLINE
	
		const ft::set<int>::const_iterator it = money.find(100);
		std::cout << *it << std::endl;

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
		
		ft::set<std::string> extinct;
		extinct.insert("Dodo");
		
		ft::set<std::string> other;

		std::cout << "DEF == DEF\t-> " << ( extinct == extinct) << std::endl;
		std::cout << "OTH == DEF\t-> " << ( extinct == other) << std::endl;
		NEWLINE
		std::cout << "DEF < DEF\t-> " << ( extinct < extinct) << std::endl;
		std::cout << "DEF < OTH\t-> " << ( extinct < extinct) << std::endl;
		std::cout << "OTH < DEF\t-> " << ( other < extinct) << std::endl;
		NEWLINE BORDER
	}
}