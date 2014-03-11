#include <iostream> 
#include <string.h> 
#include <vector>
#include <algorithm>
#include <iomanip>
typedef std::vector<int> IntVector;
typedef std::vector<IntVector> Table;
class LinearPartition {
public:
    Table m_possible_cost_table;
    Table m_partition_table;
    IntVector m_input;
    int m_num_partitions;
    int m_size;
    void Solve( int m_input[]);
    LinearPartition(int n, int k): m_size(n),
                                   m_num_partitions(k),
                                   m_possible_cost_table(n + 1,IntVector(k + 1)),
                                   m_partition_table(n + 1,IntVector(k + 1)),
                                   m_input(n + 1){
    }
    void reconstruct_partition(int n, int k);
    void print_matrix();
    void print_partitions(int start, int end);
    void prepare_input(int s[]);
private:
protected:
};
void LinearPartition::print_partitions(int start, int end){
    std::cout << "{";
    for ( int i = start; i <= end; i++)
        std::cout << " " << m_input[i] << " " ;
    std::cout << "}" << std::endl;
}
 
void LinearPartition::reconstruct_partition(int n, int k) {
    if (k == 1)
        print_partitions(1,n);
    else {
        reconstruct_partition(m_partition_table[n][k], k - 1);
        print_partitions(m_partition_table[n][k] + 1, n);
    }
}
void LinearPartition::print_matrix(){
    std::cout << std::endl;
    for (int i = 1; i <= m_size; i++) {
        for (int j = 1 ; j <= m_num_partitions; j++)
            std::cout << std::setw(5) << m_possible_cost_table[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int i = 1; i <= m_size; i++) {
        for (int j = 1 ; j <= m_num_partitions; j++)
            std::cout << std::setw(5) << m_partition_table[i][j];
        std::cout << std::endl;
    }
}
void LinearPartition::prepare_input(int s[]) {
    for ( int i = 1; i <= m_size; i++) {
        m_input[i] = s[i - 1];
    }
}
void LinearPartition::Solve(int s[]) {
    prepare_input(s);
    IntVector p(m_size + 1);
    p[0] = 0;
    for ( int i = 1 ; i <= m_size; i++)
        p[i] = p[i - 1] + m_input[i];
    for ( int i = 1; i <= m_size; i++)
        m_possible_cost_table[i][1] = p[i];
    for ( int j = 1; j <= m_num_partitions; j++)
        m_possible_cost_table[1][j] = m_input[1];
    for ( int i = 2; i <= m_size; i++) {
        for ( int j = 2; j <= m_num_partitions; j++) {
            m_possible_cost_table[i][j] = 100000;
            for ( int x = 1; x <= (i - 1); x++) {
                int cost = std::max(m_possible_cost_table[x][ j - 1 ],p[i] - p[x] );
                if (m_possible_cost_table[i][j] > cost) {
                    m_possible_cost_table[i][j] = cost;
                    m_partition_table[i][j] = x;
                }
            }
        }
    }
    print_matrix();
    reconstruct_partition(m_size, m_num_partitions);
}
int main ( int argc, char **argv ) {
    int s[] = {1, 4, 7, 9, 3, 11, 10};
    LinearPartition lp(9,3);
    lp.Solve(s) ;
    return 0;
}