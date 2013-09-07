#pragma once

#include <array>
#include <math.h>

namespace tt
{
        namespace algo
        {
                struct KnuthSeq
                {
                        int operator()(int i)
                        {
                                return seqElems_[i];
                        }

                private:
                        static int seqElems_[20];
                };

                int KnuthSeq::seqElems_[20] = {1, 4, 13, 40, 121, 364, 1093, 3280, 9841,
                        295214, 88573, 265720, 797161, 2391484, 7174453, 21523360, 64570081,
                        193710244, 581130733, 1743392200};

                struct SedgewickSeq
                {
                        int operator()(int i)
                        {
                                return seqElems_[i];
                        }

                private:
                        static int seqElems_[28];
                };

                int SedgewickSeq::seqElems_[28] = {1, 5, 19, 41, 109, 209, 505, 929, 2161,
                        3905, 8929, 16001, 36289, 64769, 146305, 260609, 587521, 1045505, 
                        2354689, 4188161, 9427969, 16764929, 37730305, 67084289, 150958081, 
                        268386305, 603906049, 1073643521};

                struct Sedgewick2Seq
                {
                        int operator()(int i)
                        {
                                return seqElems_[i];
                        }

                private:
                        static int seqElems_[28];
                };

                int Sedgewick2Seq::seqElems_[28] = {1, 6, 19, 40, 109, 210, 505, 928, 2161,
                        3906, 8929, 16000, 36289, 64770, 146305, 260608, 587521, 1045506, 
                        2354689, 4188160, 9427969, 16764930, 37730305, 67084288, 150958082, 
                        268386305, 603906048, 1073643521};

                struct PowersOfTwoMinusOneSeq
                {
                        int operator()(int i)
                        {
                                return static_cast<int>(pow(2, i + 1)) - 1;
                        }
                };

                template<typename Iterator, typename Sequence, typename Predicate>
                void shellSort(Iterator begin, Iterator end, Sequence strideSeq, Predicate pred)
                {
                        int numElems = std::distance(begin, end);
                        int startIndex = 0;
                        while(strideSeq(startIndex + 1) < numElems)
                        {
                                startIndex++;
                        }

                        detail::recursiveShellSort(begin, end, strideSeq, pred, numElems, startIndex);
                }

                namespace detail
                {
                        template<typename Iterator, typename Predicate>
                        void hSort(Iterator begin, Iterator end, int stride, Predicate pred)
                        {
                                for(Iterator it = begin + stride; it != end; ++it)
                                {
                                        for(Iterator lhs = it; lhs - begin >= stride;)
                                        {
                                                Iterator rhs = lhs;
                                                lhs -= stride;
                                                if(!pred(*lhs, *rhs))
                                                {
                                                        std::iter_swap(lhs, rhs);
                                                }
                                        }
                                }
                        }

                        template<typename Iterator, typename Sequence, typename Predicate>
                        void recursiveShellSort(Iterator begin, Iterator end, Sequence strideSeq, Predicate pred, int numElems, int index)
                        {
                                hSort(begin, end, strideSeq(index), pred);

                                if(index > 0)
                                        recursiveShellSort(begin, end, strideSeq, pred, numElems, index - 1);
                        }
                }
        }
}