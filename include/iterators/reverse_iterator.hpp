/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:48:51 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/08 14:29:19 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
	template < class Iterator >
	class reverse_iterator
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
		typedef typename ft::iterator_traits<Iterator>	Iter_traits;
		public:
		typedef Iterator									iterator_type;
		typedef	typename Iter_traits::iterator_category		iterator_category;
		typedef typename Iter_traits::value_type			value_type;
		typedef typename Iter_traits::difference_type		difference_type;
		typedef typename Iter_traits::pointer				pointer;
		typedef typename Iter_traits::reference				reference;

		// <<<<<<<<<<<<<<<<<<<<<< MEMBER VARIABLES >>>>>>>>>>>>>>>>>>>>>>
		protected:
			iterator_type	_current;
			
		// <<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		// ----------------------- CONSTRUCTORS -------------------------
		// default constructor
		reverse_iterator() :_current() {}
		
		// initialisation constructor
		explicit reverse_iterator (iterator_type it) :_current(it) {}

		// copy constructor
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) :_current(rev_it.base()) {}

		// ---------------------------- METHOD --------------------------

		iterator_type	base( void ) const { return _current; };

		// ---------------------- OPERATOR OVERLOADS --------------------

		template< class T >
		reverse_iterator&	operator=( const reverse_iterator<T>& other )
		{
			_current = other.base();
			return *this;
		}
		
		reference			operator*() const
		{
			iterator_type _tmp = _current;
			return *--_tmp;
		}
		
		pointer				operator->() const	{ return &(operator*()); }

		reverse_iterator&	operator++() { --_current; return *this; }
		
		reverse_iterator&	operator--() { ++_current; return *this; }

		reverse_iterator	operator++(int) { reverse_iterator _tmp = *this; --_current; return _tmp; }

		reverse_iterator	operator--(int) { reverse_iterator _tmp = *this; ++_current; return _tmp; }

		reverse_iterator	operator+ (difference_type n) const	{ return reverse_iterator(_current - n); }

		reverse_iterator	operator- (difference_type n) const	{ return reverse_iterator(_current + n); }

		reverse_iterator&	operator+=(difference_type n) const	{ _current -= n; return *this; }

		reverse_iterator&	operator-=(difference_type n) const	{ _current += n; return *this; }

		reference			operator[](difference_type n) const { return *(*this + n); }

	};

	template <class Iterator>
		bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	
	template <class Iterator>
		bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() != rhs.base();
	}
	
	template <class Iterator>
		bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() < rhs.base();
	}
	
	template <class Iterator>
		bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() > rhs.base();
	}
	
	template <class Iterator>
		bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs > rhs);
	}
	
	template <class Iterator>
		bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs < rhs);
	}
	
	template <class Iterator>
	reverse_iterator<Iterator> operator+
		(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator-
		(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() + n);
	}

}	//namespace f
	
#endif