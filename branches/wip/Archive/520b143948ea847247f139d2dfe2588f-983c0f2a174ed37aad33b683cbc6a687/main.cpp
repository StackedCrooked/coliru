#include <iostream>
#include <algorithm>
#include <cstring>

//#include <xmmintrin.h>

/*
 * The _mm_shuffle_ps(a,b,imm) intrinsics selects any two values from a
 * and places them in the low two components, and any two values from b
 * and places them in the high two components.
 *
 * To do an arbitrary shuffle, an additonal shuffle may need to be
 * performed.
 *
 * There are 4096 possible two-operand shuffles
 */

int main()
{
    int simple_count = 0;    // simple means one shuffle will do whole operation
    int easy_count = 0;		// easy means two shuffles will do whole operation
    int hard_count = 0;		// hard means everything else
    
    for (int s0 = 0; s0 < 8; ++s0) {
        for (int s1 = 0; s1 < 8; ++s1) {
            for (int s2 = 0; s2 < 8; ++s2) {
                for (int s3 = 0; s3 < 8; ++s3) {
                    std::cout << "shuffle<" << s0 << ',' << s1 << ',' <<
                                 s2 << ',' << s3 << ">: ";
                    
                    ++simple_count;
                    
                    if (s0 == 0 && s1 == 1 && s2 == 2 && s3 == 3) {
                        std::cout << "trivial 1 op: return a" << std::endl;
                    }
                    else if (s0 == 4 && s1 == 5 && s2 == 6 && s3 == 7) {
                        std::cout << "trivial 1 op: return b" << std::endl;
                    }
                    else if (s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4) {
                        /* single operand a shuffle */
                        std::cout << "simple  1 op: return _mm_shuffle(a, a, _MM_SHUFFLE(" <<
                                     s0 << ',' << s1 << ',' <<
                                     s2 << ',' << s3 << "))" << std::endl;
                    }
                    else if (s0 >= 4 && s1 >= 4 && s2 >= 4 && s3 >= 4) {
                        /* single operand b shuffle */
                        std::cout << "simple  1 op: return _mm_shuffle(b, b, _MM_SHUFFLE(" <<
                                     (s0-4) << ',' << (s1-4) << ',' <<
                                     (s2-4) << ',' << (s3-4) << "))" << std::endl;
                    }
                    else {
                        /* two operand shuffle */
                        
                        if (s0 == 6 && s1 == 7 && s2 == 2 && s3 == 3) {
                            /* movehlps special case */
                            std::cout << "special case: return _mm_movehl_ps(a, b)" << std::endl;
                        }
                        else if (s0 == 2 && s1 == 3 && s2 == 6 && s3 == 7) {
                            /* movehlps reversed special case */
                            std::cout << "special case: return _mm_movehl_ps(b, a)" << std::endl;
                        }
                        else if (s0 == 0 && s1 == 1 && s2 == 4 && s3 == 5) {
                            /* movelhps special case */
                            std::cout << "special case: return _mm_movelh_ps(a, b)" << std::endl;
                        }
                        else if (s0 == 4 && s1 == 5 && s2 == 0 && s3 == 1) {
                            /* movelhps reversed special case */
                            std::cout << "special case: return _mm_movelh_ps(b, a)" << std::endl;
                        }
                        else if (s0 < 4 && s1 < 4 && s2 >= 4 && s3 >= 4) {
                            /* simple shuffle */
                            std::cout << "simple  1 op: return _mm_shuffle(a, b, _MM_SHUFFLE(" <<
                                         (s0) << ',' << (s1) << ',' <<
                                         (s2-4) << ',' << (s3-4) << "))" << std::endl;
                        }
                        else if (s0 >= 4 && s1 >= 4 && s2 < 4 && s3 < 4) {
                            /* simple reversed shuffle */
                            std::cout << "simple  1 op: return _mm_shuffle(b, a, _MM_SHUFFLE(" <<
                                         (s2) << ',' << (s3) << ',' <<
                                         (s0-4) << ',' << (s1-4) << "))" << std::endl;
                        }
                        else if (s0 == 0 && s1 == 4 && s2 == 1 && s3 == 5) {
                            /* unpacklo special case */
                            std::cout << "special case: return _mm_unpacklo_ps(a, b)" << std::endl;
                        }
                        else if (s0 == 4 && s1 == 0 && s2 == 5 && s3 == 1) {
                            /* unpacklo reversed special case */
                            std::cout << "special case: return _mm_unpacklo_ps(b, a)" << std::endl;
                        }
                        else if (s0 == 2 && s1 == 6 && s2 == 3 && s3 == 7) {
                            /* unpackhi special case */
                            std::cout << "special case: return _mm_unpackhi_ps(a, b)" << std::endl;
                        }
                        else if (s0 == 6 && s1 == 2 && s2 == 7 && s3 == 3) {
                            /* unpackhi reversed special case */
                            std::cout << "special case: return _mm_unpackhi_ps(b, a)" << std::endl;
                        }
                        else if (s0 == 4 && s1 == 1 && s2 == 2 && s3 == 3) {
                            /* movss special case */
                            std::cout << "special case: return _mm_move_ss(a, b)" << std::endl;
                        }
                        else if (s0 == 0 && s1 == 5 && s2 == 6 && s3 == 7) {
                            /* movss reversed special case */
                            std::cout << "special case: return _mm_move_ss(b, a)" << std::endl;
                        }
                        else {
                            /* complex shuffle */
                            
                            --simple_count;
                            
                            // build bitmasks of components accessed
                            int a_used = 0;
                            a_used |= 1 << s0;
                            a_used |= 1 << s1;
                            a_used |= 1 << s2;
                            a_used |= 1 << s3;
                            int b_used = a_used >> 4;
                            a_used &= 0xF;
                            
                            int a_count = 0;
                            int b_count = 0;
                            
                            // count set bits
                            for (int bit = 0; bit < 4; ++bit) {
                                if (a_used & (1<<bit))
                                    ++a_count;
                                if (b_used & (1<<bit))
                                    ++b_count;
                            }
                            
                            if (a_count <= 2 && b_count <= 2) {
                                ++easy_count;
                                std::cout << "easy: ";
                                
                                /* arbitrarily bring in the two values from a
                                 * followed by the two values from b */
                                
                                int a_components[2], b_components[2];
                                int a_seen = 0, b_seen = 0;
                                memset(a_components, -1, sizeof(a_components));
                                memset(b_components, -1, sizeof(b_components));
                                
                                for (int bit = 0; bit < 4; ++bit) {
                                    if (a_used & (1<<bit))
                                        a_components[a_seen++] = bit;
                                    if (b_used & (1<<bit))
                                        b_components[b_seen++] = bit;
                                }
                                
                                /* Make sure we're getting two things from each, even
                                 * if we don't need to */
                                if (a_seen == 1)
                                    a_components[1] = a_components[0];
                                if (b_seen == 1)
                                    b_components[1] = b_components[0];
                                
                                std::cout << "tmp = _mm_shuffle_ps(a, b, _MM_SHUFFLE(" <<
                                             b_components[1] << ',' <<
                                             b_components[0] << ',' <<
                                             a_components[1] << ',' <<
                                             a_components[0] << ")); ";
                                
                                /* Generate a lookup table to find the components in tmp */
                                int tmp_lookup[8];
                                memset(tmp_lookup, -1, sizeof(tmp_lookup));
                                
                                tmp_lookup[a_components[0]] = 0;
                                tmp_lookup[a_components[1]] = 1;
                                tmp_lookup[b_components[0]+4] = 2;
                                tmp_lookup[b_components[1]+4] = 3;
                                
                                std::cout << "return _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(" <<
                                             tmp_lookup[s3] << ',' <<
                                             tmp_lookup[s2] << ',' <<
                                             tmp_lookup[s1] << ',' <<
                                             tmp_lookup[s0] << "));" <<
                                             std::endl;
                            }
                            else {
                                ++hard_count;
                                std::cout << "hard" << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }
    
    std::cout << "simple: " << simple_count << std::endl;
    std::cout << "easy  : " << easy_count << std::endl;
    std::cout << "hard  : " << hard_count << std::endl;
    return 0;
}

