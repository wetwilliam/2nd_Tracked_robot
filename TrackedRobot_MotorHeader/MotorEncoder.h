/*---Read and Check Motor Encoder---*/


int MotorPE(int MotorNumber);/*---Read Motor Positions---*/

/*---Inheritance : Check Motor's Positions---*/
int Check_MotorPE(int MotorNumber0);
int Check_MotorPE(int MotorNumber0,int MotorNumber1);
int Check_MotorPE(int MotorNumber0,int MotorNumber1,int MotorNumber2);
int Check_MotorPE(int MotorNumber0,int MotorNumber1,int MotorNumber2,int MotorNumber3);

/*---Inheritance : Check Motor's You Set Positions---*/
//int Check_MotorPE_Pos(int MotorNumber0,int Position_Of_Motor0);
//int Check_MotorPE_Pos(int MotorNumber0,int Position_Of_Motor0,int MotorNumber1,int Position_Of_Motor1);
//int Check_MotorPE_Pos(int MotorNumber0,int Position_Of_Motor0,int MotorNumber1,int Position_Of_Motor1,int MotorNumber2,int Position_Of_Motor2);
//int Check_MotorPE_Pos(int MotorNumber0,int Position_Of_Motor0,int MotorNumber1,int Position_Of_Motor1,int MotorNumber2,int Position_Of_Motor2,int MotorNumber3,int Position_Of_Motor3);

/*---Check All Motor's Positions---*/
//int Check_Slim_PE(int Number, int *Number_Of_Motor, int *Position_Of_Motor);



/*---Read motor PE, and print---*/
int MotorPE(int MotorNumber)
{
    //printf("ininder\n");
    int wordsRead, wordsWritten;
    char Readbuf[20];
    char WaitReadBuf[30];
    int sum;
    int j,k;

   if(MotorNumber>=4)
    {
        printf("*** MotorNumber Greater than 3 ***\n");
        return 0;
    }

RE_MotorPE:

    tcflush(fd_Slim5, TCIFLUSH); //---flush motor buf
    usleep(30000);

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));//give buff '\0'
    memset(Readbuf, '\0', sizeof(Readbuf));//give buff '\0'
    sum = 0;

    //---Write Data
    sprintf(Writtenbuf,"?T%dPE\r\n",MotorNumber);
    wordsWritten = write(fd_Slim5, Writtenbuf, sizeof(Writtenbuf));

//    wordsWritten = write(fd_Slim5, "?T1PE\r\n", sizeof(Writtenbuf));
//    printf("wordsWritten=%d \n",wordsWritten);

    if(wordsWritten <= 0)
    {
        printf("*** Error wordsWritten=0 ***\n");
        goto RE_MotorPE;
    }

    usleep(30000);

    //---Read Data
    int Check_count=0,Check_error=0;
    int sum_of_wordsRead = 0,Check_point_position = -1;

    while(TRUE)
    {
//        printf("Check_count=%d\tCheck_error=%d\n",Check_count,Check_error);

        wordsRead = read(fd_Slim5,Readbuf,sizeof(Readbuf));
        usleep(7000);

        if(wordsRead >= 5 && Readbuf[0]=='?' && Readbuf[1]=='T' && Readbuf[2]==(MotorNumber+48) && Readbuf[3]=='P' && Readbuf[4]=='E')//first ask ==> find "?XXXX"
        {
            if(Check_count == 0)
            {
                for(int i=0; i< wordsRead; i++)
                {
                    WaitReadBuf[i+sum_of_wordsRead] = Readbuf[i];
                    //printf("%c\n", Readbuf[i]);
                }

                sum_of_wordsRead = sum_of_wordsRead + wordsRead;
            }

//            for(int i=0; i< wordsRead; i++)
//                printf("%c\n", Readbuf[i]);

            Check_count++;
        }
        else if(wordsRead > 0 && Check_count>=1)
        {
            for(int i=0; i< wordsRead; i++)
            {
                WaitReadBuf[i+sum_of_wordsRead] = Readbuf[i];
                //printf("%c\n", Readbuf[i]);

                if(Readbuf[i] == '.')
                {
                    Check_point_position = i;

                    for(i = Check_point_position+1; i < wordsRead; i++)
                    {
                        if(Readbuf[i] >= 48 && Readbuf[i] <= 57)
                            goto RE_MotorPE;
                    }

                    break;
                }

            }

            if(Check_point_position == -1)
                sum_of_wordsRead = sum_of_wordsRead + wordsRead;
            else
            {
                sum_of_wordsRead = sum_of_wordsRead + (Check_point_position+1);
                break;
            }

            Check_count++;
        }
        else Check_error++;

        if(Check_count == 10 || Check_error==10)
            goto RE_MotorPE;
    }


