#include <iostream>
#include <list>
#include <vector>

void func(int required, int required2[], double* optional1 = NULL, double* optional2 = NULL) {
  if (optional1) {
    std::cout << "optional1: " << *optional1 << "\n";
  }

  if (optional2) {
    std::cout << "optional2: " << *optional2 << "\n";
  }

  std::cout << required << "\n";
  std::cout << required2[0] << "\n";
}

template <class opt1_type = std::vector<double>,
          class opt2_type = std::vector<double> >
struct func_functor {
  template <class required2_type>
  void operator()(int required, required2_type required2,
                  opt1_type* opt1 = NULL, opt2_type* opt2 = NULL) const {
    double *opt1_ptr = (opt1) ? &opt1->front() : NULL;
    double *opt2_ptr = (opt2) ? &opt2->front() : NULL;
    func(required, &required2[0], opt1_ptr, opt2_ptr);
  }
};

template <class opt1_type>
func_functor<opt1_type> make_func_opt1(const opt1_type&) {
  return func_functor<opt1_type>();
}

template <class opt2_type>
func_functor<std::vector<double>, opt2_type> make_func_opt2(const opt2_type&) {
  return func_functor<std::vector<double>, opt2_type>();
}

template <class opt1_type, class opt2_type>
func_functor<opt1_type, opt2_type> make_func(const opt1_type&,
                                             const opt2_type&) {
  return func_functor<opt1_type, opt2_type>();
}

int main() {
  int array[] = {42};
  std::vector<int> array2;
  array2.push_back(42);

  // Base function
  func(0, array);
  double a = 3.;
  double b = 4.;
  func(1, array, &a);
  func(2, array,NULL, &b);
  func(3, array, &a, &b);

  // "Convenience" functor
  func_functor<> func2;
  func2(4, array2);

  func_functor<std::list<double> > func3;
  std::list<double> a_list;
  a_list.push_back(5.);
  func3(5, array2, &a_list);

  func_functor<std::vector<double>, std::list<double> > func4;
  std::vector<double> a_vec;
  a_vec.push_back(6.);
  func4(6, array2, &a_vec, &a_list);

  // Convenience functor-function!
  make_func_opt1(a_list)(7, array2, &a_list);

  make_func_opt2(a_list)(8, array2, NULL, &a_list);
  
  make_func(a_vec, a_list)(9, array2, &a_vec, &a_list);

  return 0;
}
