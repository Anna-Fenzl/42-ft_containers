/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rbt_Node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:19:47 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/19 13:43:24 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_NODE_HPP
# define RBT_NODE_HPP

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

}	// namespace ft

#endif