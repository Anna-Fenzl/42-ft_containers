/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:12:00 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/14 17:49:10 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "vector_iterator.hpp"
# include "type_traits.hpp"
# include <iostream>
# include <stdexcept>
# include <limits>
# include <memory>

namespace ft
{


// □ constructores					✓
	//  "Substitution Failure Is Not An Error" -> SFINAE
// □ iteratores						
// □ capacity 						✓
// □ element access					✓
// □ modifiers
// □ allocator						✓
// □ non_member function overloads
// □ std::enable if					✓
// □ std::is_integral				✓


	//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< VECTOR >>>>>>>>>>>>>>>>>>>>>>>>>>>
	
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

		// empty container constructor  XXXX should i allocate here or put data as a null_ptr??
		explicit vector(const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(0), _capacity(0)
		{
			_data = _alloc.allocate(_capacity);
		}
		
		// fill constructor
		explicit vector(size_type n, value_type val ,const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(0), _capacity(n)
		{
			_data = _alloc.allocate(_capacity);
			assign(n, val);
		}

		// range constructor
		template <class InputIterator>
		explicit vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
			: _alloc(alloc), _size(0), _capacity(0)
		{
			_data = _alloc.allocate(ft::distance(first, last));
			assign(first, last);
		}

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
		// In most implementations, alloc.max_size() returns std::numeric_limits<size_type>::max() / sizeof(value_type)
		size_type	max_size() const
		{
			size_type max_size = _alloc.max_size();
			if (max_size < std::numeric_limits< size_type >::max() / sizeof(value_type))
			{
				return (max_size);
			}
			return (std::numeric_limits< size_type >::max() / sizeof(value_type));
		}

		// resize -> Resizes the container
		void resize (size_type n, value_type val = value_type())
		{
			if (n > _capacity)
				reserve(n);
			if (n > _size)
			{
				while (n != _size)
					push_back(val);
			}
			else if (n < _size)
			{
				while (n != _size)
					pop_back();
			}
			_size = n;
		}

		// capacity -> Return size of allocated storage capacity
		size_type	capacity() const	{ return _capacity; };

		// empty -> Test wheter vector is empty
		bool		empty() const		{ return _size == 0; }

		// reserve -> Increase the capacity of the vector
		void		reserve (size_type n)
		{
			if (n > max_size())
				throw std::length_error("ft::vector: 'n' exceeds maximum supported size");
			if (n > _capacity)
			{
				pointer new_data = _alloc.allocate(n);
				size_type size = _size;

				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(&new_data[i], _data[i]);
				}
				clear();
				_alloc.deallocate(_data, _capacity);
				
				_size = size;
				_data = new_data;
				_capacity = n;
			}
		}

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
		
		// assign -> Assigns new contents to the vector,
		// replacing its current contents, and modifying its size accordingly.
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
		{
			clear();
			_assign_range(first, last , typename ft::iterator_traits<InputIterator>::iterator_category());
		}

		void assign (size_type n, const value_type& val)
		{
			clear();
			_size = n;
			if (_size > _capacity)
				reserve(_size);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], val);
		}

		// push_back -> Adds a new element at the end of the vector, after its current last element
		void push_back (const value_type& val)
		{
			if (_size < _capacity)
				_alloc.construct(&_data[_size], val);
			else
			{
				reserve(_capacity * 2);
				_alloc.construct(&_data[_size], val);
			}
			_size += 1;
		}

		// pop_back -> Removes the last element in the vector
		void	pop_back()
		{
			_alloc.destroy(&_data[_size-1]);
			_size -= 1;
		}

		// insert

		// erase -> Removes elements from the vector

		// iterator erase (iterator first, iterator last)

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

		// clear -> clears the elements
		void	clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_data[i]);
			_size = 0;
		}

		// ----------------------- ALLOCATOR --------------------
	
		// get_allocator -> Returns a copy of the allocator object associated with the vector.
		allocator_type get_allocator() const { return allocator_type(_alloc); }


		// <<<<<<<<<<<<<<<<<<<<< PRIVATE METHODS >>>>>>>>>>>>>>>>
		// _assign_range -> assignes values via iterators
		 template< typename InputIterator >
		void	_assign_range( InputIterator first, InputIterator last, input_iterator_tag  )
		{
			for ( ; first != last; first++)
				push_back(*first);
		}

		template< typename InputIterator >
		void	_assign_range( InputIterator first, InputIterator last, random_access_iterator_tag )
		{
			reserve(ft::distance(first, last));
			for (_size = 0; first != last; _size++, first++)
				_alloc.construct(_data + _size, *first);
		}

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













	// void	grow(void)
	// {
	// 	_capacity = (_capacity) ? _capacity * 2 : 1;

	// 	pointer new_data = _alloc.allocate(_capacity);
	// 	for (size_type i = 0; i < _size; i++)
	// 		_alloc.construct(&new_data[i], _data[i]);

	// 	for (size_type i = 0; i < _size; i++)
	// 		_alloc.destroy(&_data[i]);
	// 	_alloc.deallocate(_data, _capacity);

	// 	_data = new_data;
	// }

}	//namespace ft

#endif