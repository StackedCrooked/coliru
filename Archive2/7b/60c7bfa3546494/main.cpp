#include <cstdint>

template<class T>
struct pod_version{
    private:
        alignas(T) uint8_t m_data[sizeof(T)];
    public:
        pod_version()=default;
        pod_version(const pod_version&)=default;
        pod_version(pod_version&&)=default;
        ~pod_version()=default;
        pod_version& operator=(const pod_version&)=default;
        pod_version& operator=(pod_version&&)=default;

        template<class...V>void construct(V&&...v){
            new (m_data) T((V&&)v...);
        }

        void destroy(){
            ((T*)m_data)->~T(); // g++: warning typed punned blah im allowed to break ur code LOL
            ((T*)this)->~T(); // g++: :D
        }
};

int main()
{
    pod_version<int> p;
}