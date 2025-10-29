#include <iostream>
#include <windows.h>
#include <algorithm>
#include <queue>//Для працюваня priority_queue
using namespace std;

class Array {
	unsigned int capacity = 10; // при створенні масиву, він одразу для себе робить запас пам'яті на 10 елементів
	int* data = new int[capacity];
	unsigned int length = 0; // фактична (реальна) кількість елементів, присутніх у масиві


public:
	priority_queue<int> q;
	Array() {}

	void AddToBack(int value) {
		q.push(value);
		if (length < capacity) // якщо виділенної зарання пам'яті ВИСТАЧАЄ для додавання чергового елемента
			data[length] = value;
		else { // АЛЕ ЯКЩО МІСЦЯ ВЖЕ НЕ ВИСТАЧАЄ, ТО
			capacity *= 2; // збільшуємо запас пам'яті у 2 рази (можна і в 1.5, можна і в 1.2)
			int* temp = new int[capacity]; // новий масив буде в 2 рази більше по пам'яті
			////	// але в старому масиві все ще усього 10 елементів, тому цикл треба написати так, щоб зачепити лише старі елементі зі старого масиву
			for (int i = 0; i < length; i++) {
				temp[i] = data[i];
			}
			temp[length] = value;
			delete[] data; // в цілях запобігання витокам пам'яті, чистимо пам'ять від старого масиву
			data = temp; // переставляємо покажчик на новий масив
		}
		data[length] = q.top();
		q.pop();
		length++;

	}

	void Print() const {
		if (length == 0) {
			cout << "array empty!\n";
		}
		else {
			cout << "Element array: ";
			for (int i = 0; i < length; i++)
			{
				cout << data[i] << " ";
			}
			cout << "\n";
		}
	}

	~Array() {
		cout << "D-TOR\n";
		if (data != nullptr) {
			delete[] data;
		}
	}

	Array(const Array& original) {
		cout << "COPY C-TOR\n";
		this->length = original.length;
		this->capacity = original.capacity;
		this->data = new int[capacity];
		for (int i = 0; i < length; i++)
			this->data[i] = original.data[i];
	}
};
void operator +=(Array& a, int value) {
	cout << "HELLO FROM += function !!!\n";
	a.AddToBack(value);
}
int main() {
	SetConsoleOutputCP(1251);
	srand(time(0));

	Array a;
	a += 20;
	operator+=(a, 30); // 10 20 30
	a.Print(); // 10 20 30
}