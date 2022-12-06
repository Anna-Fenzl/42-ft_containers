/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:12:00 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/06 17:59:39 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>

namespace ft
{
	template< typename T >
	class VectorIterator
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
			typedef T		value_type;
			typedef T*		pointer;
			typedef T&		reference;
			// typedef						difference_type
			// typedef						iterator_category
		
		// <<<<<<<<<<<<<<<<<<<<<< MEMBER VARIABLES >>>>>>>>>>>>>>>>>>>>>>
		private:
			pointer		_ptr;

		// <<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		
		// ----------------------- CONSTRUCTORS -------------------------
		VectorIterator(pointer ptr) :_ptr(ptr) {}

		VectorIterator(const VectorIterator &src) :_ptr(src._ptr) {}

		// ----------------------- OPERATOR OVERLOAD --------------------
		VectorIterator	&operator++() 		{ _ptr++; return *this; }

		// DOESNT COMPILE reference to stack memory associated with local variable 'cpy' returned
		VectorIterator	&operator++(int)	{ VectorIterator cpy = *this; ++(*this); return cpy; }

		VectorIterator	&operator--()		{ _ptr--; return *this; }

		// DOESNT COMPILE reference to stack memory associated with local variable 'cpy' returned
		VectorIterator	&operator--(int)	{ VectorIterator cpy = *this; --(*this); return cpy; }

		// 1
		reference		operator[](int idx)	{ return *(_ptr + idx); }

		reference		operator->()		{ return _ptr; }

		reference		operator*()			{return *_ptr; }

		// 1
		bool	operator==(const VectorIterator& other) const { return _ptr == other._ptr; }

		// 1
		bool	operator!=(const VectorIterator& other) const { return _ptr != other._ptr; }

	};
	
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		
			typedef T			value_type;
			typedef Alloc		allocator_type;
			typedef T&			reference;
			typedef const T&	const_reference;
			typedef T*			pointer;
			typedef const T*	const_pointer;
			
			typedef VectorIterator<value_type>			iterator;
			typedef VectorIterator<value_type const>	const_iterator;
			// typedef ReverseIterator<iterator>			reverse_iterator;
			// typedef ReverseIterator<const_iterator>		const_reverse_iterator;

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

		// <<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>>>
		
		// ----------------------- CONSTRUCTORS --------------------

		// empty container constructor  XXXX should i allocate here or put data as a null_ptr
		explicit vector(const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(0), _capacity(0)
		{
			_data = _alloc.allocate(_capacity);
		}
		
		// fill constructor
		explicit vector(size_type n, value_type val ,const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(n), _capacity(n)
		{
			_data = _alloc.allocate(_capacity);
			
			for (size_type i = 0; i < _size; i++)
				 _alloc.construct(&_data[i], val);
		}

		// range constructor
		
		// copy constructor -> creates a container that keeps and uses a copy of src's allocator
		explicit vector( const vector &src)
			: _alloc(src.get_allocator()), _size(src.size()), _capacity(src.capacity())
		{
			_data = _alloc.allocate(_capacity);

			for (size_type i = 0; i < _size; i++)
				 _alloc.construct(&_data[i], src[i]);
		}

		// deconstructor
		~vector()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_data[i]);
			
			_alloc.deallocate(_data, _capacity);
		}
		
		// ----------------------- ITERATORS -------------------

		iterator		begin() 		{ return iterator(_data); };
		
		const_iterator	begin() const	{ return iterator(_data); };

		// return the begin pof the rev iterator
		iterator		end()			{ return iterator(_data + _size); };
		
		const_iterator	end() const		{ return iterator(_data + _size); };

		// ----------------------- CAPACITY --------------------
		// size -> Return size
		size_type	size() const		{ return _size; }

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
		reference			operator[](size_type n)			{ return _data[n]; }
		const_reference		operator[](size_type n) const	{ return _data[n]; }

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
		// get_allocator -> Returns a copy of the allocator object associated with the vector.
		allocator_type get_allocator() const { return allocator_type(_alloc); }
		
	};
}	//namespace ft

#endif