# SimpleSQL

A project implementing a lightweight SQLite engine with support for `CREATE`,`INSERT`, and `SELECT` queries, including mathematical operations on columns.

![demo](./assets/demo.gif)

## Project Architecture

The project comprises of different components as shown below fig:-

<img src='./assets/rdbms.drawio.png' width='60%'>

1. **Parser**: 
The parser component is responsible for analyzing and validating user-provided SQL queries. It ensures that the input queries are syntactically correct and adherent to the SQL language rules. In case of any errors or illegal input, the parser generates error messages for the user. Once validated, the parser invokes the appropriate methods in the RDBMS component to execute the specified operations.

2. **B+ Tree:** 
The B+ Tree library is a standardized component offering a set of functions for performing CRUD (Create, Read, Update, Delete) operations in the context of SQL queries. It serves as a robust library for managing B+ tree data structures, providing efficient mechanisms for insertion, retrieval, updating, and deletion operations.

3. **RDBMS Engine:** 
The RDBMS engine is the project's core, orchestrating backend operations by processing parsed tokens from the parser. It interacts with various components to manage user input, creating tables using the B+ Tree library, storing records, and providing outputs for select queries. The supported operations are `SELECT`, `DROP`, `INSERT` and `CREATE`.

4. **SQL Interface:**
The SQL interface comprises a set of APIs bridging the interaction between the core RDBMS, and the Mathematical Expression library. Serving as a wrapper, it facilitates seamless communication by encapsulating the internal APIs of the mathematical expression library.

5. **libMexpr.a:** 
libMexpr.a is a math expression parser package that processes mathematical expressions, generating parse trees from input expressions typically found in select queries applied to columns. This file is compiled from this [package](https://github.com/sachinites/MathExpressionParser).
