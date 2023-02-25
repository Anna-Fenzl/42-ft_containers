/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:42:06 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/25 16:08:24 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "utils/redblack.hpp"
# include "utils/pair.hpp"
# include "./iterators/reverse_iterator.hpp"
# include "./utils/compare.hpp"

namespace ft
{
	//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MAP >>>>>>>>>>>>>>>>>>>>>>>>>>>

	template<
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T> >
	> class map

	{
		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		typedef	Key													key_type;
		typedef	T													mapped_type;
		typedef	ft::pair<const Key, T>								value_type;
	
		typedef size_t												size_type;
		typedef ptrdiff_t											difference_type;

		typedef Compare												key_compare;
		typedef Allocator											allocator_type;
	
		typedef value_type&											reference;
		typedef const value_type&									const_reference;
		typedef typename Allocator::pointer							pointer;
		typedef typename Allocator::const_pointer					const_pointer;

		typedef ft::rbt_iterator<value_type>						iterator;
		typedef ft::const_rbt_iterator<value_type>					const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER CLASS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		// binary_function is a base class for creating function objects with two arguments.
		// template< class Arg1, class Arg2, class Result > struct binary_function;
		class value_compare : public std::binary_function< value_type, value_type, bool >
		{
			private:
			friend class map;
			
			protected:
			key_compare	_compare;
			
			public:
			// constructor for the internal comparator of map
			value_compare(): _compare()											{}
			value_compare( key_compare k ): _compare(k)							{}
			value_compare( const value_compare& other ) : _compare(other._compare)	{}
			~value_compare()														{}

			value_compare&  operator=( const value_compare& other )
			{
				if (this != &other)
					_compare = other._compare;
				return (*this);
			}

			// compares the two keys (.first) to each other, by calling the stored comparator
			bool	operator() (const value_type& lhs, const value_type& rhs) const
			{
				return(_compare(lhs.first, rhs.first));
			}
		};
		
		typedef	redblack_tree<value_type, value_compare, allocator_type>		rb_tree;

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER VARIABLES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		protected:
		allocator_type	_value_alloc;
		value_compare	_compare;
		rb_tree			_tree;
		
		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< CONSTRUCTORS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:

		// default constructor: Constructs an empty container.
		explicit map(const key_compare& key_comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _value_alloc(alloc), _compare(key_comp) {}

		// Constructs the container with the contents of the range [first, last).
		// If multiple elements in the range have keys that compare equivalent,
		// it is unspecified which element is inserted
		template< class InputIt >
		map( InputIt first, InputIt last, const key_compare& key_comp = key_compare(),
			const allocator_type& alloc = allocator_type() ): _value_alloc(alloc), _compare(key_comp)
		{
			insert(first, last);
		}

		// Copy constructor: Constructs the container with the copy of the contents of other.
		map( const map& other )
		{
			*this = other;
		}

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ASSIGNMENT OPERATOR  >>>>>>>>>>>>>>>>>>>>>>>

		map& operator=( const map& other)
		{
			if (this != &other)
			{
				_value_alloc = other._value_alloc;
				_compare = other._compare;
				_tree = other._tree;
			}
			return *this;
		}
		

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ITERATORS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		iterator begin()						{ return _tree.begin(); }
		
		const_iterator begin() const			{ return _tree.begin(); }

		iterator end()							{ return _tree.end(); }
		
		const_iterator end() const				{ return _tree.end(); }

		reverse_iterator rbegin()				{ return reverse_iterator(end()); }

		const_reverse_iterator rbegin() const	{ return const_reverse_iterator(end()); }

		reverse_iterator rend()					{ return reverse_iterator(begin()); }
	
		const_reverse_iterator rend() const		{ return const_reverse_iterator(begin()); };

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< CAPACITY >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		bool		empty() const				{ return _tree.empty(); }

		size_type	size() const				{ return _tree.size(); }

		size_type	max_size() const			{ return _tree.max_size(); }
		

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ELEMENT_ACCESS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		// Returns a reference to the mapped value of the element with key equivalent to key.
		// If no such element exists, an exception of type std::out_of_range is thrown.
		mapped_type&	at(const key_type& k)
		{
			iterator	it = _tree.find(ft::make_pair(k, mapped_type()));

			if ( it == _tree.end() )
				throw std::out_of_range("ft::map::at key not found");
			
			return (*it).second;
		}

		const mapped_type& at(const key_type& k) const
		{
			const_iterator	it = _tree.find(ft::make_pair(k, mapped_type()));

			if ( it == _tree.end() )
				throw std::out_of_range("ft::map::at key not found");

			return (*it).second;
		}

		// Returns a reference to the value that is mapped to a key equivalent to key, performing an insertion if such key does not already exist.
		mapped_type& operator[]( const key_type& key )
		{
			return (insert(ft::make_pair(key, mapped_type())).first)->second;
		}

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MODIFIERS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		// Erases all elements from the container.
		void clear()	{ _tree.clear(); }

		// single element (1)
		pair<iterator, bool> insert (const value_type& val)
		{
			return _tree.insert(val);
		}

		// hint (2)
		// just a hint and does not force the new element to be inserted at that position within the map container
		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			return _tree.insert(val).first;
		}

		// range (3)	
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				_tree.insert(*first);
		}

