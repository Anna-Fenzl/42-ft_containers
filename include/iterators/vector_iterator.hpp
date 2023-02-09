/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:48 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/09 17:37:53 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
	template< typename T >
	class vector_iterator
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>
		private:
			typedef typename ft::Iterator<ft::random_access_iterator_tag , T> Iterator;
		public:
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::difference_type		difference_type;
			typedef	typename Iterator::iterator_category	iterator_category;
		
		// <<<<<<<<<<<<<<<<<<<<<< MEMBER VARIABLES >>>>>>>>>>>>>>>>>>>>>>
		private:
			pointer		_ptr;

		// <<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		
		// ----------------------- CONSTRUCTORS -------------------------
		vector_iterator(pointer ptr) :_ptr(ptr) {}

		vector_iterator(const vector_iterator &src) :_ptr(src._ptr) {}

		// ---------------------------- METHOD --------------------------
		
		pointer	base() const		{ return _ptr; }
		
		void			swap(vector_iterator &other)
		{
			pointer tmp = _ptr;
			_ptr = other.ptr;
			other._ptr = tmp;
		}

	// ----------------------- OPERATOR OVERLOAD --------------------
		reference		operator[](int idx)	{ return *(_ptr + idx); }

		reference		operator->()		{ return _ptr; }

		reference		operator*()			{return *_ptr; }

		vector_iterator	&operator++() 		{ _ptr++; return *this; }

		vector_iterator	&operator--()		{ _ptr--; return *this; }

		vector_iterator	operator++(int)		{vector_iterator cpy(*this); ++(*this); return cpy; }

		vector_iterator	operator--(int)		{vector_iterator cpy(*this); --(*this); return cpy; }

		vector_iterator	&operator+=(difference_type n)	{ _ptr += n; return *this; }

		vector_iterator	&operator-=(difference_type n)	{ _ptr -= n; return *this; }

		vector_iterator	operator+(difference_type n ) const	{ return _ptr + n; }

		vector_iterator	operator-(difference_type n ) const	{ return _ptr - n; }

		vector_iterator	&operator=(const vector_iterator &other )
		{
			if (_ptr != other.base())
			{
				_ptr = other.base();
			}
			return *this;
		}
	};
		
		// ----------------------- OPERATOR OVERLOAD --------------------
		
		template< typename T >
		bool	operator==( const vector_iterator< T >& lhs, const vector_iterator< T >& rhs )
		{
			return (lhs.base() == rhs.base());
		}

		template< typename T1, typename T2 >
		bool	operator==( const vector_iterator< T1 >& lhs, const vector_iterator< T2 >& rhs )
		{
			return (lhs.base() == rhs.base());
		}

		template< typename T >
		bool	operator!=( const vector_iterator< T >& lhs, const vector_iterator< T >& rhs )
		{
			return (!(lhs == rhs));
		}

		template< typename T1, typename T2 >
		bool	operator!=( const vector_iterator< T1 >& lhs, const vector_iterator< T2 >& rhs )
		{
			return (!(lhs == rhs));
		}

		template< typename T >
		bool	operator<( const vector_iterator< T >& lhs, const vector_iterator< T >& rhs )
		{
			return (lhs.base() < rhs.base());
		}

		template< typename T1, typename T2 >
		bool	operator<( const vector_iterator< T1 >& lhs, const vector_iterator< T2 >& rhs )
		{
			return (lhs.base() < rhs.base());
		}

		template< typename T >
		bool	operator<=( const vector_iterator< T >& lhs, const vector_iterator< T >& rhs )
		{
			return (!(rhs < lhs));
		}

		template< typename T1, typename T2 >
		bool	operator<=( const vector_iterator< T1 >& lhs, const vector_iterator< T2 >& rhs )
		{
			return (!(rhs < lhs));
		}

		template< typename T >
		bool	operator>( const vector_iterator< T >& lhs, const vector_iterator< T >& rhs )
		{
			return (rhs < lhs);
		}

		template< typename T1, typename T2 >
		bool	operator>( const vector_iterator< T1 >& lhs, const vector_iterator< T2 >& rhs )
		{
			return (rhs < lhs);
		}

		template< typename T >
		bool	operator>=( const vector_iterator< T >& lhs, const vector_iterator< T >& rhs )
		{
			return (!(lhs < rhs));
		}

		template< typename T1, typename T2 >
		bool	operator>=( const vector_iterator< T1 >& lhs, const vector_iterator< T2 >& rhs )
		{
			return (!(lhs < rhs));
		}

		template< typename T >
		vector_iterator< T >	operator+( const typename vector_iterator< T >::difference_type& i,
											const vector_iterator< T >& iter )
		{
			return (vector_iterator< T >(iter.base() + i));
		}

		template< typename T >
		vector_iterator< T >	operator-( const typename vector_iterator< T >::difference_type& i,
											const vector_iterator< T >& iter )
		{
			return (vector_iterator< T >(iter.base() - i));
		}

		template< typename T >
		typename vector_iterator< T >::difference_type	operator+( const vector_iterator< T >& lhs,
																	const vector_iterator< T >& rhs )
		{
			return (lhs.base() + rhs.base());
		}

		template< typename T >
		typename vector_iterator< T >::difference_type	operator-( const vector_iterator< T >& lhs,
																	const vector_iterator< T >& rhs )
		{
			return (lhs.base() - rhs.base());
		}

		template< typename T1, typename T2 >
		typename vector_iterator< T1 >::difference_type	operator+( const vector_iterator< T1 >& lhs,
																	const vector_iterator< T2 >& rhs )
		{
			return (lhs.base() + rhs.base());
		}

		template< typename T1, typename T2 >
		typename vector_iterator< T1 >::difference_type	operator-( const vector_iterator< T1 >& lhs,
																	const vector_iterator< T2 >& rhs )
		{
			return (lhs.base() - rhs.base());
		}

} // namespace ft


# endif