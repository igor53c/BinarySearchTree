#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace binary_search_tree
{
template <typename T>
struct binary_tree
{
    T                               data_;
    std::unique_ptr<binary_tree<T>> left_;
    std::unique_ptr<binary_tree<T>> right_;

    std::unique_ptr<binary_tree<T>> &left() { return left_; }

    std::unique_ptr<binary_tree<T>> &right() { return right_; }

    T data() { return data_; }

    void insert(T data)
    {
        if (data < data_)
        {
            if (!left_)
            {
                left_ = std::make_unique<binary_tree<T>>(data);
            }
            else
            {
                left_->insert(data);
            }
        }
        else
        {
            if (!right_)
            {
                right_ = std::make_unique<binary_tree<T>>(data);
            }
            else
            {
                right_->insert(data);
            }
        }
    }

    binary_tree<T>(T data) : data_(data), left_(nullptr), right_(nullptr) {}

    binary_tree<T>() : data_(T()), left_(nullptr), right_(nullptr) {}

    struct iterator
    {
        binary_tree<T>               *current_;
        std::vector<binary_tree<T> *> stack_;

        bool operator==(iterator other) const { return current_ == other.current_; }
        bool operator!=(iterator other) const { return current_ != other.current_; }

        void operator++()
        {
            if (!current_ && stack_.empty())
            {
                return;
            }

            if (current_ && current_->right_)
            {
                current_ = current_->right_.get();
                while (current_ && current_->left_)
                {
                    stack_.push_back(current_);
                    current_ = current_->left_.get();
                }
            }
            else
            {
                while (!stack_.empty() && current_ == stack_.back()->right_.get())
                {
                    current_ = stack_.back();
                    stack_.pop_back();
                }
                if (!stack_.empty())
                {
                    current_ = stack_.back();
                    stack_.pop_back();
                }
                else
                {
                    current_ = nullptr;
                }
            }
        }
        const T &operator*()
        {
            if (current_)
                return current_->data_;
            else
                throw std::runtime_error("Dereferencing null iterator");
        }
        iterator() : current_(nullptr) {}
        iterator(binary_tree<T> *tree_pointer) : current_(tree_pointer)
        {
            if (current_)
            {
                while (current_->left_)
                {
                    stack_.push_back(current_);
                    current_ = current_->left_.get();
                }
            }
        }
        iterator(const iterator &tree_iterator) : current_(tree_iterator.current_), stack_(tree_iterator.stack_) {}
    };

    const iterator begin()
    {
        binary_tree<T> *current = this;
        while (current && current->left_)
        {
            current = current->left_.get();
        }
        return iterator(current);
    }
    const iterator end() { return iterator(nullptr); }
};
} // namespace binary_search_tree

template <typename T>
bool testBinarySearchTree()
{
    std::cout << "Početak testa binarnog stabla pretrage.\n";

    // Test case 1: Binary Search Tree with uint32_t values
    binary_search_tree::binary_tree<uint32_t> intTree(4);
    intTree.insert(2);
    intTree.insert(4);
    intTree.insert(5);
    intTree.insert(6);
    intTree.insert(1);
    intTree.insert(3);
    intTree.insert(7);

    std::cout << "Početak iteracije za test slučaj 1.\n";

    auto intIterator = intTree.begin();
    for (; intIterator != intTree.end(); ++intIterator)
    {
        if (intIterator != intTree.end())
        {
            std::cout << "Trenutna vrednost iteratora: " << *intIterator << '\n';
        }
        else
        {
            std::cerr << "Greška: Iterator pokazuje na kraj pre očekivanog vremena.\n";
            return false;
        }
    }
    std::cout << "Kraj iteracije za test slučaj 1.\n";

    // Test case 2: Binary Search Tree with std::string values
    binary_search_tree::binary_tree<std::string> strTree("delicious");
    strTree.insert("ballon");
    strTree.insert("flag");
    strTree.insert("apple");
    strTree.insert("cat");
    strTree.insert("elispsis");
    strTree.insert("grains");

    std::cout << "Početak iteracije za test slučaj 2.\n";

    auto strIterator = strTree.begin();
    for (; strIterator != strTree.end(); ++strIterator)
    {
        if (strIterator != strTree.end())
        {
            std::cout << "Trenutna vrednost iteratora: " << *strIterator << '\n';
        }
        else
        {
            std::cerr << "Greška: Iterator pokazuje na kraj pre očekivanog vremena.\n";
            return false;
        }
    }
    std::cout << "Kraj iteracije za test slučaj 2.\n";

    if (intIterator == intTree.end() && strIterator == strTree.end())
    {
        std::cout << "Test binarnog stabla pretrage uspešno završen.\n";
        return true;
    }
    else
    {
        std::cout << "Test binarnog stabla pretrage nije prošao.\n";
        return false;
    }
}

int main()
{
    if (testBinarySearchTree<uint32_t>() && testBinarySearchTree<std::string>())
    {
        std::cout << "Binary Search Tree tests passed!" << std::endl;
    }
    else
    {
        std::cout << "Binary Search Tree tests failed!" << std::endl;
    }

    return 0;
}
