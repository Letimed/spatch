#ifndef PARSER_H
#define PARSER_H

/*
 * This function epurate a string , removing every space and tabulations that
 * might be garbage.
 * It returns a pointer to a newly created string being the epurated version of
 * the provided string @to_epurate, the returned string must be freed by the
 * caller
 * @to_epurate:	The string to epurate.
 */
char * epurate_string(const char *to_epurate);

/*
 * This function returns 1 or 0 wether the provided string is a comment.
 * A string is considered a comment when the first alphanumeric character in it
 * is a '#'
 * A return value of 0 means : the line is not a comment
 * A return value of 1 means : the line is a comment
 * A return value < 0 means an error.
 * @to_check:	The string to check
 */
int is_comment(const char *to_check);

/*
 * This function tokenise the given string according to the given delimiter.
 * On the first call the function should be called with @to_parse set to the
 * desired string. On every subsequent call targetting the same string @to_parse
 * should be set to NULL.
 * @to_parse:	The string to be parsed (NULL if same as previous one)
 * @delim:	Array of delimiters
 */
char * get_token(char *to_parse, const char *delim);

#endif
