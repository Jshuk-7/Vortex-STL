#pragma once

#include <iterator>
#include <cstdint>
#include <cstddef>

namespace vstl {

	// Scoped array
	template <typename T, uint32_t Count>
	class stack_array
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
		stack_array(const T& value)
		{
			for (uint32_t i = 0; i < Count; i++)
				m_Data[i] = value;
		}

		constexpr uint32_t Size() const { return Count; }

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
		iterator end() { return iterator(&m_Data[Count]); }
		iterator begin() const { return iterator(&m_Data[0]); }
		iterator end() const { return iterator(&m_Data[Count]); }

		const_iterator cbegin() const { return const_iterator(&m_Data[0]); }
		const_iterator cend() const { return const_iterator(&m_Data[Count]); }
		const_reverse_iterator crbegin() const { return const_reverse_iterator(&m_Data[Count - 1]); }
		const_reverse_iterator crend() const { return const_reverse_iterator(&m_Data[0] - 1); }

		reverse_iterator rbegin() { return reverse_iterator(&m_Data[Count - 1]); }
		reverse_iterator rend() { return reverse_iterator(&m_Data[0] - 1); }
		reverse_iterator rbegin() const { return reverse_iterator(&m_Data[Count - 1]); }
		reverse_iterator rend() const { return reverse_iterator(&m_Data[0] - 1); }

	private:
		T m_Data[Count];
	};

}
