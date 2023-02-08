/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:12:00 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/08 11:41:08 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "./iterators/vector_iterator.hpp"
# include "./iterators/reverse_iterator.hpp"
# include "./utils/type_traits.hpp"
# include "./utils/pair.hpp"
# include <iostream>
# include <stdexcept>
# include <limits>
# include <memory>

namespace ft
{


// □ constructores					✓
	//  "Substitution Failure Is Not An Error" -> SFINAE
// □ iteratores						✓
// □ capacity 						✓
// □ element access					✓
// □ modifiers						✓
// □ allocator						✓
// □ std::enable if					✓
// □ std::is_integral				✓
// □ std::pair						✓
// □ std::make_pair					✓
// □ std::equal						✓
// □ std::lexicographical_compare	✓
// □ non_member function overloads	✓

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
			
			typedef ft::VectorIterator<value_type>			iterator;
			typedef ft::VectorIterator<value_type const>	const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		
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

		iterator				begin() 		{ return iterator(_data); };
		
		const_iterator			begin() const	{ return const_iterator(_data); };

		reverse_iterator		rbegin()		{ return reverse_iterator(end()); };

		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end()); };

		iterator				end()			{ return iterator(_data + _size); };
		
		const_iterator			end() const		{ return const_iterator(_data + _size); };

		reverse_iterator		rend()			{ return reverse_iterator(begin()); };
	
		const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin()); };

		// ----------------------- OPERATOR --------------------

		vector& operator=( const vector& other )
		{
			clear();
			_alloc.deallocate(_data, _capacity);

			_alloc = other.get_allocator();
			_capacity = other.capacity();
			_size = other.size();
			_data = _alloc.allocate(_capacity);
			
			for (size_type i = 0; i < _size; i++)
				 _alloc.construct(&_data[i], other[i]);
			
			return *this;
		}
		
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
			if (n > _capacity)
				reserve(n);
			clear();
			_size = n;
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], val);
		}

		// push_back -> Adds a new element at the end of the vector, after its current last element
		void push_back (const value_type& val)
		{
			if (_size >= _capacity)
				reserve((_capacity) ? _capacity * 2 : 1);
			_alloc.construct(&_data[_size++], val);
		}

		// pop_back -> Removes the last element in the vector
		void	pop_back()
		{
			_alloc.destroy(&_data[--_size]);
		}

		// insert -> Inserts value before pos
		iterator insert( iterator pos, const T& value )
		{
			return insert(pos, 1, value);
		}

		// insert -> Inserts count copies of the value before pos
		iterator insert( iterator pos, size_type count, const T& value )
		{
			if (count < 1)
				return pos;
			
			size_type	position = ft::distance(begin(), pos);
			size_type	new_size = _size + count;
			pointer		new_data = _alloc.allocate(new_size);

			size_type	i = 0;
			for (; i != position; ++i)
				_alloc.construct(&new_data[i], _data[i]);

			for (; i != count + position; ++i)
				_alloc.construct(&new_data[i], value);

			for (; i != new_size; ++i)
				_alloc.construct(&new_data[i], _data[i - count]);

			clear();
			_alloc.deallocate(_data, _capacity);
		
			if (_capacity < new_size)
				_capacity = new_size;
			_size = new_size;
			_data = new_data;

			return iterator(_data + position);
		}

		// insert -> inserts elements from range [first, last) before pos
		template< class InputIterator >
		iterator insert( iterator pos, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
		{
			size_type	count = ft::distance(first, last);
			if (count < 1)
				return pos;
			
			size_type	position = ft::distance(begin(), pos);
			size_type	new_size = _size + count;
			pointer		new_data = _alloc.allocate(new_size);

			size_type	i = 0;
			for (; i != position; ++i)
				_alloc.construct(&new_data[i], _data[i]);

			for (; i != count + position; ++i, ++first)
				_alloc.construct(&new_data[i], *first);

			for (; i != new_size; ++i)
				_alloc.construct(&new_data[i], _data[i - count]);

			clear();
			_alloc.deallocate(_data, _capacity);
		
			if (_capacity < new_size)
				_capacity = new_size;
			_size = new_size;
			_data = new_data;

			return iterator(_data + position);
		}

		// erase -> Removes elements from the vector (single element)
		iterator erase( iterator pos )
		{
			_alloc.destroy(pos.base());
			
			_size--;
			for (size_type	count = ft::distance(begin(), pos); count != _size; ++count)
				_data[count] = _data[count + 1];
			return pos;
		}

		// erase -> Removes elements from the vector (range)
		iterator erase (iterator first, iterator last)
		{
			for(iterator it = first; it != last; ++it)
				_alloc.destroy(it.base());
			
			size_type	amount = ft::distance(first, last);
			_size -= amount;
			for (size_type	count = ft::distance(begin(), first); count != _size; ++count)
				_data[count] = _data[count + amount];
			return first;
		}

		// swap -> Exchanges the contents of the container with those of the other
		void	swap( vector& other )
		{
			ft::swap(_alloc, other._alloc);
			ft::swap(_data, other._data);
			ft::swap(_size, other._size);
			ft::swap(_capacity, other._capacity);
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

	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs,
					const ft::vector<T,Alloc>& rhs )
	{
		return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()));
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
		ft::vector<T> tmp(lhs);
		lhs = rhs;
		rhs = tmp;
	}

}	//namespace ft

#endif