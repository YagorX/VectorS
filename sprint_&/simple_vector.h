#pragma once
#include <cassert>
#include <initializer_list>


struct ReserveProxyObj
{
public:
    size_t new_capacity_;
    ReserveProxyObj(size_t capacity_reserve) : new_capacity_{ capacity_reserve } {};
};

template <typename Type>
class SimpleVector {
private:
    size_t size_;
    size_t capacity_;
    Type* arr_;

    void Swap(const SimpleVector& vect)
    {
        size_ = vect.size_;
        capacity_ = vect.capacity_;
        arr_ = static_cast<Type*>(new Type[size_]);
        for (int i{}; i < size_; i++)
            arr_[i] = vect[i];
    }

public:
    using Iterator = Type*;
    using ConstIterator = const Type*;

    SimpleVector() noexcept = default;

    explicit SimpleVector(size_t size) : size_{ size }, capacity_{ size } {
        arr_ = static_cast<Type*> (new Type[size]{});
        std::fill(begin(), end(), 0);
    }

    explicit SimpleVector(ReserveProxyObj obj) : size_{ 0 }, capacity_ { obj.new_capacity_ } {
        arr_ = static_cast<Type*> (new Type[capacity_]{});
        std::fill(begin(), end(), 0);
    }

    SimpleVector(size_t size, const Type& value) : size_{ size }, capacity_{ size } {
        arr_ = static_cast<Type*> (new Type[size]);
        std::fill(begin(), end(), value);
    }

    SimpleVector(std::initializer_list<Type> init) : size_{ init.size() }, capacity_{init.size()}
    {
        arr_ = static_cast<Type*> (new Type[init.size()+1]);
        for (int i{}; i < size_; ++i)
            arr_[i] = *(init.begin() + i);
    }

    SimpleVector(const SimpleVector& other) {
        assert(size_ == 0);
        SimpleVector<Type> copy_vector(other.size_);
        for (size_t i{}; i < copy_vector.GetSize(); ++i)
            copy_vector[i] = other[i];

        Swap(copy_vector);
    }

    SimpleVector& operator=(const SimpleVector& rhs) {
        if (this == &rhs)
            return *this;

        SimpleVector<Type> copy_vector(rhs);
        Swap(copy_vector);
        return *this;
    }

    SimpleVector(SimpleVector&& other) noexcept
    {
        arr_ = std::exchange(other.arr_, nullptr);
        size_ = std::exchange(other.size_, 0);
        capacity_ = std::exchange(other.capacity_, 0);
    }

    SimpleVector& operator=(SimpleVector&& rhs) noexcept {
        if (this == &rhs)
            return *this;

        arr_ = std::exchange(rhs.arr_, nullptr) ;
        size_ = std::exchange(rhs.size_, 0) ;
        capacity_ = std::exchange(rhs.capacity_, 0);

        return *this;
    }

    ~SimpleVector()
    {
        
        capacity_ = 0;
        size_ = 0;
        delete[] arr_;
    }

    size_t GetSize() const noexcept {
        return size_;
    }

    size_t GetCapacity() const noexcept {
        return capacity_;
    }

    bool IsEmpty() const noexcept {
        return size_ <= 0? true : false;
    }

    Type& operator[](size_t index) noexcept {
        return (arr_[index]);
    }

    const Type& operator[](size_t index) const noexcept {
        return (arr_[index]);
    }

    Type& At(size_t index) {
        if (index >= size_)
            throw std::out_of_range{"out of range SimpleVector"};
        
        return (arr_[index]);
    }

    const Type& At(size_t index) const {
        if (index >= size_)
            throw std::out_of_range{ "out of range SimpleVector" };

        return (arr_[index]);
    }

    void Clear() noexcept {
        for (int i{}; i < size_; ++i)
            arr_[i] = 0;

        size_ = 0;
    }

