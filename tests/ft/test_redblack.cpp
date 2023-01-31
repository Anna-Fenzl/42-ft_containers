/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redblack.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:20:12 by afenzl            #+#    #+#             */
/*   Updated: 2023/01/31 15:22:46 by afenzl           ###   ########.fr       */
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
		ft::Redblack_Tree<int> test;

		ft::pair<ft::Rbt_Iterator<int>, bool> ret = test.insert(1);
		// std::cout << "inserted " << *ret.first << "  and bool returns: " << ret.second << std::endl;
		// ret = test.insert(1);
		// std::cout << "inserted " << *ret.first << "  and bool returns: " << ret.second << std::endl;
		test.insert(4);
		test.insert(5);
		test.insert(6);
		test.insert(2);
		test.insert(3);
		test.insert(13);
		test.insert(14);
		test.insert(17);
		test.insert(10);
		test.insert(7);
		test.insert(9);
		test.insert(0);
		test.insert(11);

		test.print_tree();
		std::cout << "---------------------------\n" << std::endl;

		// test.erase(test.find(4));
		// test.erase(test.find(17));
		// test.erase(test.find(10));
		// test.erase(test.find(5));
		// test.erase(test.find(9));
		// test.erase(test.find(2));
		// test.erase(test.find(6));
		// test.erase(test.find(13));
			

		std::cout << "compare:\n";
		// test.print_tree();
		// test.clear();
		// std::cout << "behind clear" << std::endl;
		ft::Redblack_Tree<int> copy = test;
		copy.print_tree();
		test.print_tree();

}