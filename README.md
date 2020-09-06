# Pseudo-Random Number Generators
While hardware modules exist that use physical phenomena to generate truly random numbers, most computing systems use either hardware or software pseudo-random number generators (PRNGs) that produce sequences of values that appear to be random. PRNGs can be initialized to a specific value, allowing the same sequence of (seemingly) random values to be generated repeatedly, which is helpful in program debugging. Most programming languages and operating systems provide a built-in function to generate random numbers uniformly distributed in the range (0, 1); these values then can be either (a) appropriately scaled to yield a desired continuous random function or (b) divided into proportionallysized ranges for discrete random functions.

The accuracy of program results (e.g., simulations) obviously depends on the randomness of the PRNGs. This randomness can be evaluated, to some extent, by applying various mathematical measures to the generated sequences and comparing the results with those of truly random sequences. Obvious measures include the mean value and, for discrete functions, how often each value occurs. Such tests are of limited value, however, since a counter that repeatedly cycles through the numbers 1 through 6 would generate values with the same frequency as a true six-sided die, even though it clearly is not random. 

Other mathematical measures also can be used to measure randomness; for example, when flipping a coin, the actual frequency of various runs of consecutives heads or tails can be compared to the expected frequency of occurrence. This project compares PRNGs using the simple mathematical measures of mean and standard deviation, considering both short and long sequences of random values.

Linear Feedback Shift Registers (LFSRs) are widely used in hardware applications such as low-cost counters (with an unusual sequence), random number generators, coding, and signature generation (e.g., checksums) for blocks of data. 

Figure 1 illustrates an 8-bit LFSR, consisting of an 8-bit shift register and a multiple-input XOR gate. On each clock cycle, the existing shift register value is shifted left and a new least-significant bit value is loaded. The “characteristic polynomial” specifies which bits of the current value are XORed to compute the next value of the leastsignificant-bit. The “+1” in the characteristic polynomial is important for certain mathematical models of LFSRs, but is ignored in determining which bits to XOR.

<p align="center">
  <img src="https://i.imgur.com/w0L8l14.png">
  <b>Figure 1.</b> 8-bit LFSR
</p>

For appropriate characteristic polynomials, the LFSR produces a maximum-length cycle of 2^n– 1 values, excluding only the all-zero value. Other hardware implementations are also used in various applications, but this configuration is easily simulated in software. Dividing the LFSR value by 2^n yields a result in the range (0, 1).

Numerous categories of software algorithms also exist for generating random sequences. A simple one is the Linear Congruential Generator (LCG), defined by the relation: Xn+1 = (a Xn + c) mod m. The resulting value or a specified subset of bits is used to generate the output value. (The lower-order bits are not always used, since they may not exhibit the same quality of mathematical randomness.)
