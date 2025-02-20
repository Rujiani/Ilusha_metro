#ifndef LOOK_UP_TABLE
#define LOOK_UP_TABLE

#include <stdexcept>
#include <utility>
#include <type_traits>
#include <concepts>

namespace mgc{
/**
 * @file lookup_table.cpp
 * @brief A self-contained implementation of a LookupTable class in C++20.
 *
 * This file defines a template class LookupTable that stores key-value pairs
 * in a dynamically allocated array (using new/delete). The container is
 * unsorted so that search operations are O(n) via linear iteration.
 * Custom iterators (both mutable and const) are implemented for iteration.
 * The class supports various methods (at, operator[], front, back, data, begin,
 * end, cbegin, cend, empty, size, capacity, reserve, clear, insert, emplace,
 * erase, and find) with Doxygen-style comments.
 */
 


 /**
  * @brief Concept ensuring that Key and Value types meet basic requirements.
  *
  * Key must be copy constructible and support equality comparison.
  * Value must be copy constructible.
  *
  * @tparam Key Type of the key.
  * @tparam Value Type of the value.
  */
 template <typename Key, typename Value>
 concept LookupTableKeyValueConcept =
     std::is_copy_constructible_v<Key> &&
     std::is_copy_constructible_v<Value> &&
     requires(Key a, Key b) {
         { a == b } -> std::convertible_to<bool>;
     };
 
 /**
  * @brief LookupTable class template storing key-value pairs.
  *
  * The container uses a dynamically allocated array to store pairs
  * in an unsorted order. Insertion appends new elements, and search
  * operations run in O(n) time.
  *
  * @tparam Key Type of the key.
  * @tparam Value Type of the value.
  */
 template <typename Key, typename Value>
     requires LookupTableKeyValueConcept<Key, Value>
 class LookupTable {
 public:
     using PairType = std::pair<Key, Value>;
 
     /**
      * @brief Default constructor.
      */
     LookupTable() : m_size(0), m_capacity(0), data_(nullptr) {}
 
     /**
      * @brief Destructor.
      *
      * Calls clear() to destroy all elements and deallocates the internal storage.
      */
     ~LookupTable() {
         clear();
         operator delete(data_);
     }
 
     /**
      * @brief Copy constructor.
      * @param other Another LookupTable to copy from.
      */
     LookupTable(const LookupTable& other)
         : m_size(other.m_size), m_capacity(other.m_capacity) {
         if (m_capacity > 0) {
             data_ = reinterpret_cast<PairType*>(operator new(m_capacity * sizeof(PairType)));
             for (size_t i = 0; i < m_size; ++i) {
                 new (&data_[i]) PairType(other.data_[i]);
             }
         } else {
             data_ = nullptr;
         }
     }
 
     /**
      * @brief Copy assignment operator.
      * @param other Another LookupTable to copy from.
      * @return Reference to this LookupTable.
      */
     LookupTable& operator=(const LookupTable& other) {
         if (this != &other) {
             clear();
             if (other.m_capacity != m_capacity) {
                 operator delete(data_);
                 m_capacity = other.m_capacity;
                 data_ = (m_capacity > 0)
                             ? reinterpret_cast<PairType*>(operator new(m_capacity * sizeof(PairType)))
                             : nullptr;
             }
             m_size = other.m_size;
             for (size_t i = 0; i < m_size; ++i) {
                 new (&data_[i]) PairType(other.data_[i]);
             }
         }
         return *this;
     }
 
     /**
      * @brief Move constructor.
      * @param other Another LookupTable to move from.
      */
     LookupTable(LookupTable&& other) noexcept
         : m_size(other.m_size), m_capacity(other.m_capacity), data_(other.data_) {
         other.data_ = nullptr;
         other.m_size = 0;
         other.m_capacity = 0;
     }
 
