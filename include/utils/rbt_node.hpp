/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:19:47 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/23 12:56:28 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_NODE_HPP
# define RBT_NODE_HPP

# include <stdexcept>

namespace ft
{
	enum	rbt_colour {RED, BLACK};
	enum	Side {LEFT, RIGHT};

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

		// ----------------------- METHODS --------------------------

		value_type	&get_value() const	{ return this->_value; }

		rbt_colour	get_colour() const { return this->_colour; }

		node_type	*get_child( int	side ) const
		{
			if (side == LEFT)
				return this->_left;
			else if (side == RIGHT)
				return this->_right;
			throw std::invalid_argument("only takes value LEFT(0) or RIGHT(1)!");
		}

	};

}	// namespace ft

#endif