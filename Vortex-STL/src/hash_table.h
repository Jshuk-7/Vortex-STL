#pragma once

#include "stack_vector.h"

#include <algorithm>

namespace vstl {

	template <typename TKey, typename TValue>
	class hash_table
	{
	public:
		hash_table()
		{
		}

		void Insert(const TKey& key, const TValue& value)
		{
			uint64_t hash = Hash(key);
			auto it = std::find(m_HashedKeys.begin(), m_HashedKeys.end(), hash);
			if (it != m_HashedKeys.end())
			{
				return;
			}

			m_HashedKeys.PushBack(hash);
			m_Data.PushBack(value);
		}

		TValue& operator[](const TKey& key)
		{
			uint64_t hash = Hash(key);
			auto it = std::find(m_HashedKeys.begin(), m_HashedKeys.end(), hash);
			if (it == m_HashedKeys.end())
			{
				// TODO assert here
			}

			auto pos = it - m_HashedKeys.begin();
			return m_Data[pos];
		}

	private:
		uint64_t Hash(const TKey& key)
		{
			uint64_t hash = 0;
			hash += sizeof(TKey);
			hash += (uint64_t)key << 4 * (hash << std::distance(m_HashedKeys.begin(), m_HashedKeys.end()));
			return hash;
		}

	private:
		vstl::stack_vector<uint64_t> m_HashedKeys;
		vstl::stack_vector<TValue> m_Data;
	};

}
