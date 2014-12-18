#include <iostream>           
#include <queue>
#include <algorithm>
#include <memory>
#include <list>
#include <mutex>

using namespace std;


    template<typename T>
    class ThreadSafeList {
    public:
        struct Node {
            std::recursive_mutex m;
            T *data;
            Node *next;

            Node() {
                data = nullptr;
                next = nullptr;
            }

            Node(T value) {
                data = new T(value);
                next = nullptr;
            }

            ~Node() {
            }
        };

    private:
        Node *m_head;
        Node *m_tail;
        size_t m_size;

    public:
        ThreadSafeList() {
            m_size = 0;
            m_head = nullptr;
            m_tail = nullptr;
        }

        virtual ~ThreadSafeList() {
//        remove_if([](Node const&){return true;});
        }

//	ThreadSafeList(ThreadSafeList const& other) = delete;
//	ThreadSafeList& operator=(ThreadSafeList const& other) = delete;

        // возвращает указатель на голову
        Node *getHead() {
            return m_head;
        }

        Node *getTail() {
            return m_tail;
        }

        // return count of nodes within list (node is struct with T array[] inside)
        size_t getSize() const {
            return m_size;
        }

        void push_back(T value) {
            Node *new_node;
            try {
                new_node = new Node(value);
            } catch (std::bad_alloc &ba) {
                printf("bad_alloc caught!%s\n", ba.what());
                return;
            }
            if (m_head == nullptr) {
                std::lock_guard<std::recursive_mutex> lk(new_node->m);
                m_head = new_node;
                m_head->next = nullptr;
                m_tail = m_head;
                m_tail->next = nullptr;
                ++m_size;
                return;
            }
            std::lock_guard<std::recursive_mutex> lk(m_tail->m);
            m_tail->next = new_node;
            m_tail = new_node;
            ++m_size;
        }

        template<typename Function>
        void for_each(Function f) {
            Node *curr = m_head;
            while (curr) {
                std::unique_lock<std::recursive_mutex> lk(curr->m);
                f(*curr->data);
                lk.unlock();
                curr = curr->next;
            }
        }

        template<typename Predicate>
        void remove_if(Predicate p) {
            while (p(*m_head->data)) {
                Node *ptr = m_head;
                std::unique_lock<std::recursive_mutex> lk(m_head->m);
                m_head = m_head->next;
                delete ptr;
                ptr = nullptr;
                --m_size;
                if (m_size == 0) {
                    m_tail = nullptr;
                    m_head = nullptr;
                    return;
                }
                lk.unlock();
            }
            Node *prev = m_head;
            Node *curr = m_head->next;
            while (curr) {
                if (p(*curr->data)) {
//				if(curr->next == nullptr) {
//					std::unique_lock<std::recursive_mutex> lk(curr->m);
//					m_tail = prev;
//					delete curr->data;
//					delete curr;
//					lk.unlock();
//				}
                    std::unique_lock<std::recursive_mutex> lk(curr->m);
                    prev->next = curr->next;
                    delete curr;
                    curr = nullptr;
                    --m_size;
                    lk.unlock();
                    curr = prev->next;
                    continue;
                }
                curr = curr->next;
                prev = prev->next;
            }
        }

        // remove element from list. keeps pointer alive
        void remove(T &data) {
            if (m_size == 0) {
                return;
            }
            Node *prev = m_head;
            Node *curr = m_head->next;
            if (data == *prev->data) {
                Node *ptr = m_head;
                std::unique_lock<std::recursive_mutex> lk(m_head->m);
                m_head = m_head->next;
                delete ptr;
                ptr = nullptr;
                --m_size;
                if (m_size == 0) {
                    m_tail = nullptr;
                    m_head = nullptr;
                    return;
                }
                lk.unlock();
                curr = nullptr;
            }
            while (curr) {
                std::unique_lock<std::recursive_mutex> lk(curr->m);
                if (*curr->data == data) {
                    if (data == *m_tail->data) {
                        Node *ptr = m_tail;
                        m_tail = prev;
                        delete ptr;
                        ptr = nullptr;
                        --m_size;
                        m_tail->next = nullptr;
                        lk.unlock();
                        break;
                    }
                    prev->next = curr->next;
                    delete curr;
                    curr = nullptr;
                    --m_size;
                    lk.unlock();
                    break;
                }
                lk.unlock();
                if (curr->next != nullptr) {
                    curr = curr->next;
                    prev = prev->next;
                }
            }
        }

        // erase element from list. kills pointer
        void erase(T &data) {
            if (m_size == 0) {
                return;
            }
            Node *prev = m_head;
            Node *curr = m_head->next;
            if (data == *prev->data) {
                Node *ptr = m_head;
                std::unique_lock<std::recursive_mutex> lk(m_head->m);
                m_head = m_head->next;
                delete *ptr->data;//TODO (Rinat):Note that operator * has LESS priority then ->. If this code is correct please place () where it is needed to clarify code and notify me.
                delete ptr;
                ptr = nullptr;
                --m_size;
                if (m_size == 0) {
                    m_tail = nullptr;
                    m_head = nullptr;
                    return;
                }
                lk.unlock();
                curr = nullptr;
            }
            while (curr) {
                std::unique_lock<std::recursive_mutex> lk(curr->m);
                if (*curr->data == data) {
                    if (data == *m_tail->data) {
                        Node *ptr = m_tail;
                        m_tail = prev;
                        delete *ptr->data;//TODO same here
                        delete ptr;
                        ptr = nullptr;
                        --m_size;
                        m_tail->next = nullptr;
                        lk.unlock();
                        break;
                    }
                    prev->next = curr->next;
                    delete *curr->data;//TODO and here
                    delete curr;
                    curr = nullptr;
                    --m_size;
                    lk.unlock();
                    break;
                }
                lk.unlock();
                if (curr->next != nullptr) {
                    curr = curr->next;
                    prev = prev->next;
                }
            }
        }

        // remove entire node from list. kills pointer to data.
        void erase(Node *value) {
            if (m_size == 0) {
                return;
            }
            Node *prev = m_head;
            Node *curr = m_head->next;
            if (value == prev) {
                Node *ptr = m_head;
                std::unique_lock<std::recursive_mutex> lk(m_head->m);
                m_head = m_head->next;
                delete *ptr->data;
                delete ptr;
                ptr = nullptr;
                --m_size;
                if (m_size == 0) {
                    m_tail = nullptr;
                    m_head = nullptr;
                    return;
                }
                lk.unlock();
                curr = nullptr;
            }
            while (curr) {
                std::unique_lock<std::recursive_mutex> lk(curr->m);
                if (curr == value) {
                    if (value == m_tail) {
                        Node *ptr = m_tail;
                        m_tail = prev;
                        delete *ptr->data;
                        delete ptr;
                        ptr = nullptr;
                        --m_size;
                        m_tail->next = nullptr;
                        lk.unlock();
                        break;
                    }
                    prev->next = curr->next;
                    delete *curr->data;
                    delete curr;
                    curr = nullptr;
                    --m_size;
                    lk.unlock();
                    break;
                }
                lk.unlock();
                if (curr->next != nullptr) {
                    curr = curr->next;
                    prev = prev->next;
                }
            }
        }

        /*
            Kinda slow realization
        */
        T &operator[](size_t num) {
            if (num > m_size) throw std::out_of_range("ThreadSafeList::out_of_range");
            Node *curr = m_head;
            for (size_t i = 0; i < num; ++i) {
                curr = curr->next;
            }
            return *curr->data;
        }

    }; // class SuimmList

class A {
    public:
    A() {cout << "A()" << endl;}
    ~A() { cout << "~A()" << endl;}
};

int main ()
{
    A* a = new A();
    
    ThreadSafeList<A*> lst;
    lst.push_back(a);
    lst.erase(a);
    
}






















