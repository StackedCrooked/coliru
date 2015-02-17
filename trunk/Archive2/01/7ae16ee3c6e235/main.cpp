128         struct outItem {
129             using SourceElement = TokenRecordHolder;
130             std::vector<SourceElement> sourceElements;
131             ConjunctionsHelpers::TagType tag;
132         };
133         ASSERT_IS_NOTHROW_CONSTRUCTIBLE(outItem);


180         static outItem firstOfAKind(TokenRecordHolder&& in){
181             auto tag = in.tag();
182             return {{std::move(in)}, tag};
183         }

135         template <typename In, typename OutQueue>
136             void process(In&& in, OutQueue& out){
137                 if(!nextOutput){
138                     // no data available from previous calls to process
139                     // store the input TokenRecord, and wait for further inputs
140                     nextOutput = firstOfAKind( std::move(in) );
141                     pass( !(nextOutput->sourceElements.empty()) );
142                     return;
143                 }