     /**
      * @brief Move assignment operator.
      * @param other Another LookupTable to move from.
      * @return Reference to this LookupTable.
      */
     LookupTable& operator=(LookupTable&& other) noexcept {
         if (this != &other) {
             clear();
             operator delete(data_);
             data_ = other.data_;
             m_size = other.m_size;
             m_capacity = other.m_capacity;
             other.data_ = nullptr;
             other.m_size = 0;
             other.m_capacity = 0;
         }
         return *this;
     }
 
     /**
      * @brief Returns a reference to the element at the specified index with bounds checking.
      * @param index Position of the element.
      * @return Reference to the pair at the specified index.
      * @throws std::out_of_range if index is out of bounds.
      */
     PairType& at(size_t index) {
         if (index >= m_size) {
             throw std::out_of_range("Index out of range in LookupTable::at");
         }
         return data_[index];
     }
 
     /**
      * @brief Returns a constant reference to the element at the specified index with bounds checking.
      * @param index Position of the element.
      * @return Constant reference to the pair at the specified index.
      * @throws std::out_of_range if index is out of bounds.
      */
     const PairType& at(size_t index) const {
         if (index >= m_size) {
             throw std::out_of_range("Index out of range in LookupTable::at");
         }
         return data_[index];
     }
 
     /**
      * @brief Returns a reference to the element at the specified index without bounds checking.
      * @param index Position of the element.
      * @return Reference to the pair at the specified index.
      */
     PairType& operator[](size_t index) {
         return data_[index];
     }
 
     /**
      * @brief Returns a constant reference to the element at the specified index without bounds checking.
      * @param index Position of the element.
      * @return Constant reference to the pair at the specified index.
      */
     const PairType& operator[](size_t index) const {
         return data_[index];
     }
 
     /**
      * @brief Returns a reference to the first element.
      * @return Reference to the first pair.
      * @throws std::out_of_range if the container is empty.
      */
     PairType& front() {
         if (empty()) {
             throw std::out_of_range("LookupTable is empty in front()");
         }
         return data_[0];
     }
 
     /**
      * @brief Returns a constant reference to the first element.
      * @return Constant reference to the first pair.
      * @throws std::out_of_range if the container is empty.
      */
     const PairType& front() const {
         if (empty()) {
             throw std::out_of_range("LookupTable is empty in front()");
         }
         return data_[0];
     }
 
     /**
      * @brief Returns a reference to the last element.
      * @return Reference to the last pair.
      * @throws std::out_of_range if the container is empty.
      */
     PairType& back() {
         if (empty()) {
             throw std::out_of_range("LookupTable is empty in back()");
         }
         return data_[m_size - 1];
     }
 
     /**
      * @brief Returns a constant reference to the last element.
      * @return Constant reference to the last pair.
      * @throws std::out_of_range if the container is empty.
      */
     const PairType& back() const {
         if (empty()) {
             throw std::out_of_range("LookupTable is empty in back()");
         }
         return data_[m_size - 1];
     }
 
     /**
      * @brief Returns a pointer to the underlying data.
      * @return Pointer to the internal array of pairs.
      */
     PairType* data() {
         return data_;
     }
 
     /**
      * @brief Returns a constant pointer to the underlying data.
      * @return Constant pointer to the internal array of pairs.
      */
     const PairType* data() const {
         return data_;
     }
 
     /**
      * @brief Checks whether the container is empty.
      * @return true if the container is empty, false otherwise.
      */
     bool empty() const {
         return m_size == 0;
     }
 
     /**
      * @brief Returns the number of elements in the container.
      * @return Number of pairs stored.
      */
     size_t size() const {
         return m_size;
     }
 
     /**
      * @brief Returns the current capacity of the container.
      * @return Capacity of the internal storage.
      */
     size_t capacity() const {
         return m_capacity;
     }
 
