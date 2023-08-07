#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <stack>
#include <string>

namespace binary_search_tree
{
    template <typename T>
    struct binary_tree
    {

    private:
        T                               _data;
        std::unique_ptr<binary_tree<T>> _left;
        std::unique_ptr<binary_tree<T>> _right;

    public:
        std::unique_ptr<binary_tree<T>>& left() { return _left; }

        std::unique_ptr<binary_tree<T>>& right() { return _right; }

        T data() { return _data; }

        void insert(T data)
        {
            if (data <= _data)
            {
                if (!_left)
                {
                    _left = std::make_unique<binary_tree<T>>(data);
                }
                else
                {
                    _left->insert(data);
                }
            }
            else
            {
                if (!_right)
                {
                    _right = std::make_unique<binary_tree<T>>(data);
                }
                else
                {
                    _right->insert(data);
                }
            }
        }

        binary_tree<T>(T data) : _data(data), _left(nullptr), _right(nullptr) {}

        binary_tree<T>() : _data(T()), _left(nullptr), _right(nullptr) {}

        struct iterator
        {

            std::stack<binary_tree<T>*> _stack;

            void push_left(binary_tree<T>* node)
            {
                while (node)
                {
                    _stack.push(node);
                    node = node->_left.get();
                }
            }

            bool operator==(iterator other) const { return _stack == other._stack; }
            bool operator!=(iterator other) const { return _stack != other._stack; }

            void operator++()
            {
                if (_stack.empty()) return;

                binary_tree<T>* node = _stack.top();
                _stack.pop();

                push_left(node->_right.get());
            }

            const T& operator*() { return _stack.top()->_data; }

            iterator() : _stack() {}

            iterator(binary_tree<T>* tree_pointer) { push_left(tree_pointer); }

            iterator(const iterator& tree_iterator) : _stack(tree_iterator._stack) {}
        };

        const iterator begin() { return iterator(this); }
        const iterator end() { return iterator(nullptr); }
    };
} // namespace binary_search_tree

void testScenario1()
{
    using namespace binary_search_tree;

    // Test 1: Initialization of the tree with uint32_t value 4
    binary_tree<uint32_t> tree1(4);
    assert(tree1.data() == 4);

    // Test 2: Insert 2 into the tree
    tree1.insert(2);
    assert(tree1.left()->data() == 2);

    // Test 3: Insert 4 into the tree
    binary_tree<uint32_t> tree2(4);
    tree2.insert(4);
    assert(tree2.left()->data() == 4);

    // Test 4: Insert 5 into the tree
    binary_tree<uint32_t> tree3(4);
    tree3.insert(5);
    assert(tree3.right()->data() == 5);

    // Test 5: Insert a sequence of elements into the tree
    binary_tree<uint32_t> tree4(4);
    tree4.insert(2);
    tree4.insert(6);
    tree4.insert(1);
    tree4.insert(3);
    tree4.insert(5);
    tree4.insert(7);
    assert(tree4.data() == 4);
    assert(tree4.left()->data() == 2);
    assert(tree4.right()->data() == 6);
    assert(tree4.left()->left()->data() == 1);
    assert(tree4.left()->right()->data() == 3);
    assert(tree4.right()->left()->data() == 5);
    assert(tree4.right()->right()->data() == 7);

    // Test 6: Insert string values into the tree
    binary_tree<std::string> tree5("delicious");
    tree5.insert("ballon");
    tree5.insert("flag");
    tree5.insert("apple");
    tree5.insert("cat");
    tree5.insert("elispsis");
    tree5.insert("grains");
    assert(tree5.data() == "delicious");
    assert(tree5.left()->data() == "ballon");
    assert(tree5.right()->data() == "flag");
    assert(tree5.left()->left()->data() == "apple");
    assert(tree5.left()->right()->data() == "cat");
    assert(tree5.right()->left()->data() == "elispsis");
    assert(tree5.right()->right()->data() == "grains");
}

void testScenario2()
{
    using namespace binary_search_tree;

    // Test 1: Iteration over a tree with a single node
    binary_tree<uint32_t> tree1(4);
    auto                  it1 = tree1.begin();
    assert(*it1 == 4);

    // Test 2: Iteration over a complex tree
    binary_tree<uint32_t> tree2(4);
    tree2.insert(2);
    tree2.insert(6);
    tree2.insert(1);
    tree2.insert(3);
    tree2.insert(5);
    tree2.insert(7);
    auto it2 = tree2.begin();
    assert(*it2 == 1);
    ++it2;
    assert(*it2 == 2);
    ++it2;
    assert(*it2 == 3);
    ++it2;
    assert(*it2 == 4);
    ++it2;
    assert(*it2 == 5);
    ++it2;
    assert(*it2 == 6);
    ++it2;
    assert(*it2 == 7);

    // Test 3: Iteration over trees with two nodes
    binary_tree<uint32_t> tree3(2);
    tree3.insert(1);
    auto it3 = tree3.begin();
    assert(*it3 == 1);
    ++it3;
    assert(*it3 == 2);

    binary_tree<uint32_t> tree4(2);
    tree4.insert(2);
    auto it4 = tree4.begin();
    assert(*it4 == 2);
    ++it4;
    assert(*it4 == 2);

    binary_tree<uint32_t> tree5(2);
    tree5.insert(3);
    auto it5 = tree5.begin();
    assert(*it5 == 2);
    ++it5;
    assert(*it5 == 3);

    // Test 4: Iteration over a tree with string values
    binary_tree<std::string> tree6("A");
    tree6.insert("few");
    tree6.insert("random");
    tree6.insert("strings");
    tree6.insert("that");
    tree6.insert("should");
    tree6.insert("be");
    tree6.insert("sorted");
    auto itStr = tree6.begin();
    assert(*itStr == "A");
    ++itStr;
    assert(*itStr == "be");
    ++itStr;
    assert(*itStr == "few");
    ++itStr;
    assert(*itStr == "random");
    ++itStr;
    assert(*itStr == "should");
    ++itStr;
    assert(*itStr == "sorted");
    ++itStr;
    assert(*itStr == "strings");
    ++itStr;
    assert(*itStr == "that");
}

int main()
{
    testScenario1();
    testScenario2();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
