/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:01:50 by afenzl            #+#    #+#             */
/*   Updated: 2023/01/31 14:50:21 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACK_ITERATOR_HPP
# define REDBLACK_ITERATOR_HPP

# include "iterator.hpp"
# include "../utils/rbt_node.hpp"

namespace ft
{
	template < typename NodePointer >
	NodePointer red_black_tree_min(NodePointer node)
	{
		while (node->_left != node->_nil)
			node = node->_left;
		return node;
	}

	template < typename NodePointer >
	NodePointer red_black_tree_max(NodePointer node)
	{
		while (node->_right != node->_nil)
			node = node->_right;
		return node->_parent;
	}

	template < typename NodePointer >
	NodePointer red_black_tree_next(NodePointer node)
	{
		if (node->_right != node->_nil)
			return red_black_tree_min(node->_right);
		while (node->_parent != node->_nil && node == node->_parent->_right)
			node = node->_parent;
		return node->_parent;
	}

	template < typename NodePointer >
	NodePointer red_black_tree_prev(NodePointer node)
	{
		if (node->_left != node->_nil)
			return red_black_tree_max(node->_left);
		while (node->_parent != node->_nil && node == node->_parent->_left)
			node = node->_parent;
		return node->_parent;
	}

	template< typename T>
	struct Const_Rbt_Iterator;

	template< typename T>
	struct Rbt_Iterator
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		typedef T											value_type;
		typedef T&											reference;
		typedef T*											pointer;

		typedef Rbt_Iterator<T>								iterator;
		typedef Const_Rbt_Iterator<T>						const_iterator;
		
		typedef bidirectional_iterator_tag					iterator_category;
		typedef std::ptrdiff_t								difference_type;

		typedef typename RbtNode<T>::node_pointer			node_pointer;
		typedef typename RbtNode<T>::const_node_pointer		const_node_pointer;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>
		private:
		node_pointer	_ptr;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>

		public:
		// ----------------------- CONSTRUCTORS --------------------
		Rbt_Iterator(): _ptr(NULL) {}
		
		Rbt_Iterator( node_pointer ptr ): _ptr(ptr) {}

		Rbt_Iterator( const iterator& rhs): _ptr(rhs.base()) {}

		~Rbt_Iterator( void ) {}

		// ----------------------- ACCESSORS -----------------------

		node_pointer base() const	{ return _ptr; }

		// ------------------- OPERATOR OVERLOADS ------------------
		
		reference	operator*() const	{ return *_ptr->_value; }

		pointer		operator->() const	{ return _ptr->_value; }

		iterator	&operator++() 
		{
			_ptr = red_black_tree_next< node_pointer >(_ptr);
			return (*this);
		}

		iterator	&operator--()
		{
			_ptr = red_black_tree_prev< node_pointer >(_ptr);
			return (*this);
		}
		
		iterator	operator++(int)
		{
			iterator cpy(_ptr);
			++(*this);
			return (cpy);
		}

		iterator	operator--(int)
		{
			iterator cpy(_ptr);
			--(*this);
			return (cpy);
		}

		bool	operator==( const iterator& other) const
		{
			return (_ptr == other.base());
		}
		
		bool	operator==( const const_iterator& other) const
		{
			return (_ptr == other.base());
		}

		bool	operator!=( const iterator& other) const
		{
			return (!(*this == other));
		}
		
		bool	operator!=( const const_iterator& other) const
		{
			return (!(*this == other));
		}

	};






template< typename T>
	struct Const_Rbt_Iterator
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		typedef const T										value_type;
		typedef const T&											reference;
		typedef const T*											pointer;

		typedef const Rbt_Iterator<T>						iterator;
		typedef const Const_Rbt_Iterator<T>					const_iterator;
		
		typedef ft::bidirectional_iterator_tag				iterator_category;
		typedef std::ptrdiff_t								difference_type;

		typedef typename RbtNode<T>::node_pointer			node_pointer;
		typedef typename RbtNode<T>::const_node_pointer		const_node_pointer;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>
		private:
		node_pointer	_ptr;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>

		public:
		// ----------------------- CONSTRUCTORS --------------------
		Const_Rbt_Iterator(): _ptr(NULL) {}
		
		Const_Rbt_Iterator( node_pointer ptr ): _ptr(ptr) {}

		Const_Rbt_Iterator( const iterator& rhs): _ptr(rhs.base()) {}

		~Const_Rbt_Iterator( void ) {}

		// ----------------------- ACCESSORS -----------------------

		node_pointer base() const	{ return _ptr; }

		// ------------------- OPERATOR OVERLOADS ------------------
		
		reference	operator*() const	{ return *_ptr->_value; }

		pointer		operator->() const	{ return _ptr->value; }

		const_iterator	&operator++() 
		{
			_ptr = red_black_tree_next< node_pointer >(_ptr);
			return (*this);
		}

		const_iterator	&operator--()
		{
			_ptr = red_black_tree_prev< node_pointer >(_ptr);
			return (*this);
		}
		
		const_iterator	operator++(int)
		{
			const_iterator cpy(_ptr);
			++(*this);
			return (cpy);
		}

		const_iterator	operator--(int)
		{
			const_iterator cpy(_ptr);
			--(*this);
			return (cpy);
		}

		bool	operator==( const iterator& other) const
		{
			return (_ptr == other.base());
		}
		
		bool	operator==( const const_iterator& other) const
		{
			return (_ptr == other.base());
		}

		bool	operator!=( const iterator& other) const
		{
			return (!(*this == other));
		}

		bool	operator!=( const const_iterator& other) const
		{
			return (!(*this == other));
		}
	};

}	// namespace ft

#endif