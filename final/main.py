import ply.lex as lex
import ply.yacc as yacc
import sys
import ast

tokens = ( 
    'PLUS', 'MINUS', 'MULTIPLY', 'DIVIDE', 'MODULUS', 'GREATER', 'SMALLER', 'EQUAL',
    'AND', 'OR', 'NOT', 'DEFINE', 'FUN', 'IF', 'LPAREN', 'RPAREN',
    'ID', 'NUMBER', 'BOOL', 'PRINTNUM', 'PRINTBOOL'
)

reserved = {
    'mod' : 'MODULUS',
    'and' : 'AND',
    'or' : 'OR',
    'not' : 'NOT',
    'if' : 'IF',
    'define' : 'DEFINE',
    'fun' : 'FUN',
    'print-num' : 'PRINTNUM',
    'print-bool' : 'PRINTBOOL'
}


t_PLUS = r'\+'
t_MINUS = r'\-'
t_MULTIPLY = r'\*'
t_DIVIDE = r'/'
t_GREATER = r'>'
t_SMALLER = r'<'
t_EQUAL = r'='
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_ignore = ' \t\n\r'

def t_NUMBER(t):
    r'0|([1-9][0-9]*)|(-[1-9][0-9]*)'
    t.value = int(t.value)
    return t

def t_BOOL(t):
    r'\#(t|f)'
    t.value = True if t.value == '#t' else False
    return t

def t_ID(t):
    r'[a-zA-Z][a-zA-Z0-9-]*'
    t.type = reserved.get(t.value, 'ID')
    return t

def t_error(t):
    print('Illegal character:', t.value[0])
    t.lexer.skip(1)

# lexer
lexer = lex.lex()

def p_program(p):
    '''program : STMTS'''
    p[0] = ast.Module(body=p[1], type_ignores=[],  lineno=p.lineno(1), col_offset=0)

def p_stmts(p):
    '''STMTS : STMTS STMT
             | STMT'''
    if len(p) == 2:
        p[0] = [p[1]]
    else:
        p[0] = p[1] + [p[2]]

def p_stmt(p):
    '''STMT : EXP
            | DEF_STMT
            | PRINT_STMT'''
    if isinstance(p[1], ast.expr): # EXP
        p[0] = ast.Expr(value=p[1], lineno=p.lineno(1), col_offset=0)
    else: # DEF_STMT or PRINT_STMT
        p[0] = p[1]

def p_exp(p):
    '''EXP : BOOL_VAL
           | NUMBER_VAL
           | VARIABLE
           | NUM_OP
           | LOGICAL_OP
           | FUN_EXP
           | FUN_CALL
           | IF_EXP'''
    p[0] = p[1]

