/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:19:47 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/07 13:59:58 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_NODE_HPP
# define RBT_NODE_HPP
# include <stdexcept>
# include <iostream>

# include <unistd.h>

namespace ft
{
	enum	rbt_colour {RED, BLACK};
	enum	Side {LEFT, RIGHT};

	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< RBT_NODE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	template <typename T, typename Alloc = std::allocator<T> >
	class	RbtNode
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		typedef T								value_type;
		typedef T*								value_pointer;
		typedef RbtNode<value_type>				node_type;
		typedef	RbtNode<value_type>*			node_pointer;
		typedef const RbtNode<value_type>*		const_node_pointer;
		typedef Alloc							value_alloc;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>>
		value_pointer	_value;
		rbt_colour		_colour;
		node_pointer	_parent;
		node_pointer	_left;
		node_pointer	_right;
		node_pointer	_nil;
		value_alloc		_value_alloc;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>

		// ----------------------- CONSTRUCTORS --------------------------

		// default constructor -> everything set to NULL and BLACK
		// RbtNode(): _colour(BLACK), _parent(NULL), _left(NULL), _right(NULL), _value_alloc(std::allocator<value_type> () )
		// {
		// 	_value = _value_alloc.allocate(1);
		// }

		// constructor takes value -> colour set to red
		RbtNode(const value_type& value, const node_pointer nil): _colour(RED), _parent(nil), _left(nil), _right(nil), _nil(nil),  _value_alloc(std::allocator<value_type> () )
		{
			_value = _value_alloc.allocate(1);
			_value_alloc.construct(_value, value);
		}

		// constructor takes value & parent -> colour set to red
		RbtNode(const value_type& value, node_pointer parent, const node_pointer nil ): _colour(RED), _parent(parent), _left(nil), _right(nil), _nil(nil), _value_alloc(std::allocator<value_type> () )
		{
			_value = _value_alloc.allocate(1);
			_value_alloc.construct(_value, value);
		}

		// constructor takes value & parent & colour
		RbtNode(const value_type&  value, node_pointer parent, const node_pointer nil, rbt_colour colour): _colour(colour), _parent(parent), _left(nil), _right(nil), _nil(nil), _value_alloc(std::allocator<value_type> () )
		{
			_value = _value_alloc.allocate(1);
			_value_alloc.construct(_value, value);
		}

		RbtNode(node_type& src): _value(NULL)
		{
			*this = src;
		}

		RbtNode(const node_type& src): _value(NULL)
		{
			*this = src;
		}

		~RbtNode()
		{
			_value_alloc.destroy(_value);
			_value_alloc.deallocate(_value, 1);
		}
	
		// ----------------------- =OPERATOR --------------------------

		node_type	&operator=(node_type &src)
		{
			if (this != &src)			//<--- ADDED!
			{
				if (_value)
					_value_alloc.deallocate(_value, 1);
				_value_alloc = src._value_alloc;
				_value = _value_alloc.allocate(1);
				_value_alloc.construct(_value, src.get_value());
				_colour = src._colour;
				_parent = src._parent;
				_left = src._left;
				_right = src._right;
				_nil = src._nil;
			}
			return *this;
		}

		node_type	&operator=(const node_type &src)
		{
			if (this != &src)
			{
				if (_value)
					_value_alloc.deallocate(_value, 1);
				_value_alloc = src._value_alloc;
				_value = _value_alloc.allocate(1);
				_value_alloc.construct(_value, src.get_value());
				_colour = src._colour;
				_parent = src._parent;
				_left = src._left;
				_right = src._right;
			}
			return *this;
		}

		// ----------------------- METHODS --------------------------

		value_type	get_value() const	{ return *this->_value; }

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

		void		set_colour(rbt_colour colour) { _colour = colour; }
		
		void		switch_colour() { _colour = (_colour == RED) ? BLACK : RED; }

	};

	template <typename V>
	std::ostream&	operator <<(std::ostream& output, const RbtNode<V> &node)
	{
		std::cout << ((node.get_colour() == RED) ? "\033[0;31m" : "");
		output << "\n:---------:\n";
		output << "|VALUE: " << node.get_value() << "";
		output << "\n:---------:\n";
		std::cout << ((node.get_colour() == RED) ? "\033[0m" : "");
		return (output);
	}

}	// namespace ft

#endif