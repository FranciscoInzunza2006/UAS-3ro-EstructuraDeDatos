
add_library(Node node.hpp)
add_library(BST binary_search_tree.cpp binary_search_tree.hpp)
target_link_libraries(BST PUBLIC Node)
target_include_directories(BST PUBLIC .)