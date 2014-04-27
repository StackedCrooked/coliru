static const totalThreads = 16;

void func() {
    static vector<thread> threads(totalThreads);
    for(unsigned i=0; i<totalThreads; i++)
        threads[i] = thread(workOnTheseEdges,startIndex[i], endIndex[i]); 
    for (auto& thread : threads)
         thread.join();
}