//    printf("WaitReadBuf = ");
//    for(int i=0;i<sum_of_wordsRead;i++)
//        printf("%c",WaitReadBuf[i]);


    int num = 1;

    for(int i=sum_of_wordsRead-1; i>= 4+1; i--)
    {
        if(WaitReadBuf[i]>=48 && WaitReadBuf[i]<=57)//WaitReadBuf[i] must be 0~9
        {
            sum = sum + (WaitReadBuf[i]-48)*num;
            num = num*10;
        }
        else if(WaitReadBuf[i]== '-')
        {
            for(int j=i-1; j>=5; j--)
            {
                if(WaitReadBuf[j]>=48 && WaitReadBuf[j]<=57)
                    goto RE_MotorPE;
            }
            sum = -sum;
            break;
        }
    }

    return sum;
}

/*---Inheritance : Check Motor's Positions---*/
int Check_MotorPE(int MotorNumber0)
{
    int Position0=0;
    int Motor_pos0=0;
    int Double_Check0=0;

    /*---Load Position---*/
    if(MotorNumber0==0)
        Motor_pos0 = Globle_T0MA_Position;
    else if(MotorNumber0==1)
        Motor_pos0 = Globle_T1MA_Position;
    else if(MotorNumber0==2)
        Motor_pos0 = Globle_T2MA_Position;
    else if(MotorNumber0==3)
        Motor_pos0 = Globle_T3MA_Position;

    /*---Check Position---*/
    while(TRUE)
    {
        Position0 = MotorPE(MotorNumber0);
        //printf("Position0=%d\n",Position0);

        /*---Double Check Position---*/
        if(abs(Position0-Motor_pos0) <= 50)
        {
            for(int i=0; i<2; i++)
            {
                Position0 = MotorPE(MotorNumber0);
                //printf("Position0=%d \n",Position0);
                if(abs(Position0-Motor_pos0) <= 50)
                     Double_Check0++;
            }

            /*---If Double Check Position OK---*/
            if(Double_Check0==2)
            {
                //printf("Double_Check0=%d\n",Double_Check0);
                break;
            }
            else Double_Check0=0;
        }
    }


}

int Check_MotorPE(int MotorNumber0,int MotorNumber1)
{
    int Position0=0,Position1=0;
    int Motor_pos0=0,Motor_pos1=0;
    int Select_Check0=0,Select_Check1=0;
    int Double_Check0=0,Double_Check1=0;
    int key0=0,key1=0;
    int Out_While_0=0,Out_While_1=0;

    /*---Check Repeat---*/
    if(MotorNumber0==MotorNumber1)
    {
        printf("*** Use Check_MotorPE(2 Motor) Error : The Same Number ***\n");
        return 0;
    }
    /*---Load Position : First Motor---*/
    if(MotorNumber0==0)         Motor_pos0 = Globle_T0MA_Position;
    else if(MotorNumber0==1)    Motor_pos0 = Globle_T1MA_Position;
    else if(MotorNumber0==2)    Motor_pos0 = Globle_T2MA_Position;
    else if(MotorNumber0==3)    Motor_pos0 = Globle_T3MA_Position;
    /*---Load Position : Second Motor---*/
    if(MotorNumber1==0)         Motor_pos1 = Globle_T0MA_Position;
    else if(MotorNumber1==1)    Motor_pos1 = Globle_T1MA_Position;
    else if(MotorNumber1==2)    Motor_pos1 = Globle_T2MA_Position;
    else if(MotorNumber1==3)    Motor_pos1 = Globle_T3MA_Position;

    //printf("G_T1MA=%d\tG_T2MA=%d\n",Globle_T1MA_Position,Globle_T2MA_Position);

    /*---Check Position---*/
    while(TRUE)
    {
        /*---Update Motor PE Data---*/


        if(key0!=1)
            Position0 = MotorPE(MotorNumber0);
        if(key1!=1)
            Position1 = MotorPE(MotorNumber1);

        //printf("Position0=%d\tPosition1=%d\n",Position0,Position1);

        /*---Select Check---*/
        if(abs(Position0-Motor_pos0) <= 50) Select_Check0=1;
        if(abs(Position1-Motor_pos1) <= 50) Select_Check1=1;

        /*---Double Check Position---*/
        if(Select_Check0==1 || Select_Check1==1)
        {
            if(Select_Check0==1 && key0!=1){
                for(int i=0; i<2; i++){
                    Position0 = MotorPE(MotorNumber0);
                    //printf("Position0=%d \n",Position0);
                    if(abs(Position0-Motor_pos0) <= 50) Double_Check0++;
                }
            }

            if(Select_Check1==1 && key1!=1){
                for(int i=0; i<2; i++){
                    Position1 = MotorPE(MotorNumber1);
                    //printf("Position0=%d \n",Position0);
                    if(abs(Position1-Motor_pos1) <= 50) Double_Check1++;
                }
            }

            /*---If Double Check Position OK---*/
            if(Double_Check0==2 && key0!=1){
                printf("Motor%d\tOK\n",MotorNumber0);
                Out_While_0=1;
                key0=1;
            }
            else {
                Double_Check0=0;
                //Double_Check1=0;
                Select_Check0=0;
                //Select_Check1=0;
            }

            if(Double_Check1==2 && key1!=1){
                printf("Motor%d\tOK\n",MotorNumber1);
                Out_While_1=1;
                key1=1;
            }
            else {
                //Double_Check0=0;
                Double_Check1=0;
                //Select_Check0=0;
                Select_Check1=0;
            }
            /*---Break Condition---*/
            if(Out_While_0==1 && Out_While_1==1)
                return 1;
        }
    }
}

