## Lexer

Use the follow C standard functions to identify the character class of
a _single_ character.

    isalpha - is a letter
    isalnum - is a letter or number
    isdigit - is a number
    ispunct - is a punctuation character, i.e., not a letter or digit but still printable

Use the following idioms to build up the list of tokens.  `new_token`
and `new_identifier` are helper methods defined in `token.c` that you
may use to construct the correct `Token` `struct`.

    token_list[token_list_i++] = new_token(EQ);

    token_list[token_list_i++] = new_identifier(IDENT, buffer);

Use `atoi` to create the value for a `NUMBER` token.

     token_list[token_list_i++] = new_number(NUMBER, atoi(buffer));

Use the following idiom to save a lexeme during lexing.

    buffer[buffer_i++] = c;
    c = fgetc(lexerin);

### Debugging

If your lexer is hanging, make sure the input is being advanced with
`fgetc`.
