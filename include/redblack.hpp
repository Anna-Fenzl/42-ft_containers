/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redblack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:17:48 by afenzl            #+#    #+#             */
/*   Updated: 2023/02/06 17:03:33 by afenzl           ###   ########.fr       */
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

		typedef _Compare								value_compare;
		typedef _Val									value_type;
		typedef const _Val								const_value_type;
		typedef _Val*									value_pointer;
		typedef const _Val*								const_value_pointer;
		typedef _Val&									value_reference;
		typedef const _Val&								const_value_reference;
		typedef RbtNode<_Val>							node_type;
		typedef RbtNode<_Val>*							node_pointer;
		typedef const RbtNode<_Val>*					const_node_pointer;

		typedef	size_t									size_type;
		typedef	ptrdiff_t								difference_type;

		// iterators
		typedef ft::Rbt_Iterator<value_type>			iterator;
		typedef ft::Const_Rbt_Iterator<value_type>		const_iterator;
		
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< MEMBER_VARIABLES >>>>>>>>>>>>>>>>>>
		node_pointer	_nil;
		protected:
		node_pointer	_root;

		size_type		_size;
		node_alloc		_node_alloc;
		value_compare	_compare;

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< METHODS >>>>>>>>>>>>>>>>>>>>>>>>>>

		public:
		// ----------------------- CONSTRUCTOR --------------------
		// default constructor
		Redblack_Tree(): _size(0), _compare(_Compare()), _node_alloc(std::allocator<RbtNode<value_type> >())
		{
			alloc_nil();
			_root = _nil;
		}
		
		// copy_constructor
		Redblack_Tree(const Redblack_Tree& src)
		{
			alloc_nil();
			_root = _nil;

			*this = src;
		}

		~Redblack_Tree()
		{
			clear();
			_node_alloc.deallocate(_nil, 1);
		}

		// ----------------------- OPERATOR ----------------------

		Redblack_Tree& operator=(const Redblack_Tree& other )
		{
			if (this != &other)
			{
				clear();
				_root = copy_tree(other._root, other._nil, other._nil);
				_size = other._size;
				_node_alloc = other._node_alloc;
				_compare = other._compare;
			}
			return *this;
		}
		
		// ----------------------- ITERATORS ----------------------

		iterator		begin() 			{ return iterator(red_black_tree_min(_root)); };
		
		const_iterator	begin() const		{ return const_iterator(red_black_tree_min(_root)); };
		
		iterator		end()				{ return iterator(_nil); };

		const_iterator	end() const			{ return const_iterator(_nil); };

		
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
			move->_nil = move->_left;
			
			insert_fixup(move);
			++_size;
			return (ft::make_pair(find(value), true));
		}

		size_type	erase(iterator pos)
		{
			if (pos == end())
				return 0;
			node_pointer	z = pos.base();
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
			delete_node(z);
			if (original_colour == BLACK) {
				erase_fixup(x);
			}
			--_size;
			return 1;
		}

		iterator find (const value_type& value)
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

		const_iterator find (const value_type& value) const
		{
			node_pointer move = _root;
			while (move && move != _nil)
			{
				if (_compare(*move->_value, value))
					move = move->_right;
				else if (_compare(value, *move->_value))
					move = move->_left;
				else
					return(const_iterator(move));
			}
			return(end());
		}

		void	swap( Redblack_Tree& other )
		{
			ft::swap(_node_alloc, other._node_alloc);
			ft::swap(_compare, other._compare);
			ft::swap(_size, other._size);
			ft::swap(_root, other._root);
			ft::swap(_nil, other._nil);
		}

		void	clear()
		{
			clear_tree(_root);
			_root = _nil;
			_size = 0;
		}

		// ----------------------- LOOKUP ------------------------

		iterator	lower_bound(const value_type& value)
		{
			iterator it = begin();
			for(; _compare(*it, value); ++it)
				continue;
			return it;
		}

		const_iterator	lower_bound(const value_type& value) const
		{
			const_iterator it = begin();
			for(; _compare(*it, value); ++it)
				continue;
			return it;
		}

		iterator	upper_bound(const value_type& value)
		{
			iterator it = lower_bound(value);
			if (is_equal(*it, value))
				++it;
			return it;
		}

		const_iterator	upper_bound(const value_type& value) const
		{
			iterator it = lower_bound(value);
			if (is_equal(*it, value))
				++it;
			return it;
		}

		ft::pair<iterator,iterator> equal_range( const value_type& value)
		{
			return (ft::make_pair(lower_bound(value), upper_bound(value)));
		}

		ft::pair<const_iterator,const_iterator> equal_range( const value_type& value) const
		{
			return (ft::make_pair(lower_bound(value), upper_bound(value)));
		}

		// ----------------------- PRIVATE METHODS ------------------------

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
					else
					{
						if (w->_right->get_colour() == BLACK)
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
				}
				else
				{
					w = x->_parent->_left;
					if (w->get_colour() == RED)
					{
						w->set_colour(BLACK);
						x->_parent->set_colour(RED);
						right_rotate(x->_parent);
						w = x->_parent->_left;
					}
					if (w->_right->get_colour() == BLACK && w->_left->get_colour() == BLACK)
					{
						w->set_colour(RED);
						x = x->_parent;
					}
					else
					{
						if (w->_left->get_colour() == BLACK)
						{
							w->_right->set_colour(BLACK);
							w->set_colour(RED);
							left_rotate(w);
							w = x->_parent->_left;
						}
						w->set_colour(x->_parent->_colour);
						x->_parent->set_colour(BLACK);
						w->_left->set_colour(BLACK);
						right_rotate(x->_parent);
						x = _root;
					}
				}
			}
			x->_colour = BLACK;
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

		bool is_equal(value_type value, value_type comp)
		{
			return (!_compare(value, comp) && !_compare(comp, value));
		}
		
		node_pointer	allocate_node(node_pointer src)
		{
			node_pointer node = _node_alloc.allocate(1);
			
			RbtNode<value_type>	set_node(*src->_value, src->_parent, _nil, src->get_colour());
			_node_alloc.construct(node, set_node);
			return (node);
		}

		void	alloc_nil()
		{
			_nil = _node_alloc.allocate(1);
			_nil->set_colour(BLACK);
			_nil->_left = _nil;
			_nil->_right = _nil;
		}

		void	delete_node(node_pointer node)
		{
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
			node = NULL;
		}

		node_pointer	copy_tree(node_pointer node, node_pointer parent, node_pointer nil)
		{
			if (node == nil )
				return _nil;

 			node_pointer	new_node = allocate_node(node);
			new_node->_left = copy_tree(node->_left, new_node, nil);
			new_node->_right = copy_tree(node->_right, new_node ,nil);
			return new_node;
		}
		
		void	clear_tree(node_pointer node)
		{
			if (node == _nil || node == NULL || node == node->_left || node == node->_right)
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
