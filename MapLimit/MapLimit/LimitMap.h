#ifndef _LIMIT_MAP_H_
#define _LIMIT_MAP_H_

#include <map>

template <typename T, typename V>
class LimitMap {
public:
	LimitMap(int size = (1 << 16)) { 
		m_nSize = size;
		m_pHead = new T_DoubleLink;
		m_pHead->prev = m_pHead->next = m_pHead;
	}

	typedef struct tag_DoubleLink {
		tag_DoubleLink* next = NULL;
		tag_DoubleLink* prev = NULL;
		T key = T();
		V value = V();
	} T_DoubleLink;

	void set(T key, V value) {
		if (m_MapValue.size() == m_nSize) {
			// remove first element
			T_DoubleLink* cur = m_pHead->next;
			cur->next->prev = cur->prev;
			cur->prev->next = cur->next;
			m_MapValue.erase(cur->key);
			delete cur;
		}

		T_DoubleLink* pLink = new T_DoubleLink;
		if (!pLink) {
			return;
		}
		pLink->value = value;
		pLink->key = key;

		pLink->prev = m_pHead->prev;
		pLink->next = m_pHead;
		pLink->prev->next = pLink;
		pLink->next->prev = pLink;
		m_MapValue[key] = pLink;
	}

	V get(T key) {
		if (has(key)) {
			T_DoubleLink* pCurrent = m_MapValue[key];
			
			// remove pCurrent from list
			pCurrent->prev->next = pCurrent->next;
			pCurrent->next->prev = pCurrent->prev;

			// add pCurrent to the end of list
			pCurrent->next = m_pHead;
			pCurrent->prev = m_pHead->prev;
			pCurrent->prev->next = pCurrent;
			pCurrent->next->prev = pCurrent;

			return pCurrent->value;
		}
		return V();
	}

	bool has(T key) {
		return m_MapValue.count(key) > 0;
	}

	void erase(T key) {
		m_MapValue.erase(key);
	}

	void clear() {
		m_MapValue.clear();
	}

	size_t size() {
		return m_MapValue.size();
	}
private:
	std::map<T, T_DoubleLink*> m_MapValue;
	int m_nSize;
	T_DoubleLink *m_pHead;
};

#endif	/* _LIMIT_MAP_H_ */