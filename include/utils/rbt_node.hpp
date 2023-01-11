/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:19:47 by afenzl            #+#    #+#             */
/*   Updated: 2023/01/11 17:03:51 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_NODE_HPP
# define RBT_NODE_HPP
# include <stdexcept>
# include <iostream>

namespace ft
{
	enum	rbt_colour {RED, BLACK};
	enum	Side {LEFT, RIGHT};

	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< RBT_NODE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	template <typename T, typename _Alloc = std::allocator<T> >
	class	Rbt_Node
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		typedef T								value_type;
		typedef T*								value_pointer;
		typedef Rbt_Node<value_type>			node_type;
		typedef	Rbt_Node<value_type>*			node_pointer;
		typedef const Rbt_Node<value_type>*		const_node_pointer;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>>
		value_pointer	_value;
		rbt_colour		_colour;
		node_pointer	_parent;
		node_pointer	_left;
		node_pointer	_right;
		_Alloc			_value_alloc;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>

		// ----------------------- CONSTRUCTORS --------------------------
		Rbt_Node()
		: _colour(RED), _parent(NULL), _left(NULL), _right(NULL)
		{
			_value = _value_alloc.allocate(1);
		}

		Rbt_Node(value_type val, node_pointer par)
		: _colour(RED), _left(NULL), _right(NULL)
		{
			_parent = par;
			_value = _value_alloc.allocate(1);
			_value_alloc.construct(_value, val);
		}

		Rbt_Node(node_type &other)
		{
			_value = _value_alloc.allocate(1);
			*this = other;
		}

		// NOT SURE IF I NEED TO DESTROY THE VALUE
		~Rbt_Node()
		{
			_value_alloc.destroy(_value);
			if ( _value != NULL)
				_value_alloc.deallocate(_value, 1);
		}

		// ----------------------- =OPERATOR --------------------------

		node_type	&operator=(node_type &src)
		{
			// if (*this != src)
			// {
				*_value = *(src._value);
				_colour = src._colour;
				_parent = src._parent;
				_left = src._left;
				_right = src._right;
			// }
			return *this;
		}

		// ----------------------- METHODS --------------------------

		value_pointer	get_value() const	{ return this->_value; }

		rbt_colour		get_colour() const { return this->_colour; }

		node_type		*get_child( int	side ) const
		{
			if (side == LEFT)
				return this->_left;
			else if (side == RIGHT)
				return this->_right;
			throw std::invalid_argument("only takes value LEFT(0) or RIGHT(1)!");
		}

		void		set_parent(node_pointer parent) { _parent = parent; }

	};

	template <typename T>
	std::ostream&	operator <<(std::ostream& output, const Rbt_Node<T> &node)
	{
		output << "\n<<<<<<>>>>>>>>\n";
		output << "COLOR: " << (node.get_colour() ? " BLACK\n" : " RED\n");
		output << "VALUE " << *node.get_value() << std::endl;
		output << "<<<<<<>>>>>>>>" << std::endl;
		return (output);
	}

}	// namespace ft

#endif