    void Resize(size_t new_size){
        Type* new_arr = static_cast<Type*>(new Type[new_size]);
        for (int i{}; i < new_size; ++i)
            new_arr[i] = arr_[i];
        delete[] arr_;
        if (new_size < size_)
        {
            arr_ = new_arr;
            size_ = new_size;
        }
        else {
            for (size_t i{ size_ }; i < new_size; ++i)
                new_arr[i] = 0;
            arr_ = new_arr;
            size_ = new_size;
            capacity_ = new_size;
        }
    }

    Iterator begin() noexcept {
        if (size_==0)
            return nullptr;
        return arr_;
    }

    Iterator end() noexcept {
        if (size_ == 0)
            return nullptr;
        return &arr_[size_];
    }

    ConstIterator begin() const noexcept {
        if (size_ == 0)
            return nullptr;
        return arr_;
    }

    ConstIterator end() const noexcept {
        if (size_ == 0)
            return nullptr;
        return &arr_[size_];
    }

    ConstIterator cbegin() const noexcept {
        if (size_ == 0)
            return nullptr;
        return arr_;
    }

    ConstIterator cend() const noexcept {
        if (size_ == 0)
            return nullptr;
        return &arr_[size_];
    }
    
    void PushBack(const Type& item) {
        if (size_ == 0)
        {
            Type* new_arr = static_cast<Type*>(new Type[1]);
            new_arr[0] = item;
            arr_ = new_arr;
            size_++;
            capacity_++;
        }
        else {
            Type* new_arr = static_cast<Type*>(new Type[capacity_ * 2]);
            for (int i{}; i < size_; ++i)
                new_arr[i] = arr_[i];
            new_arr[size_] = item;
            delete[] arr_;

            if (size_ == capacity_)
            {
                for (size_t i{ size_ + 1 }; i < size_ * 2; ++i)
                    new_arr[i] = 0;
                arr_ = new_arr;
                capacity_ = size_ * 2;
                size_++;
            }
            else
            {
                arr_ = new_arr;
                size_++;
            }
        }
    }

    void PopBack() noexcept {
        // size_ != 0
        arr_[--size_] = 0;
    }

    Iterator Insert(Iterator pos, const Type& value) {
        if (size_ == capacity_)
        {
            Type* new_arr = static_cast<Type*> (new Type[size_ * 2]);
            int i{};
            for (; &arr_[i] <= pos; ++i)
                new_arr[i] = arr_[i];
            new_arr[i] = value;
            for (; i < size_; ++i)
                new_arr[i+1] = arr_[i];

            delete[] arr_;
            arr_ = new_arr;

            size_++;
            capacity_ *= 2;
        }
        else {
            arr_[size_] = arr_[size_ - 1];
            arr_[size_ - 1] = arr_[size_ - 2];
            size_t i{ size_ - 2 };
            for (; &arr_[i-1] != pos; --i)
                std::swap(arr_[i - 1], arr_[i]);
            arr_[i] = value;
            size_++;
        }
        
        return pos++;
    }

    Iterator Erase(Iterator pos) {
        assert(size_ != 0);
        int i{};
        Type* new_arr = static_cast<Type*> (new Type[size_]);
        for (; &arr_[i] != pos; ++i)
            new_arr[i] = arr_[i];
        for (i++; i < size_; ++i)
            new_arr[i - 1] = arr_[i];
        delete[] arr_;
        arr_ = new_arr;
        size_--;

        return pos--;
    }

    void Reserve(size_t new_capacity)
    {
        if (new_capacity > capacity_) 
        {
            Type* new_arr = static_cast<Type*> (new Type[new_capacity]);
            for (int i{}; i < size_; ++i)
                new_arr[i] = arr_[i];

            delete[] arr_;
            arr_ = new_arr;
            capacity_ = new_capacity;
        }
    }

    void swap(SimpleVector& other) noexcept {
        std::swap(other.size_, size_);
        std::swap(other.capacity_, capacity_);
        std::swap(other.arr_, arr_);
    }
};

template <typename Type>
inline bool operator==(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
inline bool operator!=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
inline bool operator<(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
inline bool operator<=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
inline bool operator>(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
inline bool operator>=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

ReserveProxyObj Reserve(size_t capacity_to_reserve) {
    return ReserveProxyObj(capacity_to_reserve);
};