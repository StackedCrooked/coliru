#include <iostream>
#include <string>
#include <vector>

struct Edge{
    Face *face;
};

static Gface *getCommonFaceBetweenMases(Edge *mase1, Edge *mase2)
{
    PtrArray *faces1, *faces2;
    Edge *run_mase;
    Face *common_face = NULL, *run_face; void *run_ent;
    int num_common_faces = 0;
    faces1 = ptr_array_new(0); faces2 = ptr_array_new(0); 
    VISIT_MANEAR_ABS(mase1, run_mase,
                    {
                    ptr_array_append_val(faces1, run_mase->itf);
                    });
    VISIT_MANEAR_ABS(mase2, run_mase,
                    {
                    ptr_array_append_val(faces2, run_mase->itf);
                    });
       ptr_array_unique(faces1);
       ptr_array_unique(faces2);
       RUN_PTR_ARRAY(faces1, run_ent,
                    {
    run_face = (Gface *)run_ent;
    if ( ptr_array_find_index(faces2, run_face) >= 0 ){ if ( !common_face && !num_common_faces ){ common_face = run_face;
num_common_faces++;
} else if ( common_face != run_face ){ num_common_faces++;
}
}
});
       ptr_array_free_dum(faces1);
       ptr_array_free_dum(faces2);
return (num_common_faces > 0) ? common_face : NULL; }
int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
