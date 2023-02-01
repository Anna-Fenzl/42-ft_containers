/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:20:12 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/01 16:47:26 by afenzl           ###   ########.fr       */
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


void	test_map()
{
	{
		HEADLINE
			std::cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<< CONSTRUCTORS >>>>>>>>>>>>>>>>>>>>>>>>>>>"; RESET
		
		ft::map<int, std::string> map;

		map.insert(ft::make_pair(1, "one"));
		map.insert(ft::make_pair(7, "seven"));
		map.insert(ft::make_pair(4, "four"));
		map.insert(ft::make_pair(2, "two"));
		map.insert(ft::make_pair(5, "five"));

		map.print();
		// map.insert(map.begin(), ft::make_pair(4, "six"));
		std::cout << map[6] << std::endl;
		std::cout << "find returns " << *map.find(6) << std::endl;

		// std::cout << "count " << map.count(1) << std::endl;

	}

	
}