     /**
      * @brief Increases the capacity of the container.
      *
      * If new_cap is greater than the current capacity, the internal storage
      * is reallocated with the new capacity and existing elements are moved.
      *
      * @param new_cap The new capacity to reserve.
      */
     void reserve(size_t new_cap) {
         if (new_cap > m_capacity) {
             PairType* new_data = reinterpret_cast<PairType*>(operator new(new_cap * sizeof(PairType)));
             // Move construct new elements into new storage
             for (size_t i = 0; i < m_size; ++i) {
                 new (&new_data[i]) PairType(std::move(data_[i]));
                 data_[i].~PairType();
             }
             operator delete(data_);
             data_ = new_data;
             m_capacity = new_cap;
         }
     }
 
     /**
      * @brief Clears the container, destroying all elements.
      *
      * The capacity remains unchanged.
      */
     void clear() {
         for (size_t i = 0; i < m_size; ++i) {
             data_[i].~PairType();
         }
         m_size = 0;
     }
 
     /**
      * @brief Inserts a new element at the end of the container.
      *
      * If there is not enough capacity, reserve() is called to expand storage.
      *
      * @param key The key of the element.
      * @param value The value of the element.
      */
     void insert(const Key& key, const Value& value) {
         if (m_size == m_capacity) {
             reserve(m_capacity == 0 ? 1 : m_capacity * 2);
         }
         new (&data_[m_size]) PairType(key, value);
         ++m_size;
     }
 
     /**
      * @brief Constructs and inserts a new element at the end of the container.
      *
      * Uses perfect forwarding to construct the pair in place.
      *
      * @tparam Args Variadic template parameters for constructing PairType.
      * @param args Arguments to forward to the PairType constructor.
      */
     template <typename... Args>
     void emplace(Args&&... args) {
         if (m_size == m_capacity) {
             reserve(m_capacity == 0 ? 1 : m_capacity * 2);
         }
         new (&data_[m_size]) PairType(std::forward<Args>(args)...);
         ++m_size;
     }
 
     /**
      * @brief Erases the element at the specified index.
      *
      * The elements following the erased element are shifted to fill the gap.
      *
      * @param index Position of the element to erase.
      * @throws std::out_of_range if index is out of bounds.
      */
     void erase(size_t index) {
         if (index >= m_size) {
             throw std::out_of_range("Index out of range in LookupTable::erase");
         }
         data_[index].~PairType();
         // Shift remaining elements to fill the gap.
         for (size_t i = index; i < m_size - 1; ++i) {
             new (&data_[i]) PairType(std::move(data_[i + 1]));
             data_[i + 1].~PairType();
         }
         --m_size;
     }
 
     /**
      * @brief Finds the index of the element with the specified key.
      *
      * Performs a linear search (O(n)) over the elements.
      *
      * @param key The key to search for.
      * @return The index of the element if found; otherwise, returns size().
      */
     size_t find(const Key& key) const {
         for (size_t i = 0; i < m_size; ++i) {
             if (data_[i].first == key) {
                 return i;
             }
         }
         return m_size; // Not found
     }
 
     /**
      * @brief Erases the element with the specified key.
      *
      * @param key The key of the element to erase.
      * @return true if an element was erased, false otherwise.
      */
     bool erase(const Key& key) {
         size_t index = find(key);
         if (index != m_size) {
             erase(index);
             return true;
         }
         return false;
     }
 
     ////////////////////////////////////////////////////////////////////////////////
     // Iterator implementations
     ////////////////////////////////////////////////////////////////////////////////
 
     /**
      * @brief Iterator class for LookupTable.
      */
     class Iterator {
     public:
         using value_type = PairType;
         using pointer = PairType*;
         using reference = PairType&;
         using difference_type = std::ptrdiff_t;
         using iterator_category = std::forward_iterator_tag;
 
         /**
          * @brief Constructs an iterator.
          * @param ptr Pointer to the current element.
          */
         Iterator(pointer ptr) : ptr_(ptr) {}
 
         /**
          * @brief Dereferences the iterator.
          * @return Reference to the current element.
          */
         reference operator*() const { return *ptr_; }
 
         /**
          * @brief Arrow operator.
          * @return Pointer to the current element.
          */
         pointer operator->() const { return ptr_; }
 
