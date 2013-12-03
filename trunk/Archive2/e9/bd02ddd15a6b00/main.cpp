#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>
#include <mutex>
#include <thread>
#include <functional>
#include <memory>

#define EXPIRE_TIME 10
#define EXPIRE_ITEM_SCAN_PERIOD 1

template <typename KeyType, typename DataType>
class ExpiringHashMap
{
private:
    struct interalExpiringItem
	{
		int _expire;
		DataType _value;
	};
	std::mutex HashMapLock;
	std::map<KeyType,interalExpiringItem> ExpiringMap;
public:
	explicit ExpiringHashMap();
	void InsertElement(KeyType key, DataType value);
	DataType GetElement(KeyType key);
	void RemoveElement(KeyType key);
	void HashResourceCollector();
	int _expire;
	std::string _value;
};

template <typename KeyType, typename DataType>
ExpiringHashMap<KeyType, DataType>::ExpiringHashMap()
{
	// Initialize expiring hashMap
	auto bound = std::bind(&ExpiringHashMap<KeyType, DataType>::HashResourceCollector, this);
	std::thread t(bound);
	t.detach();
}

template <typename KeyType, typename DataType>
void ExpiringHashMap<KeyType, DataType>::InsertElement(KeyType key, DataType value)
{
	typename std::map<KeyType,interalExpiringItem>::iterator it;
	struct interalExpiringItem item;
	item._expire = time(NULL) + EXPIRE_TIME;
	item._value = value;
	
	HashMapLock.lock();
	it = ExpiringMap.find(key);
	if (it == ExpiringMap.end())
	{
		ExpiringMap[key] = item;
	}
	else
	{
		// Unexpected, write some log.
	}
	HashMapLock.unlock();
}

template <typename KeyType, typename DataType>
DataType ExpiringHashMap<KeyType, DataType>::GetElement(KeyType key)
{
	typename std::map<KeyType,interalExpiringItem>::iterator it;
	DataType result;
	
	HashMapLock.lock();
	it = ExpiringMap.find(key);
	if (it != ExpiringMap.end())
	{
		result = ExpiringMap[key]._value;
	}
	HashMapLock.unlock();
	
	return result;
}

template <typename KeyType, typename DataType>
void ExpiringHashMap<KeyType, DataType>::RemoveElement(KeyType key)
{
	typename std::map<KeyType,interalExpiringItem>::iterator it;
	
	HashMapLock.lock();
	it = ExpiringMap.find(key);
	if (it != ExpiringMap.end())
	{
		ExpiringMap.erase(it);
	}
	HashMapLock.unlock();
}

template <typename KeyType, typename DataType>
void ExpiringHashMap<KeyType, DataType>::HashResourceCollector()
{
	typename std::map<KeyType,interalExpiringItem>::iterator it;
	typename std::map<KeyType,interalExpiringItem>::iterator toErase;
	KeyType key;
	struct interalExpiringItem item;
	
	while (1)
	{
		HashMapLock.lock();
		it = ExpiringMap.begin();
		while (it != ExpiringMap.end())
		{
			key = it->first;
			item = it->second;

			if (time(NULL) > item._expire)
			{
				toErase = it;
				++it;
				ExpiringMap.erase(toErase);
			}
			else
			{
				++it;
			}
		}
		HashMapLock.unlock();
		sleep(EXPIRE_ITEM_SCAN_PERIOD);
	}
}

int main()
{	
	ExpiringHashMap<std::string, std::string> map;
    map.InsertElement(std::move("123"), std::move("456"));
    sleep(EXPIRE_TIME + 2);
	printf("Get result : %s\r\n", map.GetElement(std::move("123")).c_str());
	
	return 0;
}