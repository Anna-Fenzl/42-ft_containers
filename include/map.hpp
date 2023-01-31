/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:42:06 by afenzl            #+#    #+#             */
/*   Updated: 2023/01/31 17:09:48 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "redblack.hpp"
# include "utils/pair.hpp"
# include "./iterators/reverse_iterator.hpp"

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
		typedef const value_type&									const_reverence;
		typedef typename Allocator::pointer							pointer;
		typedef typename Allocator::const_pointer					const_pointer;

		typedef ft::Rbt_Iterator<value_type>						iterator;
		typedef ft::Const_Rbt_Iterator<const value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		private:
		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER CLASS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		// binary_function is a base class for creating function objects with two arguments.
		// template< class Arg1, class Arg2, class Result > struct binary_function;
		class map_compare : public std::binary_function< value_type, value_type, bool >
		{
			private:
			friend class map;
			
			protected:
			key_compare	_compare;
			
			public:
			// constructor for the internal comparator of map
			map_compare(): _compare()											{}
			map_compare( key_compare k ): _compare(k)							{}
			map_compare( const map_compare& other ) : _compare(other._compare)	{}
			~map_compare()														{}

			map_compare&  operator=( const map_compare& other )
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
		
		typedef	Redblack_Tree<value_type, map_compare>					redblack_tree;

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER VARIABLES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		private:
		allocator_type	_value_alloc;
		map_compare		_compare;
		redblack_tree	_tree;
		
		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< CONSTRUCTORS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:

		// default constructor: Constructs an empty container.
		map(const allocator_type& alloc = allocator_type(), const key_compare& key_comp = key_compare())
		: _value_alloc(alloc), _compare(key_comp) {}

		// Constructs the container with the contents of the range [first, last).
		// If multiple elements in the range have keys that compare equivalent,
		// it is unspecified which element is inserted
		template< class InputIt >
		map( InputIt first, InputIt last, const key_compare& key_comp = key_compare(),
			const Allocator& alloc = allocator_type() ): _value_alloc(alloc), _compare(key_comp)
		{
			
		}

		// Copy constructor: Constructs the container with the copy of the contents of other.
		map( const map& other )
		{
			*this = other;
		}

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ASSIGNMENT OPERATOR  >>>>>>>>>>>>>>>>>>>>>>>

		map& operator=( const map& other)
		{
			if (this == &other)
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

		mapped_type&	at(const key_type& k)
		{
			const_iterator	it = _tree.find(k);

			if ( it == _tree.end() )
				throw std::out_of_range("ft::map");
			
			return *it.second;
		}

		const mapped_type& at(const key_type& k) const
		{
			const_iterator	it = _tree.find(k);

			if ( it == _tree.end() )
				throw std::out_of_range("ft::map");
			
			return *it.second;
		}

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MODIFIERS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		// single element (1)	
		pair<iterator, bool> insert (const value_type& val)
		{
			return _tree.insert(val);
		}

		// // with hint (2)	
		// iterator insert (iterator position, const value_type& val);

		// // range (3)	
		// template <class InputIterator>  void insert (InputIterator first, InputIterator last);
		// };
	};
}

#endif