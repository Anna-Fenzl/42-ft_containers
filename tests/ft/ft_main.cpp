/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:08:05 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/25 16:08:33 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./ft_tests.hpp"

# include "../../include/vector.hpp"
# include "../../include/map.hpp"
# include "../../include/utils/compare.hpp"
# include "../../include/utils/pair.hpp"

# include <map>

int main()
{
	test_other();
	test_vector();
	test_stack();
	test_map();
	test_set();

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