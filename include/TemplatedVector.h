#include <mutex>
#include <vector>
#include <iostream>
template <typename T>
class TemplatedVector {
private:
	std::vector<T> vector;
	std::mutex mutex_;
	int pos = 0;
	std::vector<int>::iterator it;
public:
	TemplatedVector() {

	}

	~TemplatedVector() {

	}

	T push(T a) {
		T insertedValue = a;
		//mutex_.lock();
		it = vector.begin() + pos;
		vector.insert(it, a);
		int x = 0;
		for (int i = 0; i <= 100; i++) {
			x += i;
		}
		for (int i = 0; i <= 1; i++) {
			pos = pos + i;

		}
		//mutex_.unlock();
		return insertedValue;
	};

	//Añadir un elemento al final del vector
	T& push_back(const T& v) {
		//mutex_.lock();

		it = vector.back();
		vector.insert(it, a);
		//mutex_.unlock();

	}


	T& push_back(T&& v) {
		//mutex_.lock();

		vector.push_back(v);
		//mutex_.unlock();

	}

	//Limpiar el vector
	void clear() {
		//mutex_.lock();

		vector.clear();
		pos = 0;
		//mutex_.unlock();

	}


	//Redimensionar el vector
	void resize(size_t n) {

		//mutex_.lock();
		vector.resize(n);
		//mutex_.unlock();
	}

	//Reservar elementos
	void reserve(size_t n) {

		//mutex_.lock();
		vector.reserve(n);
		//mutex_.unlock();

	}

	//Construir e insertar elemento
	T& emplace_back(T&& v) {
		//mutex_.lock();
		vector = std::vector<T>();
		vector.push_back(v);
		//mutex_.unlock();

	}

	//Borrar elementos en un rango
	void erase(std::size_t first, std::size_t last) {

		//mutex_.lock();
		vector.erase(first, last);
		//mutex_.unlock();

	}

	//Borrar el ultimo elemento
	T pop_back() {
		//mutex_.lock();
		T lastElement = 0;
		//lastElement = vector[vector.size];
		vector.pop_back();
		//mutex_.unlock();
		return lastElement;
	}

	//Tamaño del vector
	size_t size() {
		int size = 0;

		//mutex_.lock();
		size = vector.size();
		//mutex_.unlock();


		return size;
	}

	size_t capacity() {
		int capacity = 0;

		//mutex_.lock();
		capacity = vector.capacity();
		//mutex_.unlock();


		return capacity;
	}

	//Verifica si el vector esta vacío
	bool empty() {
		bool empty = true;

		//mutex_.lock();
		empty = vector.empty;
		//mutex_.unlock();

		return empty;
	}

	//Accede a un elemento
	T& operator[](size_t idx) {
		T element = 0;
		//mutex_.lock();

		return vector.at(idx);
		//mutex_.unlock();

	}

	T at(size_t idx) {
		T element = 0;
		//mutex_.lock();

		return vector.at(idx);
		//mutex_.unlock();

	}
	const T& operator[](size_t idx) const {
		//mutex_.lock();
		return at(idx);
		//mutex_.unlock();

	}

	//Accede al último elemento
	T& back() {
		T lastElement;
		//mutex_.lock();

		lastElement = vector.back();
		//mutex_.unlock();

		return lastElement;
	}

	const T& back() const {
		//mutex_.lock();
		vector.back();
		//mutex_.unlock();

	}
	//Recorre el vector y ejecuta la función pasada por parámetro para cada elemento
	void foreach(std::function<void(const T&)> f) const {
		//mutex_.lock();
		foreach(f);
		//mutex_.unlock();
	}
	void foreach(std::function<void(T&)> f) {
		//mutex_.lock();
		for (size_t i = 0; i < vector.size; i++)
		{
			swapElement(vector.at(i), f(vector.at(i)));
		}
		//mutex_.unlock();
	}
	//Intercambia un elemento del vector
	void swapElement(size_t pos, T *other) {
		//mutex_.lock();
		std::vector<int>::iterator it2;

		it2 = vector.begin() + pos;
		vector.insert(it2, other);

		//mutex_.unlock();

	}
	//Intercambia el vector entero con otro vector
	void swap(std::vector<T> &other) {
		//mutex_.lock();
		for (size_t i = 0; i < other.size(); i++)
		{
			swapElement(i, other.at(i))
		}

		//mutex_.unlock();
	}

};