		// single element (1)
		void erase( iterator pos )
		{
			try
			{
				_tree.erase(pos);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << "ft::map";
			}
			
		}

		// range (2)
		void erase( iterator first, iterator last )
		{
			try
			{
				iterator it;
				while ( first != last)
				{
					it = first;
					++it;
					_tree.erase(first);
					first = it;
				}
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << "ft::map";
			}
			
		}

		// Removes the element (if one exists) with the key equivalent to key (3)
		// throws any exceptions thrown by the Compare object.
		size_type erase( const key_type& key )
		{
			return _tree.erase(find(key));
		}

		// Exchanges the contents of the container with those of other
		void swap( map& other )
		{
			ft::swap(_compare, other._compare);
			ft::swap(_value_alloc, other._value_alloc);
			_tree.swap(other._tree);
		}

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOKUP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		// Number of elements with key that compares equivalent to key or x, which is either 1 or 0.
		size_type count(const Key& key ) const
		{
			size_type ret = 0;
			if (find(key) != end())
				ret = 1;
			return ret;
		}

		// Finds an element with key equivalent to key.
		iterator find( const key_type& key )											{ return _tree.find(ft::make_pair(key, mapped_type())); }
		
		const_iterator find( const key_type& key ) const								{ return _tree.find(ft::make_pair(key, mapped_type())); }

		// Returns a range containing all elements with the given key in the container.
		ft::pair<iterator,iterator> equal_range( const Key& key )						{ return _tree.equal_range(ft::make_pair(key, mapped_type())); }
		
		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const		{ return _tree.equal_range(ft::make_pair(key, mapped_type())); }

		// Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key
		iterator lower_bound( const Key& key )											{ return _tree.lower_bound(ft::make_pair(key, mapped_type())); }

		const_iterator lower_bound( const Key& key ) const								{ return _tree.lower_bound(ft::make_pair(key, mapped_type())); }

		// Returns an iterator pointing to the first element that is greater than key.
		iterator upper_bound( const Key& key )											{ return _tree.upper_bound(ft::make_pair(key, mapped_type())); }
		
		const_iterator upper_bound( const Key& key ) const								{ return _tree.upper_bound(ft::make_pair(key, mapped_type())); }

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< OBSERVERS>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		// Returns the function object that compares the keys, which is a copy of this container's constructor argument comp.
		key_compare key_comp() const													{ return key_compare(); }

		// Returns a function object that compares objects of type ft::map::value_type (key-value pairs) by using key_comp to compare the first components of the pairs.
		value_compare value_comp() const												{ return _compare; }

		allocator_type get_allocator() const											{ return _value_alloc; }
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DEBUG >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		// void	print() const
		// {
		// 	_tree.print_tree();
		// }
	};

	//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< NON_MEMBER FUNCTIONS >>>>>>>>>>>>>>>>>>>>>>>>>>>

		template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}

	//  Specializes the ft::swap algorithm for ft::map. Swaps the contents of lhs and rhs
	template< class Key, class T, class Compare, class Alloc >
	void    swap( ft::map< Key, T, Compare, Alloc >& lhs,
				ft::map< Key, T, Compare, Alloc >& rhs )
	{
		lhs.swap(rhs);
	}
}

#endif
