#include <string>
#include <memory>
#include <vector>

class SourceRow {
public:
    std::vector<std::string> Values = std::vector<std::string>();
};

class SourceData {
public:
    std::vector<std::shared_ptr<SourceRow>> Rows = std::vector<std::shared_ptr<SourceRow>>();
};

class DataRow : public SourceRow {
public:
    double RowTotal = 50;
};

class RowSet {
public:
    std::vector<std::shared_ptr<DataRow>> Rows = std::vector<std::shared_ptr<DataRow>>();
};

std::shared_ptr<SourceData> GetSourceData() {
    auto data = SourceData();
    for( auto row_count = 0; row_count < 100; row_count++ ) {
        auto row = SourceRow();
        for( auto col_count = 0; col_count < 10; col_count++ ) {
            row.Values.push_back("Row " + std::to_string(row_count) + " Value " + std::to_string(col_count) );
        };
        data.Rows.push_back(std::make_shared<SourceRow>(row));
    };
    return std::make_shared<SourceData>(data);
}


int main() {
    
    auto source = GetSourceData();
    
    auto rowset = RowSet();
    for( auto row : source->Rows )
        rowset.Rows.push_back( std::static_pointer_cast<DataRow>(row) );
        
    auto test_row = rowset.Rows[1];
    
    fprintf( stdout, "ColValue: [%s]   Total: [%d]", test_row->Values[2].c_str(), test_row->RowTotal );  // Row Total Address not valid!
}

