
<b>Limitation</b></p>

I use 4 bytes unsigned int for saving frequency of char by haffman encoding.
The 4 bytes of unsigned int ranges from 0 to 4,294,967,295.
If the number’s calculation like frequency or file size are larger than 4,294,967,295, it will be overflow.
So, be sure that your files is not beyond than 4,294,967,295.
</p>
</p>
<b>Compile</b></p>
gcc henc9149.c -o henc </p>
gcc hdec9149.c -o hdec</p>
</p>
</p>
<b>Run</b></p>
./henc  abc.pdf</p>
./hdec  abc.pdf.huf</p>

Check result with following instructions
diff      XX.pdf origan.pdf </p>
md5sum    XX.pdf origan.pdf </p>
