#ifndef __Container_H_
#define __Container_h_

#include < stdexcept >

template< class T > 
class Element {
public:
	Element< T >( T const & iElem ) {
		value = iElem;
		prev = next = nullptr;
	}

	T value;
	Element< T > * next;
	Element< T > * prev;

};

template< class T >
class Container {
public:
	Container() {
		m_head = m_tail = nullptr;
		m_size = 0;
	}
	explicit Container( T & iElem ){
		m_head = new Element< T >( iElem );
		m_tail = m_head;
		m_size = 1;
	}
	~Container(){
		Clear();
	}

	void PushFirstElem( T const & iElem ) {
		Element< T > * firstElem = new Element< T >( iElem );
		if (! Empty() ) {
			m_head->prev = firstElem;
			firstElem->next = m_head;
			m_head = firstElem;
		} else {
			m_head = firstElem;
			m_tail = m_head;
		}
		++ m_size;
	}
	void PushLastElem( T const & iElem ) {
		Element< T > * lastElem = new Element< T >( iElem );
		if ( ! Empty() ) {
			m_tail->next = lastElem;
			lastElem->prev = m_tail;
			m_tail = lastElem;
		} else {
			m_tail = lastElem;
			m_head = m_tail;
		}
		++ m_size;
	}
	int PopFistElem() {
		if ( ! Empty() ) {
			if ( m_size != 1 ) {
				m_head = m_head->next;
				delete m_head->prev;
				m_head->prev = nullptr;
			} else {
				delete m_head;
				m_tail = nullptr;
			}
			-- m_size;
		} else {
			throw std::invalid_argument( "You remove from the empty container." );
		}
		return 1;
	}
	int PopLastElem() {
		if ( ! Empty ) {
			if ( m_size != 1 ){
				m_tail = m_tail->prev;
				delete m_tail->next;
				m_tail->next = nullptr;
			} else {
				delete m_tail;
				m_head = nullptr;
			}
			-- m_size;
		} else {
			throw std::invalid_argiment( "You remove from the empty container." );
		}
		return 1;
	}
	T const * GetFistElem() {
		return & m_head->value;
	}
	T const * GetLastElem() {
		return & m_tail->value;
	}
	T const * GetElem( size_t iIndex ) {
		if( iIndex > m_size ) {
			throw std::invalid_argument( "The requested element does not exist." );
		} else {
			Element< T > * elSearch = m_head;
			while ( iIndex > 0 ) {
				elSearch = elSearch->next;
				-- iIndex;
			}
			return & elSearch->value;
		}
	}
	size_t GetCount() {
		return m_size;
	}
	bool Empty() {
		if ( m_size == 0 ) {
			return true;
		} else {
			return false;
		}
	}
	void Clear() {
		while( ! Empty() ) {
			try {
				PopFistElem();
			}
			catch( std::invalid_argument & except ) {
				std::cerr << except.what() << std::endl;
			}
		}
	}
private:
	Element< T > * m_head;
	Element< T > * m_tail;
	size_t m_size;
};

#endif // __Container_H_
