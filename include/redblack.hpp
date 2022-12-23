/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redblack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:17:48 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/23 13:29:39 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACK_HPP
# define REDBLACK_HPP

// https://gcc.gnu.org/onlinedocs/gcc-4.6.2/libstdc++/api/a01067_source.html

# include "./iterators/redblack_iterator.hpp"
# include "./utils/rbt_node.hpp"
# include "./utils/pair.hpp"
# include <stddef.h>
# include <memory>

namespace ft
{

	// 1. Every node is either red or black.
	// 2. The root is black.
	// 3. Every leaf (NIL) is black.
	// 4. If a node is red, then both its children are black.
	// 5. For each node, all simple paths from the node to descendant leaves contain the
	// same number of black nodes.

	template<typename _Key, typename _Val, typename _Compare=std::less<_Key>, typename _Alloc = std::allocator<_Val> >
	class Redblack_Tree
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		typedef typename	_Alloc::template rebind<Rbt_Node<_Val> >::other	node_alloc;
		public:
		typedef _Alloc														value_alloc;

		typedef _Key					key_type;
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

		// just an idea
		typedef ft::pair<const key_type, value_type>	data_type;

		// iterators

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>>
		protected:
		
		node_pointer	_root;
		// node_pointer	_begin;
		// node_pointer	_end;

		size_type		_size;
		node_alloc		_node_alloc;
		value_alloc		_value_alloc;
		value_compare	_compare;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>
		private:

		public:

		// ----------------------- CONSTRUCTOR --------------------
		Redblack_Tree(): _root(NULL), _size(0), _compare(_Compare()), _value_alloc(_Alloc())
		{
			_node_alloc = std::allocator<Rbt_Node<value_type> >();
		}

		// ----------------------- GETTERS ------------------------
		
		node_alloc	get_node_alloc()	{ return _node_alloc; }

		value_alloc	get_value_alloc()	{ return _value_alloc; }
		
		size_type	size()				{ return _size; }

		node_pointer	root()			{ return _root; }
		
		// ----------------------- MODIFY -------------------------

	};
	

}	// namespace ft

#endif


