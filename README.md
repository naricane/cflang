![cflang](https://github.com/comes-group/cflang) interpreter

At the moment, it only tokenizes the source code and prints the resulting tokens with their corresponding spans.

For example it turns this source:
```
|echo| {
  echo : echo, ??;
}
: |self, char| {
  (char <> 0) : {
    char!!;
    self : self, ??;
  };
}
```
into:
```
Pipe 0 1 |
Identifier 1 5 echo
Pipe 5 6 |
LeftBrace 7 8 {
Identifier 11 15 echo
Colon 16 17 :
Identifier 18 22 echo
Comma 22 23 ,
DoubleAsk 24 26 ??
Semicolon 26 27 ;
RightBrace 28 29 }
Colon 30 31 :
Pipe 32 33 |
Identifier 33 37 self
Comma 37 38 ,
Identifier 39 43 char
Pipe 43 44 |
LeftBrace 45 46 {
LeftParen 49 50 (
Identifier 50 54 char
NotEqual 55 57 <>
Number 58 59 0
RightParen 59 60 )
Colon 61 62 :
LeftBrace 63 64 {
Identifier 69 73 char
DoubleShow 73 75 !!
Semicolon 75 76 ;
Identifier 81 85 self
Colon 86 87 :
Identifier 88 92 self
Comma 92 93 ,
DoubleAsk 94 96 ??
Semicolon 96 97 ;
RightBrace 100 101 }
Semicolon 101 102 ;
RightBrace 103 104 }
EOF 104 104
```
