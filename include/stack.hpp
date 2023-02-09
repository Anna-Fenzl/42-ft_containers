/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:23:21 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/09 14:57:02 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	// <<<<<<<<<<<<<<<<<<<<<<<<< STACK >>>>>>>>>>>>>>>>>>>>>>>>>>>>

	template< class T, class Container = ft::vector<T> >
	class stack
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		// <<<<<<<<<<<<<<<<<<<<<< MEMBER VARIABLES >>>>>>>>>>>>>>>>>>>>>>
		protected:
		container_type	c;

		// <<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		// ----------------------- CONSTRUCTORS --------------------

		// Copy-constructs the underlying container c with the contents of cont.
		// This is also the default constructor
		explicit stack( const Container& cont = Container() ) : c(cont) {}

		~stack() {}

		// ----------------------- OPERATOR --------------------
		
		// Replaces the contents with a copy of the contents of other. Effectively calls c = other.c;
		stack& operator=( const stack& other ) { c = other.c; return *this; }

		// ----------------------- ELEMENT ACCESS --------------

		// Returns reference to the top element in the stack. This is the most recently pushed element
		reference top()				{ return c[c.size() - 1]; }
		
		const_reference top() const	{ return c[c.size() - 1]; }
		
		// ----------------------- CAPACITY --------------------

		// true if the underlying container is empty, false otherwise
		bool empty() const			{ return c.empty(); }

		// Returns the number of elements in the underlying container, that is, c.size().
		size_type size() const		{ return c.size(); }

		// ----------------------- MODIFIERS --------------------
		
		// Pushes the given element value to the top of the stack.
		void push( const value_type& value )	{ c.push_back(value); }

		// Removes the top element from the stack. Effectively calls c.pop_back()
		void pop()								{ c.pop_back(); }

		// ----------------------- FRIENDS --------------------
		
		template< class T1, class Con >
		friend bool operator==( const ft::stack<T1, Con>& lhs, const ft::stack<T1, Con>& rhs );

		template< class T1, class Con >
		friend bool operator<( const ft::stack<T1, Con>& lhs, const ft::stack<T1, Con>& rhs );

	};

	// Compares the contents of the underlying containers of two container adaptors.
	// The comparison is done by applying the corresponding operator to the underlying containers.

	template< class T, class Container >
	bool operator==( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs )
	{
		return lhs.c == rhs.c;
	}

	template< class T, class Container >
	bool operator!=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class T, class Container >
	bool operator<( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs )
	{
		return lhs.c < rhs.c;
	}

	template< class T, class Container >
	bool operator<=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs )
	{
		return !(lhs > rhs);
	}

	template< class T, class Container >
	bool operator>( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs )
	{
		return rhs < lhs;
	}

	template< class T, class Container >
	bool operator>=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs )
	{
		return !(lhs < rhs);
	}
	
}	// namespace ft


#endif