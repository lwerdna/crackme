solution0.txt explains what f_evaluate() and lsvec[] are
solution1.txt explains what VerifyParity() does, and how to invert it
cryptanalysis.pdf explains how to invert the core MQ problem

the keygen is split into two halves:
keygen_source\attack.cpp implements the attack from the pdf, deriving the private data
keygen_source\keygen.cpp uses the private data from the attack, adds parity, encodes serial as strong

misc\* is some experiments on random s-boxes when I was searching for a collision attack (see Eli Biham paper)

attack_results\* is the results of the attack (explained in PDF) performed 2 more times

As you see, the attack finds consistently that the first sbox is 16->14 and the last is 14->14, which is
different than how the scheme is advertised. The 16->14 should make 3/4 of all searches pass
the first s-box but this is not always true (the entire scheme is not guaranteed to have a
plaintext<->ciphertext for some arbitrarily chosen ciphertext). So if the first sbox fails
and you get "no solution", just re-run the keygen.

Honestly, the keygen finds a solution within ~2 minutes only about 33% of the time. I would just re-run
it if it appears to enter s8 a few times without solving.

example chosen id keys:

2QTT6-TQFIQ-9SMSL-DAZXW-RQQ2M (id: 0x1122)
JT2CQ-6HY7O-6B3DJ-HIAJC-BEC2Q (id: 0x5678)
FGU6J-WAHFJ-T6ZD7-CBKOQ-6LJHD (id: 0x9999)
PMOFN-WJIJW-DQ9T9-IOM62-RXIIR (id: 0xBBBB)
39O7V-9E2O3-3HUCR-ZAOGH-VUKHM (ID: 0xDDDD)
NNE92-NS62P-TZ9QC-NGEII-6UJ4V (id: 0xDDDD)

example random id keys:

HSCTZ-KL9E2-OW67U-UBVEN-VYW7X
PMAUJ-9CJ2W-3SBSY-3A26Y-HAR4V
Z4ANL-MTVRL-3XVL3-A3NMB-3UI39
U3Z3Y-UM337-ZPT9R-4RCKP-C7MSP
SE2FI-B2LOS-EN4LK-HLJ9I-CWZ47
PGPPP-ZVPJW-UEE2Q-FWLY3-3KPPX

Sorry for any (expected) errors in the docs/code; kindly notify me if you find any!

--
andrewl
jan13_2009
crackmes.de