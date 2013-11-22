//------quad_tree.hpp------

#include <cassert>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <memory>
#include <utility> /* for std::swap */
#include <valarray>

inline size_t partition(double* array, size_t length, double pivot_element, double* array2, double* array3, double* array4, double* array5) {
    size_t start = 0, end = length;
    std::cout << array[0] << " " << array2[0] << " " << array3[0] << " " << array4[0] << std::endl;
    while (start != end) {
        //std::cout << array[start] << std::endl;
        if (array[start] >= pivot_element) {
            std::swap(array[start], array[end - 1]);
            std::swap(array2[start], array2[end - 1]);
            std::swap(array3[start], array3[end - 1]);
            std::swap(array4[start], array4[end - 1]);
            std::swap(array5[start], array5[end - 1]);

            end--;
        } else {

            start++;
        }
    }
    //std::cout << start << std::endl;
    return start;
}

class quad_tree {
public:
    quad_tree(double geom_center_x, double geom_center_y, double half_length,
        double* particles_x, double* particles_y,
        double* particles_vx, double* particles_vy,
        double* particles_m, size_t particles_count) :
        geom_center_x(geom_center_x), geom_center_y(geom_center_y), half_length(half_length),
        mass_center_x(0.0), mass_center_y(0.0), mass_sum(0.0),
        particles_x(particles_x), particles_y(particles_y),
        particles_vx(particles_vx), particles_vy(particles_vy),
        particles_m(particles_m), particles_count(particles_count)
    {
        //std::cout << particles_count << std::endl;
        //std::cout << particles_x[0] << " " << particles_y[0] << " " << particles_vx[0] << " " << particles_vy[0] << std::endl;
        //std::cout << *(particles_x) << " " << *(particles_y) << " " << *(particles_vx) << " " << *(particles_vy) << std::endl;
        for (size_t particle = 0; particle < particles_count; particle++) {
            mass_center_x += particles_x[particle];
            mass_center_y += particles_y[particle];
            mass_sum += particles_m[particle];
        }
        mass_center_x /= double(particles_count);
        mass_center_y /= double(particles_count);

        this->children[0] = NULL;
        this->children[1] = NULL;
        this->children[2] = NULL;
        this->children[3] = NULL;
        if (particles_count > 10) {
            const size_t left_elements = partition(particles_x, particles_count, geom_center_x, particles_y, particles_vx, particles_vy, particles_m);
            const size_t right_elements = particles_count - left_elements;
            const size_t top_left_elements = partition(particles_y, left_elements, geom_center_y, particles_x, particles_vx, particles_vy, particles_m);
            const size_t top_right_elements = partition(particles_y + left_elements, particles_count - left_elements, geom_center_y, particles_x + left_elements, particles_vx + left_elements, particles_vy + left_elements, particles_m + left_elements);
            const double quarter_length = 0.5 * half_length;
            //std::cout << geom_center_x << " " << geom_center_y  << " " << half_length << std::endl;
            this->children[0] = new quad_tree(geom_center_x - quarter_length, geom_center_y - quarter_length, quarter_length,
                particles_x, particles_y,
                particles_vx, particles_vy,
                particles_m, top_left_elements);
            this->children[1] = new quad_tree(geom_center_x - quarter_length, geom_center_y + quarter_length, quarter_length,
                particles_x + top_left_elements, particles_y + top_left_elements,
                particles_vx + top_left_elements, particles_vy + top_left_elements,
                particles_m + top_left_elements, left_elements - top_left_elements);
            this->children[2] = new quad_tree(geom_center_x + quarter_length, geom_center_y - quarter_length, quarter_length,
                particles_x + left_elements, particles_y + left_elements,
                particles_vx + left_elements, particles_vy + left_elements,
                particles_m + left_elements, top_right_elements);
            this->children[3] = new quad_tree(geom_center_x + quarter_length, geom_center_y + quarter_length, quarter_length,
                particles_x + left_elements + top_right_elements, particles_y + left_elements + top_right_elements,
                particles_vx + left_elements + top_right_elements, particles_vy + left_elements + top_right_elements,
                particles_m + left_elements + top_right_elements, right_elements - top_right_elements);
        }
    }

    ~quad_tree() {
        for (size_t i = 0; i < 4; i++) {
            //std::cout << i << std::endl;
            if (this->children[i] != NULL) {
                delete this->children[i];
                this->children[i] = NULL;
            }
        }
    }

