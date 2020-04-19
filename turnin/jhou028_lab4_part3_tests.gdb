# Test file for "Lab4_stateMachines"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Test sequence from locked: A2, 00, A1 => PORTB: 0x01, PORTC = 4 (unlocked)
test "PINA 4, 0, 2=> PORTB: 0x01 PORTC = 4, state: unlocked"

set state = locked

print state
setPINA 4
continue 2

print state
setPINA 0
continue 2

print state
setPINA 2
continue 2

print state
expectPORTB 0x01
expectPORTC 0x04
expect state unlocked
checkResult


# Test sequence from locked: A2, A0 => PORTB: 0x00, PORTC = 1 (locked)
test "PINA 4, 1=> PORTB: 0x00 PORTC = 1, state: locked"

set state = locked

print state
setPINA 4
continue 2

print state
setPINA 1
continue 2

print state
expectPORTB 0x00
expectPORTC 0x01
expect state locked
checkResult


# Test sequence from unlocked: A7 => PORTB: 0x00, PORTC = 1 (locked)
test "PINA 0x80=> PORTB: 0x00 PORTC = 1, state: locked"

set state = unlocked

print state
setPINA 0x80
continue 2

print state
expectPORTB 0x00
expectPORTC 0x01
expect state locked
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
