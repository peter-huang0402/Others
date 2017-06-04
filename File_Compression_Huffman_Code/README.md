
<Limitation> 

I use 4 bytes unsigned int for saving frequency of char by haffman encoding.
The 4 bytes of unsigned int ranges from 0 to 4,294,967,295.
If the number’s calculation like frequency or file size are larger than 4,294,967,295, it will be overflow.
So, be sure that your files is not beyond than 4,294,967,295.


Compile:
gcc henc9149.c -o henc
gcc hdec9149.c -o hdec

Run:
./henc  abc.pdf
./hdec  abc.pdf.huf
