/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:47:47 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/18 16:08:16 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define NEWLINE std::cout << std::endl;
# define BORDER std::cout << "------------------------------------------------------------------" << std::endl;
# define HEADLINE std::cout << "\033[32;5;81m ";
# define BOLD std::cout << "\033[0;1m";
# define RESET std::cout << "\033[0m" << std::endl;

# include "./include/stack.hpp"

# include <string>
# include <vector>

void	test_stack()
{
	std::cout << std::boolalpha;

	{
		HEADLINE
		std::cout << "\n<<<<<<<<<<<<<<< ELEMENT_ACCESS && MODIFIERS >>>>>>>>>>>>>>>>>>>>>>"; RESET
	
		ft::stack<std::string> stack;

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
		ft::stack<int> stack;

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
		ft::stack<int> empty;

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

		ft::stack<int> def;

		def.push(1);
		def.push(2);
		def.push(3);

		ft::stack<int> oth;

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