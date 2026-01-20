#include <cassert>
#include <iostream>
#define CHECK assert(Invariant());

using namespace std;

template <typename T>
class Vector
{
private:
    T *_data;
    size_t _size;
    size_t _capacity;

    //Reallocate memory
    void reallocate(size_t _newCapacity)
    {
        T *newData = new T[_newCapacity];
        for (int i = 0; i < _size; i++)
        {
            newData[i] = _data[i];
        }
        delete[] _data;
        _data = newData;
        _capacity = _newCapacity;
    }

public:
    friend void swap(Vector &lhs, Vector &rhs);

    // Iterators
    using iterator = T *;
    using const_iterator = const T *;

    // reverse iterators
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    //returns reference to first element
    iterator begin() noexcept
    {
        return &_data[0];
    }

    iterator end() noexcept
    {
        return &_data[_size];
    }

    const_iterator begin() const noexcept
    {
        return &_data[0];
    }
    const_iterator end() const noexcept
    {
        return &_data[_size];
    }

    const_iterator cbegin() const noexcept
    {
        return &_data[0];
    }
    const_iterator cend() const noexcept
    {
        return &_data[_size];
    }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }
    const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    // Default constructor - initializes an empty vector
    Vector() : _data(nullptr), _size(0), _capacity(0) {}

    // Constructor that initializes vector from a C-string
    Vector(const char *other)
    {
        size_t len = strlen(other);
        _data = new T[len];
        _size = len;
        _capacity = len;
        for (int i = 0; i < len; i++)
        {
            _data[i] = other[i];
        }
    }

    // Copy constructor
    Vector(const Vector &other)
    {
        size_t len = other.size();
        _data = new T[len];
        _size = len;
        _capacity = len;
        for (int i = 0; i < len; i++)
        {
            _data[i] = other[i];
        }
    }

    // Move constructor
    Vector(Vector &&other) noexcept
    {
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    // Destructor - deallocates the dynamically allocated memory
    ~Vector()
    {
        delete[] _data;
    }

    // Public resize - changes size to n, fills with T() if growing
    void resize(size_t n)
    {
        if (n > _capacity)
        {
            reserve(n);
        }
        if (n > _size)
        {
            for (int i = _size; i < n; i++)
            {
                _data[i] = T();
            }
        }
        _size = n;
    }

    // Adds an element to the end of the vector, resizing if necessary
    void push_back(const T &value)
    {
        if (_size == _capacity)
        {
            reallocate(_capacity == 0 ? 1 : _capacity * 2);
        }
        _data[_size++] = value;
    }

    // Removes the last element from the vector
    void pop_back()
    {
        if (_size > 0)
        {
            _size--;
        }
    }

    // Allocate more memory
    void reserve(size_t n)
    {
        if (n > _capacity)
        {
            reallocate(n);
        }
    }

    // Shrink so that size = capacity
    void shrink_to_fit()
    {
        if (_size != _capacity)
        {
            reallocate(_size);
        }
    }

    // Returns the number of elements currently in the vector
    size_t size() const { return _size; }

    // Returns the total allocated capacity of the vector
    size_t capacity() const { return _capacity; }

    // Returns pointer to internal array
    T *data() noexcept { return _data; }

    // Returns const pointer to internal array
    const T *data() const noexcept { return _data; }

    // Const subscript operator - provides read-only access to elements by index
    const T &operator[](size_t i) const { return _data[i]; }

    // Non-const subscript operator - provides write access to elements by index
    T &operator[](size_t i) { return _data[i]; }

    // Copy assignment
    Vector &operator=(const Vector &other)
    {
        if (this == &other)
        {
            return *this;
        }
        delete[] _data;
        size_t len = other.size();
        _data = new T[len];
        _size = len;
        _capacity = len;
        for (int i = 0; i < len; i++)
        {
            _data[i] = other[i];
        }
        return *this;
    }

    // Move assignment
    Vector &operator=(Vector &&other) noexcept
    {
        if (this != &other)
        {
            delete[] _data;
            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;
            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    // Const at() method - provides safe read-only access with bounds checking
    const T &at(size_t i) const
    {
        if (i >= _size)
            throw std::out_of_range("Index out of range");
        return _data[i];
    }

    // Non-const at() method - provides safe write access with bounds checking
    T &at(size_t i)
    {
        if (i >= _size)
            throw std::out_of_range("Index out of range");
        return _data[i];
    }

    // Equality operator - checks if two vectors are equal
    friend bool operator==(const Vector &lhs, const Vector &other)
    {
        if (lhs.size() != other.size())
            return false;
        for (int i = 0; i < lhs.size(); i++)
        {
            if (lhs[i] != other[i])
                return false;
        }
        return true;
    }

    // Inequality operator - checks if two vectors are not equal
    friend bool operator!=(const Vector &lhs, const Vector &other)
    {
        return !(lhs == other);
    }

    // Less than operator - lexicographically compares two vectors
    friend bool operator<(const Vector &lhs, const Vector &other)
    {
        size_t minSize = (lhs.size() < other.size()) ? lhs.size() : other.size();
        for (int i = 0; i < minSize; i++)
        {
            if (lhs[i] < other[i])
                return true;
            if (lhs[i] > other[i])
                return false;
        }
        return lhs.size() < other.size();
    }

    // Greater than operator - checks if lhs is greater than other
    friend bool operator>(const Vector &lhs, const Vector &other)
    {
        return other < lhs;
    }

    // Less than or equal operator
    friend bool operator<=(const Vector &lhs, const Vector &other)
    {
        return lhs < other || lhs == other;
    }

    // Greater than or equal operator
    friend bool operator>=(const Vector &lhs, const Vector &other)
    {
        return other < lhs || lhs == other;
    }

    // Stream output operator - allows printing the vector to an output stream
    friend std::ostream &operator<<(std::ostream &cout, const Vector &other)
    {
        for (size_t i = 0; i < other.size(); ++i)
            cout << other[i];
        return cout;
    }

    // Invariant check - verifies the internal consistency of the vector
    bool Invariant() const
    {
        // 1. Size should never exceed capacity
        if (_size > _capacity)
            return false;
        // 2. If capacity is 0, data should be nullptr
        if (_capacity == 0 && _data != nullptr)
            return false;
        // 3. If capacity is > 0, data should not be nullptr
        if (_capacity > 0 && _data == nullptr)
            return false;
        return true;
    }
};

template <class T>
// Friend method of Vector to swap the values between to vectors
void swap(Vector<T> &lhs, Vector<T> &rhs)
{
    T *tempData = lhs._data;
    lhs._data = rhs._data;
    rhs._data = tempData;

    size_t tempSize = lhs._size;
    lhs._size = rhs._size;
    rhs._size = tempSize;

    size_t tempCapacity = lhs._capacity;
    lhs._capacity = rhs._capacity;
    rhs._capacity = tempCapacity;
}