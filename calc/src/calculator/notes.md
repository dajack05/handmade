# Calc process

1. ✅ Process input into digits and operators.
2. Use the Shunting Yard algorithm to transform in-fix to post-fix notation.
3. Process post-fixed data into result
4. Profit.

## Shunting Yard Algorithm

Create a Stack and Queue.

When processing, digits go into the Queue, operators go onto the stack.

When an operator is put onto the Stack, check the last operator. If it is higher importance, pop the older one off and put it in the Queue. Then place the new operator on the stack.

When dealing with parenteses, push the `(` onto the Stack. When you reach the `)`, push all operators into the Queue until you reach the `(`. Once you reach the `(`, discard it and the paired `)`.

The input of `(5*4+3*2)-1` (infix) should transform to `54*32*+1-` (postfix).

## Postfix processing

Create a stack.

### Rules:

- Numbers
  - -> push
- Operators
  - -> pop
    - -> 2nd
  - -> pop
    - -> 1st

Example: `54*32*+1-`

`5` -> push
`4` -> push
`*` -> pop (4) (2nd)
    -> pop (5) (1st)
    `5*4` = `20`
    push (20)

continue until finished
