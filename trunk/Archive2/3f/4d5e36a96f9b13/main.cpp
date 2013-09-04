#pragma once

#include <math.h>

namespace tt
{
        namespace algo
        {
                typedef unsigned int uint;

                struct KnuthSeq
                {
                        uint operator()(uint i)
                        {
                                if(i == 0)
                                        return 1;
                                else
                                        return 3*(*this)(i-1) + 1; 
                        }
                };

                struct PowersOfTwoMinusOneSeq
                {
                        uint operator()(uint i)
                        {
                                return static_cast<uint>(pow(2, i + 1)) - 1;
                        }
                };

                template<typename Iterator, typename Sequence, typename Predicate>
                void shellSort(Iterator begin, Iterator end, Sequence strideSeq, Predicate pred)
                {
                        struct RecursiveSorter
                        {
                                RecursiveSorter(Iterator begin, Iterator end, Sequence strideSeq, Predicate pred):
                                        beg_(begin), end_(end), strideSeq_(strideSeq), pred_(pred), numElems_(std::distance(beg_, end_)) {}

                                void sort(uint index)
                                {
                                        if(strideSeq_(index + 1) < numElems_)
                                                sort(index + 1);

                                        detail::hSort(beg_, end_, strideSeq_(index), pred_);
                                }

                        private:
                                Iterator beg_, end_;
                                Sequence strideSeq_;
                                Predicate pred_;
                                uint numElems_;
                        };

                        RecursiveSorter sorter(begin, end, strideSeq, pred);
                        sorter.sort(0);
                }

                namespace detail
                {
                        template<typename Iterator, typename Predicate>
                        void hSort(Iterator begin, Iterator end, uint stride, Predicate pred)
                        {
                                int numElems = std::distance(begin, end);
                                int numRepetitions = ((numElems - 1) % stride) + 1;

                                for(int i=stride; i<numElems; i++)
                                {
                                        for(int j=i-stride; j>=0; j -= stride)
                                        {
                                                auto rhs = begin + j + stride;
                                                auto lhs = begin + j;

                                                if(!pred(*lhs, *rhs))
                                                {
                                                        std::iter_swap(lhs, rhs);
                                                }
                                        }
                                }
                        }
                }
        }
}