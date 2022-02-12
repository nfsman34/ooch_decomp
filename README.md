# ooch_decomp
A program to decompress files using CRIware's OOCH compression scheme (a modified version of LZ77)
Based on AZUCO's OOCH decompressor and has been modified to work with big endian files.

Usage:

    ooch_decomp.exe (file to decompress)
    
The program will save a file as (filename)\_decomp(file extention)
    
for example, a file named "BDSNC.p" will be decompressed and saved as "BDSNC_decomp.p"

Based on AZUCO's original decompressor for Code Geass Leroach of the Rebellion Lost Colours (yes, that's the games title)
    Link to the original program: https://azuco.sakura.ne.jp/column/ag_ps2cglc/
