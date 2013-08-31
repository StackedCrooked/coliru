
/**
3.  Sack Option Format

   The SACK option is to be used to convey extended acknowledgment
   information from the receiver to the sender over an established TCP
   connection.

       TCP SACK Option:

       Kind: 5

       Length: Variable

                         +--------+--------+
                         | Kind=5 | Length |  // 2 bytes
       +--------+--------+--------+--------+
       |      Left Edge of 1st Block       |  // 4 bytes
       +--------+--------+--------+--------+
       |      Right Edge of 1st Block      |
       +--------+--------+--------+--------+
       |                                   |
       /            . . .                  /
       |                                   |
       +--------+--------+--------+--------+
       |      Left Edge of nth Block       |
       +--------+--------+--------+--------+
       |      Right Edge of nth Block      |
       +--------+--------+--------+--------+
*/