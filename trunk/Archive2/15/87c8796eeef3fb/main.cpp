// #include <type_traits>
// #include <memory>
// #include <vector>
// #include <array>
// #include <string>
// #include <algorithm>
// #include <numeric>
// #include <iostream>
//
// using namespace std;
//
// int main ()
// {
//     cout << "Hello, world!" << endl;
// }


#include <type_traits>
#include <memory>

//-----------------------------------------------------------------------------
// arbitrary stuff to fill in missing pieces of original code

struct AbstractGeometry {
    bool IsEnabled() { return false; }
	bool GetMoveZToFirstInteraction() { return false; }
};

struct AbstractScorer
{
	AbstractScorer(...) {}
	double material_rad_len;
	void SetEvent(...) {}
	void CloseAfterRunEnd() {}
};

struct invariant_error { invariant_error(const char*) {} };
struct GodObject { static double GetEcut() { return 0; } };
struct XYZHit { int x,y,z; double GetParticleKineticEnergy() const { return 0; } };

//-----------------------------------------------------------------------------
// original code at http://codereview.stackexchange.com/q/47083/39083

class XYZScorer: public virtual AbstractScorer{
public:

    XYZScorer(double material_rad_len=-1):
        AbstractScorer(material_rad_len){;}

    virtual void RegisterHit(const XYZHit hit)=0;

};

class SomeScorer: public virtual XYZScorer{
public:

    SomeScorer(double material_rad_len=-1):
        XYZScorer(material_rad_len){;}

    virtual void RegisterHit(const XYZHit) {}

};

template <typename Scorer>
class ScorerDecorator: public virtual XYZScorer{

protected:
    Scorer scorer;
public:
    ScorerDecorator(Scorer scorer): XYZScorer(scorer.material_rad_len), scorer(scorer){;}
    virtual ~ScorerDecorator(){}

    virtual void SetEvent(size_t new_incident){
        scorer.SetEvent(new_incident);
    }

    virtual void CloseAfterRunEnd(){
        scorer.CloseAfterRunEnd();
    }
};

template <typename Scorer>
class FixZToFirstInteractionScorer: public virtual ScorerDecorator<Scorer>{
private:
    bool fixed_in_this_event=false;
    double position_of_first_intraction=0;
public:

    FixZToFirstInteractionScorer(Scorer scorer): ScorerDecorator<Scorer>(scorer){}
    virtual ~FixZToFirstInteractionScorer(){}

    virtual void SetEvent(size_t new_incident){
        fixed_in_this_event=false;
        ScorerDecorator<Scorer>::SetEvent(new_incident);
    }

    virtual void RegisterHit(const XYZHit hit){
        if(!fixed_in_this_event){
            fixed_in_this_event=true;
            position_of_first_intraction=hit.z;
        }
        XYZHit fixed_coords = hit;
        fixed_coords.z-=position_of_first_intraction;
        this->scorer.RegisterHit(fixed_coords);
    }

};

template<typename Scorer>
class ApplyEnergyCutsScorer: public virtual ScorerDecorator<Scorer>{
    const double e_cut_energy;
public:
    ApplyEnergyCutsScorer(Scorer scorer):
        ScorerDecorator<Scorer>(scorer), e_cut_energy(GodObject::GetEcut()){}
    virtual ~ApplyEnergyCutsScorer(){}
inline bool accept(const XYZHit hit){
    double kin_energy = hit.GetParticleKineticEnergy();
    if(e_cut_energy < 0){
        return true;
    }
    if (kin_energy <0){
        throw new invariant_error("Energy less than zero --- normally it signifies that step wasnt passed to XYZHit");
    }
    if (kin_energy < e_cut_energy){
        return false;
    }
    return true;
}

virtual void RegisterHit(const XYZHit hit){
    if (accept(hit)){
        this->scorer.RegisterHit(hit);
    }
}

};

template<typename Scorer>
std::shared_ptr<XYZScorer> InitializeAnyScorer(
        std::shared_ptr<AbstractGeometry> geometry, Scorer scorer, double){
    if (!geometry->IsEnabled()){
        return std::shared_ptr<XYZScorer>(0);
    }

    std::shared_ptr<XYZScorer> result_scorer;
    if (!geometry->GetMoveZToFirstInteraction()){
        result_scorer = std::shared_ptr<ApplyEnergyCutsScorer<Scorer>>(
                 new ApplyEnergyCutsScorer<Scorer>(
                         scorer
                 )
             );
    }else{
        result_scorer = std::shared_ptr<FixZToFirstInteractionScorer<ApplyEnergyCutsScorer<Scorer>>>(
                new FixZToFirstInteractionScorer<ApplyEnergyCutsScorer<Scorer>>(
                    ApplyEnergyCutsScorer<Scorer>(
                            scorer
                )
            )
        );
    }

    return result_scorer;
}

//-----------------------------------------------------------------------------
// decorate() implementation

template <typename S>
using result = typename std::result_of<S>::type;

template <template <typename> class E, template <typename> class... D>
struct decorate_impl
{
    template <typename A, typename N = result<decorate_impl<D...>(A)>>
	E<N> operator()(A&& a) const
	{
		return E<N>(decorate_impl<D...>()(std::forward<A>(a)));
	}
};

template <template <typename> class E>
struct decorate_impl <E>
{
	template <typename A, typename N = typename std::decay<A>::type>
	E<N> operator()(A&& a) const { return E<N>(std::forward<A>(a)); }
};

template <template <typename> class E, template <typename> class... D, typename A>
std::shared_ptr <E<result<decorate_impl<D...>(A)>>>
decorate(A&& a)
{
	return std::make_shared <E<result<decorate_impl<D...>(A)>>>
		(decorate_impl<D...>()(std::forward<A>(a)));
}

//-----------------------------------------------------------------------------
// individual decorator functions

template <typename S>
using decay = typename std::decay<S>::type;

template <typename S>
FixZToFirstInteractionScorer<decay<S>> fixZToFirstInteraction(S&& scorer)
{
	return FixZToFirstInteractionScorer<decay<S>>(std::forward<S>(scorer));
}

template <typename S>
ApplyEnergyCutsScorer<decay<S>> applyEnergyCuts(S&& scorer)
{
	return ApplyEnergyCutsScorer<decay<S>>(std::forward<S>(scorer));
}

template<typename S>
std::shared_ptr<decay<S>> share(S&& scorer)
{
	return std::make_shared<decay<S>>(std::forward<S>(scorer));
}

//-----------------------------------------------------------------------------

int main ()
{
	SomeScorer scorer;
	std::shared_ptr<XYZScorer> ptr =
        decorate<FixZToFirstInteractionScorer, ApplyEnergyCutsScorer>(scorer);

	std::shared_ptr<XYZScorer> ptr2 =
        share(fixZToFirstInteraction(applyEnergyCuts(scorer)));

	static_assert(std::is_same<
		decltype(decorate<FixZToFirstInteractionScorer, ApplyEnergyCutsScorer>(scorer)),
		decltype(share(fixZToFirstInteraction(applyEnergyCuts(scorer))))
	>::value, "");
}
