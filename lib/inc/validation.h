#ifndef VALIDATION_H
#define VALIDATION_H

// support stringify macro args
#define ARG_FIRST_CHAR(arg) (#arg[0])
#define ARG_LAST_CHAR(arg) (#arg)[sizeof(#arg)-2]

// check port for ABCDE
#define IS_VALID_PORT(port) ARG_FIRST_CHAR(port) == 'A' || ARG_FIRST_CHAR(port) == 'B' || ARG_FIRST_CHAR(port) == 'C' || ARG_FIRST_CHAR(port) == 'D' || ARG_FIRST_CHAR(port) == 'E'

// check pin for 0-15
#define IS_VALID_PIN(pin) pin>=0 && pin<16

// check callback instruction for ending ')' symbol
#define IS_FUNCTION(func_name) ARG_LAST_CHAR(func_name) == ')'

#endif