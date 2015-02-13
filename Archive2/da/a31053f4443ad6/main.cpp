// VigVersion.hpp
//#ifndef VIG_H
//#include "./VigCore/VigHeader.hpp"
//#endif

#include <cwchar>
#include <iostream>
using namespace std;

class VigVersion
{
private:
    wstring _Name;
	long _Release;
	long _Patch;
	long _Hotfix;
	long _Build;
public:
    inline bool operator>=(VigVersion& rhs)
    {
        if ( GetBuild() >= rhs.GetBuild() )
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    inline VigVersion& operator++()
    {
        ++_Build;
        return *this;
    };
	inline wstring& GetName()
	{
		return _Name;
	};
	inline long GetPatch()
	{
		return _Patch;
	};
	inline long GetBuild()
	{
		return _Build;
	};
	inline long GetRelease()
	{
		return _Release;
	};
	inline long GetHF()
	{
		return _Hotfix;
	};
	inline VigVersion()
	{
        _Name    = L"VigVersionTemplate";
		_Release = 0;
		_Patch 	 = 0;
		_Hotfix  = 0;
		_Build   = 0;
	};
	inline VigVersion(VigVersion& Ver)
	{
        _Name    = Ver.GetName();
		_Release = Ver.GetRelease();
		_Patch   = Ver.GetPatch();
		_Hotfix  = Ver.GetHF();
		_Build   = Ver.GetBuild();
	};
    inline VigVersion(VigVersion* Ver)
    {
        _Name    = Ver -> GetName();
        _Release = Ver -> GetRelease();
        _Patch   = Ver -> GetPatch();
        _Hotfix  = Ver -> GetHF();
        _Build   = Ver -> GetBuild();
    };
	inline wstring* GetStamp()
	{
		static wstring Stamp = L"";
		Stamp += _Name;
		Stamp += L" Ver. ";
		Stamp += GetRelease();
		Stamp += GetPatch();
		Stamp += GetHF();
		Stamp += GetBuild();
		return &Stamp;
	};
};

int main()
{
    VigVersion VV1;
    return 0;  
}