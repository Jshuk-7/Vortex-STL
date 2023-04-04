#pragma once

#include <iterator>
#include <cstdint>
#include <cstddef>
#include <memory>

namespace vstl {

	// Scoped Vector
	template <typename T>
	class stack_vector
	{
	public:
		struct iterator
		{
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer_type = value_type*;
			using reference_type = value_type&;

			iterator()
				: m_Ptr(nullptr) { }
			iterator(std::nullptr_t)
				: m_Ptr(nullptr) { }
			iterator(pointer_type ptr)
				: m_Ptr(ptr) { }

			reference_type operator*() { return *m_Ptr; }
			pointer_type operator->() { return m_Ptr; }

			// prefix
			iterator& operator++()
			{
				m_Ptr++;
				return *this;
			}

			// postfix
			iterator operator++(int index)
			{
				iterator temp = *this;
				++(*this);
				return temp;
			}

			friend bool operator==(const iterator& lhs, const iterator& rhs)
			{
				return lhs.m_Ptr == rhs.m_Ptr;
			}

			friend bool operator!=(const iterator& lhs, const iterator& rhs)
			{
				return !(lhs == rhs);
			}

		private:
			pointer_type m_Ptr = nullptr;
		};

		struct const_iterator
		{
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = const T;
			using pointer_type = value_type*;
			using reference_type = value_type&;

			const_iterator()
				: m_Ptr(nullptr) { }
			const_iterator(std::nullptr_t)
				: m_Ptr(nullptr) { }
			const_iterator(pointer_type ptr)
				: m_Ptr(ptr) { }

			reference_type operator*() const { return *m_Ptr; }
			pointer_type operator->() const { return m_Ptr; }

			// prefix
			const const_iterator& operator++() const
			{
				m_Ptr++;
				return *this;
			}

			// postfix
			const_iterator operator++(int index) const
			{
				const_iterator temp = *this;
				++(*this);
				return temp;
			}

			friend bool operator==(const const_iterator& lhs, const const_iterator& rhs)
			{
				return lhs.m_Ptr == rhs.m_Ptr;
			}

			friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs)
			{
				return !(lhs == rhs);
			}

		private:
			mutable pointer_type m_Ptr = nullptr;
		};

		struct reverse_iterator
		{
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer_type = value_type*;
			using reference_type = value_type&;

			reverse_iterator()
				: m_Ptr(nullptr) { }
			reverse_iterator(std::nullptr_t)
				: m_Ptr(nullptr) { }
			reverse_iterator(pointer_type ptr)
				: m_Ptr(ptr) { }

			reference_type operator*() { return *m_Ptr; }
			pointer_type operator->() { return m_Ptr; }

			// prefix
			reverse_iterator& operator++()
			{
				m_Ptr--;
				return *this;
			}

			// postfix
			reverse_iterator operator++(int index)
			{
				reverse_iterator temp = *this;
				++(*this);
				return temp;
			}

			friend bool operator==(const reverse_iterator& lhs, const reverse_iterator& rhs)
			{
				return lhs.m_Ptr == rhs.m_Ptr;
			}

			friend bool operator!=(const reverse_iterator& lhs, const reverse_iterator& rhs)
			{
				return !(lhs == rhs);
			}

		private:
			pointer_type m_Ptr = nullptr;
		};

		struct const_reverse_iterator
		{
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = const T;
			using pointer_type = value_type*;
			using reference_type = value_type&;

			const_reverse_iterator()
				: m_Ptr(nullptr) { }
			const_reverse_iterator(std::nullptr_t)
				: m_Ptr(nullptr) { }
			const_reverse_iterator(pointer_type ptr)
				: m_Ptr(ptr) { }

			reference_type operator*() const { return *m_Ptr; }
			pointer_type operator->() const { return m_Ptr; }

			// prefix
			const const_reverse_iterator& operator++() const
			{
				m_Ptr--;
				return *this;
			}

			// postfix
			const_reverse_iterator operator++(int index) const
			{
				const_reverse_iterator temp = *this;
				++(*this);
				return temp;
			}

			friend bool operator==(const const_reverse_iterator& lhs, const const_reverse_iterator& rhs)
			{
				return lhs.m_Ptr == rhs.m_Ptr;
			}

