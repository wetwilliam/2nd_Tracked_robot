/*---Motor Pulse Move : Absolute coordinates---*/
int Globle_T1MA_Position=0,Globle_T2MA_Position=0;
int Globle_T0MA_Position=0,Globle_T3MA_Position=0;


void bodyma(int v1,int v2);
void legma(int v1,int v2);


void bodyma(int v1,int v2)
{
    Globle_T1MA_Position=v1;
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"\r\nT1MA%d\r\n",v1);
    int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    //printf("wordsWritten = %d\n",wordsWritten);

    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer dat
    //usleep(50000);
    usleep(100000);

    Globle_T2MA_Position=v2;
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"\r\nT2MA%d\r\n",v2);
    wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    //printf("wordsWritten = %d\n",wordsWritten);

    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data

//    for(int i=0; i < 50; i++)
//    {
//        if(Writtenbuf[i] == '\0')
//        {
//            wordsWritten = write(fd_Slim5, Writtenbuf, i);
//            break;
//        }
//    }

    //printf("wordsWritten = %d\n",wordsWritten);
}

void legma(int v1,int v2)
{
    Globle_T0MA_Position=v1;
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"\r\nMA%d\r\n",v1);
    write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    //int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));

    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer dat
    //usleep(50000);
    usleep(100000);

    Globle_T3MA_Position=v2;
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"\r\nT3MA%d\r\n",v2);
    write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));

    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
}
