/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_other.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:02:29 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/08 16:12:48 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define NEWLINE std::cout << std::endl;
# define BORDER std::cout << "------------------------------------------------------------------" << std::endl;
# define HEADLINE std::cout << "\033[33;5;81m ";
# define BOLD std::cout << "\033[0;1m";
# define RESET std::cout << "\033[0m" << std::endl;

# include "../../include/utils/compare.hpp"
# include "../../include/utils/pair.hpp"

# include <string>
# include <iostream>

void test_other()
{
	std::cout << std::boolalpha << std::endl;
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