#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>

#define EXPIRE_TIME 10
#define EXPIRE_ITEM_SCAN_PERIOD 1

#define __LOCK_TYPE__ pthread_mutex_t
#define __INIT_LOCK__(S) pthread_mutex_init(S, NULL)
#define __LOCK__(S) pthread_mutex_lock(S)
#define __UNLOCK__(S) pthread_mutex_unlock(S)
#define __DESTROY_LOCK__(S) pthread_mutex_destroy(S)

struct ExpiringItem
{
    int _expire;
	std::string _value;
};

__LOCK_TYPE__ HashMapLock;
std::map<std::string,ExpiringItem> ExpiringMap;

void InsertElement(std::string key, std::string value)
{
	std::map<std::string,ExpiringItem>::iterator it;
	struct ExpiringItem item;
	item._expire = time(NULL) + EXPIRE_TIME;
	item._value = value;
	
	__LOCK__(&HashMapLock);
	it = ExpiringMap.find(key);
	if (it == ExpiringMap.end())
	{
		ExpiringMap[key] = item;
	}
	else
	{
		// Unexpected, write some log.
	}
	__UNLOCK__(&HashMapLock);
}

std::string GetElement(std::string key)
{
	std::map<std::string,ExpiringItem>::iterator it;
	std::string result = "";
	
	__LOCK__(&HashMapLock);
	it = ExpiringMap.find(key);
	if (it != ExpiringMap.end())
	{
		result = ExpiringMap[key]._value;
	}
	__UNLOCK__(&HashMapLock);
	
	return result;
}

void RemoveElement(std::string key)
{
	std::map<std::string,ExpiringItem>::iterator it;
	
	__LOCK__(&HashMapLock);
	it = ExpiringMap.find(key);
	if (it != ExpiringMap.end())
	{
		ExpiringMap.erase(it);
	}
	__UNLOCK__(&HashMapLock);
}

void* HashResourceCollector(void *parm)
{
	std::map<std::string,ExpiringItem>::iterator it;
	std::map<std::string,ExpiringItem>::iterator toErase;
	std::string key;
	struct ExpiringItem item;
	
	while (1)
	{
		__LOCK__(&HashMapLock);
		it = ExpiringMap.begin();
		while (it != ExpiringMap.end())
		{
			key = it->first;
			item = it->second;

			if (time(NULL) > item._expire)
			{
				toErase = it;
				++it;
				printf("Delete object called [%s]\r\n", key.c_str());
				ExpiringMap.erase(toErase);
			}
			else
			{
				++it;
			}
		}
		__UNLOCK__(&HashMapLock);
		sleep(EXPIRE_ITEM_SCAN_PERIOD);
	}
}

int main()
{
	__INIT_LOCK__(&HashMapLock);
	
	// Initialize expiring hashMap
	pthread_t thread;
	pthread_create(&thread, NULL, HashResourceCollector, NULL);
	pthread_detach(thread);
	
	// Test
	InsertElement("123", "456");
	sleep(EXPIRE_TIME + 2);
	printf("Get result : %s\r\n", GetElement("123").c_str());
	return 0;
}