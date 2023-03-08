/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:19:47 by afenzl            #+#    #+#             */
/*   Updated: 2023/03/07 12:20:53 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
	class	rbt_node
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		typedef T								value_type;
		typedef T*								value_pointer;
		typedef rbt_node<value_type>			node_type;
		typedef	rbt_node<value_type>*			node_pointer;
		typedef const rbt_node<value_type>*		const_node_pointer;
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
		rbt_node(const value_type& value = value_type()): _colour(BLACK), _parent(NULL), _left(NULL), _right(NULL), _value_alloc(std::allocator<value_type> () )
		{
			_value = _value_alloc.allocate(1);
			_value_alloc.construct(_value, value);
		}

		// constructor takes value & parent -> colour set to red
		rbt_node(const value_type& value, node_pointer parent, const node_pointer nil ): _colour(RED), _parent(parent), _left(nil), _right(nil), _nil(nil), _value_alloc(std::allocator<value_type> () )
		{
			_value = _value_alloc.allocate(1);
			_value_alloc.construct(_value, value);
		}

		// constructor takes value & parent & colour
		rbt_node(const value_type& value, node_pointer parent, const node_pointer nil, rbt_colour colour): _colour(colour), _parent(parent), _left(nil), _right(nil), _nil(nil), _value_alloc(std::allocator<value_type> () )
		{
			_value = _value_alloc.allocate(1);
			_value_alloc.construct(_value, value);
		}

		rbt_node(node_type& src): _value(NULL)
		{
			*this = src;
		}

		rbt_node(const node_type& src): _value(NULL)
		{
			*this = src;
		}

		~rbt_node()
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

		value_type		get_value() const	{ return *this->_value; }

		rbt_colour		get_colour() const { return this->_colour; }

		void			set_parent(node_pointer parent) { _parent = parent; }

		void			set_nil(node_pointer nil) { _nil = nil; }

		void			set_colour(rbt_colour colour) { _colour = colour; }

	};

	template <typename V>
	std::ostream&	operator <<(std::ostream& output, const rbt_node<V> &node)
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
