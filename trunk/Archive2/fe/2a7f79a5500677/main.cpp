#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

struct Student_info {
    std::string name;
	double midterm, final;
	std::vector<double> homework;
};	// note the semicolon--it's required

// compute the median of a `vector<double>'
// note that calling this function copies the entire argument `vector'
double median( std::vector<double> vec)
{
	typedef std::vector<double>::size_type vec_sz;

	vec_sz size = vec.size();
	if (size == 0)
		throw std::domain_error("median of an empty vector");

	sort( vec.begin(), vec.end() );

	vec_sz mid = size/2;

	return size % 2 == 0 ? (vec[mid] + vec[mid-1]) / 2 : vec[mid];
}

// compute a student's overall grade from midterm and final exam grades and homework grade
double grade(double midterm, double final, double homework)
{
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

// compute a student's overall grade from midterm and final exam grades
// and vector of homework grades.
// this function does not copy its argument, because `median' does so for us.
double grade(double midterm, double final, const std::vector<double>& hw)
{
	if (hw.size() == 0)
		throw std::domain_error("student has done no homework");
	return grade(midterm, final, median(hw));
}

double grade(const Student_info& s)
{
	return grade(s.midterm, s.final, s.homework);
}

// read homework grades from an input stream into a `vector<double>'
std::istream& read_hw( std::istream& in, std::vector<double>& hw )
{
	if (in) {
		// get rid of previous contents
		hw.clear();

		// read homework grades
		double x;
		while (in >> x)
			hw.push_back(x);

		// clear the stream so that input will work for the next student
		in.clear();
	}
	return in;
}

std::istream& read( std::istream& is, Student_info& s)
{
	// read and store the student's name and midterm and final exam grades
	is >> s.name >> s.midterm >> s.final;

	read_hw(is, s.homework);  // read and store all the student's homework grades
	return is;
}

bool compare(const Student_info& x, const Student_info& y)
{
	return x.name < y.name;
}

int main()
{
	std::vector<Student_info> students;
	Student_info record;
	std::string::size_type maxlen = 0;

	// read and store all the records, and find the length of the longest name
    /*
	while (read( std::cin, record )) {
		maxlen = std::max(maxlen, record.name.size());
		students.push_back(record);
	}
	*/

	std::string test_data[] = { "Ccccc 80 90 5 6", "Aaaaa 10 20 1 2 3", "Ddddd 50 50  6 5 6", "Bbbbb 50 30 4 5 6 7" } ;
	for( std::string datum : test_data )
    {
        std::istringstream stm(datum) ;
        read( stm, record ) ;
		maxlen = std::max(maxlen, record.name.size());
		students.push_back(record);
    }

	// alphabetize the records
	std::sort(students.begin(), students.end(), compare);

	for (std::vector<Student_info>::size_type i = 0;
	     i != students.size(); ++i) {

		// write the name, padded on the right to `maxlen' `+' `1' characters
		std::cout << students[i].name
		     << std::string(maxlen + 1 - students[i].name.size(), ' ');

		// compute and write the grade
		try {
			double final_grade = grade(students[i]);
			std::streamsize prec = std::cout.precision();
			std::cout << std::setprecision(3) << final_grade
			     << std::setprecision(prec);
		} catch ( const std::domain_error& e) {
			std::cout << e.what();
		}

		std::cout << '\n';
	}
}
