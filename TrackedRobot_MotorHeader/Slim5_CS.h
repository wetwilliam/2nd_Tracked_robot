/*---Set Motor Coordinates---*/


void bodycs(int v1,int v2);	//Set T1,T2 Coordinates
void legcs(int v1,int v2);	//Set T0,T3 Coordinates


void bodycs(int v1,int v2)
{
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T1CS%d\r\n",v1);
    int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    usleep(100000);

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T2CS%d\r\n",v2);
    wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
}

void legcs(int v1,int v2)//reset zero
{
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"CS%d\r\n",v1);
    int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    usleep(100000);

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T3CS%d\r\n",v2);
    wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));

    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
}

