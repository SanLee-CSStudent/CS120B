test "PINA: 0x00 => PORTB: 0x02"
setPINA 0x00
continue 5
expectPORTB 0x02
checkResult

test "PINA: 0x02 => PORTB: 0x02"
setPINA 0x02
continue 5
expectPORTB 0x02
checkResult

test "PINA: 0x01 => PORTB: 0x01"
setPINA 0x01
continue 5
expectPORTB 0x01
checkResult
