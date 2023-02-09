/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:21:29 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/08 16:08:57 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP
# include <iostream>

namespace ft
{
	// <<<<<<<<<<<<<<<<<<<<<<<< PAIR >>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	// pair is a class template that provides a way to store two heterogeneous objects as a single unit
	template< class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type	first;
		second_type	second;

		// ---------------------- CONSTRUCTORS ---------------------
		
		// 1) Default constructor. Value-initializes both elements of the pair, first and second.
		pair(): first(), second() {}
		
		// 2) Initializes first with x and second with y
		pair( const T1& x, const T2& y ): first(x), second(y) {}
		
		// 5) Initializes first with p.first and second with p.second.
		template< class U1, class U2 >
		pair( const pair<U1, U2>& p ):  first(p.first), second(p.second) {}

		// ---------------------- OPERATOR= ------------------------

		pair& operator=( const pair& other )
		{
			first = other.first;
			second = other.second;
			return *this;
		}

	};
	
	template< class T1, class T2 >
		ft::pair<T1, T2> make_pair( T1 t, T2 u )
	{
		return pair<T1, T2>(t, u);
	}
	
	template< class T1, class T2 >
		bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template< class T1, class T2 >
		bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class T1, class T2 >
		bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return lhs.first < rhs.first || (!(lhs.first < rhs.first) && lhs.second < rhs.second);
	}

	template< class T1, class T2 >
		bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return !(lhs < rhs);
	}

	template< class T1, class T2 >
		bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return rhs < lhs;
	}

	template< class T1, class T2 >
		bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return !(rhs < lhs);
	}

	template <typename Key, typename Value>
	std::ostream&	operator <<(std::ostream& output, const pair<Key, Value> data)
	{
		output << data.first << "/" << data.second;
		return (output);
	}

	template< class T >
	void	swap( T& lhs, T& rhs )
	{
		T	tmp(lhs);
		lhs = rhs;
		rhs = tmp;
	}

}	//namespace ft

#endif