/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redblack.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:20:12 by afenzl            #+#    #+#             */
/*   Updated: 2023/01/11 18:10:35 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define NEWLINE std::cout << std::endl;
# define BORDER std::cout << "------------------------------------------------------------------" << std::endl;
# define HEADLINE std::cout << "\033[32;5;81m ";
# define BOLD std::cout << "\033[0;1m";
# define RESET std::cout << "\033[0m" << std::endl;

# include "../../include/map.hpp"
# include "../../include/utils/rbt_node.hpp"
	# include <map>

void	test_redblack()
{
	ft::Redblack_Tree<int> test;

	// std::cout << "the size is " << test.size() << std::endl;
	// std::cout << "the maxsize is " << test.max_size() << std::endl;
	// std::cout << "empty is " << test.empty() << std::endl;

	test.insert(1);
	test.insert(-8);
	test.insert(4);
	test.insert(2);
	test.insert(5);
	test.insert(10);
	test.insert(100);

	ft::Rbt_Iterator<int> start = test.begin();

	// while(start != test.end())
	// {
	// 	std::cout << *start << std::endl;
	// 	++start;
	// }

	// std::cout << "\nROOT IS  " << *test.root() << std::endl;

	// ft::Rbt_Node<char> def;
	// ft::Rbt_Node<char> des('c', NULL);


	// std::cout << test.root()->_value << std::endl;

	// std::map<std::string, int> map;
	// map["HEY"] = 10;
	// map["YOU"] = -1;
	// map.insert(std::make_pair("this", 55));

	// system("leaks ft_containers");
	

	// map.insert(5, 'c');


}