#pragma once
#include <iostream>

template <typename T>
class Vector
{
private:
	T* data;
	size_t size;
	size_t capacity;

	void copy(const Vector& other);
	void erase();
	void resize();

public:
	Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	void push_back(const T& el);//new element in the end
	void pop_back();//remove element from the end
	void push_front(const T& el);//new element in the start
	void pop_front();//remove element from the start
	void push_at(const T& el, int position);//inserts element in a certain position
	void pop_at(int position);//remove element from a certain position

	size_t getSize() const;
	size_t getCapacity() const;
	bool isEmpty() const; //check if the vector is empty or not

	Vector<T> operator+(const Vector& other);
	Vector<T>& operator+=(const Vector& other);
	Vector<T> operator+(const T& other);
	Vector<T>& operator+=(const T& other);
	T& operator [](int i) const;
	bool operator==(const Vector& other) const;
	bool operator!=(const Vector& other) const;

	friend std::ostream& operator<<(std::ostream& out, const Vector<T>& vec)
	{
		size_t size = vec.getSize();
		for (size_t i = 0; i < size; i++)
		{
			out << vec[i];
		}

		return out;
	}

	/*friend std::istream& operator>>(std::istream& in, Vector<T>& vec)
	{
		size_t size = vec.getSize();
		for (size_t i = 0; i < size; i++)
		{
			in >> vec[i];
		}

		return in;
	}*/
};

template <typename T>
void Vector<T>::copy(const Vector& other)
{
	this->capacity = other.capacity;

	this->data = new T[capacity];

	for (size_t i = 0; i < other.size; i++)
	{
		this->data[i] = other.data[i];
	}

	this->size = other.size;
}

template <typename T>
void Vector<T>::erase()
{
	delete[] this->data;
}

template <typename T>
void Vector<T>::resize()
{
	this->capacity *= 2;
	T* biggerVector = new T[this->capacity];

	for (size_t i = 0; i < this->size; i++)
	{
		biggerVector[i] = this->data[i];
	}

	this->erase();
	this->data = biggerVector;
}

template <typename T>
Vector<T>::Vector()
{
	this->size = 0;
	this->capacity = 8;
	this->data = new T[this->capacity];
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	this->copy(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}

	return *this;
}

template <typename T>
Vector<T>::~Vector()
{
	this->erase();
}

template <typename T>
void Vector<T>::push_back(const T& el)
{
	if (this->size == this->capacity)
	{
		this->resize();
	}
	this->data[size] = el;
	this->size++;
}

template <typename T>
void Vector<T>::pop_back()
{
	if (this->size <= 0)
	{
		return;
	}
	this->size--;
}

template <typename T>
void Vector<T>::push_front(const T& el)
{
	if (this->size >= this->capacity)
	{
		this->resize();
	}
	T* bigger = new T[this->size + 1];

	for (int i = 0; i < this->size; i++)
	{
		bigger[i + 1] = this->data[i];
	}

	size++;
	bigger[0] = el;
	this->erase();
	this->data = bigger;
}

template <typename T>
void Vector<T>::pop_front()
{
	T* smaller = new T[this->size + 1];

	for (size_t i = 0; i < this->size; i++)
	{
		smaller[i] = this->data[i + 1];
	}

	this->size--;
	this->erase();
	this->data = smaller;
}

template <typename T>
void Vector<T>::push_at(const T& el, int position)
{
	this->resize();

	if (this->size >= position)
	{
		for (int i = this->size; i >= position; i--)
		{
			this->data[i] = this->data[i - 1];
		}

		this->size++;
		this->data[position - 1] = el;
	}
	else
		std::cout << "invalid position" << std::endl;
}

template <typename T>
void Vector<T>::pop_at(int position)
{
	for (size_t i = position; i < this->size; i++)
	{
		this->data[i] = this->data[i + 1];
	}

	this->size--;
}

template <typename T>
size_t Vector<T>::getSize() const
{
	return this->size;
}

template <typename T>
size_t Vector<T>::getCapacity() const
{
	return this->capacity;
}

template <typename T>
bool Vector<T>::isEmpty() const
{
	return this->size == 0;
}

template <typename T>
Vector<T> Vector<T>::operator +(const Vector<T>& other)
{
	Vector<T> result;

	this->resize();
	result.data = new T[this->capacity + other.capacity];

	for (size_t i = 0; i < this->size; i++)
	{
		result[i] = this->data[i];
	}

	for (size_t i = 0; i < other.size; i++)
	{
		result[this->size + i] = other.data[i];
	}


	result.size = this->size + other.size;
	return result;
}

template <typename T>
Vector<T>& Vector<T>::operator +=(const Vector& other)
{
	this->resize();
	T* bigger = new T[this->capacity];

	for (size_t i = 0; i < this->size; i++)
	{
		bigger[i] = this->data[i];
	}

	for (size_t i = 0; i < other.size; i++)
	{
		bigger[this->size + i] = other.data[i];
	}

	this->erase();
	this->data = bigger;
	this->size = this->size + other.size;

	return *this;
}

template <typename T>
Vector<T> Vector<T>::operator +(const T& other)
{
	Vector<T> withAddedElement;
	withAddedElement = *this;
	withAddedElement.push_back(other);
	return withAddedElement;
}

template <typename T>
Vector<T>& Vector<T>::operator +=(const T& other)
{
	*this = *this + other;
	return *this;
}

template <typename T>
T& Vector<T>::operator [](int i) const
{
	return data[i];
}

template <typename T>
bool Vector<T>::operator==(const Vector& other) const
{
	if (this->size != other.size)
		return false;

	for (size_t i = 0; i < this->size; i++)
	{
		if (this->data[i] != other.data[i])
			return false;
	}

	return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector& other) const
{
	return !(this == &other);
}

