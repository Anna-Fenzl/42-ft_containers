/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:12:00 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/11 20:04:58 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "iterator.hpp"
# include <iostream>
# include <memory>

namespace ft
{
	template< typename T >
	class VectorIterator
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
		private:
			typedef typename ft::Iterator<ft::random_access_iterator_tag , T> Iterator;
		public:
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::difference_type		difference_type; //maybe also size_t
			typedef	typename Iterator::iterator_category	iterator_category;
		
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

		VectorIterator	operator++(int)		{VectorIterator cpy(*this); ++(*this); return cpy; }

		VectorIterator	&operator--()		{ _ptr--; return *this; }

		VectorIterator	operator--(int)		{VectorIterator cpy = *this; --(*this); return cpy; }

		reference		operator[](int idx)	{ return *(_ptr + idx); }

		reference		operator->()		{ return _ptr; }

		reference		operator*()			{return *_ptr; }

		bool	operator==(const VectorIterator& other) const { return _ptr == other._ptr; }

		bool	operator!=(const VectorIterator& other) const { return _ptr != other._ptr; }

	};

	// need to do the other overloads
	// it needs to be comatible with STL containers















	
	
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		
			typedef size_t		size_type;
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

		
		// <<<<<<<<<<<<<<<<<<<<<< MEMBER VARIABLES >>>>>>>>>>>>>>>>>>>>>>
		private:

			allocator_type		_alloc;
			pointer				_data;
			size_type			_size;
			size_type			_capacity;

			void	grow(void)
			{
				_capacity = (_capacity) ? _capacity * 2 : 1;
		
				pointer new_data = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&new_data[i], &_data[i]);

				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_data[i]);
				_alloc.deallocate(_data, _capacity);

				_data = new_data;
			}

			//  template< typename InputIterator >
			// void	_assign_range( InputIterator first, InputIterator last, input_iterator_tag  )
			// {
			// 	clear();
			// 	for ( ; first != last; first++)
			// 		push_back(*first);
			// }

			// template< typename InputIterator >
			// void	_assign_range( InputIterator first, InputIterator last, random_access_iterator_tag )
			// {
			// 	clear();
			// 	reserve(ft::distance(first, last));
			// 	for (_size = 0; first != last; _size++, first++)
			// 		_alloc.construct(_ptr + _size, *first);
			// }

		public:
		// EXPLICIT:
		// used to mark constructors to not implicitly convert types in C++.
		// It is optional for constructors that take exactly one argument
		// and work on constructors(with a single argument)
		// since those are the only constructors that can be used in typecasting -> (BEING ABLE TO CAST TO STD CONTAINER???)
		// ====> converting constructor

		// <<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>>>
		
		// ----------------------- CONSTRUCTORS --------------------

		// PUT THE ALLOCATION IN AN TRY CATCH!!

		// empty container constructor  XXXX should i allocate here or put data as a null_ptr
		explicit vector(const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(0), _capacity(0)
		{
			_data = _alloc.allocate(_capacity);
		}
		
		// fill constructor
		// LATER USE ASSIGN
		explicit vector(size_type n, value_type val ,const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(n), _capacity(n)
		{
			_data = _alloc.allocate(_capacity);
			
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], val);
		}

		// range constructor
		// template <class InputIterator>
		// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		// 	: _alloc(alloc), _size(0), _capacity(0)
		// {
		// 	assign(first, last);
		// }

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
			clear();
			if (_data != NULL)
				_alloc.deallocate(_data, _capacity);
		}
		
		// ----------------------- ITERATORS -------------------

		iterator		begin() 		{ return iterator(_data); };
		
		const_iterator	begin() const	{ return iterator(_data); };

		iterator		end()			{ return iterator(_data + _size); };
		
		const_iterator	end() const		{ return iterator(_data + _size); };

		// ----------------------- CAPACITY --------------------
		// size -> Return size
		size_type	size() const		{ return _size; }

		// max_size -> 	Return maximum size
		size_type	max_size() const	{ return _alloc.max_size(); }

		// // reserve -> Increase the capacity of the vector   STRONG EXECPTION GARANTIE

		// capacity -> Return size of allocated storage capacity
		size_type	capacity() const	{ return _capacity; };

		// empty -> Test wheter vector is empty
		bool		empty() const		{ return _size == 0; }

		// ----------------------- ELEMENT ACCESS --------------------
		
		// [] -> DOESN'T THROW AN EXCEPTION !!! -> UNDEFINED behavior, doesn't segfault
		reference			operator[](size_type n)			{ return _data[n]; }
		const_reference		operator[](size_type n) const	{ return _data[n]; }

		// as -> Checks whether n is in the bounds and throws an exception and accesses element
		reference 			at(size_type n)			{ if (n >= _size) throw std::out_of_range("ft::vector"); return _data[n]; }
		const_reference		at(size_type n) const	{ if (n >= _size) throw std::out_of_range("ft::vector"); return _data[n]; }
		
		// front -> Accesses first element, if empty its UNDEFINED
		reference			front()			{ return _data[0]; }
		const_reference		front() const	{ return _data[0]; }

		// back -> Accesses last element, if empty its UNDEFINED
		reference			back()			{ return _data[_size - 1]; }
		const_reference		back() const	{ return _data[_size - 1]; }

		// ----------------------- MODIFIERS --------------------
		// assign -> assignsn ew contents to the vector (1) Range
		// template <class InputIterator>
		// void assign (InputIterator first, InputIterator last)
		// {
		// 	_assign_range(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
		// }
		
		// void assign (size_type n, const value_type& val)
		// {
		// }
		
		// clear -> clears the elements
		void	clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_data[i]);
			_size = 0;
		}


		// pop_back -> Removes the last element in the vector
		void	pop_back()
		{
			_alloc.destroy(&_data[_size-1]);
			_size -= 1;
		}

		// swap -> Exchanges the contents of the container with those of the other
		void	swap( vector& other )
		{
			allocator_type tmp_alloc = _alloc;
			_alloc = other._alloc;
			other._alloc = tmp_alloc;
			
			pointer tmp_data = _data;
			_data = other._data;
			other._data = tmp_data;
			
			if (_size != other.size())
			{
				_size ^= other._size;
				other._size ^= _size;
				_size ^= other._size;
			}

			if (_capacity != other.capacity())
			{
				_capacity ^= other._capacity;
				other._capacity ^= _capacity;
				_capacity ^= other._capacity;
			}
		}
		
		// ----------------------- ALLOCATOR --------------------
	
		// get_allocator -> Returns a copy of the allocator object associated with the vector.
		allocator_type get_allocator() const { return allocator_type(_alloc); }
	};


	// NEED TO CHANGE IT TO FT::EQUAL
	// template <class T, class Alloc>
	// bool	operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	// {
	// 	return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()));
	// }

	// template <class T, class Alloc>
	// bool	operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	// {
	// 	return !(lhs == rhs);
	// }
	
	// template <class T, class Alloc>
	// bool	operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	// {
		
	// }

	// template <class T, class Alloc>
	// bool	operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// template <class T, class Alloc>
	// bool	operator>	(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	
	// template <class T, class Alloc> 
	// bool	operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

}	//namespace ft

#endif