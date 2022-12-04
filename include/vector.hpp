/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:12:00 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/04 18:18:40 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
		// <<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
		
			typedef T			value_type;
			typedef Alloc		allocator_type;
			typedef T&			reference;
			typedef const T&	const_reference;
			typedef T*			pointer;
			
			// iterator					a random access iterator to value_type			convertible to const_iterator
			// const_iterator			a random access iterator to const value_type	
			// reverse_iterator			reverse_iterator<iterator>	
			// const_reverse_iterator	reverse_iterator<const_iterator>	
			// difference_type			a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t

			typedef size_t		size_type;
		
		// <<<<<<<<<<<<<<<<<<<<<< MEMBER VARIABLES >>>>>>>>>>>>>>>>>>>>>>
		private:

			allocator_type		_alloc;
			pointer				_data;
			size_type			_size;
			size_type			_capacity;

		public:
		// EXPLICIT:
		// used to mark constructors to not implicitly convert types in C++.
		// It is optional for constructors that take exactly one argument
		// and work on constructors(with a single argument)
		// since those are the only constructors that can be used in typecasting

		// <<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>
		
		// ----------------------- CONSTRUCTORS --------------------

		// empty container constructor
		explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0)
		{
			_data = _alloc.allocate(_capacity);
		}
		
		// fill constructor
		explicit vector(size_type n, value_type val ,const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(n), _capacity(n)
		{
			_data = _alloc.allocate(_capacity);
			
			for (size_type i = 0; i < _size; i++)
				 _alloc.construct(&_data[i], val);
		}

		// range constructor
		
		// copy constructor

		// deconstructor
		
		// ----------------------- ITERATORS --------------------

		// ----------------------- CAPACITY --------------------
		// size -> Return size
		size_type	size() const	{ return _size; }

		// max_size -> 	Return maximum size
		size_type	max_size() const	{ return _alloc.max_size(); }

		// resize -> Change size
		// void		resize(size_type n, value_type val = value_type()) {}

		// capacity -> Return size of allocated storage capacity
		size_type	capacity() const	{ return _capacity; };

		// empty -> Test wheter vector is empty
		bool		empty() const		{ return _size == 0; }

		// reserve -> 	Request a change in capacity
		// void		reserve(size_type n) {}

		// ----------------------- ELEMENT ACCESS --------------------
		
		// [] -> DOESN'T THROW AN EXCEPTION !!! -> UNDEFINED behavior, doesn't segfault
		reference			&operator[](size_type n)		{ return _data[n]; }
		const_reference		&operator[](size_type n) const	{ return _data[n]; }

		// as -> Checks whether n is in the bounds and throws an exception and accesses element
		reference 			at(size_type n)			{ if (n >= _size) { throw std::out_of_range("ft::vector"); } return _data[n]; }
		const_reference		at(size_type n) const	{ if (n >= _size) { throw std::out_of_range("ft::vector"); } return _data[n]; }
		
		// front -> Accesses first element, if empty its UNDEFINED
		reference			front()			{ return _data[0]; }
		const_reference		front() const	{ return _data[0]; }

		// back -> Accesses last element, if empty its UNDEFINED
		reference			back()			{ return _data[_size - 1]; }
		const_reference		back() const	{ return _data[_size - 1]; }

		// ----------------------- MODIFIERS --------------------
		
		// ----------------------- ALLOCATOR --------------------
		
		
	};
}

#endif