			friend bool operator!=(const const_reverse_iterator& lhs, const const_reverse_iterator& rhs)
			{
				return !(lhs == rhs);
			}

		private:
			mutable pointer_type m_Ptr = nullptr;
		};

	public:
		stack_vector()
		{
			Resize(2);
			m_Size = 0;
		}

		stack_vector(uint32_t count, const T& value)
		{
			Resize(count);
			
			for (uint32_t i = 0; i < count; i++)
				m_Data[i] = value;

			m_Size = m_Capacity;
		}

		stack_vector(const std::initializer_list<T>& list)
		{
			Resize(list.size());

			uint32_t i = 0;
			for (const auto& element : list)
				m_Data[i++] = element;

			m_Size = list.size();
		}

		stack_vector(stack_vector<T>&& other)
		{
			Resize(other.m_Size);
			m_Data = std::move(other.m_Data);
			m_Size = other.m_Size;
		}

		stack_vector(const stack_vector<T>& other)
		{
			Resize(other.m_Size);
			memcpy((void*)m_Data, (void*)other.m_Data, other.m_Size * sizeof(T));
			m_Size = other.m_Size;
		}

		~stack_vector()
		{
			delete[] m_Data;
		}

		void PushBack(const T& value)
		{
			if (m_Size >= m_Capacity)
				Resize(m_Size * 2);

			m_Data[m_Size++] = value;
		}

		void PopBack()
		{
			m_Data[m_Size - 1] = T();
			m_Size--;
		}

		void Resize(uint32_t newSize)
		{
			ReAlloc(newSize);
			m_Capacity = newSize;
		}

		T& Front()
		{
			return m_Data[0];
		}
		const T& Front() const
		{
			return m_Data[0];
		}

		T& Back()
		{
			return m_Data[m_Size - 1];
		}
		const T& Back() const
		{
			return m_Data[m_Size - 1];
		}

		constexpr uint32_t Size() const { return m_Size; }
		constexpr uint32_t Capacity() const { return m_Capacity; }
		bool Empty() const { return m_Size == 0; }

		void Clear()
		{
			T _default = T();
			memcpy((void*)m_Data, (void*)&_default, m_Size * sizeof(T));
			m_Size = 0;
		}

		T* Data()
		{
			return &m_Data[0];
		}
		const T* Data() const
		{
			return &m_Data[0];
		}

		T& operator[](uint32_t index)
		{
			return m_Data[index];
		}
		const T& operator[](uint32_t index) const
		{
			return m_Data[index];
		}

		iterator begin() { return iterator(&m_Data[0]); }
		iterator end() { return iterator(&m_Data[m_Size]); }
		iterator begin() const { return iterator(&m_Data[0]); }
		iterator end() const { return iterator(&m_Data[m_Size]); }

		const_iterator cbegin() const { return const_iterator(&m_Data[0]); }
		const_iterator cend() const { return const_iterator(&m_Data[m_Size]); }
		const_reverse_iterator crbegin() const { return const_reverse_iterator(&m_Data[m_Size - 1]); }
		const_reverse_iterator crend() const { return const_reverse_iterator(&m_Data[0] - 1); }

		reverse_iterator rbegin() { return reverse_iterator(&m_Data[m_Size - 1]); }
		reverse_iterator rend() { return reverse_iterator(&m_Data[0] - 1); }
		reverse_iterator rbegin() const { return reverse_iterator(&m_Data[m_Size - 1]); }
		reverse_iterator rend() const { return reverse_iterator(&m_Data[0] - 1); }

	private:
		void ReAlloc(uint32_t newSize)
		{
			uint32_t originalSize = m_Size;
			T* temp = new T[originalSize]();
			memcpy((void*)temp, (void*)m_Data, originalSize * sizeof(T));

			delete[] m_Data;

			m_Data = new T[newSize]();
			memcpy((void*)m_Data, (void*)temp, originalSize * sizeof(T));

			delete[] temp;
		}

	private:
		T* m_Data = nullptr;
		uint32_t m_Size = 0;
		uint32_t m_Capacity = 0;
	};

}
