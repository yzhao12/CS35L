In multithreading this program, the first issue was to understand the
program enough to know which parts I was supposed to change into
threads. Then the next big challenge was seeing which variables I
needed to take out of the main and multithreaded functions and make
global. Finally, personally the biggest challenge for me was
recognizing that the arguement that I needed to pass into the
multithreaded function (the thread number) had to always exist,
because I was passing in a pointer. I couldn't simply use the for-loop
counter's address, because the for-loop counter changes every
iteration and the old number is erased.



1 Thread

real    0m48.201s
user    0m48.206s
sys     0m0.000s


2 Threads

real    0m25.716s
user    0m50.040s
sys     0m0.006s


4 Threads

real    0m12.183s
user    0m48.274s
sys     0m0.005s

8 Threads

real    0m6.559s
user    0m50.748s
sys     0m0.004s


As seen above, doubling the number of threads cuts the real time used
by almost half. This relationship applies to 1, 2, 4, and 8 threads with
no sign of diminishing returns.
