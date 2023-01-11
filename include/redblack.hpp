/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redblack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:17:48 by afenzl            #+#    #+#             */
/*   Updated: 2023/01/11 18:07:46 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACK_HPP
# define REDBLACK_HPP

// https://gcc.gnu.org/onlinedocs/gcc-4.6.2/libstdc++/api/a01067_source.html

# include "./iterators/rbt_iterator.hpp"
# include "./utils/rbt_node.hpp"
# include "./utils/pair.hpp"
# include <stddef.h>
# include <iostream>
# include <memory>

namespace ft
{

	// 1. Every node is either red or black.
	// 2. The root is black.
	// 3. Every leaf (NIL) is black.
	// 4. If a node is red, then both its children are black.
	// 5. For each node, all simple paths from the node to descendant leaves contain the
	// same number of black nodes.

	template<typename _Val, typename _Compare=std::less<_Val> >
	class Redblack_Tree
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		typedef typename	std::allocator<_Val>::template rebind<Rbt_Node<_Val> >::other	node_alloc;
		public:
		// typedef _Alloc														value_alloc;

		typedef _Compare						value_compare;
		typedef _Val							value_type;
		typedef _Val*							value_pointer;
		typedef const _Val*						const_value_pointer;
		typedef _Val&							value_reference;
		typedef const _Val&						const_value_reference;
		typedef Rbt_Node<_Val>*					node_pointer;
		typedef const Rbt_Node<_Val>*			const_node_pointer;

		typedef	size_t							size_type;
		typedef	ptrdiff_t						difference_type;

		// iterators
		typedef ft::Rbt_Iterator<value_type>				iterator;
		// typedef ft::Const_Rbt_Iterator<node_pointer>	const_iterator;
		
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>>
		protected:
		
		node_pointer	_root;

		size_type		_size;
		node_alloc		_node_alloc;
		value_compare	_compare;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>
		private:

		public:

		// ----------------------- CONSTRUCTOR --------------------
		// default constructor
		Redblack_Tree():
			_root(NULL),
			_size(0),
			_compare(_Compare()),
			_node_alloc(std::allocator<Rbt_Node<value_type> >()) {}

		// range constructor

		// copy constructor

		// ----------------------- ITERATORS ----------------------

		iterator				begin() 	{ return iterator(red_black_tree_min(_root)); };
		
		// what should the end be?
		iterator				end()		{ return iterator(red_black_tree_max(_root)); };
		

		// ----------------------- CAPACITY -----------------------
		
		size_type	size() const			{ return _size; }

		size_type	max_size() const		{ return _node_alloc.max_size(); }

		bool		empty() const			{ return _size == 0; }

		// ----------------------- GETTERS ------------------------
		
		node_alloc	get_node_alloc()	{ return _node_alloc; }

		node_pointer	root()			{ return _root; }
		
		// ----------------------- MODIFY -------------------------
		private:
		bool is_equal(value_type value, value_type comp)
		{
			return (!_compare(value, comp) && !_compare(comp, value));
		}

		public:
		void	insert(value_type value)
		{
			node_pointer move = _root, parent = _root;
			Rbt_Node<value_type> node(value, parent);

			while (move != NULL)
			{
				if (is_equal(*(move->_value), value))
					return;
				parent = move;
				_compare(*(move->_value), value) ? move = move->_right : move = move->_left;
			}

			move = _node_alloc.allocate(1);
			_node_alloc.construct(move, node);
			if (_root == NULL)
				_root = move;
			else
				(parent != NULL && _compare(*(parent->_value), value)) ? parent->_right = move: parent->_left = move;

			std::cout << '\n' << "ADDING --" << value << "--" << std::endl;
			print_tree("", _root);
		}

		void print_tree(const std::string &prefix, node_pointer node)
		{
			if (node != NULL)
			{
				std::cout << prefix;
				std::cout << ((node->_parent && node == node->_parent->_left) ? "├──" : "└──" );
				std::cout << "[" << *node->_value << "]" << std::endl;

				print_tree( prefix + ((node->_parent && node == node->_parent->_left) ? "|  " : "   "), node->_left);
				print_tree( prefix + ((node->_parent && node == node->_parent->_left) ? "|  " : "   "), node->_right);
			}
		}
	};

}	// namespace ft


#endif


