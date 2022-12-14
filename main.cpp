/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:08:05 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/14 12:19:00 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./include/containers.hpp"
# include "./tests/test.hpp"

int main()
{
	test_vector();

	// std::vector<int> i(4, 6);
	
	// std::cout << i.max_size() << std::endl;
	// try
	// {
	// 	i.reserve(i.max_size() + 1);
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	
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