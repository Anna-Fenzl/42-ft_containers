/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:08:53 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/15 13:21:58 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "utils/redblack.hpp"
# include "utils/pair.hpp"
# include "./iterators/reverse_iterator.hpp"
# include "./utils/compare.hpp"

namespace ft
{
	//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< SET >>>>>>>>>>>>>>>>>>>>>>>>>>>

	template<
	class Key,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<Key>
	> class set
	{
		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		typedef	Key															key_type;
		typedef	Key															value_type;
		typedef	Compare														key_compare;
		typedef Compare														value_compare;
		typedef Allocator													allocator_type;
	
		typedef typename Allocator::reference								reference;
		typedef typename Allocator::const_reference							const_reference;
		typedef typename Allocator::pointer									pointer;
		typedef typename Allocator::const_pointer							const_pointer;

		typedef ft::rbt_iterator<value_type>								iterator;
		typedef ft::const_rbt_iterator<value_type>							const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
	
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
		typedef size_t														size_type;
		
		private:
		typedef	redblack_tree<value_type, value_compare, allocator_type>	rb_tree;

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER VARIABLES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		private:
		value_compare	_compare;
		allocator_type	_value_alloc;
		rb_tree			_tree;

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< CONSTRUCTORS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		// Default constructor
		explicit set( const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _compare(comp), _value_alloc(alloc) {}

		// Range constructor
		template< class InputIt >
		set( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ):_compare(comp), _value_alloc(alloc) 
		{
			insert(first, last);
		}
		
		set( const set& other )
		{
			*this = other;
		}

		~set() {}

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ASSIGNMENT OPERATOR  >>>>>>>>>>>>>>>>>>>>>>>
		set& operator=( const set& other)
			{
				if (this != &other)
				{
					_value_alloc = other._value_alloc;
					_compare = other._compare;
					_tree = other._tree;
				}
				return *this;
			}

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ITERATORS  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		iterator		begin()					{ return _tree.begin(); }

		const_iterator	begin()	const			{ return _tree.begin(); }

		iterator		end()					{ return _tree.end(); }

		const_iterator	end()	const			{ return _tree.end(); }

		reverse_iterator rbegin()				{ return reverse_iterator(end()); }

		const_reverse_iterator rbegin() const	{ return const_reverse_iterator(end()); }

		reverse_iterator rend()					{ return reverse_iterator(begin()); }
	
		const_reverse_iterator rend() const		{ return const_reverse_iterator(begin()); };

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< CAPACITY >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		bool		empty() const				{ return _tree.empty(); }

		size_type	size() const				{ return _tree.size(); }

		size_type	max_size() const			{ return _tree.max_size(); }

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MODIFIERS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		// Erases all elements from the container.
		void		clear()						{ _tree.clear(); }

		// single element (1)
		ft::pair<iterator, bool> insert( const value_type& value )
		{
			return _tree.insert(value);
		}

		// hint (2)
		iterator insert( iterator pos, const value_type& value )
		{
			(void)pos;
			return _tree.insert(value).first;
		}

		// range(3)
		template< class InputIt >
		void insert( InputIt first, InputIt last )
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
				std::cerr << e.what() << "ft::set";
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
				std::cerr << e.what() << "ft::set";
			}
			
		}

		// Removes the element (if one exists) with the key equivalent to key (3)
		// throws any exceptions thrown by the Compare object.
		size_type erase( const key_type& key )
		{
			return _tree.erase(find(key));
		}

		// Exchanges the contents of the container with those of other
		void swap( set& other )
		{
			ft::swap(_compare, other._compare);
			ft::swap(_value_alloc, other._value_alloc);
			_tree.swap(other._tree);
		}

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOKUP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

			// Number of elements with key that compares equivalent to key or x, which is either 1 or 0.
		size_type count(const Key& key ) const
		{
			size_type ret = 0;
			if (find(key) != end())
				ret = 1;
			return ret;
		}

		// Finds an element with key equivalent to key.
		iterator find( const key_type& key )											{ return _tree.find(key); }
		
		const_iterator find( const key_type& key ) const								{ return _tree.find(key); }

		// Returns a range containing all elements with the given key in the container.
		ft::pair<iterator,iterator> equal_range( const Key& key )						{ return _tree.equal_range(key); }
		
		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const		{ return _tree.equal_range(key); }

		// Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key
		iterator lower_bound( const Key& key )											{ return _tree.lower_bound(key); }

		const_iterator lower_bound( const Key& key ) const								{ return _tree.lower_bound(key); }

		// Returns an iterator pointing to the first element that is greater than key.
		iterator upper_bound( const Key& key )											{ return _tree.upper_bound(key); }
		
		const_iterator upper_bound( const Key& key ) const								{ return _tree.upper_bound(key); }

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< GETTER >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		allocator_type get_allocator() const											{ return _value_alloc; }

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< OBESERVERS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		key_compare key_comp() const													{ return _compare; }

		value_compare value_comp() const										{ return _compare; }

		//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< DEBUG >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		// void	print() const
		// {
		// 	_tree.print_tree();
		// }
		
	};

	//  <<<<<<<<<<<<<<<<<<<<<<<<<<<<< NON_MEMBER FUNCTIONS >>>>>>>>>>>>>>>>>>>>>>>>>>>

		template< class Key, class Compare, class Alloc >
	bool operator==( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class Key, class Compare, class Alloc >
	bool operator!=( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class Compare, class Alloc >
	bool operator<( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class Compare, class Alloc >
	bool operator<=( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}

	template< class Key, class Compare, class Alloc >
	bool operator>( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template< class Key, class Compare, class Alloc >
	bool operator>=( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}

	template< class Key, class Compare, class Alloc >
	void swap( ft::set<Key, Compare, Alloc>& lhs,
			ft::set<Key, Compare, Alloc>& rhs )
	{
		lhs.swap(rhs);
	}


	
} // namespace ft


#endif