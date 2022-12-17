/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:21:03 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/17 16:00:35 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARE_HPP
# define COMPARE_HPP

namespace ft
{
	// <<<<<<<<<<<<<<<<<<<<<<<<<< LEXICOGRAPHICAL_COMPARE >>>>>>>>>>>>>>>>>>>>>>>>>>
	//true if the first range is lexicographically less than the second, otherwise false

	// Elements are compared using operator<
	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2 )
	{
		for(; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first1 > *first2)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	// Elements are compared using the given binary comparison function comp
	// comp returns ​true if the first argument is less than the second.
	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2, Compare comp )
	{
		for(; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	// <<<<<<<<<<<<<<<<<<<<<<<<<< EQUAL >>>>>>>>>>>>>>>>>>>>>>>>>>

	// true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), otherwise false

	template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return false;
		}
		return true;
	}
	
	// p is binary predicate which returns ​true if the elements should be treated as equal.
	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first2))
				return false;
		}
		return true;
	}
	
} // namespace ft


#endif