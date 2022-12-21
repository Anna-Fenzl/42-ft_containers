/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redblack_iterator.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:01:50 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/19 13:43:46 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACK_ITERATOR_HPP
# define REDBLACK_ITERATOR_HPP

# include "iterator.hpp"
# include "../utils/rbt_node.hpp"

namespace ft
{
	template< typename T>
	struct Rbt_Iterator
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		typedef T									value_type;
		typedef T&									reference;
		typedef T*									pointer;

		typedef ft::bidirectional_iterator_tag		iterator_category;
		typedef ptrdiff_t							difference_type;

		typedef Rbt_Iterator<T>						iterator;
		typedef const Rbt_Iterator<T>				const_iterator;
		typedef typename Rbt_Node<T>::node_pointer	node_pointer;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>>
		private:
		node_pointer	_ptr;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>

		public:
		// ----------------------- CONSTRUCTORS --------------------
		Rbt_Iterator( const node_pointer &empty = NULL): _ptr(empty) {}

		Rbt_Iterator( const iterator& rhs): _ptr(rhs.base()) {}

		~Rbt_Iterator( void ) {}

		// ----------------------- ACCESSORS -----------------------

		node_pointer base() const	{ return _ptr; }

		// ------------------- OPERATOR OVERLOADS ------------------
		
		reference	operator*() const	{ return *_ptr; }

		pointer		operator->() const	{ return _ptr; }

		// first implement RB_TREE
		
	};

	// const_version
	
}	// namespace ft

#endif