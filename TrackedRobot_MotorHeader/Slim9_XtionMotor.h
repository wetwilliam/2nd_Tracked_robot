/*---Slim9 Motor Control (Xtion Motor)---*/


void XtionMotor(int v1,int v2);
void XtionMotor_MR(int v1,int v2);

void XtionMotor(int v1,int v2)
{
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"MA%d\r\n",v1+100);
    int wordsWritten = write(fd_Slim9,Writtenbuf,sizeof(Writtenbuf));

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T1MA%d\r\n",v2);
    wordsWritten = write(fd_Slim9,Writtenbuf,sizeof(Writtenbuf));

    tcflush(fd_Slim9, TCIFLUSH); //Flush Buffer data
}
void XtionMotor_MR(int v1,int v2)
{
    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"MR%d\r\n",v1);
    int wordsWritten = write(fd_Slim9,Writtenbuf,sizeof(Writtenbuf));

    memset(Writtenbuf, '\0', sizeof(Writtenbuf));
    sprintf(Writtenbuf,"T1MR%d\r\n",v2);
    wordsWritten = write(fd_Slim9,Writtenbuf,sizeof(Writtenbuf));

    tcflush(fd_Slim9, TCIFLUSH); //Flush Buffer data
}
