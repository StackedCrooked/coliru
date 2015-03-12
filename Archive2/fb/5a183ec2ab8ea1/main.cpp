
// The ABA problem: this won't compile
//  namespace A { using namespace B; } // error: B is not a namespace
//  namespace B { using namespace A; }


// Solution to the ABA problem:
namespace A { }
namespace B { using namespace A; }
namespace A { using namespace B; }






