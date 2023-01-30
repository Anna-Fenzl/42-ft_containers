/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redblack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:17:48 by afenzl            #+#    #+#             */
/*   Updated: 2023/01/30 18:12:34 by afenzl           ###   ########.fr       */
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
		node_pointer	_nil;

		size_type		_size;
		node_alloc		_node_alloc;
		value_compare	_compare;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>
		private:

		public:

		// ----------------------- CONSTRUCTOR --------------------
		// default constructor
		Redblack_Tree(): _size(0), _compare(_Compare()), _node_alloc(std::allocator<RbtNode<value_type> >())
		{
			_nil = _node_alloc.allocate(1);
			_nil->set_colour(BLACK);
			_nil->_left = _nil;
			_nil->_right = _nil;
			_root = _nil;
		}
		
		Redblack_Tree(const Redblack_Tree& src) {*this = src;}

		~Redblack_Tree()
		{
			clear();
			_node_alloc.deallocate(_nil, 1);
		}

		// ----------------------- OPERATOR ----------------------

		Redblack_Tree& operator=( const Redblack_Tree& other )
		{
			if (*this != other)
			{
				clear();
				_nil = other._nil;				// <-- added
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
			RbtNode<value_type> node(value, parent, _nil);

			while (move != _nil)
			{
				if (is_equal(*(move->_value), value))
					return (ft::make_pair(find(value), false));
				parent = move;
				_compare(*(move->_value), value) ? move = move->_right : move = move->_left;
			}
			move = _node_alloc.allocate(1);
			_node_alloc.construct(move, node);
			if (_root == _nil)
				_root = move;
			else
				(parent != _nil && _compare(*(parent->_value), value)) ? parent->_right = move: parent->_left = move;
			move->set_parent(parent);
			
			insert_fixup(move);
			print_tree();
			return (ft::make_pair(find(value), true));
		}

		void	erase(iterator pos)
		{
			node_pointer	z = pos.base();
			std::cout << "remove " << *z << std::endl;
			node_pointer	y = z;
			node_pointer	x;
			rbt_colour		original_colour = y->get_colour();
			if (z->_left == _nil)
			{
				x = z->_right;
				transplant(z, x);
			}
			else if (z->_right == _nil)
			{
				x = z->_left;
				transplant(z, x);
			}
			else
			{
				y = red_black_tree_min(z->_right);
				original_colour = y->get_colour();
				x = y->_right;
				if (y->_parent == z)
					x->_parent = y;
				else
				{
					transplant(y, y->_right);
					y->_right = z->_right;
					y->_right->_parent = y;
				}
				transplant(z, y);
				y->_left = z->_left;
				y->_left->_parent = y;
				y->_colour = z->_colour;
			}
			if (original_colour == BLACK) {
				erase_fixup(x);
			}
		}

		void	erase_fixup(node_pointer x)
		{
			node_pointer	w;
			while (x != _root && x->get_colour() == BLACK)
			{
				if (x == x->_parent->_left)
				{
					w = x->_parent->_right;
					if (w->get_colour() == RED)
					{
						w->set_colour(BLACK);
						x->_parent->set_colour(RED);
						left_rotate(x->_parent);
						w = x->_parent->_right;
					}
					if (w->_left->get_colour() == BLACK && w->_right->get_colour() == BLACK)
					{
						w->set_colour(RED);
						x = x->_parent;
					}
					else if (w->_right->get_colour() == BLACK)
					{
						w->_left->set_colour(BLACK);
						w->set_colour(RED);
						right_rotate(w);
						w = x->_parent->_right;
					}
					w->set_colour(x->_parent->_colour);
					x->_parent->set_colour(BLACK);
					w->_right->set_colour(BLACK);
					left_rotate(x->_parent);
					x = _root;
				}
				else
				{
					w = x->_parent->_left;
					if (w->get_colour() == RED)
					{
						w->set_colour(BLACK);
						x->_parent->set_colour(RED);
						left_rotate(x->_parent);
						std::cout << "hey" << std::endl;
						w = x->_parent->_right;
					}
					if (w->_right->get_colour() == BLACK && w->_left->get_colour() == BLACK)
					{
						w->set_colour(RED);
						x = x->_parent;
					}
					else if (w->_left->get_colour() == BLACK)
					{
						w->_right->set_colour(BLACK);
						w->set_colour(RED);
						right_rotate(w);
						w = x->_parent->_left;
					}
					w->set_colour(x->_parent->_colour);
					x->_parent->set_colour(BLACK);
					w->_left->set_colour(BLACK);
					left_rotate(x->_parent);
					x = _root;
				}
			}
			x->_colour = BLACK;
		}

		iterator find (const value_type value)
		{
			node_pointer move = _root;
			while (move && move != _nil)
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
			while ( n != _root && n->_parent->_colour == RED)
			{
				if (n->_parent->_parent->_right == n->_parent)		// n's parent is a right child
				{
					if (n->_parent->_parent->_left != _nil
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
					if (n->_parent->_parent->_right != _nil
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
			node_pointer y = x->_right;
			x->_right = y->_left;				// turn y's subtree in x's subtree
			if (y->_left != _nil)
				y->_left->_parent = x;
			y->_parent = x->_parent;
			if (x->_parent == _nil)				// if x is root
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
			node_pointer y = x->_left;
			x->_left = y->_right;				// turn y's subtree in x's subtree
			if (y->_right != _nil)
				y->_right->_parent = x;
			y->_parent = x->_parent;
			if (x->_parent == _nil)				// if x is root
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
			if (u->_parent == _nil)
				_root = v;
			else if(u == u->_parent->_left)
				u->_parent->_left = v;
			else
				u->_parent->_right = v;
			v->_parent = u->_parent; 
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
			if (node == _nil)
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
			if (root == NULL || root == _nil)
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
			if (root->_value)
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


