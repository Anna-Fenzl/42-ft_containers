/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:07:21 by afenzl            #+#    #+#             */
/*   Updated: 2023/03/07 12:21:01 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef SFINAE_HPP
# define SFINAE_HPP

namespace ft
{	
	// <<<<<<<<<<<<<<<<<<<<<<< IS_INTEGRAL >>>>>>>>>>>>>>>>>>>>

	template< class T, T v >
	struct integral_constant
	{
		static const T	value = v;
		typedef T		value_type;
	};

	typedef struct integral_constant<bool, true>	true_type;
	typedef struct integral_constant<bool, false>	false_type;

	template< class T >
	struct is_integral										: public false_type { };

	template< >
	struct is_integral<bool>								: public true_type { };

	template< >
	struct is_integral<char>								: public true_type { };

	template< >
	struct is_integral<signed char>							: public true_type { };

	template< >
	struct is_integral<short int>							: public true_type { };

	template< >
	struct is_integral<int>									: public true_type { };

	template< >
	struct is_integral<long int>							: public true_type { };

	template< >
	struct is_integral<unsigned char>						: public true_type { };

	template< >
	struct is_integral<unsigned short int>					: public true_type { };

	template< >
	struct is_integral<unsigned int>						: public true_type { };

	template< >
	struct is_integral<unsigned long int>					: public true_type { };

	template< >
	struct is_integral<const bool>							: public true_type { };

	template< >
	struct is_integral<const char>							: public true_type { };

	template< >
	struct is_integral<const signed char>					: public true_type { };

	template< >
	struct is_integral<const short int>						: public true_type { };

	template< >
	struct is_integral<const int>							: public true_type { };

	template< >
	struct is_integral<const long int>						: public true_type { };

	template< >
	struct is_integral<const unsigned char>					: public true_type { };

	template< >
	struct is_integral<const unsigned short int>			: public true_type { };

	template< >
	struct is_integral<const unsigned int>					: public true_type { };

	template< >
	struct is_integral<const unsigned long int>				: public true_type { };

	template< >
	struct is_integral<volatile char>						: public true_type { };

	template< >
	struct is_integral<volatile bool>						: public true_type { };

	template< >
	struct is_integral<volatile signed char>				: public true_type { };

	template< >
	struct is_integral<volatile short int>					: public true_type { };

	template< >
	struct is_integral<volatile int>						: public true_type { };

	template< >
	struct is_integral<volatile long int>					: public true_type { };

	template< >
	struct is_integral<volatile unsigned char>				: public true_type { };

	template< >
	struct is_integral<volatile unsigned short int>			: public true_type { };

	template< >
	struct is_integral<volatile unsigned int>				: public true_type { };

	template< >
	struct is_integral<volatile unsigned long int>			: public true_type { };

	template< >
	struct is_integral<const volatile char>					: public true_type { };

	template< >
	struct is_integral<const volatile bool>					: public true_type { };

	template< >
	struct is_integral<const volatile signed char>			: public true_type { };

	template< >
	struct is_integral<const volatile short int>			: public true_type { };

	template< >
	struct is_integral<const volatile int>					: public true_type { };

	template< >
	struct is_integral<const volatile long int>				: public true_type { };

	template< >
	struct is_integral<const volatile unsigned char>		: public true_type { };

	template< >
	struct is_integral<const volatile unsigned short int>	: public true_type { };

	template< >
	struct is_integral<const volatile unsigned int>			: public true_type { };

	template< >
	struct is_integral<const volatile unsigned long int>	: public true_type { };

	// <<<<<<<<<<<<<<<<<<<<<<< ENABLE_IF >>>>>>>>>>>>>>>>>>>>>

	template <bool B, typename T = void>
	struct enable_if
	{};

	template <typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

}

#endif