         /**
          * @brief Prefix increment.
          * @return Reference to the iterator after increment.
          */
         Iterator& operator++() {
             ++ptr_;
             return *this;
         }
 
         /**
          * @brief Postfix increment.
          * @return Iterator before increment.
          */
         Iterator operator++(int) {
             Iterator temp = *this;
             ++ptr_;
             return temp;
         }
 
         /**
          * @brief Equality comparison.
          * @param other Another iterator to compare.
          * @return true if both iterators point to the same element.
          */
         bool operator==(const Iterator& other) const {
             return ptr_ == other.ptr_;
         }
 
         /**
          * @brief Inequality comparison.
          * @param other Another iterator to compare.
          * @return true if iterators point to different elements.
          */
         bool operator!=(const Iterator& other) const {
             return ptr_ != other.ptr_;
         }
 
     private:
         pointer ptr_;
     };
 
     /**
      * @brief Const iterator class for LookupTable.
      */
     class ConstIterator {
     public:
         using value_type = const PairType;
         using pointer = const PairType*;
         using reference = const PairType&;
         using difference_type = std::ptrdiff_t;
         using iterator_category = std::forward_iterator_tag;
 
         /**
          * @brief Constructs a const iterator.
          * @param ptr Pointer to the current element.
          */
         ConstIterator(pointer ptr) : ptr_(ptr) {}
 
         /**
          * @brief Dereferences the const iterator.
          * @return Constant reference to the current element.
          */
         reference operator*() const { return *ptr_; }
 
         /**
          * @brief Arrow operator.
          * @return Constant pointer to the current element.
          */
         pointer operator->() const { return ptr_; }
 
         /**
          * @brief Prefix increment.
          * @return Reference to the const iterator after increment.
          */
         ConstIterator& operator++() {
             ++ptr_;
             return *this;
         }
 
         /**
          * @brief Postfix increment.
          * @return Const iterator before increment.
          */
         ConstIterator operator++(int) {
             ConstIterator temp = *this;
             ++ptr_;
             return temp;
         }
 
         /**
          * @brief Equality comparison.
          * @param other Another const iterator to compare.
          * @return true if both iterators point to the same element.
          */
         bool operator==(const ConstIterator& other) const {
             return ptr_ == other.ptr_;
         }
 
         /**
          * @brief Inequality comparison.
          * @param other Another const iterator to compare.
          * @return true if iterators point to different elements.
          */
         bool operator!=(const ConstIterator& other) const {
             return ptr_ != other.ptr_;
         }
 
     private:
         pointer ptr_;
     };
 
     /**
      * @brief Returns an iterator to the beginning.
      * @return Iterator pointing to the first element.
      */
     Iterator begin() {
         return Iterator(data_);
     }
 
     /**
      * @brief Returns an iterator to the end.
      * @return Iterator pointing one past the last element.
      */
     Iterator end() {
         return Iterator(data_ + m_size);
     }
 
     /**
      * @brief Returns a const iterator to the beginning.
      * @return ConstIterator pointing to the first element.
      */
     ConstIterator begin() const {
         return ConstIterator(data_);
     }
 
     /**
      * @brief Returns a const iterator to the end.
      * @return ConstIterator pointing one past the last element.
      */
     ConstIterator end() const {
         return ConstIterator(data_ + m_size);
     }
 
     /**
      * @brief Returns a const iterator to the beginning.
      * @return ConstIterator pointing to the first element.
      */
     ConstIterator cbegin() const {
         return ConstIterator(data_);
     }
 
     /**
      * @brief Returns a const iterator to the end.
      * @return ConstIterator pointing one past the last element.
      */
     ConstIterator cend() const {
         return ConstIterator(data_ + m_size);
     }
 
 private:
     PairType* data_;    ///< Pointer to dynamically allocated storage.
     size_t m_size;      ///< Current number of elements.
     size_t m_capacity;  ///< Current capacity of the container.
 };
 
}

#endif