def p_num_op(p): # 題目寫錯了啦
    '''NUM_OP : LPAREN PLUS EXP EXPS RPAREN
              | LPAREN MINUS EXP EXP RPAREN
              | LPAREN MULTIPLY EXP EXPS RPAREN
              | LPAREN DIVIDE EXP EXP RPAREN
              | LPAREN MODULUS EXP EXP RPAREN
              | LPAREN GREATER EXP EXP RPAREN
              | LPAREN SMALLER EXP EXP RPAREN
              | LPAREN EQUAL EXP EXP RPAREN'''
    if p[2] == '+':
        tmp = p[3]
        for ele in p[4]:
            tmp = ast.BinOp(left=ast.Call(
                func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
                args=[tmp],
                keywords=[],
                lineno=p.lineno(2),
                col_offset=0
            ), op=ast.Add(), right=ast.Call(
                func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
                args=[ele],
                keywords=[],
                lineno=p.lineno(2),
                col_offset=0
            ),
            lineno=p.lineno(2),
            col_offset=0
            )
        p[0] = tmp
    elif p[2] == '-':
        tmp = p[3]
        tmp = ast.BinOp(left=ast.Call(
            func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
            args=[tmp],
            keywords=[],
            lineno=p.lineno(2),
            col_offset=0
        ), op=ast.Sub(), right=ast.Call(
            func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
            args=[p[4]],
            keywords=[],
            lineno=p.lineno(2),
            col_offset=0
        ),
        lineno=p.lineno(2),
        col_offset=0
        )
        p[0] = tmp
    elif p[2] == '*':
        tmp = p[3]
        for ele in p[4]:
            tmp = ast.BinOp(left=ast.Call(
                func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
                args=[tmp],
                keywords=[],
                lineno=p.lineno(2),
                col_offset=0
            ), op=ast.Mult(), right=ast.Call(
                func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
                args=[ele],
                keywords=[],
                lineno=p.lineno(2),
                col_offset=0
            ),
            lineno=p.lineno(2),
            col_offset=0
            )
        p[0] = tmp
    elif p[2] == '/':
        tmp = p[3]
        tmp = ast.BinOp(left=ast.Call(
            func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
            args=[tmp],
            keywords=[],
            lineno=p.lineno(2),
            col_offset=0
        ), op=ast.Div(), right=ast.Call(
            func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
            args=[p[4]],
            keywords=[],
            lineno=p.lineno(2),
            col_offset=0
        ),
        lineno=p.lineno(2),
        col_offset=0)
        p[0] = tmp
    elif p[2] == 'mod':
        tmp = p[3]
        tmp = ast.BinOp(left=ast.Call(
            func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
            args=[tmp],
            keywords=[],
            lineno=p.lineno(2),
            col_offset=0
        ), op=ast.Mod(), right=ast.Call(
            func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
            args=[p[4]],
            keywords=[],
            lineno=p.lineno(2),
            col_offset=0
        ),
        lineno=p.lineno(2),
        col_offset=0
        )
        p[0] = tmp
    elif p[2] == '>':
        p[0] = ast.Compare(left=ast.Call(
            func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
            args=[p[3]],
            keywords=[],
            lineno=p.lineno(2),
            col_offset=0
        ), ops=[ast.Gt()], comparators=[ast.Call(
            func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
            args=[p[4]],
            keywords=[],
            lineno=p.lineno(2),
            col_offset=0
        )],
        lineno=p.lineno(2),
        col_offset=0
        )
    elif p[2] == '<':
        p[0] = ast.Compare(left=ast.Call(
            func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
            args=[p[3]],
            keywords=[],
            lineno=p.lineno(2),
            col_offset=0
        ), ops=[ast.Lt()], comparators=[ast.Call(
            func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
            args=[p[4]],
            keywords=[],
            lineno=p.lineno(2),
            col_offset=0
        )],
        lineno=p.lineno(2),
        col_offset=0)
    elif p[2] == '=':
        p[0] = ast.Compare(left=ast.Call(
            func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
            args=[p[3]],
            keywords=[],
            lineno=p.lineno(2),
            col_offset=0
        ), ops=[ast.Eq()], comparators=[ast.Call(
            func=ast.Name(id='int', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
            args=[p[4]],
            keywords=[],
            lineno=p.lineno(2),
            col_offset=0
        )],
        lineno=p.lineno(2),
        col_offset=0
        )

def p_logical_op(p):
    '''LOGICAL_OP : LPAREN AND EXP EXPS RPAREN
                  | LPAREN OR EXP EXPS RPAREN
                  | LPAREN NOT EXP RPAREN'''
    if p[2] == 'and':
        tmp = p[3]
        for ele in p[4]:
            tmp = ast.BoolOp(op=ast.And(), values=[tmp, ele], lineno=p.lineno(2), col_offset=0) 
    elif p[2] == 'or':
        tmp = p[3]
        for ele in p[4]:
            tmp = ast.BoolOp(op=ast.Or(), values=[tmp, ele], lineno=p.lineno(2), col_offset=0) 
    elif p[2] == 'not':
        tmp = ast.UnaryOp(op=ast.Not(), operand=p[3], lineno=p.lineno(2), col_offset=0)
    p[0] = tmp

def p_def_stmt(p): # move exp to variable
    '''DEF_STMT : LPAREN DEFINE VARIABLE EXP RPAREN'''
    def_name = ast.Name(id=p[3].id, ctx=ast.Store(), lineno=p.lineno(2), col_offset=0) #賦值
    p[0] = ast.Assign(targets=[def_name], value=p[4], lineno=p.lineno(2), col_offset=0)

def p_fun_exp(p):
    '''FUN_EXP : LPAREN FUN LPAREN IDS RPAREN EXP RPAREN'''
    args = [ast.arg(arg=ele.id, annotation=None, lineno=ele.lineno, col_offset=0) for ele in p[4]]
    p[0] = ast.Lambda(args=ast.arguments(args=args, posonlyargs=[], vararg=None, kwonlyargs=[], kw_defaults=[], kwarg=None, defaults=[]), body=p[6], lineno=p.lineno(2), col_offset=0)

def p_fun_call(p):
    '''FUN_CALL : LPAREN FUN_EXP PARAMS RPAREN
                | LPAREN FUN_NAME PARAMS RPAREN'''
    p[0] = ast.Call(func=p[2], args=p[3], keywords=[], lineno=p.lineno(2), col_offset=0)

def p_if_exp(p):
    '''IF_EXP : LPAREN IF EXP EXP EXP RPAREN'''
    p[0] = ast.IfExp(test=p[3], body=p[4], orelse=p[5], lineno=p.lineno(2), col_offset=0)

def p_exps(p):
    '''EXPS : EXPS EXP
            | EXP'''
    if len(p) == 2:
        p[0] = [p[1]]
    else:
        p[0] = p[1] + [p[2]]

def p_ids(p):
    '''IDS : IDS VARIABLE
           | VARIABLE
           |'''
    if len(p) == 2:
        p[0] = [p[1]]
    elif len(p) == 3:
        p[0] = p[1] + [p[2]]
    else:
        p[0] = []

def p_fun_name(p):
    '''FUN_NAME : ID'''
    p[0] = ast.Name(id=p[1], ctx=ast.Load(), lineno=p.lineno(1), col_offset=0)

def p_params(p):
    '''PARAMS : PARAMS EXP
            | EXP
            |'''
    if len(p) == 2:
        p[0] = [p[1]]
    elif len(p) == 3:
        p[0] = p[1] + [p[2]]
    else:
        p[0] = []

def booltrans(p):
    if p == True:
        return '#t'
    else:
        return '#f'


def p_print_stmt(p):
    '''PRINT_STMT : LPAREN PRINTNUM EXP RPAREN
                  | LPAREN PRINTBOOL EXP RPAREN'''
    if p[2] == 'print-num':
        p[0] = ast.Expr(value=ast.Call(func=ast.Name(id='print', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0), args=[p[3]], keywords=[], lineno=p.lineno(2), col_offset=0))
    else:
        p[0] = ast.Expr( # 包裝表達式
            value=ast.Call(
                func=ast.Name(id='print', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
                args=[
                    ast.Call(
                        func=ast.Name(id='booltrans', ctx=ast.Load(), lineno=p.lineno(2), col_offset=0),
                        args=[p[3]],
                        keywords=[],
                        lineno=p.lineno(2),
                        col_offset=0
                    )
                ],
                keywords=[],
                lineno=p.lineno(2),
                col_offset=0
            ),
            lineno=p.lineno(2),
            col_offset=0
        )

def p_bool_val(p):
    '''BOOL_VAL : BOOL'''
    p[0] = ast.Constant(value=p[1], lineno=p.lineno(1), col_offset=0)

def p_number_val(p):
    '''NUMBER_VAL : NUMBER'''
    p[0] = ast.Constant(value=p[1], lineno=p.lineno(1), col_offset=0)

def p_variable(p):
    '''VARIABLE : ID'''
    p[0] = ast.Name(id=p[1], ctx=ast.Load(), lineno=p.lineno(1), col_offset=0)


def p_error(p):
    print('Syntax error:', p)
    exit(0)

# yacc
parser = yacc.yacc()


def main():
    filename = sys.argv[1]
    with open(filename, 'r') as file:
        data = file.read()

    result = parser.parse(data)
    ast.fix_missing_locations(result)
    code = compile(result, filename="<ast>", mode="exec")
    exec(code, {'booltrans': booltrans})


if __name__ == "__main__":
    main()
