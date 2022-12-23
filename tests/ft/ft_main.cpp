/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:08:05 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/23 13:55:42 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./ft_tests.hpp"
# include "../../include/vector.hpp"

int main()
{
	// test_vector();
	// test_stack();

	ft::vector<char> test;
	for(int i = 0; i < 99999999; ++i)
		test.push_back('x');
	test.clear();
	
	// test_redblack();
	return (0);
}
























// #include<iostream>
// int main() {
//     if (__cplusplus == 201703L) std::cout << "C++17\n";
//     else if (__cplusplus == 201402L) std::cout << "C++14\n";
//     else if (__cplusplus == 201103L) std::cout << "C++11\n";
//     else if (__cplusplus == 199711L) std::cout << "C++98\n";
//     else std::cout << "pre-standard C++\n";
// }