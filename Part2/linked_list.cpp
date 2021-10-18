#include <iostream>

using namespace std;

template <typename T>
class LinkedList {
	public:
	struct Node {
		T value;
		Node* next = nullptr;
	};

	~LinkedList() {
		if (head != nullptr) {
			Node* iter = head;
			while (iter->next != nullptr) {
				auto iterNext = iter->next;
				delete iter;
				iter = iterNext;
			}
		}
	}

	void PushFront(const T& value) {
		if (head == nullptr) {
			head = new Node;
			head->value = value;
		} else {
			auto newHead = new Node;
			newHead->value = value;
			newHead->next = head;
			head = newHead;
		}
	}

	void InsertAfter(Node* node, const T& value) {
		if (node == nullptr) {
			PushFront(value);
		}
		else {
			auto iter = head;
			while (iter != node && iter->next != nullptr) {
				iter = iter->next;
			}
			Node* newNode = new Node;
			newNode->value = value;
			newNode->next = iter->next;
			iter->next = newNode;
		}
	}

	void RemoveAfter(Node* node) {
		if (node == nullptr) {
			PopFront();
		}
		else {
			auto iter = head;
			while (iter != node) {
				iter = iter->next;
			}
			if (iter->next == nullptr) {
				return;
			}
			auto nodeToDelete = iter->next;
			iter->next = nodeToDelete->next;
			delete nodeToDelete;
		}
	}

	void PopFront() {
		if (head->next == nullptr) {
			delete head;
		}
		else {
			auto oldHead = head;
			head = head->next;
			delete oldHead;
		}
	}

	Node* getHead() { return head; }
	const Node* getHead() const { return head; }

private:
	Node* head = nullptr;
};

template<typename T>
void goThroughList(const LinkedList<T>& list) {
	for (auto iter = list.getHead(); iter != nullptr; iter = iter->next) {
		cout << iter->value << ' ';
	}
	cout << endl;
}
int main() {
	LinkedList<int> a;
	a.PushFront(1);
	cout << a.getHead()->value << endl;
	a.PushFront(11);
	cout << a.getHead()->value << endl;
	a.PushFront(12);
	cout << a.getHead()->value << endl;
	a.PushFront(123);
	cout << a.getHead()->value << endl;
	goThroughList(a);
	auto remove = a.getHead()->next;
	a.RemoveAfter(remove);
	goThroughList(a);
	a.InsertAfter(remove, 333);
	goThroughList(a);
	a.InsertAfter(remove, 404);
	goThroughList(a);

	a.RemoveAfter(remove);
	goThroughList(a);



	return 0;
}