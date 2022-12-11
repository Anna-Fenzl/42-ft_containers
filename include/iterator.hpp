/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:26:08 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/09 14:23:37 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iterator>

namespace ft
{
	// <<<<<<<<<<<<<<<<<<<<<< ITERATOR CATERGORY >>>>>>>>>>>>>>>>>>>>>>>>>>>
	typedef std::input_iterator_tag				input_iterator_tag;
	typedef std::output_iterator_tag			output_iterator_tag;
	typedef std::forward_iterator_tag			forward_iterator_tag;
	typedef std::bidirectional_iterator_tag		bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag		random_access_iterator_tag;

	// <<<<<<<<<<<<<<<<<<<<<<<<<< ITERATOR TRAITS >>>>>>>>>>>>>>>>>>>>>>>>>>
	
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits < T* >
	{
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::ptrdiff_t						difference_type;
		typedef ft::random_access_iterator_tag		iterator_category;
	};

	template <class T>
	struct iterator_traits < const T* >
	{
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::ptrdiff_t						difference_type;
		typedef ft::random_access_iterator_tag		iterator_category;
	};

	// <<<<<<<<<<<<<<<<<<<<<<<<<< BaseIterator >>>>>>>>>>>>>>>>>>>>>>>>>>
	
	template <
			class Category, 
			class T, 
			class Difference = std::ptrdiff_t, 
			class Pointer = T*, 
			class Reference = T&
			>
	struct Iterator
	{
		typedef T				value_type;
		typedef Pointer			pointer;
		typedef Reference		reference;
		typedef Difference		difference_type;
		typedef Category		iterator_category;
	};
}

#endif
