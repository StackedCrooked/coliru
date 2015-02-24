

int main() {
    TiXmlDocument document;
    TiXmlDeclaration decla("1.0","","no");
    document.link(&decla);
    
    // Create Comment
    TiXmlComment comment;
    comment.SetValue( "Our to do list data" );
    document.LinkEndChild( comment );
    
    // Create root and Link it
    TiXmlElement root( "To Do" );
    document.LinkEndChild( &root );
    
    // Link item element to root node
    TiXmlElement item0("item");
    item0.SetAttribute( "priority", "1" );
    root->LinkEndChild( &item0 );
    
    // Link text element
    TiXmlText item0Start("Go To The");
    item0.LinkEndChild(&item0Start);
    
    // Link bold Element to Item element
    TiXmlElement item0Bold("Bold");
    item0.LinkEndChild(&item0Start);
    
    // Link Text element to bold element
    TiXmlText item0BoldText( "Toy Store" );
    item0Bold.LinkEndChild(&item0Start);
    
    // Link another item element
    TiXmlElement item1("item");
    item1.SetAttribute( "priority", "2" );
    root.LinkEndChild( &item1 );
    
    // And Link Text Item
    TiXmlText item1Start("Do Bills" );
    item1.LinkEndChild( &item1Start );
    
    // Save
    document.SaveFile( "SaveTest.xml" );
}