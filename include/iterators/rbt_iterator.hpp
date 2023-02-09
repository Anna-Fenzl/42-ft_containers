/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:01:50 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/09 17:04:53 by afenzl           ###   ########.fr       */
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
		while (node->_right != node->_nil && node->_right != node)
			node = node->_right;
		return node;
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
		if (node == node->_nil)
			return node->_parent;
		while (node->_parent != node->_nil && node == node->_parent->_left)
			node = node->_parent;
		return node->_parent;
	}

	template< typename T>
	struct const_rbt_iterator;

	template< typename T>
	struct rbt_iterator
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		typedef T											value_type;
		typedef T&											reference;
		typedef T*											pointer;

		typedef rbt_iterator<T>								iterator;
		typedef const_rbt_iterator<T>						const_iterator;
		
		typedef bidirectional_iterator_tag					iterator_category;
		typedef std::ptrdiff_t								difference_type;

		typedef typename rbt_node<T>::node_pointer			node_pointer;
		typedef typename rbt_node<T>::const_node_pointer		const_node_pointer;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>
		private:
		node_pointer	_ptr;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>

		public:
		// ----------------------- CONSTRUCTORS --------------------
		rbt_iterator(): _ptr(NULL) {}
		
		rbt_iterator( node_pointer ptr ): _ptr(ptr) {}

		rbt_iterator( const iterator& rhs): _ptr(rhs.base()) {}

		~rbt_iterator( void ) {}

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
	struct const_rbt_iterator
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		typedef const T										value_type;
		typedef const T&									reference;
		typedef const T*									pointer;

		typedef const rbt_iterator<T>						iterator;
		typedef const const_rbt_iterator<T>					const_iterator;
		
		typedef ft::bidirectional_iterator_tag				iterator_category;
		typedef std::ptrdiff_t								difference_type;

		typedef typename rbt_node<T>::node_pointer			node_pointer;
		typedef typename rbt_node<T>::const_node_pointer		const_node_pointer;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>
		private:
		node_pointer _ptr;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>

		public:
		// ----------------------- CONSTRUCTORS --------------------
		const_rbt_iterator(): _ptr(NULL) {}
		
		const_rbt_iterator( node_pointer const ptr ): _ptr(ptr) {}

		const_rbt_iterator( const iterator& rhs): _ptr(rhs.base()) {}

		~const_rbt_iterator( void ) {}

		// ------------------- OPERATOR OVERLOADS ------------------
		
		reference	operator*() const	{ return *_ptr->_value; }

		pointer		operator->() const	{ return _ptr->_value; }

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
			return (_ptr == other._ptr);
		}
		
		bool	operator==( const const_iterator& other) const
		{
			return (_ptr == other._ptr);
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