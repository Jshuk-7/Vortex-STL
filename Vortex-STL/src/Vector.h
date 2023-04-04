#pragma once

#include <cstdint>
#include <memory>
#include <iterator>
#include <cstddef>

namespace vstl {

	// Scoped Stack Vector
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
			const_iterator& operator++() const
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
			pointer_type m_Ptr = nullptr;
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
				--(*this);
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
			const_reverse_iterator& operator++() const
			{
				m_Ptr--;
				return *this;
			}

			// postfix
			const_reverse_iterator operator++(int index) const
			{
				const_reverse_iterator temp = *this;
				--(*this);
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
			pointer_type m_Ptr = nullptr;
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

			for (uint32_t i = 0; i < m_Capacity; i++)
				m_Data[i] = value;

			m_Size = m_Capacity;
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
			for (uint32_t i = 0; i < m_Size; i++)
				m_Data[i] = T();

			m_Size = 0;
		}

		T* Data()
		{
			return &m_Data[0];
		}
		T* Data() const
		{
			return &m_Data[0];
		}

		T& operator[](uint32_t index)
		{
			return m_Data[index];
		}

		iterator begin() { return iterator(&m_Data[0]); }
		iterator end() { return iterator(&m_Data[m_Size]); }

		const_iterator cbegin() const { return const_iterator(&m_Data[0]); }
		const_iterator cend() const { return const_iterator(&m_Data[m_Size]); }

		reverse_iterator rbegin() { return reverse_iterator(&m_Data[m_Size]); }
		reverse_iterator rend() { return reverse_iterator(&m_Data[0]); }

		const_reverse_iterator crbegin() const { return const_reverse_iterator(&m_Data[m_Size]); }
		const_reverse_iterator crend() const { return const_reverse_iterator(&m_Data[0]); }

	private:
		void ReAlloc(uint32_t newSize)
		{
			uint32_t originalSize = m_Size;
			T* temp = new T[originalSize]();
			memcpy(temp, m_Data, originalSize * sizeof(T));

			delete[] m_Data;

			m_Data = new T[newSize]();
			for (uint32_t i = 0; i < originalSize; i++)
				m_Data[i] = temp[i];

			delete[] temp;
		}

	private:
		T* m_Data = nullptr;
		uint32_t m_Size = 0;
		uint32_t m_Capacity = 0;
	};

}