int Check_MotorPE(int MotorNumber0,int MotorNumber1,int MotorNumber2)
{
    int Position0=0,Position1=0,Position2=0;
    int Motor_pos0=0,Motor_pos1=0,Motor_pos2=0;
    int Select_Check0=0,Select_Check1=0,Select_Check2=0;
    int Double_Check0=0,Double_Check1=0,Double_Check2=0;
    int key0=0,key1=0,key2=0;
    int Out_While_0=0,Out_While_1=0,Out_While_2=0;

    /*---Check Repeat---*/
    if(MotorNumber0==MotorNumber1||MotorNumber0==MotorNumber2||MotorNumber1==MotorNumber2)
    {
        printf("*** Use Check_MotorPE(3 Motor) Error : The Same Number ***\n");
        return 0;
    }
    /*---Load Position : First Motor---*/
    if(MotorNumber0==0)         Motor_pos0 = Globle_T0MA_Position;
    else if(MotorNumber0==1)    Motor_pos0 = Globle_T1MA_Position;
    else if(MotorNumber0==2)    Motor_pos0 = Globle_T2MA_Position;
    else if(MotorNumber0==3)    Motor_pos0 = Globle_T3MA_Position;
    /*---Load Position : Second Motor---*/
    if(MotorNumber1==0)         Motor_pos1 = Globle_T0MA_Position;
    else if(MotorNumber1==1)    Motor_pos1 = Globle_T1MA_Position;
    else if(MotorNumber1==2)    Motor_pos1 = Globle_T2MA_Position;
    else if(MotorNumber1==3)    Motor_pos1 = Globle_T3MA_Position;
    /*---Load Position : Third Motor---*/
    if(MotorNumber2==0)         Motor_pos2 = Globle_T0MA_Position;
    else if(MotorNumber2==1)    Motor_pos2 = Globle_T1MA_Position;
    else if(MotorNumber2==2)    Motor_pos2 = Globle_T2MA_Position;
    else if(MotorNumber2==3)    Motor_pos2 = Globle_T3MA_Position;

    /*---Check Position---*/
    while(TRUE)
    {
        /*---Update Motor PE Data---*/
        Position0 = MotorPE(MotorNumber0);
        Position1 = MotorPE(MotorNumber1);
        Position2 = MotorPE(MotorNumber2);
        //printf("Position0=%d\tPosition1=%d\tPosition2=%d\n",Position0,Position1,Position2);

        /*---Select Check---*/
        if(abs(Position0-Motor_pos0) <= 50) Select_Check0=1;
        if(abs(Position1-Motor_pos1) <= 50) Select_Check1=1;
        if(abs(Position2-Motor_pos2) <= 50) Select_Check2=1;

        /*---Double Check Position---*/
        if(Select_Check0==1 || Select_Check1==1 || Select_Check2==1)
        {
            if(Select_Check0==1 && key0!=1){
                for(int i=0; i<2; i++){
                    Position0 = MotorPE(MotorNumber0);
                    //printf("Position0=%d \n",Position0);
                    if(abs(Position0-Motor_pos0) <= 50) Double_Check0++;
                }
            }
            if(Select_Check1==1 && key1!=1){
                for(int i=0; i<2; i++){
                    Position1 = MotorPE(MotorNumber1);
                    //printf("Position0=%d \n",Position0);
                    if(abs(Position1-Motor_pos1) <= 50) Double_Check1++;
                }
            }
            if(Select_Check2==1 && key2!=1){
                for(int i=0; i<2; i++){
                    Position2 = MotorPE(MotorNumber2);
                    //printf("Position0=%d \n",Position0);
                    if(abs(Position2-Motor_pos2) <= 50) Double_Check2++;
                }
            }

            /*---If Double Check Position OK---*/
            if(Double_Check0==2 && key0!=1){
                printf("Motor%d\tOK\n",MotorNumber0);
                Out_While_0=1;
                key0=1;
            }
            else if(Double_Check1==2 && key1!=1){
                printf("Motor%d\tOK\n",MotorNumber1);
                Out_While_1=1;
                key1=1;
            }
            else if(Double_Check2==2 && key2!=1){
                printf("Motor%d\tOK\n",MotorNumber2);
                Out_While_2=1;
                key2=1;
            }
            else{
                Double_Check0=0;
                Double_Check1=0;
                Double_Check2=0;
                Select_Check0=0;
                Select_Check1=0;
                Select_Check2=0;
            }
            /*---Break Condition---*/
            if(Out_While_0==1 && Out_While_1==1 && Out_While_2==1)
                break;
        }
    }
}

