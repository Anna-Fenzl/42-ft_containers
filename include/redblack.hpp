/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redblack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:17:48 by afenzl            #+#    #+#             */
/*   Updated: 2023/01/28 14:29:12 by afenzl           ###   ########.fr       */
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

	template<typename _Val, typename _Compare=std::less<_Val>, typename Alloc = std::allocator<_Val> >
	class Redblack_Tree
	{
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< ALIASES >>>>>>>>>>>>>>>>>>>>>>>>>>>
		typedef typename	Alloc::template rebind<RbtNode<_Val> >::other	node_alloc;
		public:

		typedef _Compare						value_compare;
		typedef _Val							value_type;
		typedef _Val*							value_pointer;
		typedef const _Val*						const_value_pointer;
		typedef _Val&							value_reference;
		typedef const _Val&						const_value_reference;
		typedef RbtNode<_Val>					node_type;
		typedef RbtNode<_Val>*					node_pointer;
		typedef const RbtNode<_Val>*			const_node_pointer;

		typedef	size_t							size_type;
		typedef	ptrdiff_t						difference_type;

		// iterators
		typedef ft::Rbt_Iterator<value_type>	iterator;
		// typedef ft::Const_Rbt_Iterator<node_pointer>	const_iterator;
		
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>>
		protected:
		node_pointer	_root;
		node_type		_loopback;

		size_type		_size;
		node_alloc		_node_alloc;
		value_compare	_compare;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>
		private:

		public:

		// ----------------------- CONSTRUCTOR --------------------
		// default constructor
		Redblack_Tree(): _root(NULL), _size(0), _compare(_Compare()), _node_alloc(std::allocator<RbtNode<value_type> >())
		{
			_loopback._left = &_loopback;
			std::cout << "loopback is " << _loopback << std::endl;
		}
		
		Redblack_Tree(const Redblack_Tree& src) {*this = src;}

		~Redblack_Tree()
		{
			clear();
		}

		// ----------------------- OPERATOR ----------------------

		Redblack_Tree& operator=( const Redblack_Tree& other )
		{
			if (*this != other)
			{
				clear();
				_root = copy_tree(other._root);
				_size = other._size;
				_node_alloc = other._node_alloc;
				_compare = other._compare;
			}
		}
		
		// ----------------------- ITERATORS ----------------------

		iterator		begin() 			{ return iterator(red_black_tree_min(_root)); };
		
		iterator		end()				{ return NULL; };
		
		// ----------------------- CAPACITY -----------------------
		
		size_type		size() const		{ return _size; }

		size_type		max_size() const	{ return _node_alloc.max_size(); }

		bool			empty() const		{ return _size == 0; }

		// ----------------------- GETTERS ------------------------
		
		node_alloc		get_node_alloc()	{ return _node_alloc; }

		node_pointer	root()				{ return _root; }
		
		// ----------------------- MODIFY -------------------------

		//  (1) return a pair
		// pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the map.
		// The pair::second element in the pair is set to true if a new element was inserted 
		ft::pair<iterator, bool>	insert(const value_type& value)
		{
			node_pointer move = _root, parent = _root;
			RbtNode<value_type> node(value, parent);

			while (move != NULL)
			{
				if (is_equal(*(move->_value), value))
					return (ft::make_pair(find(value), false));
				parent = move;
				_compare(*(move->_value), value) ? move = move->_right : move = move->_left;
			}
			move = _node_alloc.allocate(1);
			_node_alloc.construct(move, node);
			if (_root == NULL)
				_root = move;
			else
				(parent != NULL && _compare(*(parent->_value), value)) ? parent->_right = move: parent->_left = move;
			move->set_parent(parent);
			
			insert_fixup(move);
			return (ft::make_pair(find(value), true));
		}

		// size_type	erase( value_type value)
		// {
		// 	node_pointer	node = find(value).base();

		// 	// OR ENDNOTE == what is endnode/loopback
		// 	if (!node)
		// 		return 0;
		// 	erase_node(node);
		// 	return 1;
		// }

		// void	erase_node( node_pointer node )
		// {
		// 	node = deletion(node);
		// 	//case 1
		// 	if (node->get_colour() == RED)
		// 		remove_node(node);
		// 	else
		// 		fixup_delete(node);
			
		// }

		// node_pointer	deletion(node_pointer node)
		// {
		// 	node_pointer	next;
		// 	while (node->_left || node->_right)
		// 	{
		// 		if (node == )
		// 	}
		// }

		// void	erase(iterator pos)
		// {
		// 	if (pos == end())
		// 		return;

		// 	node_pointer	z = const_cast < node_pointer > (pos.base());
		// 	std::cout << "********* DELETING **********" << *z << std::endl;
		// 	node_pointer	y = z;
		// 	node_pointer	x;
		// 	rbt_colour		original_colour = y->get_colour();

		// 	if (z->_left == NULL)
		// 	{
		// 		std::cout << "1\n";
		// 		x = z->_right;
		// 		transplant(z, z->_right);
		// 	}
		// 	else if(z->_right == NULL)
		// 	{
		// 		std::cout << "2\n";
		// 		x = z->_left;
		// 		transplant(z, z->_left);
		// 		// added this
		// 		// x->_parent = z->_parent;
		// 	}
		// 	else
		// 	{
		// 		std::cout << "3\n";
		// 		y = red_black_tree_min(z->_right);
		// 		x = z->_right;
		// 		if (y->_parent == z)
		// 			x->_parent = y;
		// 		else
		// 		{
		// 			std::cout << "4\n";
		// 			transplant(y, y->_right);
		// 			y->_right = z->_right;
		// 			y->_right->_parent = y;
		// 		}
		// 		transplant(z, y);
		// 		y->_left = z->_left;
		// 		y->_left->_parent = y;
		// 		y->set_colour(z->_colour);
		// 	}
		// 	// delete_node(z);
		// 	if (original_colour == BLACK)
		// 	{
		// 		std::cout << "original colour is black\n";
		// 		// delete_fixup(x);
		// 	}
		// 	print_tree();
		// }

		iterator find (const value_type value)
		{
			node_pointer move = _root;
			while (move)
			{
				if (_compare(*move->_value, value))
					move = move->_right;
				else if (_compare(value, *move->_value))
					move = move->_left;
				else
					return(iterator(move));
			}
			return(end());
		}

		// const_iterator find (const key_type& k) const

		void	clear()
		{
			clear_tree(_root);
			_root = NULL;
			_size = 0;
		}

		private:

		void	insert_fixup(node_pointer n)
		{
			while (n != NULL && n->_parent != NULL && n->_parent->_parent != NULL
				&& n != _root && n->_parent->_colour == RED)
			{
				if (n->_parent->_parent->_right == n->_parent)		// n's parent is a right child
				{
					if (n->_parent->_parent->_left != NULL
						&& n->_parent->_parent->_left->_colour == RED)
					{
						n->_parent->_parent->_left->set_colour(BLACK);
						n->_parent->set_colour(BLACK);
						n->_parent->_parent->set_colour(RED);
						n = n->_parent->_parent;
					}
					else
					{
						if (n->_parent->_left == n)
						{
							n = n->_parent;
							right_rotate(n);
						}
						n->_parent->set_colour(BLACK);
						n->_parent->_parent->set_colour(RED);
						left_rotate(n->_parent->_parent);
					}
				}
				else												// n's parent is a left child
				{
					if (n->_parent->_parent->_right != NULL
						&& n->_parent->_parent->_right->_colour == RED)
					{
						n->_parent->_parent->_right->set_colour(BLACK);
						n->_parent->set_colour(BLACK);
						n->_parent->_parent->set_colour(RED);
						n = n->_parent->_parent;
					}
					else 
					{
						if (n->_parent->_right == n)
						{
							n = n->_parent;
							left_rotate(n);
						}
						n->_parent->set_colour(BLACK);
						n->_parent->_parent->set_colour(RED);
						right_rotate(n->_parent->_parent);
					}
				}
			}
			_root->_colour = BLACK;
		}

		void	left_rotate(node_pointer x)
		{
			if ( x == NULL || x->_right == NULL)
				return;

			node_pointer y = x->_right;
			x->_right = y->_left;				// turn y's subtree in x's subtree
			if (y->_left != NULL)
				y->_left->_parent = x;
			y->_parent = x->_parent;
			if (x->_parent == NULL)				// if x is root
				_root = y;
			else if (x == x->_parent->_left)	// or x is left child
				x->_parent->_left = y;
			else								// or x is right child
				x->_parent->_right = y;
			y->_left = x;						//put x on y's left
			x->_parent = y;
		}

		void	right_rotate(node_pointer x)
		{
			if ( x == NULL || x->_left == NULL)
				return;
	
			node_pointer y = x->_left;
			x->_left = y->_right;				// turn y's subtree in x's subtree
			if (y->_right != NULL)
				y->_right->_parent = x;
			y->_parent = x->_parent;
			if (x->_parent == NULL)				// if x is root
				_root = y;
			else if (x == x->_parent->_right)	// or x is left child
				x->_parent->_right = y;
			else								// or x is right child
				x->_parent->_left = y;
			y->_right = x;						//put x on y's left
			x->_parent = y;
		}

		void	transplant(node_pointer u, node_pointer v)
		{
			if (u == NULL)
				return;

			if (u->_parent == NULL)
				_root = v;
			else if(u == u->_parent->_left)
				u->_parent->_left = v;
			else
				u->_parent->_right = v;
			if (v)
				v->_parent = u; 
		}

		bool is_equal(value_type value, value_type comp)
		{
			return (!_compare(value, comp) && !_compare(comp, value));
		}
		
		node_pointer	allocate_node(value_type value)
		{
			node_pointer node = _node_alloc.allocate(1);
			
			RbtNode<value_type>	set_node(value);
			_node_alloc.construct(node, set_node);
			return (node);
		}

		void	delete_node(node_pointer node)
		{
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
			node = NULL;
		}

		node_pointer	copy_tree(node_pointer root)
		{
			if (root == NULL)
				return NULL;
			node_pointer new_node = allocate_node(root->get_value());
			new_node = root;
			new_node->_left = _copy_tree(root->_left, new_node);
			new_node->_right = _copy_tree(root->_right, new_node);
			return (new_node);
		}
		
		void	clear_tree(node_pointer node)
		{
			if (node == NULL)
					return;

			clear_tree(node->_right);
			clear_tree(node->_left);
			delete_node(node);
		}
		// ------------------------------- DEBUG ------------------------------------
		public:
		class Trunk
		{
			public:
			Trunk *prev;
			std::string	str;
			
			Trunk(Trunk *prev, std::string str): prev(prev), str(str) {}
		};

		void showTrunks(Trunk *p)
		{
			if (p == NULL)
				return;
	
			showTrunks(p->prev);
			std::cout << p->str;
		}
		
		void print_tree(node_pointer root, Trunk *prev, bool isLeft)
		{
			if (root == NULL)
				return;
				
			std::string prev_str = "    ";
			Trunk *trunk = new Trunk(prev, prev_str);

			print_tree(root->_right, trunk, true);
			if (!prev)
				trunk->str = "———";
			else if (isLeft)
			{
				trunk->str = ",———";
				prev_str = "   |";
			}
			else
			{
				trunk->str = "`———";
				prev->str = prev_str;
			}
			showTrunks(trunk);
			std::cout << ((root->get_colour() == RED) ? "\033[0;31m" : "");
			std::cout << "[" << *root->_value << "]"<< std::endl;
			std::cout << ((root->get_colour() == RED) ? "\033[0m" : "");


			if (prev)
				prev->str = prev_str;
			trunk->str = "   |";

			print_tree(root->_left, trunk, false);
			delete trunk;
		}

		void print_tree()
		{
			std::cout << "<  THE WHOLE TREE  >" << std::endl;
			print_tree(_root , NULL, false);
		}
		
	};

}	// namespace ft


#endif


