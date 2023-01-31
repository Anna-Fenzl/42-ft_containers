/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redblack.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:20:12 by afenzl            #+#    #+#             */
/*   Updated: 2023/01/31 18:26:49 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define NEWLINE std::cout << std::endl;
# define BORDER std::cout << "------------------------------------------------------------------" << std::endl;
# define HEADLINE std::cout << "\033[32;5;81m ";
# define BOLD std::cout << "\033[0;1m";
# define RESET std::cout << "\033[0m" << std::endl;

# include "../../include/map.hpp"
# include "../../include/utils/rbt_node.hpp"
# include "../../include/iterators/rbt_iterator.hpp"
	# include <map>
	# include <stdio.h>

void	test_redblack()
{
		ft::Redblack_Tree<ft::pair<char, int> > test;

		test.insert(ft::make_pair('a', 1));
		// ret = test.insert(1);
		// std::cout << "inserted " << *ret.first << "  and bool returns: " << ret.second << std::endl;
		test.insert(ft::make_pair('d', 4));
		test.insert(ft::make_pair('e', 5));
		test.insert(ft::make_pair('f', 90));
		test.insert(ft::make_pair('g', 80));
		test.insert(ft::make_pair('k', 14));
		test.insert(ft::make_pair('b', 11));

		ft::map<char, int> map(test.begin(), test.end());

		map.print();
		map.print();

		
		// std::cout << "inserted " << *ret.first << "  and bool returns: " << ret.second << std::endl;
		// ret = map.insert(ft::make_pair("first test", 99));
		// std::cout << "inserted " << *ret.first << "  and bool returns: " << ret.second << std::endl;

		// map.insert(ft::make_pair("first test", 15));


		
}