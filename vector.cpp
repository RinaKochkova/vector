#include <iostream>
#include <utility>
#include <math.h>

using namespace std;

template <typename T>
class Vector {
private:
  	unsigned int size_; 
  	unsigned int capacity;
  	T* array;
  
public:
	Vector(){
		size_ = 0;
		capacity = 0;
		array = nullptr;
	}
	// Конструктор копирования
	Vector(Vector<T>& value) {
		(*this) = value;
	}
	// Конструктор перемещения 
	Vector(Vector<T>&& value) {
		(*this) = value;
	}
	// Оператор присваивания копированием
	Vector<T>& operator= (Vector<T>& value) {
		if (this != &value) {
			size_ = value.size_;
			capacity = value.capacity;
			delete[] array;
			array = new T[capacity];
			for (unsigned int i = 0; i < size_; i++ )
				array[i] = value.array[i];
		}
		return *this;
	} 
	// Оператор присваивания перемещением
	Vector<T>& operator= (Vector<T>&& value) {
		if (this != &value) {
			size_ = value.size_;
			capacity = value.capacity;
			swap(this->array, value.array);
		}
		return *this;
	}
	// Деструктор
	~Vector(){
		delete[] array;
	}
	// Ф-ция resize_ отличается от ф-ции resize_ в std::vector
	// Здесь ф-ция просто увеличивает capacity, не добавляя новый элемент в array
	void resize_ (unsigned int new_size_) {
		unsigned int new_capacity = new_size_ * 2;
		T* new_array = new T[new_capacity];
		for (unsigned int i = 0; i < size_; i++)
			new_array[i] = move(array[i]);
		delete[] array;
		size_ = new_size_;
		capacity = new_capacity;
		array = move(new_array);
	}
	// Метод push_back с копированием
	void push_back(T& value) {
		if (size_ == capacity) {
			value.resize_(size_ + 1);
			--size_;
		}
		array[size_] = value;
		size_++;
	}
	// Метод push_back с перемещением
	void push_back(T&& value) {
		if (size_ == capacity) {
			value.resize_(size_ + 1);
			--size_;
		}
		array[size_] = move(value);
		size_++;
	}
	// Метод pop_back
	void pop_back() {
		--size_;
	}
	// Метод eraze с удалением одного элемента
	T* eraze(T* obj) {
		for (T* i = obj; i < this->end(); i++)
			*i = *(i + 1);
		--size_;
		return obj;
	}
	// Метод eraze с удалением элементов в диапазоне [first; last)
	T* eraze(T* first, T* last) {
		unsigned int new_capacity = capacity - (last - first);
		unsigned int new_size_ = size_ - (last - first);
		T* new_array = new T[new_capacity];
		for (unsigned int i = 0; i < first - this->begin() ; i++)
			new_array[i] = array[i];
		for (unsigned int j = last - this->begin(); j < size_; j++) {
			unsigned int i = first - this->begin();
			new_array[i] = array[j];
			i++;
		}
		delete[] array;
		size_ = new_size_;
		capacity = new_capacity;
		array = new_array;

		return first;
	}
	// Метод swap
	void Swap(Vector<T>& value) {
		swap(this->size_, value.size_);
		swap(this->capacity, value.capacity);
		swap(this->array, value.array);
	}
	// Методы begin, end и size_
	T* begin() {return array;}
	T* end() {return array + size_;}
	int size() {return size_;}
};

// Функция swap
template <typename T>
void swap(Vector<T>& value1, Vector<T>& value2) {
	value1.Swap(value2);
}