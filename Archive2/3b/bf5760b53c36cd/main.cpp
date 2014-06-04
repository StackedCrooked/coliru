typedef int Table;

class FullObjId 
{
public:
    explicit FullObjId( const Table* i ) {}
};

class TableInfo 
{
public:
    TableInfo( const FullObjId& o ) {}
    bool isValid() { return true; }
};

void dataSourceForHist( const Table& table )
{
   TableInfo tableInfo( (FullObjId( &table )) );
   if (!tableInfo.isValid())
   {
   }
}

int main() {}