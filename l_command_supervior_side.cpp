
case 'l':
    vesp.PC = 0x781; for(i = 12214; i<= 12223 && vesp.reset == 0; i++) maincycle(0); //Display "d-address:"
    updatescreen(4,10); //display the frame buffer
    vesp.MEMORY[0x0010] = getchar(); vesp.MEMORY[0x0011] = getchar(); 
    vesp.MEMORY[0x0012] = getchar(); vesp.MEMORY[0x0013] = getchar();
    getchar();
    vesp.PC = 0x795; for(i = 12224; i<= 12233 && vesp.reset == 0; i++) maincycle(0); //Display "m-address"
    updatescreen(5,10); //display the frame buffer
    vesp.MEMORY[0x0014] = getchar(); vesp.MEMORY[0x0015] = getchar(); 
    vesp.MEMORY[0x0016] = getchar(); vesp.MEMORY[0x0017] = getchar();
    getchar();
    //convert ascii digits to hex digits--This could be done in vesp as well-but doing it in C simplifies things considerably
    for(i=0x0010;i<= 0x0017;i++)
        if(vesp.MEMORY[i] >= '0' && vesp.MEMORY[i] <= '9')
            vesp.MEMORY[i] = vesp.MEMORY[i] - '0';
        else
            if(vesp.MEMORY[i] >= 'A' && vesp.MEMORY[i] <= 'F')
                vesp.MEMORY[i] = vesp.MEMORY[i] - 'A' + 10;
            else 
            {
                cout << "Invalid address. Try again.\n";
                break;
            }
    vesp.MEMORY[0x0010] = vesp.MEMORY[0x0010] << 12 | vesp.MEMORY[0x0011] << 8 | vesp.MEMORY[0x0012] << 4 | vesp.MEMORY[0x0013]; //Disk address
    vesp.MEMORY[0x0014] = vesp.MEMORY[0x0014] << 12 | vesp.MEMORY[0x0015] << 8 | vesp.MEMORY[0x0016] << 4 | vesp.MEMORY[0x0017]; //RAM address
    vesp.PC = 0x800; //load using vesp.
    for(i = 12234; i<= 12234 && vesp.reset == 0; i++) maincycle(0); //initialize IX
    while(programSize++ <= 256)
    {
        for(i = 12235; i<= 12238 && vesp.reset == 0; i++) maincycle(0);
        if (vesp.MEMORY[0] == 0) 
        {
            for(i = 12239; i<= 12242 && vesp.reset == 0; i++) maincycle(0);
            break;
        }
        else
            for(i = 12239; i<= 12246 && vesp.reset == 0; i++) maincycle(0);
    }
    break;
