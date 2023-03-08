/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:12:00 by afenzl            #+#    #+#             */
/*   Updated: 2023/03/08 12:05:33 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "./iterators/vector_iterator.hpp"
# include "./iterators/reverse_iterator.hpp"
# include "./utils/utility.hpp"
# include <iostream>
# include <stdexcept>
# include <limits>
# include <memory>

namespace ft
{

//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< VECTOR >>>>>>>>>>>>>>>>>>>>>>>>>>>
	template<
	class T,
	class Alloc = std::allocator< T >
>class vector
{
		// <<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
	public:
	
		typedef size_t									size_type;
		typedef typename Alloc::difference_type 		difference_type;

		typedef T										value_type;
		typedef Alloc									allocator_type;

		typedef T&										reference;
		typedef const T&								const_reference;

		typedef T*										pointer;
		typedef const T*								const_pointer;
		
		typedef ft::vector_iterator<value_type>			iterator;
		typedef ft::vector_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	
	// <<<<<<<<<<<<<<<<<<<<<< MEMBER VARIABLES >>>>>>>>>>>>>>>>>>>>>>
	private:
		size_type		_size;
		size_type		_capacity;
		pointer			_data;
		allocator_type	_alloc;

	public:
	// ----------------------- CONSTRUCTORS --------------------

	// default constructor
	vector() : _size(0), _capacity(0), _data(NULL), _alloc() {}

	// constructor with the given allocator
	explicit vector(const allocator_type& alloc): _size(0), _capacity(0), _data(NULL), _alloc(alloc) {}

	// fill constructor
	explicit vector( size_type count, const T& value = T(),
						const allocator_type& alloc = allocator_type() )
						: _size(0), _capacity(0), _data(NULL), _alloc(alloc)
	{
		assign(count, value);
	}

	// range constructor
	template < class InputIt >
	vector( InputIt first, InputIt last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
			: _size(0), _capacity(0), _data(NULL), _alloc(alloc)
	{
		assign(first, last);
	}

	// copy constructor
	vector( const vector& other ) : _size(0), _capacity(0), _data(NULL)
	{
		*this = other;
	}

	// destructor
	~vector( void )
	{
		clear();
		if (_data != NULL)
			_alloc.deallocate(_data, _capacity);
		_data = NULL;
		_capacity = 0;
	}

	// ----------------------- ASSIGNMENT OPERATOR --------------------
	vector &operator=( const vector& other )
	{
		if (this != &other)
		{
			_alloc = other.get_allocator();
			assign(other.begin(), other.end());
		}
		return (*this);
	}

	// ----------------------- ITERATORS -------------------

		iterator				begin() 		{ return iterator(_data); };
		
		const_iterator			begin() const	{ return const_iterator(_data); };

		reverse_iterator		rbegin()		{ return reverse_iterator(end()); };

		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end()); };

		iterator				end()			{ return iterator(_data + _size); };
		
		const_iterator			end() const		{ return const_iterator(_data + _size); };

		reverse_iterator		rend()			{ return reverse_iterator(begin()); };
	
		const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin()); };
		
	
	// ----------------------- CAPACITY --------------------

	// size -> Return size
	size_type	size() const		{ return _size; }

	// capacity -> Return size of allocated storage capacity
	size_type	capacity() const	{ return _capacity; };

	// max_size -> 	Return maximum size
	size_type	max_size() const
	{
		if (_alloc.max_size() < std::numeric_limits< size_type >::max() / 2)
			return (_alloc.max_size());
		return (std::numeric_limits< size_type >::max() / 2);
	}

	// empty -> true if size is 0
	bool empty( void ) const		{ return (_size == 0); }

	// resize -> Resizes the container
	void resize (size_type n, value_type val = value_type())
	{
		if (n > _capacity * 2)
			reserve(n);
		else if (n > _capacity)
			reserve(_capacity * 2);
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

	void reserve( size_type newCapacity )
	{
		if (newCapacity > max_size() && (_capacity == 0 || _capacity == max_size()))
			throw std::length_error("vector");
		else if (newCapacity > max_size())
			newCapacity = max_size();
		else if (newCapacity < _capacity)
			return ;
		_realloc(newCapacity);
	}

	// ----------------------- ELEMENT ACCESS --------------------
	
	// [] -> DOESN'T THROW AN EXCEPTION !!! -> UNDEFINED behavior, doesn't segfault
	reference			operator[](size_type n)			{ return _data[n]; }
	const_reference		operator[](size_type n) const	{ return _data[n]; }

	// as -> Checks whether n is in the bounds and throws an exception and accesses element
	reference 			at(size_type n)			{ if (n >= _size) throw std::out_of_range("ft::vector"); return _data[n]; }
	const_reference		at(size_type n) const	{ if (n >= _size) throw std::out_of_range("ft::vector"); return _data[n]; }
	
	// front -> Accesses first element, if empty its UNDEFINED
	reference			front()							{ return _data[0]; }
	const_reference		front() const					{ return _data[0]; }

	// back -> Accesses last element, if empty its UNDEFINED
	reference			back()							{ return _data[_size - 1]; }
	const_reference		back() const					{ return _data[_size - 1]; }

	// ----------------------- MODIFIERS --------------------

	void assign( size_type count, const T& value )
	{
		clear();
		reserve(count);
		for (size_type i = 0; i < count; i++)
		{
			_alloc.construct(_data + i, value);
		}
		_size = count;
	}

	template< class InputIt >
	void assign( InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
	{
		_assign_range(first, last, typename ft::iterator_traits<InputIt>::iterator_category());
	}

	void clear( void )
	{
		for (size_type i = 0; i < _size; i++)
		{
			_alloc.destroy(_data + i);
		}
		_size = 0;
	}

	iterator insert( iterator pos, const T& value )
	{
		return (insert(pos, 1, value));
	}

	iterator insert( iterator pos, size_type count, const T& value )
	{
		if (count == 0)
			return (pos);

		size_type   position = ft::distance(begin(), pos);
		size_type   newSize = _size + count;
		pointer     newPTR = _alloc.allocate(newSize);

		for (size_type i = 0; i < position; i++)
		{
			_alloc.construct(newPTR + i, _data[i]);
		}
		for (size_type i = position; i < position + count; i++)
		{
			_alloc.construct(newPTR + i, value);
		}
		for (size_type i = position; i < _size; i++)
		{
			_alloc.construct(newPTR + count + i, _data[i]);
		}
		clear();
		if (_data != NULL)
			_alloc.deallocate(_data, _capacity);
		_data = newPTR;
		_size = newSize;
		_capacity = newSize;
		return (iterator(_data + position));
	}

	template< class InputIt >
	iterator insert( iterator pos, InputIt first, InputIt last,
						typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true )
	{
		return (_insert_range(pos, first, last, typename ft::iterator_traits<InputIt>::iterator_category()));
	}

	// erase -> Removes the element at pos.
	iterator erase( iterator pos )
	{
		for (iterator it = pos; it < end() - 1; it++)
		{
			*it = *(it + 1);
		}
		_alloc.destroy(_data + _size - 1);
		if (pos != end())
			--_size;
		return (pos);
	}

	// erase -> Removes the elements in the range [first, last).
	iterator erase( iterator first, iterator last )
	{
		difference_type n = ft::distance(first, last);
		for (iterator it = first; last < end(); it++, last++)
		{
			*it = *last;
		}
		for (difference_type d = 1; n >= d; d++)
		{
			_alloc.destroy(end().base() - d);
		}
		_size -= n;
		return (first);
	}

	// push_back -> Appends the given element value to the end of the container.
	void push_back( const T& value )
	{
		reserve(1);
		if (_size == _capacity)
			reserve(_capacity * 2);
		_alloc.construct(_data + _size, value);
		++_size;
	}

	//  pop_back -> Removes the last element of the container. 
	void pop_back( void )
	{
		_alloc.destroy(&(_data[_size - 1]));
		--_size;
	}

	// swap -> Exchanges the contents of the container with those of other.
	void swap( vector& other )
	{
		ft::swap(_size, other._size);
		ft::swap(_capacity, other._capacity);
		ft::swap(_data, other._data);
		ft::swap(_alloc, other._alloc);
	}

	// ----------------------- ALLOCATOR --------------------

	//  Returns the allocator associated with the container.
	allocator_type get_allocator() const
	{
		return (_alloc);
	}

	// <<<<<<<<<<<<<<<<<<<<< PRIVATE METHODS >>>>>>>>>>>>>>>>
	private:
	void _realloc( size_type newCapacity )
	{
		pointer newPTR = _alloc.allocate(newCapacity);
		for (size_type i = newCapacity; i < _size; i++)
		{
			_alloc.destroy(_data + i);
		}
		if (newCapacity < _size)
			_size = newCapacity;
		for (size_type i = 0; i < _size; i++)
		{
			_alloc.construct(newPTR + i, _data[i]);
			_alloc.destroy(_data + i);
		}
		if (_data != NULL)
			_alloc.deallocate(_data, _capacity);
		_data = newPTR;
		_capacity = newCapacity;
	}

	template< typename InputIterator >
	void    _assign_range( InputIterator first, InputIterator last, input_iterator_tag  )
	{
		clear();
		for ( ; first != last; first++)
			push_back(*first);
	}

	template< typename InputIterator >
	void    _assign_range( InputIterator first, InputIterator last, random_access_iterator_tag )
	{
		clear();
		reserve(ft::distance(first, last));
		for (_size = 0; first != last; _size++, first++)
			_alloc.construct(_data + _size, *first);
	}

	template< typename InputIterator >
	iterator    _insert_range( iterator pos, InputIterator first, InputIterator last, random_access_iterator_tag )
	{
		size_type   count = ft::distance(first, last);
		if (count == 0)
			return (pos);

		size_type   position = ft::distance(begin(), pos);
		size_type   newSize = _size + count;
		pointer     newPTR = _alloc.allocate(newSize);

		for (size_type i = 0; i < position; i++)
		{
			_alloc.construct(newPTR + i, _data[i]);
		}
		for (size_type i = position; i < position + count; i++, first++)
		{
			_alloc.construct(newPTR + i, *first);
		}
		for (size_type i = position; i < _size; i++)
		{
			_alloc.construct(newPTR + count + i, _data[i]);
		}

		clear();
		if (_data != NULL)
			_alloc.deallocate(_data, _capacity);
		_data = newPTR;
		_size = newSize;
		_capacity = newSize;
		return (iterator(_data + position));
	}

	template< typename InputIterator >
	iterator    _insert_range( iterator pos, InputIterator first, InputIterator last, input_iterator_tag )
	{
		size_type   position = ft::distance(begin(), pos);
		for ( ; first != last; ++first, ++pos)
			pos = insert(pos, *first);
		return (iterator(_data + position));
	}
}; // class Vector


	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs )
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs )
	{
		return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs > rhs);
	}

	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs,
				const ft::vector<T,Alloc>& rhs )
	{
		return rhs < lhs;
	}

	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs,
			ft::vector<T,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}

}	//namespace ft

#endif