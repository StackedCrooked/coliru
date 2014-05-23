
bool PrefixTree::completePlusPrefix(string ss, list<string>* ll){
    if(validWord)
    ll->push_back(ss);

    for(auto ii = siblingsList.begin(); ii != siblingsList.end(); ii++ ){
	std::string tt = ss;
	tt += ii->first;
	ii->second->completePlusPrefix(tt, ll);
    }
}
