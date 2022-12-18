/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:48 by afenzl            #+#    #+#             */
/*   Updated: 2022/12/16 14:53:45 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "iterator.hpp"

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
			typedef typename Iterator::difference_type		difference_type;
			typedef	typename Iterator::iterator_category	iterator_category;
		
		// <<<<<<<<<<<<<<<<<<<<<< MEMBER VARIABLES >>>>>>>>>>>>>>>>>>>>>>
		private:
			pointer		_ptr;

		// <<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>>>
		public:
		
		// ----------------------- CONSTRUCTORS -------------------------
		VectorIterator(pointer ptr) :_ptr(ptr) {}

		VectorIterator(const VectorIterator &src) :_ptr(src._ptr) {}

		// ---------------------------- METHOD --------------------------
		
		pointer	base() const		{ return _ptr; }
		
		void			swap(VectorIterator &other)
		{
			pointer tmp = _ptr;
			_ptr = other.ptr;
			other._ptr = tmp;
		}

	// ----------------------- OPERATOR OVERLOAD --------------------
		reference		operator[](int idx)	{ return *(_ptr + idx); }

		reference		operator->()		{ return _ptr; }

		reference		operator*()			{return *_ptr; }

		VectorIterator	&operator++() 		{ _ptr++; return *this; }

		VectorIterator	&operator--()		{ _ptr--; return *this; }

		VectorIterator	operator++(int)		{VectorIterator cpy(*this); ++(*this); return cpy; }

		VectorIterator	operator--(int)		{VectorIterator cpy(*this); --(*this); return cpy; }

		VectorIterator	&operator+=(difference_type n)	{ _ptr += n; return *this; }

		VectorIterator	&operator-=(difference_type n)	{ _ptr -= n; return *this; }

		VectorIterator	operator+(difference_type n ) const	{ return _ptr + n; }

		VectorIterator	operator-(difference_type n ) const	{ return _ptr - n; }

		VectorIterator	&operator=(const VectorIterator &other )
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
		bool	operator==( const VectorIterator< T >& lhs, const VectorIterator< T >& rhs )
		{
			return (lhs.base() == rhs.base());
		}

		template< typename T1, typename T2 >
		bool	operator==( const VectorIterator< T1 >& lhs, const VectorIterator< T2 >& rhs )
		{
			return (lhs.base() == rhs.base());
		}

		template< typename T >
		bool	operator!=( const VectorIterator< T >& lhs, const VectorIterator< T >& rhs )
		{
			return (!(lhs == rhs));
		}

		template< typename T1, typename T2 >
		bool	operator!=( const VectorIterator< T1 >& lhs, const VectorIterator< T2 >& rhs )
		{
			return (!(lhs == rhs));
		}

		template< typename T >
		bool	operator<( const VectorIterator< T >& lhs, const VectorIterator< T >& rhs )
		{
			return (lhs.base() < rhs.base());
		}

		template< typename T1, typename T2 >
		bool	operator<( const VectorIterator< T1 >& lhs, const VectorIterator< T2 >& rhs )
		{
			return (lhs.base() < rhs.base());
		}

		template< typename T >
		bool	operator<=( const VectorIterator< T >& lhs, const VectorIterator< T >& rhs )
		{
			return (!(rhs < lhs));
		}

		template< typename T1, typename T2 >
		bool	operator<=( const VectorIterator< T1 >& lhs, const VectorIterator< T2 >& rhs )
		{
			return (!(rhs < lhs));
		}

		template< typename T >
		bool	operator>( const VectorIterator< T >& lhs, const VectorIterator< T >& rhs )
		{
			return (rhs < lhs);
		}

		template< typename T1, typename T2 >
		bool	operator>( const VectorIterator< T1 >& lhs, const VectorIterator< T2 >& rhs )
		{
			return (rhs < lhs);
		}

		template< typename T >
		bool	operator>=( const VectorIterator< T >& lhs, const VectorIterator< T >& rhs )
		{
			return (!(lhs < rhs));
		}

		template< typename T1, typename T2 >
		bool	operator>=( const VectorIterator< T1 >& lhs, const VectorIterator< T2 >& rhs )
		{
			return (!(lhs < rhs));
		}

		template< typename T >
		VectorIterator< T >	operator+( const typename VectorIterator< T >::difference_type& i,
											const VectorIterator< T >& iter )
		{
			return (VectorIterator< T >(iter.base() + i));
		}

		template< typename T >
		VectorIterator< T >	operator-( const typename VectorIterator< T >::difference_type& i,
											const VectorIterator< T >& iter )
		{
			return (VectorIterator< T >(iter.base() - i));
		}

		template< typename T >
		typename VectorIterator< T >::difference_type	operator+( const VectorIterator< T >& lhs,
																	const VectorIterator< T >& rhs )
		{
			return (lhs.base() + rhs.base());
		}

		template< typename T >
		typename VectorIterator< T >::difference_type	operator-( const VectorIterator< T >& lhs,
																	const VectorIterator< T >& rhs )
		{
			return (lhs.base() - rhs.base());
		}

		template< typename T1, typename T2 >
		typename VectorIterator< T1 >::difference_type	operator+( const VectorIterator< T1 >& lhs,
																	const VectorIterator< T2 >& rhs )
		{
			return (lhs.base() + rhs.base());
		}

		template< typename T1, typename T2 >
		typename VectorIterator< T1 >::difference_type	operator-( const VectorIterator< T1 >& lhs,
																	const VectorIterator< T2 >& rhs )
		{
			return (lhs.base() - rhs.base());
		}

} // namespace ft


# endif