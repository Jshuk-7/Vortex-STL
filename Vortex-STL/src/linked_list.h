#pragma once

#include <functional>
#include <cstdint>

namespace vstl {

	template <typename T>
	class linked_list
	{
	public:
		using DataType = T;

		struct Node
		{
			DataType Data;
			Node* Next = nullptr;
		};

	public:
		linked_list(DataType start)
		{
			m_Start = new Node();
			m_Start->Data = start;
			m_Start->Next = nullptr;
			m_Size = 1;
		}

		linked_list()
		{
			m_Start = nullptr;
			m_Size = 0;
		}

		void Add(DataType data)
		{
			Node** node = nullptr;
			if (!m_Start)
				node = &m_Start;
			else
			{
				Node* end = End();
				node = &end->Next;
			}

			*node = new Node();
			(*node)->Data = data;
			(*node)->Next = nullptr;

			m_Size++;
		}

		bool Remove(Node* node)
		{
			bool success = false;
			Node** temp = &m_Start;
			Node** last = temp;

			for (;;)
			{
				if (*temp == node)
				{
					(*last)->Next = (*temp)->Next ? (*temp)->Next : nullptr;
					success = true;
					break;
				}

				if (!(*temp)->Next)
					break;

				last = temp;
				temp = &(*temp)->Next;
			}

			m_Size--;
			return success;
		}

		void ForEach(const std::function<void(DataType&)>& func)
		{
			Node* node = m_Start;

			for (;;)
			{
				func(node->Data);

				if (!node->Next)
					break;

				node = node->Next;
			}
		}

		Node* Begin() { return m_Start; }
		const Node* Begin() const { return Begin(); }

		Node* End()
		{
			Node* node = m_Start;

			for (;;)
			{
				if (node->Next)
					node = node->Next;
				else
					break;
			}

			return node;
		}

		const Node* End() const
		{
			return End();
		}

		uint32_t Size() const { return m_Size; }

	private:
		Node* m_Start = nullptr;
		uint32_t m_Size = 0;
	};

}
