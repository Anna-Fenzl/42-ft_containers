/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redblack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:17:48 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/19 13:34:30 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACK_HPP
# define REDBLACK_HPP

// https://gcc.gnu.org/onlinedocs/gcc-4.6.2/libstdc++/api/a01067_source.html

# include "./iterators/redblack_iterator.hpp"
# include "./utils/rbt_node.hpp"
# include <stddef.h>
# include <memory>

namespace ft
{

	// iterators

	template<typename _Val, typename _Compare, typename _Alloc = std::allocator<_Val> >
	class Rbt_Tree
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		typedef typename	_Alloc::template rebind<Rbt_Node<_Val> >::other	node_alloc;
		public:
		typedef _Alloc														value_alloc;

		typedef _Compare				value_compare;
		typedef _Val					value_type;
		typedef _Val*					value_pointer;
		typedef const _Val*				const_value_pointer;
		typedef _Val&					value_reference;
		typedef const _Val&				const_value_reference;
		typedef Rbt_Node<_Val>*			node_pointer;
		typedef const Rbt_Node<_Val>*	const_node_pointer;

		typedef	size_t					size_type;
		typedef	ptrdiff_t				difference_type;

		// iterators

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>>
		private:
		
		node_pointer	_root;
		size_type		_size;
		node_alloc		_node_alloc;
		value_alloc		_value_alloc;
		value_compare	_compare;
		// _end_node && _begin_node

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		// ----------------------- CONSTRUCTORS --------------------
		Rbt_Tree(): _root(NULL), _size(0) {}

		

		
		
		
	};
	

}	// namespace ft

#endif