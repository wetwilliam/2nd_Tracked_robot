/*---Motor Pulse Move : Relative coordinates---*/


void bodymr(int v1,int v2);


void bodymr(int v1, int v2)
{
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"\r\nT1MR%d\r\n",v1);
    int wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    //usleep(50000);
    usleep(100000);

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"\r\nT2MR%d\r\n",v2);
    wordsWritten = write(fd_Slim5,Writtenbuf,sizeof(Writtenbuf));
    tcflush(fd_Slim5, TCIFLUSH); //Flush Buffer data
    //usleep(50000);
    //usleep(100000);


}
