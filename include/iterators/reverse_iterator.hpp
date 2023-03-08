/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:48:51 by afenzl            #+#    #+#             */
/*   Updated: 2023/03/07 12:19:46 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
			iterator_type	_ptr;
			
		// <<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		// ----------------------- CONSTRUCTORS -------------------------
		// default constructor
		reverse_iterator() :_ptr(iterator_type()) {}
		
		// initialisation constructor
		explicit reverse_iterator (iterator_type it) :_ptr(it) {}

		// copy constructor
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) :_ptr(rev_it.base()) {}

		// ---------------------------- METHOD --------------------------

		iterator_type	base( void ) const { return _ptr; };

		// ---------------------- OPERATOR OVERLOADS --------------------

		template< class T >
		reverse_iterator&	operator=( const reverse_iterator<T>& other )
		{
			_ptr = other.base();
			return *this;
		}
		
		reference			operator*() const
		{
			iterator_type _tmp = _ptr;
			return *--_tmp;
		}
		
		pointer				operator->() const	{ return &(operator*()); }

		reverse_iterator&	operator++() { --_ptr; return *this; }
		
		reverse_iterator&	operator--() { ++_ptr; return *this; }

		reverse_iterator	operator++(int) { reverse_iterator _tmp = *this; --_ptr; return _tmp; }

		reverse_iterator	operator--(int) { reverse_iterator _tmp = *this; ++_ptr; return _tmp; }

		reverse_iterator	operator+ (difference_type n) const	{ return reverse_iterator(_ptr - n); }

		reverse_iterator	operator- (difference_type n) const	{ return reverse_iterator(_ptr + n); }

		reverse_iterator&	operator+=(difference_type n)		{ _ptr -= n; return *this; }

		reverse_iterator&	operator-=(difference_type n)		{ _ptr += n; return *this; }

		reference			operator[](difference_type n) const { return *(*this + n); }

	};

	template < class InputIt, class Distance >
	void    advance( InputIt& it, Distance n )
	{
		it += n;
	}

	template< typename It >
	bool    operator==( const reverse_iterator< It >& lhs, const reverse_iterator< It >& rhs )
	{
		return (lhs.base() == rhs.base());
	}

	template< typename It1, typename It2 >
	bool    operator==( const reverse_iterator< It1 >& lhs, const reverse_iterator< It2 >& rhs )
	{
		return (lhs.base() == rhs.base());
	}

	template< typename It >
	bool    operator!=( const reverse_iterator< It >& lhs, const reverse_iterator< It >& rhs )
	{
		return (!(lhs == rhs));
	}

	template< typename It1, typename It2 >
	bool    operator!=( const reverse_iterator< It1 >& lhs, const reverse_iterator< It2 >& rhs )
	{
		return (!(lhs == rhs));
	}

	template< typename It >
	bool    operator<( const reverse_iterator< It >& lhs, const reverse_iterator< It >& rhs )
	{
		return (rhs.base() < lhs.base());
	}

	template< typename It1, typename It2 >
	bool    operator<( const reverse_iterator< It1 >& lhs, const reverse_iterator< It2 >& rhs )
	{
		return (rhs.base() < lhs.base());
	}

	template< typename It >
	bool    operator<=( const reverse_iterator< It >& lhs, const reverse_iterator< It >& rhs )
	{
		return (!(rhs < lhs));
	}

	template< typename It1, typename It2 >
	bool    operator<=( const reverse_iterator< It1 >& lhs, const reverse_iterator< It2 >& rhs )
	{
		return (!(rhs < lhs));
	}

	template< typename It >
	bool    operator>( const reverse_iterator< It >& lhs, const reverse_iterator< It >& rhs )
	{
		return (rhs < lhs);
	}

	template< typename It1, typename It2 >
	bool    operator>( const reverse_iterator< It1 >& lhs, const reverse_iterator< It2 >& rhs )
	{
		return (rhs < lhs);
	}

	template< typename It >
	bool    operator>=( const reverse_iterator< It >& lhs, const reverse_iterator< It >& rhs )
	{
		return (!(lhs < rhs));
	}

	template< typename It1, typename It2 >
	bool    operator>=( const reverse_iterator< It1 >& lhs, const reverse_iterator< It2 >& rhs )
	{
		return (!(lhs < rhs));
	}

	template< typename It >
	reverse_iterator< It >  operator+( const typename reverse_iterator< It >::difference_type& i, const reverse_iterator< It >& iter )
	{
		return (reverse_iterator< It >(iter.base() - i));
	}

	template< typename It >
	reverse_iterator< It >  operator-( const typename reverse_iterator< It >::difference_type& i, const reverse_iterator< It >& iter )
	{
		return (reverse_iterator< It >(iter.base() + i));
	}

	template< typename It >
	typename reverse_iterator< It >::difference_type    operator+( const reverse_iterator< It >& lhs, const reverse_iterator< It >& rhs )
	{
		return (lhs.base() + rhs.base());
	}

	template< typename It >
	typename reverse_iterator< It >::difference_type    operator-( const reverse_iterator< It >& lhs, const reverse_iterator< It >& rhs )
	{
		return (rhs.base() - lhs.base());
	}

	template< typename It1, typename It2 >
	typename reverse_iterator< It1 >::difference_type   operator+( const reverse_iterator< It1 >& lhs, const reverse_iterator< It2 >& rhs )
	{
		return (lhs.base() + rhs.base());
	}

	template< typename It1, typename It2 >
	typename reverse_iterator< It1 >::difference_type   operator-( const reverse_iterator< It1 >& lhs, const reverse_iterator< It2 >& rhs )
	{
		return (rhs.base() - lhs.base());
	}

}	//namespace f
	
#endif