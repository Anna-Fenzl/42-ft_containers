/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_stack.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:59:53 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/09 14:00:59 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define NEWLINE std::cout << std::endl;
# define BORDER std::cout << "------------------------------------------------------------------" << std::endl;
# define HEADLINE std::cout << "\033[32;5;81m ";
# define BOLD std::cout << "\033[0;1m";
# define RESET std::cout << "\033[0m" << std::endl;

# include "tests.hpp"

void	test_stack()
{
	std::cout << std::boolalpha;
	
	HEADLINE
	std::cout << "----------------------------------------------------------------------\n";
	std::cout << "|                              STACK                                 |\n";
	std::cout << "----------------------------------------------------------------------\n";
	RESET

	{
	std::cout << "\n<<<<<<<<<<<<<<< ELEMENT_ACCESS && MODIFIERS >>>>>>>>>>>>>>>>>>>>>>"; RESET
		HEADLINE
	
		std::stack<std::string> stack;

		NEWLINE
		BOLD std::cout << "--> .PUSH():"; RESET
		stack.push("first  push");
		stack.push("second push");
		stack.push("third  push");
		stack.push("fourth push");
		
		BOLD std::cout << "--> .TOP() && .POP():"; RESET
		for (size_t i = 0; i < stack.size();)
		{
			std::cout << "top is \"" << stack.top() << "\"" << std::endl;
			stack.pop();
		}
		NEWLINE
	}


	{
		HEADLINE
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<< CAPACITY >>>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		std::stack<int> stack;

		BOLD std::cout << "--> EMPTY STACK:"; RESET
		std::cout << "size()\t= " << stack.size() << std::endl;
		std::cout << "empty()\t= " << stack.empty() << std::endl;
		NEWLINE

		stack.push(1);
		stack.push(2);
		stack.push(3);
		stack.push(4);
		stack.push(5);
		stack.push(6);

		std::cout << "~pushed ints from 1 to 6" << std::endl;
		BOLD std::cout << "--> FILLED STACK:"; RESET
		std::cout << "size()\t= " << stack.size() << std::endl;
		std::cout << "empty()\t= " << stack.empty() << std::endl;
		NEWLINE



		HEADLINE
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<< =OPERATOR >>>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		std::stack<int> empty;

		std::cout << "assigning empty container to prev" << std::endl;
		empty = stack;
		
		NEWLINE
		BOLD std::cout << "--> EMPTY:"; RESET
		for (size_t i = 0; i < empty.size();)
		{
			std::cout << "top is \"" << empty.top() << "\"" << std::endl;
			empty.pop();
		}
		NEWLINE
	}


	{
		HEADLINE
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<< NON_MEMBER FUNCITONS >>>>>>>>>>>>>>>>>>>>>>"; RESET

		std::stack<int> def;

		def.push(1);
		def.push(2);
		def.push(3);

		std::stack<int> oth;

		def.push(11);

		std::cout << "~ def with 1, 2, 3\n~ oth with 11" << std::endl;
		NEWLINE

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
		std::cout << "OTH > DEF\t-> " << ( oth < def) << std::endl;
		NEWLINE BORDER
	}

}