int Check_MotorPE(int MotorNumber0,int MotorNumber1,int MotorNumber2,int MotorNumber3)
{
    int Position0=0,Position1=0,Position2=0,Position3=0;
    int Motor_pos0=0,Motor_pos1=0,Motor_pos2=0,Motor_pos3=0;
    int Select_Check0=0,Select_Check1=0,Select_Check2=0,Select_Check3=0;
    int Double_Check0=0,Double_Check1=0,Double_Check2=0,Double_Check3=0;
    int key0=0,key1=0,key2=0,key3=0;
    int Out_While_0=0,Out_While_1=0,Out_While_2=0,Out_While_3=0;

    /*---Check Repeat---*/
    if(MotorNumber0==MotorNumber1||MotorNumber0==MotorNumber2||MotorNumber0==MotorNumber3||MotorNumber1==MotorNumber2||MotorNumber1==MotorNumber3||MotorNumber3==MotorNumber2)
    {
        printf("*** Use Check_MotorPE(4 Motor) Error : The Same Number ***\n");
        return 0;
    }
    /*---Load Position : First Motor---*/
    if(MotorNumber0==0)         Motor_pos0 = Globle_T0MA_Position;
    else if(MotorNumber0==1)    Motor_pos0 = Globle_T1MA_Position;
    else if(MotorNumber0==2)    Motor_pos0 = Globle_T2MA_Position;
    else if(MotorNumber0==3)    Motor_pos0 = Globle_T3MA_Position;
    /*---Load Position : Second Motor---*/
    if(MotorNumber1==0)         Motor_pos1 = Globle_T0MA_Position;
    else if(MotorNumber1==1)    Motor_pos1 = Globle_T1MA_Position;
    else if(MotorNumber1==2)    Motor_pos1 = Globle_T2MA_Position;
    else if(MotorNumber1==3)    Motor_pos1 = Globle_T3MA_Position;
    /*---Load Position : Third Motor---*/
    if(MotorNumber2==0)         Motor_pos2 = Globle_T0MA_Position;
    else if(MotorNumber2==1)    Motor_pos2 = Globle_T1MA_Position;
    else if(MotorNumber2==2)    Motor_pos2 = Globle_T2MA_Position;
    else if(MotorNumber2==3)    Motor_pos2 = Globle_T3MA_Position;
    /*---Load Position : Third Motor---*/
    if(MotorNumber3==0)         Motor_pos3 = Globle_T0MA_Position;
    else if(MotorNumber3==1)    Motor_pos3 = Globle_T1MA_Position;
    else if(MotorNumber3==2)    Motor_pos3 = Globle_T2MA_Position;
    else if(MotorNumber3==3)    Motor_pos3 = Globle_T3MA_Position;

    /*---Check Position---*/
    while(TRUE)
    {
        /*---Update Motor PE Data---*/
        Position0 = MotorPE(MotorNumber0);
        Position1 = MotorPE(MotorNumber1);
        Position2 = MotorPE(MotorNumber2);
        Position3 = MotorPE(MotorNumber3);
        //printf("Position0=%d\tPosition1=%d\tPosition2=%d\n",Position0,Position1,Position2);

        /*---Select Check---*/
        if(abs(Position0-Motor_pos0) <= 50) Select_Check0=1;
        if(abs(Position1-Motor_pos1) <= 50) Select_Check1=1;
        if(abs(Position2-Motor_pos2) <= 50) Select_Check2=1;
        if(abs(Position3-Motor_pos3) <= 50) Select_Check3=1;

        /*---Double Check Position---*/
        if(Select_Check0==1 || Select_Check1==1 || Select_Check2==1 || Select_Check3==1)
        {
            if(Select_Check0==1 && key0!=1){
                for(int i=0; i<2; i++){
                    Position0 = MotorPE(MotorNumber0);
                    //printf("Position0=%d \n",Position0);
                    if(abs(Position0-Motor_pos0) <= 50) Double_Check0++;
                }
            }
            if(Select_Check1==1 && key1!=1){
                for(int i=0; i<2; i++){
                    Position1 = MotorPE(MotorNumber1);
                    //printf("Position0=%d \n",Position0);
                    if(abs(Position1-Motor_pos1) <= 50) Double_Check1++;
                }
            }
            if(Select_Check2==1 && key2!=1){
                for(int i=0; i<2; i++){
                    Position2 = MotorPE(MotorNumber2);
                    //printf("Position0=%d \n",Position0);
                    if(abs(Position2-Motor_pos2) <= 50) Double_Check2++;
                }
            }
            if(Select_Check3==1 && key3!=1){
                for(int i=0; i<2; i++){
                    Position3 = MotorPE(MotorNumber3);
                    //printf("Position0=%d \n",Position0);
                    if(abs(Position3-Motor_pos3) <= 50) Double_Check3++;
                }
            }

            /*---If Double Check Position OK---*/
            if(Double_Check0==2 && key0!=1){
                printf("Motor%d\tOK\n",MotorNumber0);
                Out_While_0=1;
                key0=1;
            }
            else if(Double_Check1==2 && key1!=1){
                printf("Motor%d\tOK\n",MotorNumber1);
                Out_While_1=1;
                key1=1;
            }
            else if(Double_Check2==2 && key2!=1){
                printf("Motor%d\tOK\n",MotorNumber2);
                Out_While_2=1;
                key2=1;
            }
            else if(Double_Check3==2 && key3!=1){
                printf("Motor%d\tOK\n",MotorNumber2);
                Out_While_3=1;
                key3=1;
            }
            else{
                Double_Check0=0;
                Double_Check1=0;
                Double_Check2=0;
                Double_Check3=0;
                Select_Check0=0;
                Select_Check1=0;
                Select_Check2=0;
                Select_Check3=0;
            }
            /*---Break Condition---*/
            if(Out_While_0==1 && Out_While_1==1 && Out_While_2==1 && Out_While_3==1)
                break;
        }
    }
}


