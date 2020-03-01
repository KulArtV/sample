#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <class T>
T* Copy(const T* src_begin, const T* src_end, T* dest) {
	for (auto it = src_begin; it != src_end; ++it, ++dest) {
		*dest = *it;
	}
	return dest;
}

template <class T>
T* FillN(T* dest, size_t count, const T& value) {
	for (size_t i = 0; i < count; ++i) {
		dest[i] = value;
	}
	return dest + count;
}

template <class T>
void Swap(T& lhs, T& rhs) {
	T tmp = lhs;
	lhs = rhs;
	rhs = tmp;
}

template <class T>
class Vector {
	T* buffer_;
	size_t size_;
	size_t capacity_;

	const static size_t kReallocFactor = 2;

	size_t CalculateCapacity(size_t required_size) const {
		if (capacity_ == 0 && required_size == 0) {
			return 0;
		}
		size_t new_capacity = (capacity_ == 0) ? 1 : capacity_;
		while (new_capacity < required_size) {
			new_capacity *= kReallocFactor;
		}
		return new_capacity;
	}

	void Reallocate(size_t new_capacity) {
		T* new_buffer = (new_capacity == 0) ? nullptr : new T[new_capacity];
		size_ = (size_ < new_capacity) ? size_ : new_capacity;
		Copy(buffer_, buffer_ + size_, new_buffer);
		capacity_ = new_capacity;
		delete[] buffer_;
		buffer_ = new_buffer;
	}

public:
	Vector() : buffer_(nullptr), size_(0), capacity_(0) {
	}

	explicit Vector(size_t count)
		: buffer_(new T[count])
		, size_(count)
		, capacity_(count) {
	}

	Vector(size_t count, const T& value) : Vector(count) {
		FillN(buffer_, count, value);
	}

	Vector(const Vector& other) : Vector(other.size_) {
		Copy(other.buffer_, other.buffer_ + other.size_, buffer_);
	}

	Vector& operator=(Vector other) {
		Swap(other);
		return *this;
	}

	~Vector() {
		delete[] buffer_;
	}

	void Clear() {
		size_ = 0;
	}

	void PushBack(const T& value) {
		Reserve(size_ + 1);
		buffer_[size_++] = value;
	}

	void PopBack() {
		--size_;
	}

	void Resize(size_t count) {
		Reserve(count);
		size_ = count;
	}

	void Resize(size_t count, const T& value) {
		Reserve(count);
		if (count > size_) {
			FillN(buffer_ + size_, count - size_, value);
		}
		size_ = count;
	}

	void Reserve(size_t count) {
		if (count <= capacity_) {
			return;
		}
		const size_t new_capacity = CalculateCapacity(count);
		Reallocate(new_capacity);
	}

	void ShrinkToFit() {
		if (size_ < capacity_) {
			Reallocate(size_);
		}
	}

	void Swap(Vector& other) {
		::Swap(buffer_, other.buffer_);
		::Swap(size_, other.size_);
		::Swap(capacity_, other.capacity_);
	}

	T operator[](size_t idx) const {
		return buffer_[idx];
	}

	T& operator[](size_t idx) {
		return buffer_[idx];
	}

	T Front() const {
		return buffer_[0];
	}

	T& Front() {
		return buffer_[0];
	}

	T Back() const {
		return buffer_[size_ - 1];
	}

	T& Back() {
		return buffer_[size_ - 1];
	}

	T* Data() {
		return buffer_;
	}

	const T* Data() const {
		return buffer_;
	}

	bool Empty() const {
		return size_ == 0;
	}

	size_t Size() const {
		return size_;
	}

	size_t Capacity() const {
		return capacity_;
	}
};

template <class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
	if (lhs.Size() != rhs.Size()) {
		return false;
	}

	for (size_t i = 0; i < lhs.Size(); ++i) {
		if (lhs[i] != rhs[i]) {
			return false;
		}
	}
	return true;
}

template <class T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
	return !(lhs == rhs);
}

template <class T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs) {
	const size_t min_size = (lhs.Size() < rhs.Size()) ? lhs.Size() : rhs.Size();
	for (size_t i = 0; i < min_size; ++i) {
		if (lhs[i] < rhs[i]) {
			return true;
		}
		if (lhs[i] > rhs[i]) {
			return false;
		}
	}
	return lhs.Size() < rhs.Size();
}

template <class T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
	return !(rhs < lhs);
}

template <class T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
	return rhs < lhs;
}

template <class T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
	return !(lhs < rhs);
}

#endif // VECTOR_H
