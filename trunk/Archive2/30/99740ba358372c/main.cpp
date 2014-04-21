//========================================================================================
//atomic counter.hpp file
#include <atomic>
struct AtomicCounter {
    std::atomic<int> value;
    
    void increment(){
        ++value;
    }
    void decrement(){
        --value;
    }
    
    int get(){
        return value.load();
    }
    void put(int data) {
      value.store(data);
      //value = data ;
    }
};

//========================================================================================
//========================================================================================
//kernel3_default.hpp file

//spawn the threads 
tbb::task_scheduler_init init(2);

//for each day
for (time t=1; t<=DAYS_OF_SIM; ++t) {

   //define a atomic counter
   AtomicCounter c;
   
   //function object for each agent
   sim1_default <Graph_t, AtomicCounter> SIMULATE(G, c, t);
   
   //parallel for_each  at each agent location
   tbb::parallel_for_each (agents.begin(), agents.end(), SIMULATE);
   
   //print atomic counter's value 
   cout << "CT = " << c.get() << endl;

   //update today's total contagion count in global variable
   kerneltraits::increase_inf_count(t, c.get());

   //update states for each actor 
   for_each (actors.begin(), actors.end(), update_states_default <Graph_t>(G));

   //run interventions ==> wrapper function for interventions
   run_interventions <Graph_t> (G, actors.begin(), actors.end(), randomAgent.generate(), t);  
 }



//========================================================================================
//========================================================================================


//sim1_default function object --> 
// TBB function object requires that , Operator() function should be const and not modify any 
// of functor's members. 
// therefore need to declare the m_ct variable as mutable int so that it can be modified. 
//uniformReal is thread ssafe random number generate using erand48(xsubi)


template <typename graph_t, typename counter_t, typename time=int, class kernelp = KT>
struct sim1_default {
    public:
      sim1_default () { }
       
      // graph, counter, time = int
      sim1_default (graph_t& G, counter_t& ct, time t, int a=0, int b=1)    :    m_G(G), CT(ct), m_time(t), UNI(a,b)
      {   }
     
      template <typename agent_id>  // of type vd_t
      void operator() (agent_id   agent) const  {
            
        for (edge1: all_edges)  {  
            for (edge2: all_edges)  { 
              if (edge1 != edge2)  {
                  snode = target (edge1);
                  inode = target (edge2);
                  find_duration (edge1, edge2);
                  double probability = compute_probability (snode, inode)
                  if (probability > UNI.generate())    // UNI is a uniformReal random number generator
                      m_ct ++   //increment local counter
              } 
            } //for
        }   //for
        
        
        //update the atomic counter with m_ct computed locally at each agent
        CT.put(m_ct)
        
        
      } //operator
        
    private:
        graph_t&     m_G;
        counter_t&   CT;
        time         m_time;
        uniformReal  UNI;
        mutable int  m_ct=0; 
};

        
        

