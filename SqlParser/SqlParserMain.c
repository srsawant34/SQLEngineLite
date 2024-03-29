#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "ParserExport.h"
#include "SqlEnums.h"
#include "../core/sql_create.h"
#include "../core/sql_delete.h"
#include "../core/sql_insert_into.h"
#include "../core/qep.h"

extern parse_rc_t create_query_parser () ;
extern parse_rc_t  insert_into_query_parser();
extern parse_rc_t select_query_parser();

extern sql_create_data_t cdata;
extern sql_insert_into_data_t idata; 
extern qep_struct_t qep;

int
main(int argc, char **argv) {

    parse_init();

    while (true) {

        printf ("postgreslite=# ");

        fgets ((char *)lex_buffer, sizeof(lex_buffer), stdin);

        if (lex_buffer[0] == '\n') {
            lex_buffer[0] = 0;
            continue;
        }

        lex_set_scan_buffer (lex_buffer);

        token_code = cyylex();

        switch (token_code) {

            case SQL_SELECT_Q:
                yyrewind(1);
                err = select_query_parser();
                if (err == PARSE_SUCCESS) {
                    sql_execute_qep (&qep);
                }
                else {
                    printf ("Failed : SELECT query parsing\n");
                }
                qep_deinit(&qep);
            break;

            case SQL_INSERT_Q:
                yyrewind(1);
                err = insert_into_query_parser () ;
                if (err == PARSE_SUCCESS) {
                    sql_process_insert_query (&idata);
                }
                else {
                    printf ("Failed : INSERT query\n");
                }
            break;

            case SQL_CREATE_Q:
                yyrewind(1);
                err = create_query_parser();
                if (err == PARSE_SUCCESS) {
                    sql_process_create_query (&cdata);
                }
                else {
                    printf ("Failed : CREATE query, table failed to create\n");
                }
                 sql_create_data_destroy(&cdata);
            break;

            case SQL_DROP_TABLE_Q:
            {
                    char *table_name;
                    token_code = cyylex();
                    if (strcmp (lex_curr_token, "table")) {
                        printf ("Error : Unrecognized Input - expected 'table' keyword\n");
                        break;
                    }
                    token_code = cyylex();
                    if (token_code != SQL_IDENTIFIER) {
                        printf ("Error : Unrecognized Input - expected table name\n");
                        break;
                    }
                    table_name = lex_curr_token;
                    token_code = cyylex();
                    if (token_code != PARSER_EOL) {
                        printf ("Error : Unrecognized Input - unexpected keyword token code: %d\n", token_code);
                        break;
                    }
                    sql_drop_table (table_name);
                    break;                
            }
            break;


            default:
                printf ("Error : Unrecognized Input\n");
                break;
        }

        Parser_stack_reset();
    }

    return 0;
}