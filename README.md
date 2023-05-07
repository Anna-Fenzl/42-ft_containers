# 42-ft_containers
This was a project for [42Heilbronn](https://www.42heilbronn.de/en/curriculum/) school's curriculum.

The goal of this project is to __implement the STL containers__ - vector, map, stack and set - as well as some additional utilities.  
The containers are implemented in the ft namespace and use std::allocator as the default allocator.
They are designed to be compatible with the STL containers and include all the member functions, non-member functions, and overloads of the standard containers.

## Implementations
+ __vector__: Implementation of the [vector container](https://cplusplus.com/reference/vector/vector/).
+ __map__: Implementation of the [map container](https://cplusplus.com/reference/map/map/?kw=map).
+ __stack__: Implementation of the [stack container](https://cplusplus.com/reference/stack/stack/?kw=stack).
+ __set__: Implementation of the [set container](https://cplusplus.com/reference/set/set/?kw=set).
+ __iterator_traits__: Implementation of [std::iterator_traits](https://cplusplus.com/reference/iterator/iterator_traits/).
+ __reverse_iterator__: Implementation of [std::reverse_iterator](https://cplusplus.com/reference/iterator/reverse_iterator/?kw=reverse_iterator).
+ __enable_if__ Implementation of [std::enable_if](https://cplusplus.com/reference/type_traits/enable_if/?kw=enable_if).
+ __is_integral__: Implementation of [std::is_integral](https://cplusplus.com/reference/type_traits/is_integral/?kw=is_integral).
+ __equal__: Implementation of [std::equal](https://cplusplus.com/reference/algorithm/equal/?kw=equal).
+ __lexicographical_compare__: Implementation of [std::lexicographical_compare](https://cplusplus.com/reference/algorithm/lexicographical_compare/).
+ __pair__: Implementation of [std::pair](https://cplusplus.com/reference/utility/pair/pair/).
+ __make_pair__: Implementation of [std::make_pair](https://cplusplus.com/reference/utility/make_pair/).

The underlying data structure of map and set is a [red-black-tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree).

<img width="589" alt="Screen Shot 2023-05-07 at 8 12 52 PM" src="https://user-images.githubusercontent.com/102963812/236695182-f277f7fc-86c7-4e12-9e1b-432863c7a2f0.png">

## Description
**run _`make`_**

This creates two executables: ft_containers and std_containers.

by running `./compare.sh` the outputs of both binaries are compared.

by running `./speedtest.sh` the runtimes of both programs are compared.

All the implemantations are located in the include folder.
