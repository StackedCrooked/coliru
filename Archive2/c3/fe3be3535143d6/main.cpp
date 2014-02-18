#include <deque>
#include <memory>
#include <vector>

template <typename T> class ResourcePool;

template <typename T>
class ResourcePoolManager {
public:
    ResourcePoolManager(ResourcePool<T> & pool)
    : pool(&pool)
    {
    }

    void operator()(T* releasedResource) const {
        pool->releaseResource(releasedResource);
    }
private:
    ResourcePool<T>* pool;
};

template <typename T>
class ResourcePool {
public:
    ResourcePool()
    : manager(*this)
    {
    }

    std::unique_ptr<T, ResourcePoolManager<T>> requestResource() {
        if(availableResources.size() == 0) {
            return std::unique_ptr<T, ResourcePoolManager<T>>(NULL, manager);
        } else {
            T * resource = availableResources.front();
            availableResources.pop_front();
            return std::unique_ptr<T, ResourcePoolManager<T>>(resource, manager);
        }
    }
private:
    friend class ResourcePoolManager<T>;

    void releaseResource(T * releasedResource) {
        availableResources.push_back(releasedResource);
    }

    ResourcePoolManager<T> manager;
    std::deque<T *> availableResources;
    std::deque<T *> allResources;
};

struct OpenCLDevice {};

int main() {
    ResourcePool<OpenCLDevice> computeDevicePool;
    std::unique_ptr<OpenCLDevice, ResourcePoolManager<OpenCLDevice>> devicePtr = computeDevicePool.requestResource();
    std::vector<std::unique_ptr<OpenCLDevice, ResourcePoolManager<OpenCLDevice>>> gpus;
    gpus.push_back(std::move(devicePtr));
}
