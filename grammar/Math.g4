grammar Math;

math
  : expr END;
expr
  : OPEN_PAREN expr CLOSE_PAREN               # parensExpr
  | op=(OP_ADD|OP_SUB) expr                   # unaryExpr
  | left=expr op=(OP_MUL|OP_DIV) right=expr   # infixExpr
  | left=expr op=(OP_ADD|OP_SUB) right=expr   # infixExpr
  | func=ID OPEN_PAREN expr CLOSE_PAREN       # funcExpr
  | OPEN_PAREN expr CLOSE_PAREN               # parensExpr
  | OPEN_BRACK expr CLOSE_BRACK               # bracketsExpr
  | value=NUM                                 # numberExpr
  | id=ID                                     # idExpr
  ;

OPEN_PAREN: '(';
CLOSE_PAREN: ')';
OPEN_BRACK: '[';
CLOSE_BRACK: ']';
OP_ADD: '+';
OP_SUB: '-';
OP_MUL: '*';
OP_DIV: '/';
OP_EXP: '^';
ID: [_A-z0-9]+;
NUM: [0-9]+ ('.' [0-9]+)? ([eE] [+-]? [0-9]+)?;
WS: [ \t] -> channel(HIDDEN);
END: [\r\n]+;
