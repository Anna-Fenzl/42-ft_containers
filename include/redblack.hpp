/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redblack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:17:48 by afenzl            #+#    #+#             */
/*   Updated: 2023/01/14 14:51:43 by afenzl           ###   ########.fr       */
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
		Redblack_Tree(): _root(NULL), _size(0), _compare(_Compare()), _node_alloc(std::allocator<Rbt_Node<value_type> >()) {}

		// copy constructor
		// Redblack_Tree(Redblack_Tree& src): _compare(_Compare()), _node_alloc(std::allocator<Rbt_Node<value_type> >()
		// {
		// 	*this = src;
		// }

		~Redblack_Tree()
		{
			clear();
		}
		

		// ----------------------- ITERATORS ----------------------

		iterator	begin() 	{ return iterator(red_black_tree_min(_root)); };
		
		iterator	end()		{ return NULL; };
		
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
		// also need to increase _size
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
			move->set_parent(parent);
			
			insert_fixup(move);
		}

		void	rb_delete(node_pointer z)
		{
			node_pointer x;
			node_pointer y = z;
			rbt_colour original_colour = y->get_colour();

			if (z->_left == NULL)
			{
				x = z->_right;
				transplant(z, z->_right);
			}
			else if(z->_right == NULL)
			{
				x = z->_left;
				transplant(z, z->_left);
			}
			else
			{
				y = red_black_tree_min(z->_right);
				x = z->_right;
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
				y->set_colour(z->_colour);
			}
			if (original_colour == BLACK)
			{
				std::cout << "original colour is black\n";
				delete_fixup(x);
			}
			print_tree();
		}

		void	clear()
		{
			clear_tree(_root);
			_root = NULL;
			_size = 0;
		}

		private:

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

		void	delete_fixup(node_pointer x)
		{
			while (x != _root && x->get_colour() == BLACK)
			{
				std::cout << "in while" << std::endl;
				if (x == x->_parent->_left)
				{
					std::cout << "######### PARENT IS LEFT - NODE\n";
					node_pointer w = x->_parent->_right;
					if (x->get_colour() == RED)		// if uncle is red
					{
						std::cout << "1\n";
						w->set_colour(BLACK);
						w->_parent->set_colour(RED);
						left_rotate(x->_parent);
						w = x->_parent->_right;
					}
					if (w->_left->get_colour() == BLACK
					&& w->_right->get_colour() == BLACK)
					{
						std::cout << "2\n";
						w->set_colour(RED);
						x = x->_parent;
					}
					else if (w->_right->get_colour() == BLACK)
					{
						std::cout << "3\n";
						w->_left->set_colour(BLACK);
						w->set_colour(RED);
						right_rotate(w);
						w = x->_parent->_right;
					}
					std::cout << "4\n";
					w->set_colour(x->_parent->_colour);
					x->_parent->set_colour(BLACK);
					w->_right->set_colour(BLACK);
					left_rotate(x->_parent);
					x = _root;
				}
				else
				{
					std::cout << "######### PARENT IS RIGHT - NODE\n";
					node_pointer w = x->_parent->_left;
					if (x->get_colour() == RED)		// if uncle is red
					{
						std::cout << "1\n";
						w->set_colour(BLACK);
						w->_parent->set_colour(RED);
						left_rotate(x->_parent);
						w = x->_parent->_left;
					}
					if (w->_right->get_colour() == BLACK
					&& w->_left->get_colour() == BLACK)
					{
						std::cout << "2\n";
						w->set_colour(RED);
						x = x->_parent;
					}
					else if (w->_left->get_colour() == BLACK)
					{
						std::cout << "3\n";
						w->_right->set_colour(BLACK);
						w->set_colour(RED);
						right_rotate(w);
						w = x->_parent->_left;
					}
					std::cout << "3\n";
					w->set_colour(x->_parent->_colour);
					x->_parent->set_colour(BLACK);
					w->_left->set_colour(BLACK);
					left_rotate(x->_parent);
					x = _root;
				}
			}
			x->set_colour(BLACK);
		}

		// to rotate and recolour after insertion
		void	insert_fixup(node_pointer z)
		{
			std::cout << "-------------------------------------\n==> inserted: " << *z->_value << std::endl;
			while (z->_parent && z->_parent->get_colour() == RED)
			{
				if (z->_parent->_parent && z->_parent == z->_parent->_parent->_left) // if parent is a LEFT NODE
				{
					// std::cout << "######### PARENT IS LEFT - NODE\n";
					node_pointer y =  z->_parent->_parent->_right; 		// y is uncle of z
					
					if (y && y->get_colour() == RED)					// uncle is red
					{
						// std::cout << "1\n";
						z->_parent->set_colour(BLACK);
						y->set_colour(BLACK);
						z->_parent->_parent->set_colour(RED);
						z = z->_parent->_parent;
					}
					else if (z == z->_parent->_right)					// z is the right node
					{
						// std::cout << "2\n";
						z = z->_parent;
						left_rotate(z);
					}
					if (z->_parent && z->_parent->_parent)
					{
						// std::cout << "3\n";
						z->_parent->set_colour(BLACK);
						z->_parent->_parent->set_colour(RED);
						right_rotate(z->_parent->_parent);
					}
				}
				else if (z->_parent->_parent)							// parent is RIGHT NODE
				{
					// std::cout << "############ PARENT IS RIGHT - NODE\n";
					node_pointer y =  z->_parent->_parent->_left; 		// y is uncle of z
					
					if (y && y->get_colour() == RED)					// uncle is red
					{
						// std::cout << "1\n";
						z->_parent->set_colour(BLACK);
						y->set_colour(BLACK);
						z->_parent->_parent->set_colour(RED);
						z = z->_parent->_parent;
					}
					else if (z == z->_parent->_left)					// z is the right node
					{
						// std::cout << "2\n";
						z = z->_parent;
						right_rotate(z);
					}
					if (z->_parent && z->_parent->_parent)
					{
						// std::cout << "3\n";
						z->_parent->set_colour(BLACK);
							z->_parent->_parent->set_colour(RED);
						left_rotate(z->_parent->_parent);
					}
				}
			}

			_root->set_colour(BLACK);
			// print_tree();
		}

		void	left_rotate(node_pointer x)
		{
			std::cout << "\n<  LEFT ROTATE  >" << std::endl;
			if ( x == NULL || x->_right == NULL)
				return;

			// std::cout << "x is " << *x << std::endl;
			// std::cout << "x right (y) is " << *x->_right << std::endl;
			// std::cout << "-------------------------------\n";
	
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
			std::cout << "<  RIGHT ROTATE  >" << std::endl;
			if ( x == NULL || x->_left == NULL)
				return;
			// std::cout << "x is " << *x << std::endl;
			// std::cout << "x right (y) is " << *x << std::endl;
			// std::cout << "-------------------------------\n";

	
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

		// deallocate every element from the tree
		void	clear_tree(node_pointer node)
		{
			if (node == NULL)
				return;

			clear_tree(node->_right);
			clear_tree(node->_left);
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
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
		}

		void print_tree()
		{
			std::cout << "<  THE WHOLE TREE  >" << std::endl;
			print_tree(_root , NULL, false);
		}
		
	};

}	// namespace ft


#endif


