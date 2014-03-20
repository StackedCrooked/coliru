/* 
 * File:   main.cpp
 * Author: Kyle Bentley
 * 
 * Comparison of different ODE algorithms    
 *
 * Created on January 22, 2014, 6:04 PM
 */

#include <cstdlib>
#include <chrono>
#include <functional>
#include <iterator>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Initialize "k" values in the runge-kutta algo.
template<typename functor_type,
         typename coord_type,
         template <typename functor_type> class Container1,
         template <typename coord_type> class Container2,
         typename t_type >
std::vector<double>
init(class Container1<functor_type>::iterator funct_iter1,
     class Container1<functor_type>::iterator funct_iter2,
     class Container2<coord_type>::iterator coord_iter1,
     class Container2<coord_type>::iterator coord_iter2,
     t_type t) ;

// Calculate midpoints in the RK algo.
template<typename T,
         typename coord_type,
         template <typename T> class Container1, 
         template <typename coord_type> class Container2 > 
std::vector<double>
midpt(const Container1<T>& k,
      class Container2<coord_type>::iterator coord_iter1, 
      double h);

// Compute the RK for each coordinate
template<typename T,
         typename coord_type,
         template <typename T> class Container1, 
         template <typename coord_type> class Container2 > 
std::vector<double>
runge_kutta4(class Container2<coord_type>::iterator coord_iter1, 
         class Container2<coord_type>::iterator coord_iter2,
	     class Container1<T>::iterator k1,
	     class Container1<T>::iterator k2,
	     class Container1<T>::iterator k3,
	     class Container1<T>::iterator k4,
             double h) ;

// Return a vector of X_i+1, Y_i+1, ect..
template<typename functor_type,
         typename coord_type,
         template <typename functor_type> class Container1, 
         template <typename coord_type> class Container2,         
         typename t_type > 
std::vector<double>
crk4(class Container1<functor_type>::iterator funct_iter1,
     class Container1<functor_type>::iterator funct_iter2,
     class Container2<coord_type>::iterator coord_iter1, 
     class Container2<coord_type>::iterator coord_iter2,
     t_type t, 
     double h);


int main(int argc, char* argv[]) 
{           
    // Control parameters
    const double sigma{10.0};
    const double rho{28.0};
    const double beta{8.0/3.0};
        
    // The three ODE's, x'(t), y'(t), z'(t)       
    using vec_it = std::vector<double>::iterator;
    
    auto xd = [&sigma] (vec_it coord_begin, vec_it coord_end, double t) { 
        return sigma*( *std::next(coord_begin) - *coord_begin); 
    };   
    auto yd = [&rho] (vec_it coord_begin, vec_it coord_end, double t) {
        return *coord_begin * (rho - *std::next(coord_begin,2)) - *std::next(coord_begin,1);
    };
    auto zd = [&beta] (vec_it coord_begin, vec_it coord_end, double t) {
        return *coord_begin * *std::next(coord_begin,1) - beta * *std::next(coord_begin,2); 
    };
        
    // Put the functions in a vector.  
    std::vector<std::function<double(vec_it,vec_it,double)>> f_vec = { xd, yd, zd } ;
    std::vector<double> coords{ -5, 10, 20.0 };
    
  	// Some initial conditions
    double t0{ 0.0 };
    //double tf{ 30.0 };
    double step_size{ exp2(-10) };
    //size_t N = (tf - t0)/step_size ;          
    
    // this vector should hold the results of one time step calculation
    auto vec_n = crk4(f_vec.begin(),f_vec.end(),coords.begin(),coords.end(),t0,step_size);
    // and should print them out here.  
    for(const auto& i:vec_n)
        std::cout<< i << ' ';
    std::cout<<std::endl;
   
           
    return(EXIT_SUCCESS);
}

template<typename functor_type,
         typename coord_type,
         template <typename functor_type> class Container1,
         template <typename coord_type> class Container2,
         typename t_type >
std::vector<double>
init(class Container1<functor_type>::iterator funct_iter1,
     class Container1<functor_type>::iterator funct_iter2,
     class Container2<coord_type>::iterator coord_iter1,
     class Container2<coord_type>::iterator coord_iter2,
     t_type t)
{
     std::vector<double> initial_vals(std::distance(funct_iter1, funct_iter2));
     std::transform(funct_iter1, funct_iter2, initial_vals.begin(),
            [&](const functor_type& f) {
                return f(coord_iter1, coord_iter2, t);
            }
    );

    return initial_vals;
}

template<typename T,
         typename coord_type,
         template <typename T> class Container1, 
         template <typename coord_type> class Container2> 
std::vector<double>
midpt(const Container1<T>& k,
      class Container2<coord_type>::iterator coord_iter1, 
      double h)
{
    std::vector<double> midpoints( k.size() );
    std::transform(k.cbegin(), k.cend(), coord_iter1, midpoints.begin(), 
        [&](const T& ki, const coord_type& xi) {
	    return 0.5*h*ki + xi;
	}
    );
	
    return midpoints;
}

template<typename T,
         typename coord_type,
         template <typename T> class Container1, 
         template <typename coord_type> class Container2 > 
std::vector<double>
runge_kutta4(class Container2<coord_type>::iterator coord_iter1, 
	     class Container2<coord_type>::iterator coord_iter2,
	     class Container1<T>::iterator k1,
	     class Container1<T>::iterator k2,
	     class Container1<T>::iterator k3,
	     class Container1<T>::iterator k4,
             double h) 
{
    std::vector<double> next_values( k1.size() );
    std::transform(coord_iter1, coord_iter2, next_values.begin(), 
	[&](const coord_type& xi) {
	    return xi + (h/6.0)*( *k1++ + 2*( *k2++ + *k3++ ) + *k4++ );			      
	}
    );
	
    return next_values;
}

template<typename functor_type,
         typename coord_type,
         template <typename functor_type> class Container1, 
         template <typename coord_type> class Container2,         
         typename t_type > 
std::vector<double>
crk4(class Container1<functor_type>::iterator funct_iter1,
     class Container1<functor_type>::iterator funct_iter2,
     class Container2<coord_type>::iterator coord_iter1, 
     class Container2<coord_type>::iterator coord_iter2,
     t_type t, 
     double h)
{    
    auto k1 = init(funct_iter1, funct_iter2, coord_iter1, coord_iter2, t);
    auto m1 = midpt(k1, coord_iter1, h);
    t += 0.5*h;
    auto k2 = init(funct_iter1, funct_iter2, coord_iter1, coord_iter2, t);
    auto m2 = midpt(k1, coord_iter1, h);
    auto k3 = init(funct_iter1, funct_iter2, coord_iter1, coord_iter2, t);
    auto m3 = midpt(k1, coord_iter1, h);
    t += 0.5*h;
    auto k4 = init(funct_iter1, funct_iter2, coord_iter1, coord_iter2, t);	
	
    auto coord_next = runge_kutta4(coord_iter1, coord_iter2, 
                      k1.begin(), k2.begin(), k3.begin(), k4.begin(),
		      h);
					  
    return coord_next;
}
