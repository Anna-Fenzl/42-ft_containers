# 42-ft_containers
This was a project for [42Heilbronn](https://www.42heilbronn.de/en/curriculum/) school's curriculum.

The goal of this project is to __implement the STL containers__ - vector, map, stack and set - as well as some additional utilities.  
The containers are implemented in the ft namespace and use std::allocator as the default allocator.
They are designed to be compatible with the STL containers and include all the member functions, non-member functions, and overloads of the standard containers.

## Implementations
+ __vector__: Implementation of the vector container.
+ __map__: Implementation of the map container.
+ __stack__: Implementation of the stack container.
+ __iterator_traits__: Implementation of std::iterator_traits.
+ __reverse_iterator__: Implementation of std::reverse_iterator.
+ __enable_if__ Implementation of std::enable_if.
+ __is_integral__: Implementation of std::is_integral.
+ __equal__: Implementation of std::equal.
+ __lexicographical_compare__: Implementation of std::lexicographical_compare.
+ __pair__: Implementation of std::pair.
+ __make_pair__: Implementation of std::make_pair.

The underlying data structure of map and set is a [red-black-tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree).

## Description
**run _`make`_**

This creates two executables: ft_containers and std_containers.

by running `./compare.sh` the outputs of both binaries are compared.

by running `./speedtest.sh` the runtimes of both programs are compared.
