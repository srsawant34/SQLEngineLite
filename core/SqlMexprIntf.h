#ifndef __SQL_MEXPR_INTF__
#define __SQL_MEXPR_INTF__
#include <stdbool.h>
#include <string>
#include "../SqlParser/SqlEnums.h"
#include "../MathExpressionParser/MexprcppEnums.h"

typedef struct BPlusTree BPlusTree_t ;
typedef struct joined_row_ joined_row_t;
typedef struct qep_struct_ qep_struct_t;

class MexprTree;
class Dtype;
class MexprNode;

typedef struct sql_exptree_ {

    MexprTree *tree;

} sql_exptree_t;


sql_exptree_t *
sql_create_exp_tree_compute ();

void 
sql_destroy_exp_tree (sql_exptree_t *tree);

bool 
sql_opnd_node_is_resolved (MexprNode *opnd_node);

std::string 
sql_get_opnd_variable_name (MexprNode *opnd_node);

mexprcpp_dtypes_t
sql_to_mexpr_dtype_converter (sql_dtype_t sql_dtype) ;

sql_dtype_t
mexpr_to_sql_dtype_converter (mexprcpp_dtypes_t dtype);

void 
sql_destroy_Dtype_value_holder (Dtype *dtype);

Dtype *
sql_evaluate_exp_tree (sql_exptree_t *sql_exptree);

bool 
sql_resolve_exptree (BPlusTree_t *tcatalog,
                                  sql_exptree_t *sql_exptree,
                                  qep_struct_t *qep,
                                  joined_row_t **joined_row) ;

void 
InstallDtypeOperandProperties (MexprNode *node, 
                                                    sql_dtype_t sql_dtype,
                                                    void *data_src, Dtype *(*compute_fn_ptr)(char*, void *)) ;

typedef struct dtype_value_ {

    sql_dtype_t dtype;

    union {
        int int_val;
        double d_val;
        const char *str_val;
    } u;
    
} dtype_value_t;

dtype_value_t 
DTYPE_GET_VALUE(Dtype *dtype) ;

#endif 