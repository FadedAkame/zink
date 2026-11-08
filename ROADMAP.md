# Roadmap
The initial goal is to compile a variable declaration in Zink to C code.
- [x] Lexer
    - [x] Tokens design
    - [x] Lexical analysis
    - [x] Literal lexing
- [-] Parser
    - [x] AST design
    - [x] Atom parser design
    - [ ] Pratt parser
- [ ] Semantic Analyzer
    - [ ] Treewalker design
    - [ ] Type checking
    - [ ] Invalide type compatability
    - [ ] Undefined identifiers
    - [ ] ODR enforcement (One Definition Rule)
    - [ ] Symbol lookup validation
- [ ] Codegen
    - [ ] Template C program (as baseplate)
    - [ ] Treewalk design
    - [ ] Zink to C primitive conversions
    - [ ] Declaration ordering
    - [ ] Data to C output

## Side Goals
- [x] Program arguement parser
- [ ] Automated tests
- [ ] Proper compiler error system
