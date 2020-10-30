#include "stdafx.h"
#include "SA.h"
#include <iostream>
using namespace std;

SA::SA()
{
	head_.next_ = 0;
}

SA::~SA()
{
	Node *ptr;
	while (head_.next_ != 0) {
		ptr = head_.next_;
		head_.next_ = ptr->next_;
		delete ptr;
	}
}

int SA::binarySearch(int *base, int size, int key)
{
	int left = 0, right = size - 1, mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (key == base[mid])
			return mid;
		(key < base[mid]) ? right = mid - 1 : left = mid + 1;
	}
	return -1;
}

int *SA::merge(int *base1, int *base2, int size)
{
	int *result = new int[size << 1];
	int i = 0, j = 0, k = -1;
	while (i < size && j < size)
		result[++k] = (base1[i] <= base2[j]) ? base1[i++] : base2[j++];
	while (i < size)
		result[++k] = base1[i++];
	while (j < size)
		result[++k] = base2[j++];

	delete[] base1;
	return result;
}

void SA::print() const
{
	int i;
	for (Node *ptr = head_.next_; ptr != 0; ptr = ptr->next_) {
		cout << ptr->size_ << ": ";
		for (i = 0; i < ptr->size_; i++)
			cout << ptr->base_[i] << ' ';
		cout << endl;
	}
	cout << endl;
}

SA::Position SA::search1(int key) const
{
	int index;
	for (Node *ptr = head_.next_; ptr != 0; ptr = ptr->next_) {
		index = binarySearch(ptr->base_, ptr->size_, key);
		if (index != -1)
			return Position(ptr, index);
	}
	return Position(0, -1);
}

bool SA::search(int key) const
{
	return search1(key).ptr_ != 0;
}

void SA::insert(int key)
{
	Node *ptr = head_.next_;
	int size = 1;

	while (ptr && ptr->size_ == size) {
		size *= 2;
		ptr = ptr->next_;
	}

	Node *arr = new Node(new int[size], size);

	ptr = head_.next_;
	size = 1;

	int *last = new int[1], *current;
	last[0] = key;

	while (ptr && ptr->size_ == size) {
		current = new int[size * 2];
		int i = 0, j = 0, k = 0;

		while (i < size || j < size) {
			if (i == size)
				current[k++] = ptr->base_[j++];
			else if (j == size)
				current[k++] = last[i++];
			else if (ptr->base_[j] < last[i])
				current[k++] = ptr->base_[j++];
			else
				current[k++] = last[i++];
		}

		delete[] last;
		last = current;
		head_.next_ = ptr->next_;
		delete ptr;
		ptr = head_.next_;
		size *= 2;
	}

	for (int i = 0; i < size; i++)
		arr->base_[i] = last[i];

	arr->next_ = head_.next_;
	head_.next_ = arr;
}

void SA::remove(int key)
{
	if (search(key)) {
		Node *ptr = head_.next_;
		while (binarySearch(ptr->base_, ptr->size_, key) == -1) {
			ptr = ptr->next_;
		}

		int index = binarySearch(ptr->base_, ptr->size_, key);
		if (ptr != head_.next_) {
			ptr->base_[index] = head_.next_->base_[0];
			while (index < ptr->size_ - 1 &&
				ptr->base_[index] > ptr->base_[index + 1]) {
				swap(ptr->base_[index], ptr->base_[index + 1]);
				++index;
			}
			while (index > 0 && ptr->base_[index] < ptr->base_[index - 1]) {
				swap(ptr->base_[index], ptr->base_[index - 1]);
				--index;
			}
			index = 0;
		}

		ptr = head_.next_;
		head_.next_ = ptr->next_;
		int ind = 0;

		for (int cur_size = ptr->size_ / 2; cur_size > 0; cur_size /= 2) {
			Node *current = new Node(new int[cur_size], cur_size, head_.next_);
			for (int i = 0; i < cur_size; i++) {
				if (ind == index)
					++ind;
				current->base_[i] = ptr->base_[ind++];
			}
			head_.next_ = current;
		}

		delete ptr;
	}
}
