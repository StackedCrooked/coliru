struct Medicine {};
struct RepositoryException {};

class MedicineRepository
{
public:
virtual void addMed(Medicine s) throw (RepositoryException) = 0;
};

class MedRepo : public MedicineRepository{
public:
void addMed(Medicine s)  throw (RepositoryException) {}
};

int main() {
    MedRepo a;
}