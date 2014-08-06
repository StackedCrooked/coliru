namespace Ns
{
    template<typename T>
	class TVector3
	{
		public:
			TVector3();
	};
	
	template<typename T>
	TVector3<T>::TVector3() { }
}

template class Ns::TVector3<float>;

int main() {}