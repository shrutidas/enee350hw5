//load loop (works)
//disk address is at 0x0010, memory address is at 0x0014
0x3002;   0x0010; //initialize IX to disk addr. //0x0800-801

0x2001;   0xFFFF; //load FFFF into B    //0x0802-803  //end marker
0xE000;                               //load next word to A  //0x0804
0x3018;   0x0000; //save it into temp-1         //0x0805-806
0x0300;  //A=A-B                       //0x0807

0x2001;   0x0815; //set exit address   //0x0808-809
0x7100;  //Jump if A = 0      //0x080A

0x3010;   0x0002;//save IX to temp-2 //0x080B-80C //0010 holds index to disk
0x3002;   0x0014;//load IX from 0x0014 //0x080D-80E //0014 holds index to core
0xF018; //copy temp-1 to MEMORY[IX]   //0x080F
0x3014;   0x0002; //store IX back into 0x0014   //0x0810-811
0x3002;   0x0010; //restore IX                  //0x0812-813
0x4802;  //Jump back to the loop       //0x0814

0x3002;   0x0014; //load  IX from 0x0014 //0x0815-816 //0014 holds index to core
0xF018; //copy temp-1 to MEMORY[IX]   //0x0817

0x7700; //No-operation                //0x0818
