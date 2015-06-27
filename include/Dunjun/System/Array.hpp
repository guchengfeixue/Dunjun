#ifndef DUNJUN_SYSTEM_ARRAY_HPP
#define DUNJUN_SYSTEM_ARRAY_HPP

#include <Dunjun/System/Containers.hpp>

#include <cstring>

namespace Dunjun
{
// Appends an item to the array and returns the number of items in the array
// after the append
template <typename T>
usize pushBack(Array<T>& a, const T& item);
// Removes the last element from the array
template <typename T>
void popBack(Array<T>& a);
// Appends items to the array and returns the number of items in the array after
// the array
template <typename T>
usize push(Array<T>& a, const T* items, usize count);

// Number of elements in array
template <typename T>
usize len(const Array<T>& a);
// Is array empty? len(array) == 0
template <typename T>
bool empty(const Array<T>& a);
// Maximum number of items the array can hold
template <typename T>
usize capacity(const Array<T>& a);

// Iterators
template <typename T>
T* begin(const Array<T>& a);
template <typename T>
const T* begin(const Array<T>& a);
template <typename T>
T* end(const Array<T>& a);
template <typename T>
const T* end(const Array<T>& a);

template <typename T>
T& front(const Array<T>& a);
template <typename T>
const T& front(const Array<T>& a);
template <typename T>
T& back(const Array<T>& a);
template <typename T>
const T& back(const Array<T>& a);

// Clears the content of the array
// Does not free memory nor call destructs (e.g. POD), it only zeroes the
// elements
template <typename T>
void clear(Array<T>& a);
// Resizes the array to a given size
// Old items will be copied to the new array. If the new capacity is smaller
// than the previous one, the array will be shortened.
template <typename T>
void resize(Array<T>& a, usize length);
// Sets the capacity of the array
template <typename T>
void setCapacity(Array<T>& a, usize capacity);
// Reserves space in the array for at least capacity items
template <typename T>
void reserve(Array<T>& a, usize capacity);

// Grows the array to contain at least minCapacity items
template <typename T>
void grow(Array<T>& a, usize minCapacity = 0);

////////////////////////////////////////
//        Array Implementation        //
////////////////////////////////////////

template <typename T>
inline usize pushBack(Array<T>& a, const T& item)
{
	if (a.length == a.capacity)
		grow(a);
	a.data[a.length++] = item;

	return a.length;
}

template <typename T>
inline void popBack(Array<T>& a)
{
	assert(a.length > 0);

	a.length--;
}

template <typename T>
usize push(Array<T>& a, const T* items, usize count)
{
	if (a.capacity <= a.length + count)
		grow(a, a.length + count);

	std::memcpy(&a.data[a.length], items, count * sizeof(T));
	a.length += count;

	return a.length;
}

template <typename T>
inline usize len(const Array<T>& a)
{
	return a.length;
}

template <typename T>
inline bool empty(const Array<T>& a)
{
	return a.length == 0;
}

template <typename T>
usize capacity(const Array<T>& a)
{
	return a.capacity;
}

template <typename T>
inline T* begin(const Array<T>& a)
{
	return a.data;
}

template <typename T>
inline const T* begin(const Array<T>& a)
{
	return a.data;
}

template <typename T>
inline T* end(const Array<T>& a)
{
	return a.data + a.length;
}

template <typename T>
inline const T* end(const Array<T>& a)
{
	return a.data + a.length;
}

template <typename T>
inline T& front(const Array<T>& a)
{
	assert(a.length > 0);
	return a.data[0];
}

template <typename T>
inline const T& front(const Array<T>& a)
{
	assert(a.length > 0);
	return a.data[0];
}

template <typename T>
inline T& back(const Array<T>& a)
{
	assert(a.length > 0);
	return a.data[a.length - 1];
}

template <typename T>
inline const T& back(const Array<T>& a)
{
	assert(a.length > 0);
	return a.data[a.length - 1];
}

template <typename T>
inline void clear(Array<T>& a)
{
	resize(a, 0);
}

template <typename T>
void resize(Array<T>& a, usize length)
{
	if (length > a.capacity)
		grow(a, length);
	a.length = length;
}

template <typename T>
void setCapacity(Array<T>& a, usize capacity)
{
	if (capacity == a.capacity)
		return;

	if (capacity < a.length)
		resize(a, capacity);

	T* data{nullptr};
	if (capacity > 0)
	{

		data = (T*)a.allocator->allocate(capacity * sizeof(T), alignof(T));
		std::memcpy(data, a.data, a.length * sizeof(T));
	}
	a.allocator->deallocate(a.data);
	a.data = data;
	a.capacity = capacity;
}

template <typename T>
inline void reserve(Array<T>& a, usize capacity)
{
	if (capacity > a.capacity)
		setCapacity(a, capacity);
}

template <typename T>
inline void grow(Array<T>& a, usize minCapacity)
{
	usize capacity{2 * a.capacity + 2};
	if (capacity < minCapacity)
		capacity = minCapacity;
	setCapacity(a, capacity);
}

template <typename T>
inline Array<T>::Array(Allocator& a)
: allocator{&a}
, length{0}
, capacity{0}
, data{nullptr}
{
}

template <typename T>
inline Array<T>::~Array()
{
	allocator->deallocate(data);
}

template <typename T>
Array<T>::Array(const Array& other)
: allocator{other.allocator}
, length{0}
, capacity{0}
, data{nullptr}
{
	const usize num{other.length};
	setCapacity(*this, num);
	std::memcpy(data, other.data, num * sizeof(T));
	length = num;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	const usize num{other.length};
	resize(*this, num);
	std::memcpy(data, other.data, num * sizeof(T));

	return *this;
}

template <typename T>
inline T& Array<T>::operator[](usize index)
{
	return data[index];
}

template <typename T>
inline const T& Array<T>::operator[](usize index) const
{
	return data[index];
}

} // namespace Dunjun

#endif