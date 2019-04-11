//vesp's boot code begins at location 0x0020.
// When vesp starts, it first loads the boot code from vesp.Bootsrap into vesp.MEMORY[0x0020-..]
//It then carries out the following steps:
//1- Clear the screen
//2- Display vesp is booting...  on the screen
//3- Display loading kernel... on the screen
//4- Load kernel into memory blocks 7 and 8
//5- Insert  delay 
//6- Display vesp: on the screen
//7- Blink a cursor for command entry
// 8 + 4096 + 4 + 9*16 = 8 + 4100 + 144 = 4252
// bootstrap code: initialize the screen variables and clear the screen                                 vesp.address

0x2008;   0x0000;  // clear location 8   (cursor-x)        //020-021
0x2009;   0x0000;  // clear location 9   (cursor-y)        //022-023
0x200A;   0x000F;  // set   location A   (pixel color)     //024-025
0x200B;   0x0000;  // set   display mode (ASCII)           //026-027
0x200C;   0x002B;  // set   pixel symbol  ('+' sign)       //028-029

// Clear the frame buffer(insert white space). The frame Buffer has an image of vesp's screen)
// The screen has 16x64 = 1024 ascii characters
0x2002;  0x0300;  // load IX with 0x0300 (768)-screen[0]   //02A-02B
0x2000;  0x0400;  // load 0x400(1024) into register A(l.c) //02C-02D
0x200D;  0x0020;  // load space into location 0x00D        //02E-02F
0x5034;  0xF00D;  // if A is 0 then jump out of the loop   //030-031
// else load space into next framebuffer location
0x9000;                                  // decrement A                           //032
0x4030;                                  // loop back to check if A is 0          //033

// insert a carriage return at the end of each line
0x2002;  0x033F;  // load IX with 0x033F                   //034-035
0x2000;  0x0010;  // load 0x0010 into A (A=16)             //036-037
0x200E;  '\n';    // load carriage ret into location 0x00E //038-039 
// location for carriage return is E in vesp.MEMORY 
0x2001;  0x003F;  // load B with 0x03F = 63                //03A-03B                                                          
0x5049;  0xF00E;  // if A is 0 then jump out of the loop   //03C-03D
// else load cr into the next framebuffer location
0x9000;                                  // decrement A                           //03E
0x300F;  0x0000;   // save A into temp [0x00F]              //03F-040
0x3000;  0x0002;   // copy IX into A                        //041-042
0x0000;                                  // add                                   //043
0x3002;  0x0000;   // save A into IX                        //044-045
0x3000;  0x000F;   // restore A from temp                   //046-047
0x403C;                                  // loop back to check if A is 0          //048

// write the message  "vesp is booting..."                                                         
0x2300;  0x0076;  // write v   //049-04A---line 300 to 33F (vesp...)
0x2301;  0x0065;  // write e   //04B-04C
0x2302;  0x0073;  // write s   //04D-04E
0x2303;  0x0070;  // write p   //04F-050
0x2304;  0x0020;  // write ' ' //051-052
0x2305;  0x0069;  // write i   //053-054
0x2306;  0x0073;  // write s   //055-056
0x2307;  0x0020;  // write ' ' //057-058
0x2308;  0x0062;  // write b   //059-05A
0x2309;  0x006F;  // write o   //05B-05C
0x230A;  0x006F;  // write o   //05D-05E
0x230B;  0x0074;  // write t   //05F-060
0x230C;  0x0069;  // write i   //061-062
0x230D;  0x006E;  // write n   //063-064
0x230E;  0x0067;  // write g   //065-066
0x230F;  0x002E;  // write .   //067-068
0x2310;  0x002E;  // write .   //069-06A
0x2311;  0x002E;  // write .   //06B-06C

// display the prompt: "loading kernel:"  
0x2340;   0x006C; // write l   //06D-06E-----line 340 to 37F (load...)
0x2341;   0x006F; // write o   //06F-070
0x2342;   0x0061; // write a   //071-072
0x2343;   0x0064; // write d   //073-074
0x2344;   0x0069; // write i   //075-076
0x2345;   0x006E; // write n   //077-078
0x2346;   0x0067; // write g   //079-07A
0x2347;   0x0020; // write ' ' //07B-07C
0x2348;   0x006B; // write k   //07D-07E
0x2349;   0x0065; // write e   //07F-080
0x234A;   0x0072; // write r   //081-082
0x234B;   0x006E; // write n   //083-084
0x234C;   0x0065; // write e   //085-086
0x234D;   0x006C; // write l   //087-088
0x234E;   0x002E; // .         //089-08A
0x234F;   0x002E; // .         //08B-08C
0x2350;   0x002E; // .         //08D-08E
0x2351;   0x002E; // .         //08F-090

// Load the kernel from vesp.HDISK[1000-12FF] into vesp.MEMORY[0700-09FF]
0x2002;   0x1000;// Load 0x1000 into IX                     //091-092
0x2007;   0x0700;// Load loc.7 with 0x0700                  //093-094
0x2000;   0x0300;// Load 0x0300 into A(loop count)          //095-096
0x50A4;   0xE001;// If A is 0 then jump out of the loop     //097-098
// Move the next instruction into B
0x3006;   0x0002;// Save IX (the address in HDISK)          //099-09A
0x3002;   0x0007;// Load address in kernel frame into IX    //09B-09C
0xF001;                                // move next instruction into kernel fr.   //09D
0x3007;   0x0002;// Save IX(the address in kernel fr.)      //09E-09F
0x3002;   0x0006;// Restore IX (the address in HDISK) //0A0-0A1
0x9000;  // Decrement A   //0A2
0x4097;  // Loop back to check if A is 0 //0A3
0x4700; // jump to location 0x0700   //0A4

