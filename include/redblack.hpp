/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redblack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:17:48 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/18 17:34:07 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACK_HPP
# define REDBLACK_HPP

// https://gcc.gnu.org/onlinedocs/gcc-4.6.2/libstdc++/api/a01067_source.html

# include <stddef.h>
# include <memory>

namespace ft
{
	enum	rbt_colour { RED, BLACK};

	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< RBT_NODE >>>>>>>>>>>>>>>>>>>>>>>>>>>
	template <typename T>
	class	Rbt_Node
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		typedef T						value_type;
		typedef Rbt_Node<value_type>	node_type;
		typedef	Rbt_Node*				node_pointer;
		typedef const Rbt_Node*			const_node_pointer;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>>
		value_type		_value;
		rbt_colour		_colour;
		node_pointer	_parent;
		node_pointer	_left;
		node_pointer	_right;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>

		// ----------------------- CONSTRUCTORS --------------------
		Rbt_Node()
		: _value(value_type()), _colour(RED), _parent(NULL), _left(NULL), _right(NULL) {}

		Rbt_Node(value_type val, node_pointer par)
		: _value(val), _colour(RED), _parent(par), _left(NULL), _right(NULL) {}

		Rbt_Node(const node_type &other) { *this = other; }

		~Rbt_Node() {}

		// ----------------------- =OPERATOR --------------------------

		node_type	&operator=(const node_type &src)
		{
			if (*this != src)
			{
				_value = src._value;
				_colour = src._colour;
				_parent = src._parent;
				_left = src._left;
				_right = src._right;
			}
			return *this;
		}
	};


	template<typename _Val, typename _Compare, typename _Alloc = std::allocator<_Val> >
	class _Rb_tree
	{
		
	};
	

}	// namespace ft

#endif