    void iterateThroughQuadTree(double alpha, double delta_t)
    {
        if (particles_count > 10)
        {
            //std::cout << particles_count << std::endl;
            children[0]->iterateThroughQuadTree(alpha,delta_t);
            children[1]->iterateThroughQuadTree(alpha,delta_t);
            children[2]->iterateThroughQuadTree(alpha,delta_t);
            children[3]->iterateThroughQuadTree(alpha,delta_t);
        }
        if (particles_count > 0)
        {

        std::cout << *(particles_x) << " " << *(particles_y) << " " << *(particles_vx) << " " << *(particles_vy) << std::endl;
        double temp_x_acc = 0, temp_y_acc = 0, acc_magnitude = 0, distance = 0, x_displacement = 0, y_displacement = 0, theta = 0, x_acc = 0, y_acc = 0;
        for (size_t i = 0; i < particles_count; i++) {
            temp_x_acc = 0;
            temp_y_acc = 0;
            for (size_t k = 0; k < particles_count; k++) {
                if (i != k) {
                    x_displacement = *(particles_x + k) - *(particles_x + i);
                    y_displacement = *(particles_y + k) - *(particles_y + i);
                    distance = pow((x_displacement),2) + pow((y_displacement),2);
                    acc_magnitude = *(particles_m + k) / distance;
                    theta = atan(y_displacement/x_displacement);
                    x_acc = acc_magnitude * cos(theta);
                    y_acc = acc_magnitude * sin(theta);
                    //x_acc = (x_displacement);
                    //y_acc = (y_displacement);
                    temp_x_acc += x_acc;
                    temp_y_acc += y_acc;
                }
            }
            std::cout << temp_x_acc << " " << temp_y_acc << std::endl;
            *(particles_x + i) += ((*(particles_vx + i)*delta_t) + alpha*temp_x_acc*pow(delta_t,2));
            *(particles_y + i) += ((*(particles_vy + i)*delta_t) + alpha*temp_y_acc*pow(delta_t,2));
            *(particles_vx + i) += 2*alpha*temp_x_acc*delta_t;
            *(particles_vy + i) += + 2*alpha*temp_y_acc*delta_t;
            if (i < 1) {
                //std::cout << *(particles_x + i) << " ";
            }
        }
        }
    }

private:
    double geom_center_x;
    double geom_center_y;
    double half_length;
    double mass_center_x;
    double mass_center_y;
    double mass_sum;
    double* particles_x;
    double* particles_y;
    double* particles_vx;
    double* particles_vy;
    double* particles_m;
    size_t particles_count;

    quad_tree* children[4];
};

//------tree_simulation.cpp------
class tree_simulation : public simulation {
public:
    inline tree_simulation(double delta_t, double alpha) :
        delta_t(delta_t), alpha(alpha)
    {
    }

    virtual void step(std::valarray<double>& x, std::valarray<double>& y,
        std::valarray<double>& vx, std::valarray<double>& vy,
        std::valarray<double>& m) const;
    virtual ~tree_simulation() {
    }
private:
    double alpha;
    double delta_t;
};

inline double square(double x) {
    return x * x;
}

void tree_simulation::step(std::valarray<double>& x, std::valarray<double>& y,
    std::valarray<double>& vx, std::valarray<double>& vy,
    std::valarray<double>& m) const
{
    const size_t particles_count = x.size();
    assert(particles_count == y.size());
    assert(particles_count == vx.size());
    assert(particles_count == vy.size());

    /* YOUR CODE HERE */

    std::cout << x[0] << " " << y[0] << " " << vx[0] << " " << vy[0] << std::endl;

    quad_tree *myQuad = new quad_tree(0.5, 0.5, 0.5, &x[0], &y[0], &vx[0], &vy[0], &m[0], particles_count);
    std::cout << "Right here" << std::endl;
    myQuad->iterateThroughQuadTree(alpha,delta_t);
    delete myQuad;
    myQuad = 0;
}

simulation* create_tree_simulation(double delta_t, double alpha) {
    return new tree_simulation(delta_t, alpha);
}


//------main.cpp------
int main(int argc, char **argv) {
    srand(time(0));
    std::auto_ptr<simulation> sim_ptr;
    const double delta_t = 0.000002;
        const double alpha = 1000;

    sim_ptr = std::auto_ptr<simulation>(create_tree_simulation(delta_t, alpha));

    const size_t time_steps = 200;
const size_t particles_count = 2048;
const size_t particles_shown = 2048;
const size_t image_width = 512;
const size_t image_height = 512;

std::valarray<double> m  = random_valarray(particles_count);
m = m * m * m;
std::valarray<double> x  = random_valarray(particles_count);
std::valarray<double> y  = random_valarray(particles_count);
std::valarray<double> vx, vy;
vx.resize(particles_count);
vy.resize(particles_count);
std::cout << "Simulation" << std::endl;
for (size_t time_step = 1; time_step <= time_steps; time_step++) {
    std::cout << "\tFrame " << time_step << " / " << time_steps << std::endl;
    sim_ptr->step(x, y, vx, vy, m);
}