//int Check_Slim_PE(int Number, int *Number_Of_Motor, int *Position_Of_Motor)
//{
//    int Position = Number;
//
//    if(Number != Position || Number > 6 || Position > 6)
//    {
//        printf("Use [Check_Slim_PE] function error.\n");
//        return 0;
//    }
//
//    bool check[6];
//    int p[6] = {-100,-100,-1,-1,-1,-1};
//    int record[6] = {0,0,0,0,0,0};
//
//    for(int i=0;i<6;i++)
//    {
//        if(i < Number)
//            check[i] = 0;
//        else
//            check[i] = 1;
//    }
//
//    printf("Motor\tMotor\n");
//    printf("Number\tPosition\n");
//
//    for(int i=0; i<Number ; i++)
//        printf("%d\t%d\n",Number_Of_Motor[i],Position_Of_Motor[i]);
//
//
//    while(TRUE)
//    {
//        for(int i=0;i < Number;i++)
//        {
//            if(!check[i])
//            {
//                if(!(p[i] <= Position_Of_Motor[i]+10 && p[i] >= Position_Of_Motor[i]-10))
//                {
//                    record[i] = 0;
//                    p[i] = MotorPE(Number_Of_Motor[i]);
//                }
//                else
//                {
//                    record[i]++;
//
//                    if(record[i] == 30)
//                        check[i] = 1;
//                }
//            }
//        }
//
//        printf("%d %d\n", check[0], check[1]/*, check[2], check[3], check[4], check[5]*/);
//
//        if((check[0] && check[1] && check[2] && check[3] && check[4] && check[5]))
//           break;
//    }
//
//    return 1;
//}
