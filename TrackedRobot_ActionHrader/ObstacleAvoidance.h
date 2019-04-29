/*---Chang OpenNI Set Resolution---*/

#define OB_row 85
#define OB_col 35
int OB_key=0;

/*---For Count---*/
int Depth_Data_Average(int Input_Data);
int Full_Obstacle(int Data_1,int Data_2,int Data_3,int Data_4,int Data_5,int Data_6,int Data_7,int Data_8,int Data_9,int Data_10);
/*---For Determine---*/
int Avoidance_DataAnalysis_Block_A();
int Avoidance_DataAnalysis_Block_B();
int Avoidance_DataAnalysis_Block_C();

/*---r & spped---*/
void Avoidance_Motor_r_Control(int Status_A,int Status_B,int Status_C,double Last_L_speed,double Last_R_speed,double *d1,double *d2,char *direction);

void Avoidance_speed_Control(char direction,int d1,int d2,double *car_vl,double *car_vr,double *rlim);

/*---For r & motor speed test---*/
void Avoidance_MotorControl(double r_eq,double *car_vl,double *car_vr);

/*---For Count---*/
int Depth_Data_Average(int Input_Data)
{
	int Output=0,Denominator=85;

	Output = (int)(Input_Data / Denominator);

	return Output;
}

int Full_Obstacle(int Data_1,int Data_2,int Data_3,int Data_4,int Data_5,int Data_6,int Data_7,int Data_8,int Data_9,int Data_10)
{
	int Full_Obstacle_Cont=0;
	if(Data_2-Data_1>0) Full_Obstacle_Cont++;
	if(Data_3-Data_2>0) Full_Obstacle_Cont++;
	if(Data_4-Data_3>0) Full_Obstacle_Cont++;
	if(Data_5-Data_4>0) Full_Obstacle_Cont++;
	if(Data_6-Data_5>0) Full_Obstacle_Cont++;
	if(Data_7-Data_6>0) Full_Obstacle_Cont++;
	if(Data_8-Data_7>0) Full_Obstacle_Cont++;
	if(Data_9-Data_8>0) Full_Obstacle_Cont++;
	if(Data_10-Data_9>0) Full_Obstacle_Cont++;
	//Avoid depth Unstable
	if(Data_5-Data_1>0) Full_Obstacle_Cont++; //Data Display : Pixel 5,6,7 are Stable
	if(Data_6-Data_1>0) Full_Obstacle_Cont++;
	if(Data_7-Data_1>0) Full_Obstacle_Cont++;

	return Full_Obstacle_Cont;
}


/*---For Determine---*/
int Avoidance_DataAnalysis_Block_A()
{
	//printf("Avoidance Data Analysis Block_A \n");

	/*---depth Data Variable---*/
	int A_Count[10][3]={};

    /*---Count AD : 1 Amount array---*/
	int AD[OB_row][OB_col]={};

	/*int **AD=NULL;
	AD = new int*[OB_row];
	for(int i=0;i<OB_row;i++)	AD[i]=new int[OB_col];
	for(int i=0;i<OB_row;i++)
	{
        for(int j=0;j<OB_col;j++)	AD[i][j]=0;
	}*/

	//FILE *fp;
    //fp=fopen("/home/ubuntu/CodeBlocks/TR_WallFurring/OBdata/obdata.txt","a");
	/*if(fp==NULL){
		printf("Not find .txt !\n");
	}
	else{
		printf("Open .txt Success !\n");
	}*/

	streamDepth.readFrame( &frameDepth );

	/*---depth Data total---*/
	//A1 depth Data
	for(int i=10 ; i< 95 ; i++){
		A_Count[1][1]+=depthMD(i,82);
		A_Count[2][1]+=depthMD(i,84);
		A_Count[3][1]+=depthMD(i,86);
		A_Count[4][1]+=depthMD(i,88);
		A_Count[5][1]+=depthMD(i,90);
		A_Count[6][1]+=depthMD(i,92);
		A_Count[7][1]+=depthMD(i,94);
		A_Count[8][1]+=depthMD(i,96);
		A_Count[9][1]+=depthMD(i,98);
		A_Count[10][1]+=depthMD(i,100);
	}
	//A2 depth Data
	for(int i=95 ; i< 180 ; i++){
		A_Count[1][2]+=depthMD(i,82);
		A_Count[2][2]+=depthMD(i,84);
		A_Count[3][2]+=depthMD(i,86);
		A_Count[4][2]+=depthMD(i,88);
		A_Count[5][2]+=depthMD(i,90);
		A_Count[6][2]+=depthMD(i,92);
		A_Count[7][2]+=depthMD(i,94);
		A_Count[8][2]+=depthMD(i,96);
		A_Count[9][2]+=depthMD(i,98);
		A_Count[10][2]+=depthMD(i,100);
	}
	//A3 depth Data
	for(int i=180 ; i< 265 ; i++){
		A_Count[1][3]+=depthMD(i,82);
		A_Count[2][3]+=depthMD(i,84);
		A_Count[3][3]+=depthMD(i,86);
		A_Count[4][3]+=depthMD(i,88);
		A_Count[5][3]+=depthMD(i,90);
		A_Count[6][3]+=depthMD(i,92);
		A_Count[7][3]+=depthMD(i,94);
		A_Count[8][3]+=depthMD(i,96);
		A_Count[9][3]+=depthMD(i,98);
		A_Count[10][3]+=depthMD(i,100);
	}

	/*---depth Data Average---*/
	//A depth Data Average
	int a_black_count=0;
	for(int i=1; i<11; i++)
	{
        A_Count[i][1]=Depth_Data_Average(A_Count[i][1]);
        A_Count[i][2]=Depth_Data_Average(A_Count[i][2]);
        A_Count[i][3]=Depth_Data_Average(A_Count[i][3]);

         /*---Black area---*/
        if(A_Count[i][1] < 10 || A_Count[i][2] <10 || A_Count[i][3] < 10)
        {
            a_black_count++ ;

            if(a_black_count > 5) return 7;

        }
	}



	/*---First Condition count : FULL Obstacle---*/
	int A1FirstCount=0,A2FirstCount=0,A3FirstCount=0;

    if(A1FirstCount>=5 && A2FirstCount>=5 && A3FirstCount>=5 )
    {
        printf("A Block Full OB\n");
    }
	/*---Second Condition count : SMALL Obstacle---*/
	int A1_AD_Amount=0,A2_AD_Amount=0,A3_AD_Amount=0;

	if(A1FirstCount<5 && A2FirstCount<5 && A3FirstCount<5 )
	{
		/*---All Use---*/
		int AD_X=0;
		int print_int0=0,print_int1=0,print_int2=0,print_int3=0,print_int4=0,print_int5=0,print_int6=0,print_int7=0,print_int8=0,print_int9=0;
		int A1_Small_Obstacle_Condition_2=400; //400
		/*------------*/
		int A1_Small_Obstacle_Condition=30;
		for(int i=10; i<95; i++)
		{
			print_int0 = abs(A_Count[1][1]-depthMD(i,82));
			print_int1 = abs(A_Count[2][1]-depthMD(i,84));
			print_int2 = abs(A_Count[3][1]-depthMD(i,86));
			print_int3 = abs(A_Count[4][1]-depthMD(i,88));
			print_int4 = abs(A_Count[5][1]-depthMD(i,90));
			print_int5 = abs(A_Count[6][1]-depthMD(i,92));
			print_int6 = abs(A_Count[7][1]-depthMD(i,94));
			print_int7 = abs(A_Count[8][1]-depthMD(i,96));
			print_int8 = abs(A_Count[9][1]-depthMD(i,98));
			print_int9 = abs(A_Count[10][1]-depthMD(i,100));

            if(print_int0>A1_Small_Obstacle_Condition && print_int0<A1_Small_Obstacle_Condition_2) AD[AD_X][0]=1;
            if(print_int1>A1_Small_Obstacle_Condition && print_int1<A1_Small_Obstacle_Condition_2) AD[AD_X][1]=1;
            if(print_int2>A1_Small_Obstacle_Condition && print_int2<A1_Small_Obstacle_Condition_2) AD[AD_X][2]=1;
            if(print_int3>A1_Small_Obstacle_Condition && print_int3<A1_Small_Obstacle_Condition_2) AD[AD_X][3]=1;
            if(print_int4>A1_Small_Obstacle_Condition && print_int4<A1_Small_Obstacle_Condition_2) AD[AD_X][4]=1;
            if(print_int5>A1_Small_Obstacle_Condition && print_int5<A1_Small_Obstacle_Condition_2) AD[AD_X][5]=1;
            if(print_int6>A1_Small_Obstacle_Condition && print_int6<A1_Small_Obstacle_Condition_2) AD[AD_X][6]=1;
            if(print_int7>A1_Small_Obstacle_Condition && print_int7<A1_Small_Obstacle_Condition_2) AD[AD_X][7]=1;
            if(print_int8>A1_Small_Obstacle_Condition && print_int8<A1_Small_Obstacle_Condition_2) AD[AD_X][8]=1;
            if(print_int9>A1_Small_Obstacle_Condition && print_int9<A1_Small_Obstacle_Condition_2) AD[AD_X][9]=1;

            AD_X++;

//			if(abs(A_Count[1][1]-depthMD(i,82)) > A1_Small_Obstacle_Condition)	AD[AD_X][0]=1;
//			if(abs(A_Count[2][1]-depthMD(i,84)) > A1_Small_Obstacle_Condition)	AD[AD_X][1]=1;
//			if(abs(A_Count[3][1]-depthMD(i,86)) > A1_Small_Obstacle_Condition)	AD[AD_X][2]=1;
//			if(abs(A_Count[4][1]-depthMD(i,88)) > A1_Small_Obstacle_Condition)	AD[AD_X][3]=1;
//			if(abs(A_Count[5][1]-depthMD(i,90)) > A1_Small_Obstacle_Condition)	AD[AD_X][4]=1;
//			if(abs(A_Count[6][1]-depthMD(i,92)) > A1_Small_Obstacle_Condition)	AD[AD_X][5]=1;
//			if(abs(A_Count[7][1]-depthMD(i,94)) > A1_Small_Obstacle_Condition)	AD[AD_X][6]=1;
//			if(abs(A_Count[8][1]-depthMD(i,96)) > A1_Small_Obstacle_Condition)	AD[AD_X][7]=1;
//			if(abs(A_Count[9][1]-depthMD(i,98)) > A1_Small_Obstacle_Condition)	AD[AD_X][8]=1;
//			if(abs(A_Count[10][1]-depthMD(i,100)) > A1_Small_Obstacle_Condition)	AD[AD_X][9]=1;
//
//			AD_X++;
		}

		AD_X=0;
		int A2_Small_Obstacle_Condition=30;
		for(int i=95; i<180; i++)
		{
			print_int0 = abs(A_Count[1][2]-depthMD(i,82));
			print_int1 = abs(A_Count[2][2]-depthMD(i,84));
			print_int2 = abs(A_Count[3][2]-depthMD(i,86));
			print_int3 = abs(A_Count[4][2]-depthMD(i,88));
			print_int4 = abs(A_Count[5][2]-depthMD(i,90));
			print_int5 = abs(A_Count[6][2]-depthMD(i,92));
			print_int6 = abs(A_Count[7][2]-depthMD(i,94));
			print_int7 = abs(A_Count[8][2]-depthMD(i,96));
			print_int8 = abs(A_Count[9][2]-depthMD(i,98));
			print_int9 = abs(A_Count[10][2]-depthMD(i,100));

            if(print_int0>A2_Small_Obstacle_Condition && print_int0<A1_Small_Obstacle_Condition_2) AD[AD_X][10]=1;
            if(print_int1>A2_Small_Obstacle_Condition && print_int1<A1_Small_Obstacle_Condition_2) AD[AD_X][11]=1;
            if(print_int2>A2_Small_Obstacle_Condition && print_int2<A1_Small_Obstacle_Condition_2) AD[AD_X][12]=1;
            if(print_int3>A2_Small_Obstacle_Condition && print_int3<A1_Small_Obstacle_Condition_2) AD[AD_X][13]=1;
            if(print_int4>A2_Small_Obstacle_Condition && print_int4<A1_Small_Obstacle_Condition_2) AD[AD_X][14]=1;
            if(print_int5>A2_Small_Obstacle_Condition && print_int5<A1_Small_Obstacle_Condition_2) AD[AD_X][15]=1;
            if(print_int6>A2_Small_Obstacle_Condition && print_int6<A1_Small_Obstacle_Condition_2) AD[AD_X][16]=1;
            if(print_int7>A2_Small_Obstacle_Condition && print_int7<A1_Small_Obstacle_Condition_2) AD[AD_X][17]=1;
            if(print_int8>A2_Small_Obstacle_Condition && print_int8<A1_Small_Obstacle_Condition_2) AD[AD_X][18]=1;
            if(print_int9>A2_Small_Obstacle_Condition && print_int9<A1_Small_Obstacle_Condition_2) AD[AD_X][19]=1;

            AD_X++;

//			if(abs(A_Count[1][2]-depthMD(i,82)) > A2_Small_Obstacle_Condition)	AD[AD_X][10]=1;
//			if(abs(A_Count[2][2]-depthMD(i,84)) > A2_Small_Obstacle_Condition)	AD[AD_X][11]=1;
//			if(abs(A_Count[3][2]-depthMD(i,86)) > A2_Small_Obstacle_Condition)	AD[AD_X][12]=1;
//			if(abs(A_Count[4][2]-depthMD(i,88)) > A2_Small_Obstacle_Condition)	AD[AD_X][13]=1;
//			if(abs(A_Count[5][2]-depthMD(i,90)) > A2_Small_Obstacle_Condition)	AD[AD_X][14]=1;
//			if(abs(A_Count[6][2]-depthMD(i,92)) > A2_Small_Obstacle_Condition)	AD[AD_X][15]=1;
//			if(abs(A_Count[7][2]-depthMD(i,94)) > A2_Small_Obstacle_Condition)	AD[AD_X][16]=1;
//			if(abs(A_Count[8][2]-depthMD(i,96)) > A2_Small_Obstacle_Condition)	AD[AD_X][17]=1;
//			if(abs(A_Count[9][2]-depthMD(i,98)) > A2_Small_Obstacle_Condition)	AD[AD_X][18]=1;
//			if(abs(A_Count[10][2]-depthMD(i,100)) > A2_Small_Obstacle_Condition)	AD[AD_X][19]=1;
//
//			AD_X++;
		}

		AD_X=0;
		int A3_Small_Obstacle_Condition=30;
		for(int i=180; i<265; i++)
		{
			print_int0 = abs(A_Count[1][3]-depthMD(i,82));
			print_int1 = abs(A_Count[2][3]-depthMD(i,84));
			print_int2 = abs(A_Count[3][3]-depthMD(i,86));
			print_int3 = abs(A_Count[4][3]-depthMD(i,88));
			print_int4 = abs(A_Count[5][3]-depthMD(i,90));
			print_int5 = abs(A_Count[6][3]-depthMD(i,92));
			print_int6 = abs(A_Count[7][3]-depthMD(i,94));
			print_int7 = abs(A_Count[8][3]-depthMD(i,96));
			print_int8 = abs(A_Count[9][3]-depthMD(i,98));
			print_int9 = abs(A_Count[10][3]-depthMD(i,100));

            if(print_int0>A3_Small_Obstacle_Condition && print_int0<A1_Small_Obstacle_Condition_2) AD[AD_X][20]=1;
            if(print_int1>A3_Small_Obstacle_Condition && print_int1<A1_Small_Obstacle_Condition_2) AD[AD_X][21]=1;
            if(print_int2>A3_Small_Obstacle_Condition && print_int2<A1_Small_Obstacle_Condition_2) AD[AD_X][22]=1;
            if(print_int3>A3_Small_Obstacle_Condition && print_int3<A1_Small_Obstacle_Condition_2) AD[AD_X][23]=1;
            if(print_int4>A3_Small_Obstacle_Condition && print_int4<A1_Small_Obstacle_Condition_2) AD[AD_X][24]=1;
            if(print_int5>A3_Small_Obstacle_Condition && print_int5<A1_Small_Obstacle_Condition_2) AD[AD_X][25]=1;
            if(print_int6>A3_Small_Obstacle_Condition && print_int6<A1_Small_Obstacle_Condition_2) AD[AD_X][26]=1;
            if(print_int7>A3_Small_Obstacle_Condition && print_int7<A1_Small_Obstacle_Condition_2) AD[AD_X][27]=1;
            if(print_int8>A3_Small_Obstacle_Condition && print_int8<A1_Small_Obstacle_Condition_2) AD[AD_X][28]=1;
            if(print_int9>A3_Small_Obstacle_Condition && print_int9<A1_Small_Obstacle_Condition_2) AD[AD_X][29]=1;

            AD_X++;

//			if(abs(A_Count[1][3]-depthMD(i,82)) > A3_Small_Obstacle_Condition)	AD[AD_X][20]=1;
//			if(abs(A_Count[2][3]-depthMD(i,84)) > A3_Small_Obstacle_Condition)	AD[AD_X][21]=1;
//			if(abs(A_Count[3][3]-depthMD(i,86)) > A3_Small_Obstacle_Condition)	AD[AD_X][22]=1;
//			if(abs(A_Count[4][3]-depthMD(i,88)) > A3_Small_Obstacle_Condition)	AD[AD_X][23]=1;
//			if(abs(A_Count[5][3]-depthMD(i,90)) > A3_Small_Obstacle_Condition)	AD[AD_X][24]=1;
//			if(abs(A_Count[6][3]-depthMD(i,92)) > A3_Small_Obstacle_Condition)	AD[AD_X][25]=1;
//			if(abs(A_Count[7][3]-depthMD(i,94)) > A3_Small_Obstacle_Condition)	AD[AD_X][26]=1;
//			if(abs(A_Count[8][3]-depthMD(i,96)) > A3_Small_Obstacle_Condition)	AD[AD_X][27]=1;
//			if(abs(A_Count[9][3]-depthMD(i,98)) > A3_Small_Obstacle_Condition)	AD[AD_X][28]=1;
//			if(abs(A_Count[10][3]-depthMD(i,100)) > A3_Small_Obstacle_Condition)	AD[AD_X][29]=1;
//
//			AD_X++;
		}

		/*---Count AD : 1 Amount---*/
		//A1 Count AD
		for(int i=0; i<10 ;i++)
		{
			for(int j=0; j<85; j++){

				if(AD[j][i]==1)	A1_AD_Amount++;
			}
		}

		//A2 Count AD
		for(int i=10; i<20 ;i++)
		{
			for(int j=0; j<85; j++){

				if(AD[j][i]==1)	A2_AD_Amount++;
			}
		}

		//A3 Count AD
		for(int i=20; i<30 ;i++)
		{
			for(int j=0; j<85; j++){

				if(AD[j][i]==1)	A3_AD_Amount++;
			}
		}

	   /*printf("A1 1 amount: %d \n",A1_AD_Amount);
		printf("A2 1 amount: %d \n",A2_AD_Amount);
		printf("A3 1 amount: %d \n",A3_AD_Amount);*/

		/*---fprintf AD array---*/
		/*fprintf(fp,"Block A1\n");
		int a=0;
		for(int i=0; i<10; i++){
			for(int j=0; j<85; j++){
				fprintf(fp,"%d  ",AD[j][i]);
				a++;
				if(a>84){
					fprintf(fp,"\n");
					a=0;
				}
			}
		}
		fprintf(fp,"\n");

		fprintf(fp,"Block A2\n");
		a=0;
		for(int i=10; i<20; i++){
			for(int j=0; j<85; j++){
				fprintf(fp,"%d  ",AD[j][i]);
				a++;
				if(a>84){
					fprintf(fp,"\n");
					a=0;
				}
			}
		}
		fprintf(fp,"\n");

		fprintf(fp,"Block A3\n");
		a=0;
		for(int i=20; i<30; i++){
			for(int j=0; j<85; j++){
				fprintf(fp,"%d  ",AD[j][i]);
				a++;
				if(a>84){
					fprintf(fp,"\n");
					a=0;
				}
			}
		}
		fprintf(fp,"\n");*/
	}


	/*---Return Obstacle position---*/
	if((A1FirstCount>=5 && A3FirstCount>=5) || (A1FirstCount>=5 && A2FirstCount>=5 && A3FirstCount>=5) || (A1_AD_Amount>50 && A3_AD_Amount>50) || (A1_AD_Amount>50 && A2_AD_Amount>50 && A3_AD_Amount>50))
	{
		return 1;//Obstacle in A1.A2.A3
	}
	else if((A1FirstCount>=5 && A2FirstCount>=5) || (A1_AD_Amount>50 && A2_AD_Amount>50))
	{
		return 2;//Obstacle in A2.A3
	}
	else if((A2FirstCount>=5 && A3FirstCount>=5) || (A2_AD_Amount>50 && A3_AD_Amount>50))
	{
		return 3;//Obstacle in A1.A2
	}
	else if(A1FirstCount>=5 || A1_AD_Amount>50) //50
	{
		return 4;//Obstacle in A3
	}
	else if(A2FirstCount>=5 || A2_AD_Amount>50)
	{
		return 5;//Obstacle in A2
	}
	else if(A3FirstCount>=5 || A3_AD_Amount>50)
	{
		return 6;//Obstacle in A1
	}

	/*for(int i=0;i<OB_row;i++)delete AD[i];
	delete AD;*/

	//fclose(fp);

    //printf("obdata close \n");

    return 0;
}

int Avoidance_DataAnalysis_Block_B()
{
	//printf("Avoidance Data Analysis Block_B \n");

	/*---depth Data Variable---*/
	int B_Count[10][3]={};

    /*---Count AD : 1 Amount array---*/
	int AD[OB_row][OB_col]={};


	/*int **AD=NULL;
	AD = new int*[OB_row];
	for(int i=0;i<OB_row;i++)	AD[i]=new int[OB_col];
	for(int i=0;i<OB_row;i++)
	{
        for(int j=0;j<OB_col;j++)	AD[i][j]=0;
	}*/

	//FILE *fp;
    //fp=fopen("/home/ubuntu/CodeBlocks/TR_WallFurring/OBdata/obdata.txt","a");
	/*if(fp==NULL){
		printf("Not find .txt !\n");
	}
	else{
		printf("Open .txt Success !\n");
	}*/

	streamDepth.readFrame( &frameDepth );

	/*---depth Data total---*/
	//B1 depth Data
	for(int i=10 ; i< 95 ; i++){
		B_Count[1][1]+=depthMD(i,102);
		B_Count[2][1]+=depthMD(i,104);
		B_Count[3][1]+=depthMD(i,106);
		B_Count[4][1]+=depthMD(i,108);
		B_Count[5][1]+=depthMD(i,110);
		B_Count[6][1]+=depthMD(i,112);
		B_Count[7][1]+=depthMD(i,114);
		B_Count[8][1]+=depthMD(i,116);
		B_Count[9][1]+=depthMD(i,118);
		B_Count[10][1]+=depthMD(i,120);
	}
	//B2 depth Data
	for(int i=95 ; i< 180 ; i++){
		B_Count[1][2]+=depthMD(i,102);
		B_Count[2][2]+=depthMD(i,104);
		B_Count[3][2]+=depthMD(i,106);
		B_Count[4][2]+=depthMD(i,108);
		B_Count[5][2]+=depthMD(i,110);
		B_Count[6][2]+=depthMD(i,112);
		B_Count[7][2]+=depthMD(i,114);
		B_Count[8][2]+=depthMD(i,116);
		B_Count[9][2]+=depthMD(i,118);
		B_Count[10][2]+=depthMD(i,120);
	}
	//B3 depth Data
	for(int i=180 ; i< 265 ; i++){
		B_Count[1][3]+=depthMD(i,102);
		B_Count[2][3]+=depthMD(i,104);
		B_Count[3][3]+=depthMD(i,106);
		B_Count[4][3]+=depthMD(i,108);
		B_Count[5][3]+=depthMD(i,110);
		B_Count[6][3]+=depthMD(i,112);
		B_Count[7][3]+=depthMD(i,114);
		B_Count[8][3]+=depthMD(i,116);
		B_Count[9][3]+=depthMD(i,118);
		B_Count[10][3]+=depthMD(i,120);
	}

	/*---depth Data Average---*/
	//B depth Data Average
	int b_black_count=0;
	for(int i=1; i<11; i++)
	{
        B_Count[i][1]=Depth_Data_Average(B_Count[i][1]);
        B_Count[i][2]=Depth_Data_Average(B_Count[i][2]);
        B_Count[i][3]=Depth_Data_Average(B_Count[i][3]);

         /*---Black area---*/
        if(B_Count[i][1] < 10 || B_Count[i][2] <10 || B_Count[i][3] < 10)
        {
            b_black_count++ ;

            if(b_black_count > 5) return 7;

        }

	}


	/*---First Condition count : FULL Obstacle---*/
	int B1FirstCount=0,B2FirstCount=0,B3FirstCount=0;

    if(B1FirstCount>=5 && B2FirstCount>=5 && B3FirstCount>=5 )
    {
        printf("B Block Full OB\n");
    }

	/*---Second Condition count : SMALL Obstacle---*/
	int B1_AD_Amount=0,B2_AD_Amount=0,B3_AD_Amount=0;

	if(B1FirstCount<5 && B2FirstCount<5 && B3FirstCount<5 )
	{
		/*---All Use---*/
		int AD_X=0;
		int print_int0=0,print_int1=0,print_int2=0,print_int3=0,print_int4=0,print_int5=0,print_int6=0,print_int7=0,print_int8=0,print_int9=0;
		int B1_Small_Obstacle_Condition_2=400;
		/*------------*/
		int B1_Small_Obstacle_Condition=35; //org:25
		for(int i=10; i<95; i++)
		{
			print_int0 = abs(B_Count[1][1]-depthMD(i,102));
			print_int1 = abs(B_Count[2][1]-depthMD(i,104));
			print_int2 = abs(B_Count[3][1]-depthMD(i,106));
			print_int3 = abs(B_Count[4][1]-depthMD(i,108));
			print_int4 = abs(B_Count[5][1]-depthMD(i,110));
			print_int5 = abs(B_Count[6][1]-depthMD(i,112));
			print_int6 = abs(B_Count[7][1]-depthMD(i,114));
			print_int7 = abs(B_Count[8][1]-depthMD(i,116));
			print_int8 = abs(B_Count[9][1]-depthMD(i,118));
			print_int9 = abs(B_Count[10][1]-depthMD(i,120));

            if(print_int0>B1_Small_Obstacle_Condition && print_int0<B1_Small_Obstacle_Condition_2) AD[AD_X][0]=1;
            if(print_int1>B1_Small_Obstacle_Condition && print_int1<B1_Small_Obstacle_Condition_2) AD[AD_X][1]=1;
            if(print_int2>B1_Small_Obstacle_Condition && print_int2<B1_Small_Obstacle_Condition_2) AD[AD_X][2]=1;
            if(print_int3>B1_Small_Obstacle_Condition && print_int3<B1_Small_Obstacle_Condition_2) AD[AD_X][3]=1;
            if(print_int4>B1_Small_Obstacle_Condition && print_int4<B1_Small_Obstacle_Condition_2) AD[AD_X][4]=1;
            if(print_int5>B1_Small_Obstacle_Condition && print_int5<B1_Small_Obstacle_Condition_2) AD[AD_X][5]=1;
            if(print_int6>B1_Small_Obstacle_Condition && print_int6<B1_Small_Obstacle_Condition_2) AD[AD_X][6]=1;
            if(print_int7>B1_Small_Obstacle_Condition && print_int7<B1_Small_Obstacle_Condition_2) AD[AD_X][7]=1;
            if(print_int8>B1_Small_Obstacle_Condition && print_int8<B1_Small_Obstacle_Condition_2) AD[AD_X][8]=1;
            if(print_int9>B1_Small_Obstacle_Condition && print_int9<B1_Small_Obstacle_Condition_2) AD[AD_X][9]=1;

            AD_X++;

//			if(abs(B_Count[1][1]-depthMD(i,102)) > B1_Small_Obstacle_Condition)	AD[AD_X][0]=1;
//			if(abs(B_Count[2][1]-depthMD(i,104)) > B1_Small_Obstacle_Condition)	AD[AD_X][1]=1;
//			if(abs(B_Count[3][1]-depthMD(i,106)) > B1_Small_Obstacle_Condition)	AD[AD_X][2]=1;
//			if(abs(B_Count[4][1]-depthMD(i,108)) > B1_Small_Obstacle_Condition)	AD[AD_X][3]=1;
//			if(abs(B_Count[5][1]-depthMD(i,110)) > B1_Small_Obstacle_Condition)	AD[AD_X][4]=1;
//			if(abs(B_Count[6][1]-depthMD(i,112)) > B1_Small_Obstacle_Condition)	AD[AD_X][5]=1;
//			if(abs(B_Count[7][1]-depthMD(i,114)) > B1_Small_Obstacle_Condition)	AD[AD_X][6]=1;
//			if(abs(B_Count[8][1]-depthMD(i,116)) > B1_Small_Obstacle_Condition)	AD[AD_X][7]=1;
//			if(abs(B_Count[9][1]-depthMD(i,118)) > B1_Small_Obstacle_Condition)	AD[AD_X][8]=1;
//			if(abs(B_Count[10][1]-depthMD(i,120)) > B1_Small_Obstacle_Condition)	AD[AD_X][9]=1;
//
//			AD_X++;
		}

		AD_X=0;
		int B2_Small_Obstacle_Condition=35; //org:25
		for(int i=95; i<180; i++)
		{
			print_int0 = abs(B_Count[1][2]-depthMD(i,102));
			print_int1 = abs(B_Count[2][2]-depthMD(i,104));
			print_int2 = abs(B_Count[3][2]-depthMD(i,106));
			print_int3 = abs(B_Count[4][2]-depthMD(i,108));
			print_int4 = abs(B_Count[5][2]-depthMD(i,110));
			print_int5 = abs(B_Count[6][2]-depthMD(i,112));
			print_int6 = abs(B_Count[7][2]-depthMD(i,114));
			print_int7 = abs(B_Count[8][2]-depthMD(i,116));
			print_int8 = abs(B_Count[9][2]-depthMD(i,118));
			print_int9 = abs(B_Count[10][2]-depthMD(i,120));

            if(print_int0>B2_Small_Obstacle_Condition && print_int0<B1_Small_Obstacle_Condition_2) AD[AD_X][10]=1;
            if(print_int1>B2_Small_Obstacle_Condition && print_int1<B1_Small_Obstacle_Condition_2) AD[AD_X][11]=1;
            if(print_int2>B2_Small_Obstacle_Condition && print_int2<B1_Small_Obstacle_Condition_2) AD[AD_X][12]=1;
            if(print_int3>B2_Small_Obstacle_Condition && print_int3<B1_Small_Obstacle_Condition_2) AD[AD_X][13]=1;
            if(print_int4>B2_Small_Obstacle_Condition && print_int4<B1_Small_Obstacle_Condition_2) AD[AD_X][14]=1;
            if(print_int5>B2_Small_Obstacle_Condition && print_int5<B1_Small_Obstacle_Condition_2) AD[AD_X][15]=1;
            if(print_int6>B2_Small_Obstacle_Condition && print_int6<B1_Small_Obstacle_Condition_2) AD[AD_X][16]=1;
            if(print_int7>B2_Small_Obstacle_Condition && print_int7<B1_Small_Obstacle_Condition_2) AD[AD_X][17]=1;
            if(print_int8>B2_Small_Obstacle_Condition && print_int8<B1_Small_Obstacle_Condition_2) AD[AD_X][18]=1;
            if(print_int9>B2_Small_Obstacle_Condition && print_int9<B1_Small_Obstacle_Condition_2) AD[AD_X][19]=1;

            AD_X++;

//			if(abs(B_Count[1][2]-depthMD(i,102)) > B2_Small_Obstacle_Condition)	AD[AD_X][10]=1;
//			if(abs(B_Count[2][2]-depthMD(i,104)) > B2_Small_Obstacle_Condition)	AD[AD_X][11]=1;
//			if(abs(B_Count[3][2]-depthMD(i,106)) > B2_Small_Obstacle_Condition)	AD[AD_X][12]=1;
//			if(abs(B_Count[4][2]-depthMD(i,108)) > B2_Small_Obstacle_Condition)	AD[AD_X][13]=1;
//			if(abs(B_Count[5][2]-depthMD(i,110)) > B2_Small_Obstacle_Condition)	AD[AD_X][14]=1;
//			if(abs(B_Count[6][2]-depthMD(i,112)) > B2_Small_Obstacle_Condition)	AD[AD_X][15]=1;
//			if(abs(B_Count[7][2]-depthMD(i,114)) > B2_Small_Obstacle_Condition)	AD[AD_X][16]=1;
//			if(abs(B_Count[8][2]-depthMD(i,116)) > B2_Small_Obstacle_Condition)	AD[AD_X][17]=1;
//			if(abs(B_Count[9][2]-depthMD(i,118)) > B2_Small_Obstacle_Condition)	AD[AD_X][18]=1;
//			if(abs(B_Count[10][2]-depthMD(i,120)) > B2_Small_Obstacle_Condition)	AD[AD_X][19]=1;
//
//			AD_X++;
		}

		AD_X=0;
		int B3_Small_Obstacle_Condition=35; //org:25
		for(int i=180; i<265; i++)
		{
			print_int0 = abs(B_Count[1][3]-depthMD(i,102));
			print_int1 = abs(B_Count[2][3]-depthMD(i,104));
			print_int2 = abs(B_Count[3][3]-depthMD(i,106));
			print_int3 = abs(B_Count[4][3]-depthMD(i,108));
			print_int4 = abs(B_Count[5][3]-depthMD(i,110));
			print_int5 = abs(B_Count[6][3]-depthMD(i,112));
			print_int6 = abs(B_Count[7][3]-depthMD(i,114));
			print_int7 = abs(B_Count[8][3]-depthMD(i,116));
			print_int8 = abs(B_Count[9][3]-depthMD(i,118));
			print_int9 = abs(B_Count[10][3]-depthMD(i,120));

            if(print_int0>B3_Small_Obstacle_Condition && print_int0<B1_Small_Obstacle_Condition_2) AD[AD_X][20]=1;
            if(print_int1>B3_Small_Obstacle_Condition && print_int1<B1_Small_Obstacle_Condition_2) AD[AD_X][21]=1;
            if(print_int2>B3_Small_Obstacle_Condition && print_int2<B1_Small_Obstacle_Condition_2) AD[AD_X][22]=1;
            if(print_int3>B3_Small_Obstacle_Condition && print_int3<B1_Small_Obstacle_Condition_2) AD[AD_X][23]=1;
            if(print_int4>B3_Small_Obstacle_Condition && print_int4<B1_Small_Obstacle_Condition_2) AD[AD_X][24]=1;
            if(print_int5>B3_Small_Obstacle_Condition && print_int5<B1_Small_Obstacle_Condition_2) AD[AD_X][25]=1;
            if(print_int6>B3_Small_Obstacle_Condition && print_int6<B1_Small_Obstacle_Condition_2) AD[AD_X][26]=1;
            if(print_int7>B3_Small_Obstacle_Condition && print_int7<B1_Small_Obstacle_Condition_2) AD[AD_X][27]=1;
            if(print_int8>B3_Small_Obstacle_Condition && print_int8<B1_Small_Obstacle_Condition_2) AD[AD_X][28]=1;
            if(print_int9>B3_Small_Obstacle_Condition && print_int9<B1_Small_Obstacle_Condition_2) AD[AD_X][29]=1;

            AD_X++;
//			if(abs(B_Count[1][3]-depthMD(i,102)) > B3_Small_Obstacle_Condition)	AD[AD_X][20]=1;
//			if(abs(B_Count[2][3]-depthMD(i,104)) > B3_Small_Obstacle_Condition)	AD[AD_X][21]=1;
//			if(abs(B_Count[3][3]-depthMD(i,106)) > B3_Small_Obstacle_Condition)	AD[AD_X][22]=1;
//			if(abs(B_Count[4][3]-depthMD(i,108)) > B3_Small_Obstacle_Condition)	AD[AD_X][23]=1;
//			if(abs(B_Count[5][3]-depthMD(i,110)) > B3_Small_Obstacle_Condition)	AD[AD_X][24]=1;
//			if(abs(B_Count[6][3]-depthMD(i,112)) > B3_Small_Obstacle_Condition)	AD[AD_X][25]=1;
//			if(abs(B_Count[7][3]-depthMD(i,114)) > B3_Small_Obstacle_Condition)	AD[AD_X][26]=1;
//			if(abs(B_Count[8][3]-depthMD(i,116)) > B3_Small_Obstacle_Condition)	AD[AD_X][27]=1;
//			if(abs(B_Count[9][3]-depthMD(i,118)) > B3_Small_Obstacle_Condition)	AD[AD_X][28]=1;
//			if(abs(B_Count[10][3]-depthMD(i,120)) > B3_Small_Obstacle_Condition)	AD[AD_X][29]=1;
//
//			AD_X++;
		}

		/*---Count AD : 1 Amount---*/
		//B1 Count AD
		for(int i=0; i<10 ;i++)
		{
			for(int j=0; j<85; j++){

				if(AD[j][i]==1)	B1_AD_Amount++;
			}
		}

		//B2 Count AD
		for(int i=10; i<20 ;i++)
		{
			for(int j=0; j<85; j++){

				if(AD[j][i]==1)	B2_AD_Amount++;
			}
		}

		//B3 Count AD
		for(int i=20; i<30 ;i++)
		{
			for(int j=0; j<85; j++){

				if(AD[j][i]==1)	B3_AD_Amount++;
			}
		}

		/*printf("B1 1 amount: %d\n",B1_AD_Amount);
		printf("B2 1 amount: %d\n",B2_AD_Amount);
		printf("B3 1 amount: %d\n",B3_AD_Amount);*/

		//fprintf AD array
		/*fprintf(fp,"Block B1\n");
		int b=0;
		for(int i=0; i<10; i++){
			for(int j=0; j<85; j++){
				fprintf(fp,"%d  ",AD[j][i]);
				b++;
				if(b>84){
					fprintf(fp,"\n");
					b=0;
				}
			}
		}
		fprintf(fp,"\n");

		fprintf(fp,"Block B2\n");
		b=0;
		for(int i=10; i<20; i++){
			for(int j=0; j<85; j++){
				fprintf(fp,"%d  ",AD[j][i]);
				b++;
				if(b>84){
					fprintf(fp,"\n");
					b=0;
				}
			}
		}
		fprintf(fp,"\n");

		fprintf(fp,"Block B3\n");
		b=0;
		for(int i=20; i<30; i++){
			for(int j=0; j<85; j++){
				fprintf(fp,"%d  ",AD[j][i]);
				b++;
				if(b>84){
					fprintf(fp,"\n");
					b=0;
				}
			}
		}
		fprintf(fp,"\n");*/
	}


	/*---Return Obstacle position---*/
	if((B1FirstCount>=5 && B3FirstCount>=5) || (B1FirstCount>=5 && B2FirstCount>=5 && B3FirstCount>=5) || (B1_AD_Amount>50 && B3_AD_Amount>50) || (B1_AD_Amount>50 && B2_AD_Amount>50 && B3_AD_Amount>50))
	{
		return 1;//Obstacle in B1.B2.B3
	}
	else if((B1FirstCount>=5 && B2FirstCount>=5) || (B1_AD_Amount>50 && B2_AD_Amount>50))
	{
		return 2;//Obstacle in B2.B3
	}
	else if((B2FirstCount>=5 && B3FirstCount>=5) || (B2_AD_Amount>50 && B3_AD_Amount>50))
	{
		return 3;//Obstacle in B1.B2
	}
	else if(B1FirstCount>=5 || B1_AD_Amount>50)
	{
		return 4;//Obstacle in B3
	}
	else if(B2FirstCount>=5 || B2_AD_Amount>50)
	{
		return 5;//Obstacle in B2
	}
	else if(B3FirstCount>=5 || B3_AD_Amount>50)
	{
		return 6;//Obstacle in B1
	}


	/*for(int i=0;i<OB_row;i++)delete AD[i];
	delete AD;*/

	//fclose(fp);

    //printf("obdata close \n");

    return 0;

}

int Avoidance_DataAnalysis_Block_C()
{
	//printf("Avoidance Data Analysis Block_C \n");

    /*---depth Data Variable---*/
	int C_Count[10][3]={};

    /*---Count AD : 1 Amount array---*/
	int AD[OB_row][OB_col]={};

//    int CD_AD=0;
//    for(int i=0; i<10 ;i++)
//    {
//        for(int j=0; j<85; j++){
//
//            if(AD[j][i]==1)	CD_AD++;
//        }
//    }
//    printf("%d\n",CD_AD);

	/*int **AD=NULL;
	AD = new int*[OB_row];
	for(int i=0;i<OB_row;i++)	AD[i]=new int[OB_col];
	for(int i=0;i<OB_row;i++)
	{
        for(int j=0;j<OB_col;j++)	AD[i][j]=0;
	}*/

    //FILE *fp;
    //fp=fopen("/home/ubuntu/CodeBlocks/TR_WallFurring/OBdata/obdata.txt","a");
	/*if(fp==NULL){
		printf("Not find .txt !\n");
	}
	else{
		printf("Open .txt Success !\n");
	}*/

	streamDepth.readFrame( &frameDepth );

	/*---depth Data total---*/
	//C1 depth Data
	for(int i=10 ; i< 95 ; i++){
		C_Count[1][1]+=depthMD(i,122);
		C_Count[2][1]+=depthMD(i,124);
		C_Count[3][1]+=depthMD(i,126);
		C_Count[4][1]+=depthMD(i,128);
		C_Count[5][1]+=depthMD(i,130);
		C_Count[6][1]+=depthMD(i,132);
		C_Count[7][1]+=depthMD(i,134);
		C_Count[8][1]+=depthMD(i,136);
		C_Count[9][1]+=depthMD(i,138);
		C_Count[10][1]+=depthMD(i,140);
		//fprintf(fp,"%d  %d  %d  %d  %d  %d  %d  %d  %d  %d  \n",C1count1,C1count2,C1count3,C1count4,C1count5,C1count6,C1count7,C1count8,C1count9,C1count10);
	}
	//C2 depth Data
	for(int i=95 ; i< 180 ; i++){
		C_Count[1][2]+=depthMD(i,122);
		C_Count[2][2]+=depthMD(i,124);
		C_Count[3][2]+=depthMD(i,126);
		C_Count[4][2]+=depthMD(i,128);
		C_Count[5][2]+=depthMD(i,130);
		C_Count[6][2]+=depthMD(i,132);
		C_Count[7][2]+=depthMD(i,134);
		C_Count[8][2]+=depthMD(i,136);
		C_Count[9][2]+=depthMD(i,138);
		C_Count[10][2]+=depthMD(i,140);
		//fprintf(fp,"%d  %d  %d  %d  %d  %d  %d  %d  %d  %d  \n",C2count1,C2count2,C2count3,C2count4,C2count5,C2count6,C2count7,C2count8,C2count9,C2count10);
	}
	//C3 depth Data
	for(int i=180 ; i< 265 ; i++){
		C_Count[1][3]+=depthMD(i,122);
		C_Count[2][3]+=depthMD(i,124);
		C_Count[3][3]+=depthMD(i,126);
		C_Count[4][3]+=depthMD(i,128);
		C_Count[5][3]+=depthMD(i,130);
		C_Count[6][3]+=depthMD(i,132);
		C_Count[7][3]+=depthMD(i,134);
		C_Count[8][3]+=depthMD(i,136);
		C_Count[9][3]+=depthMD(i,138);
		C_Count[10][3]+=depthMD(i,140);
		//fprintf(fp,"%d  %d  %d  %d  %d  %d  %d  %d  %d  %d  \n",C3count1,C3count2,C3count3,C3count4,C3count5,C3count6,C3count7,C3count8,C3count9,C3count10);
	}

	/*---depth Data Average---*/
	//C depth Data Average
	 int c_black_count = 0;

	for(int i=1; i<11; i++)
	{
        C_Count[i][1]=Depth_Data_Average(C_Count[i][1]);
        C_Count[i][2]=Depth_Data_Average(C_Count[i][2]);
        C_Count[i][3]=Depth_Data_Average(C_Count[i][3]);

        /*---Black area---*/
        if(C_Count[i][1] < 10 || C_Count[i][2] <10 || C_Count[i][3] < 10)
        {
            c_black_count++ ;

            if(c_black_count > 5) return 7;

        }
	}

	/*---First Condition count : FULL Obstacle---*/
	int C1FirstCount=0,C2FirstCount=0,C3FirstCount=0;
	//C1 FULL Obstacle
	C1FirstCount = Full_Obstacle(C_Count[1][1],C_Count[2][1],C_Count[3][1],C_Count[4][1],C_Count[5][1],C_Count[6][1],C_Count[7][1],C_Count[8][1],C_Count[9][1],C_Count[10][1]);
	//C2 FULL Obstacle
	C2FirstCount = Full_Obstacle(C_Count[1][2],C_Count[2][2],C_Count[3][2],C_Count[4][2],C_Count[5][2],C_Count[6][2],C_Count[7][2],C_Count[8][2],C_Count[9][2],C_Count[10][2]);
	//C3 FULL Obstacle
	C3FirstCount = Full_Obstacle(C_Count[1][3],C_Count[2][3],C_Count[3][3],C_Count[4][3],C_Count[5][3],C_Count[6][3],C_Count[7][3],C_Count[8][3],C_Count[9][3],C_Count[10][3]);

    if(C1FirstCount>=5 && C2FirstCount>=5 && C3FirstCount>=5 )
    {
        printf("C Block Full OB\n");
    }
	/*---Second Condition count : SMALL Obstacle---*/
	int C1_AD_Amount=0,C2_AD_Amount=0,C3_AD_Amount=0;

	if(C1FirstCount<5 && C2FirstCount<5 && C3FirstCount<5 )
	{
		/*---All Use---*/
		int AD_X=0;
		int print_int0=0,print_int1=0,print_int2=0,print_int3=0,print_int4=0,print_int5=0,print_int6=0,print_int7=0,print_int8=0,print_int9=0;
		int C1_Small_Obstacle_Condition_2=400;
		/*------------*/
		int C1_Small_Obstacle_Condition=30; //30
		for(int i=10; i<95; i++)
		{
			print_int0 = abs(C_Count[1][1]-depthMD(i,122));
			print_int1 = abs(C_Count[2][1]-depthMD(i,124));
			print_int2 = abs(C_Count[3][1]-depthMD(i,126));
			print_int3 = abs(C_Count[4][1]-depthMD(i,128));
			print_int4 = abs(C_Count[5][1]-depthMD(i,130));
			print_int5 = abs(C_Count[6][1]-depthMD(i,132));
			print_int6 = abs(C_Count[7][1]-depthMD(i,134));
			print_int7 = abs(C_Count[8][1]-depthMD(i,136));
			print_int8 = abs(C_Count[9][1]-depthMD(i,138));
			print_int9 = abs(C_Count[10][1]-depthMD(i,140));

            if(print_int0>C1_Small_Obstacle_Condition && print_int0<C1_Small_Obstacle_Condition_2) AD[AD_X][0]=1;
            if(print_int1>C1_Small_Obstacle_Condition && print_int1<C1_Small_Obstacle_Condition_2) AD[AD_X][1]=1;
            if(print_int2>C1_Small_Obstacle_Condition && print_int2<C1_Small_Obstacle_Condition_2) AD[AD_X][2]=1;
            if(print_int3>C1_Small_Obstacle_Condition && print_int3<C1_Small_Obstacle_Condition_2) AD[AD_X][3]=1;
            if(print_int4>C1_Small_Obstacle_Condition && print_int4<C1_Small_Obstacle_Condition_2) AD[AD_X][4]=1;
            if(print_int5>C1_Small_Obstacle_Condition && print_int5<C1_Small_Obstacle_Condition_2) AD[AD_X][5]=1;
            if(print_int6>C1_Small_Obstacle_Condition && print_int6<C1_Small_Obstacle_Condition_2) AD[AD_X][6]=1;
            if(print_int7>C1_Small_Obstacle_Condition && print_int7<C1_Small_Obstacle_Condition_2) AD[AD_X][7]=1;
            if(print_int8>C1_Small_Obstacle_Condition && print_int8<C1_Small_Obstacle_Condition_2) AD[AD_X][8]=1;
            if(print_int9>C1_Small_Obstacle_Condition && print_int9<C1_Small_Obstacle_Condition_2) AD[AD_X][9]=1;
            AD_X++;
		}

		AD_X=0;
		int C2_Small_Obstacle_Condition=30;
		for(int i=95; i<180; i++)
		{
			print_int0 = abs(C_Count[1][2]-depthMD(i,122));
			print_int1 = abs(C_Count[2][2]-depthMD(i,124));
			print_int2 = abs(C_Count[3][2]-depthMD(i,126));
			print_int3 = abs(C_Count[4][2]-depthMD(i,128));
			print_int4 = abs(C_Count[5][2]-depthMD(i,130));
			print_int5 = abs(C_Count[6][2]-depthMD(i,132));
			print_int6 = abs(C_Count[7][2]-depthMD(i,134));
			print_int7 = abs(C_Count[8][2]-depthMD(i,136));
			print_int8 = abs(C_Count[9][2]-depthMD(i,138));
			print_int9 = abs(C_Count[10][2]-depthMD(i,140));

			if(print_int0>C2_Small_Obstacle_Condition && print_int0<C1_Small_Obstacle_Condition_2) AD[AD_X][10]=1;
            if(print_int1>C2_Small_Obstacle_Condition && print_int1<C1_Small_Obstacle_Condition_2) AD[AD_X][11]=1;
            if(print_int2>C2_Small_Obstacle_Condition && print_int2<C1_Small_Obstacle_Condition_2) AD[AD_X][12]=1;
            if(print_int3>C2_Small_Obstacle_Condition && print_int3<C1_Small_Obstacle_Condition_2) AD[AD_X][13]=1;
            if(print_int4>C2_Small_Obstacle_Condition && print_int4<C1_Small_Obstacle_Condition_2) AD[AD_X][14]=1;
            if(print_int5>C2_Small_Obstacle_Condition && print_int5<C1_Small_Obstacle_Condition_2) AD[AD_X][15]=1;
            if(print_int6>C2_Small_Obstacle_Condition && print_int6<C1_Small_Obstacle_Condition_2) AD[AD_X][16]=1;
            if(print_int7>C2_Small_Obstacle_Condition && print_int7<C1_Small_Obstacle_Condition_2) AD[AD_X][17]=1;
            if(print_int8>C2_Small_Obstacle_Condition && print_int8<C1_Small_Obstacle_Condition_2) AD[AD_X][18]=1;
            if(print_int9>C2_Small_Obstacle_Condition && print_int9<C1_Small_Obstacle_Condition_2) AD[AD_X][19]=1;
            AD_X++;

		}

		AD_X=0;
		int C3_Small_Obstacle_Condition=30;
		for(int i=180; i<265; i++)
		{
			print_int0 = abs(C_Count[1][3]-depthMD(i,122));
			print_int1 = abs(C_Count[2][3]-depthMD(i,124));
			print_int2 = abs(C_Count[3][3]-depthMD(i,126));
			print_int3 = abs(C_Count[4][3]-depthMD(i,128));
			print_int4 = abs(C_Count[5][3]-depthMD(i,130));
			print_int5 = abs(C_Count[6][3]-depthMD(i,132));
			print_int6 = abs(C_Count[7][3]-depthMD(i,134));
			print_int7 = abs(C_Count[8][3]-depthMD(i,136));
			print_int8 = abs(C_Count[9][3]-depthMD(i,138));
			print_int9 = abs(C_Count[10][3]-depthMD(i,140));

			if(print_int0>C3_Small_Obstacle_Condition && print_int0<C1_Small_Obstacle_Condition_2) AD[AD_X][20]=1;
            if(print_int1>C3_Small_Obstacle_Condition && print_int1<C1_Small_Obstacle_Condition_2) AD[AD_X][21]=1;
            if(print_int2>C3_Small_Obstacle_Condition && print_int2<C1_Small_Obstacle_Condition_2) AD[AD_X][22]=1;
            if(print_int3>C3_Small_Obstacle_Condition && print_int3<C1_Small_Obstacle_Condition_2) AD[AD_X][23]=1;
            if(print_int4>C3_Small_Obstacle_Condition && print_int4<C1_Small_Obstacle_Condition_2) AD[AD_X][24]=1;
            if(print_int5>C3_Small_Obstacle_Condition && print_int5<C1_Small_Obstacle_Condition_2) AD[AD_X][25]=1;
            if(print_int6>C3_Small_Obstacle_Condition && print_int6<C1_Small_Obstacle_Condition_2) AD[AD_X][26]=1;
            if(print_int7>C3_Small_Obstacle_Condition && print_int7<C1_Small_Obstacle_Condition_2) AD[AD_X][27]=1;
            if(print_int8>C3_Small_Obstacle_Condition && print_int8<C1_Small_Obstacle_Condition_2) AD[AD_X][28]=1;
            if(print_int9>C3_Small_Obstacle_Condition && print_int9<C1_Small_Obstacle_Condition_2) AD[AD_X][29]=1;
            AD_X++;

		}

		/*---Count AD : 1 Amount---*/
		//C1 Count AD
		for(int i=0; i<10 ;i++)
		{
			for(int j=0; j<85; j++){

				if(AD[j][i]==1) C1_AD_Amount++;
			}
		}

		//C2 Count AD
		for(int i=10; i<20 ;i++)
		{
			for(int j=0; j<85; j++){

				if(AD[j][i]==1) C2_AD_Amount++;
			}
		}

		//C3 Count AD
		for(int i=20; i<30 ;i++)
		{
			for(int j=0; j<85; j++){

				if(AD[j][i]==1) C3_AD_Amount++;
			}
		}

        //printf("C1:%d\tC2:%d\tC3:%d\n\n",C1_AD_Amount,C2_AD_Amount,C3_AD_Amount);


		/*printf("C1 AD amount: %d \n",C3_AD_Amount);
		printf("C2 AD amount: %d \n",C2_AD_Amount);
		printf("C3 AD amount: %d \n",C1_AD_Amount);*/

		/*---fprintf AD array---*/
		/*	fprintf(fp,"Block C1\n");
			int c=0;
			for(int i=0; i<10; i++){
				for(int j=0; j<85; j++){
					fprintf(fp,"%d  ",AD[j][i]);
					c++;
					if(c>84){
						fprintf(fp,"\n");
						c=0;
					}
				}
			}
			fprintf(fp,"\n");

			fprintf(fp,"Block C2\n");
			c=0;
			for(int i=10; i<20; i++){
				for(int j=0; j<85; j++){
					fprintf(fp,"%d  ",AD[j][i]);
					c++;
					if(c>84){
						fprintf(fp,"\n");
						c=0;
					}
				}
			}
			fprintf(fp,"\n");

			fprintf(fp,"Block C3\n");
			c=0;
			for(int i=20; i<30; i++){
				for(int j=0; j<85; j++){
					fprintf(fp,"%d  ",AD[j][i]);
					c++;
					if(c>84){
						fprintf(fp,"\n");
						c=0;
					}
				}
			}
			fprintf(fp,"\n");*/
	}

	/*---Return Obstacle position---*/

	if((C1FirstCount>=5 && C3FirstCount>=5) || (C1FirstCount>=5 && C2FirstCount>=5 && C3FirstCount>=5) || (C1_AD_Amount>50 && C3_AD_Amount>50) || (C1_AD_Amount>50 && C2_AD_Amount>50 && C3_AD_Amount>50))
	{
		return 1;//Obstacle in C1.C2.C3
	}
	else if((C1FirstCount>=5 && C2FirstCount>=5) || (C1_AD_Amount>50 && C2_AD_Amount>50))
	{
		return 2;//Obstacle in C2.C3
	}
	else if((C2FirstCount>=5 && C3FirstCount>=5) || (C2_AD_Amount>50 && C3_AD_Amount>50))
	{
		return 3;//Obstacle in C1.C2
	}
	else if(C1FirstCount>=5 || C1_AD_Amount>50)
	{
		return 4;//Obstacle in C3
	}
	else if(C2FirstCount>=5 || C2_AD_Amount>50)
	{
		return 5;//Obstacle in C2
	}
	else if(C3FirstCount>=5 || C3_AD_Amount>50)
	{
		return 6;//Obstacle in C1
	}

	/*for(int i=0;i<OB_row;i++)delete AD[i];
	delete AD;*/

	//fclose(fp);

    //printf("obdata close \n");

    return 0;
}


/*---For obstacle avoidance strategy ---*/
void Avoidance_Motor_r_Control(int Status_A,int Status_B,int Status_C,double Last_L_speed,double Last_R_speed,double *d1,double *d2,char *direction)
{

    if( Status_A==0 && Status_B==0 && Status_C==0 )
    {
        *d1=NULL;
        *d2=NULL;
        *direction = NULL;
    }
    else if( Status_A == 7 || Status_B == 7 || Status_C == 7 )
    {
//        *d1=NULL;
//        *d2=NULL;
//        *direction = 'S';
        *d1 = 0 ;
        *d2 = 0 ;

       if(Last_L_speed == Last_R_speed )
       {
            *direction = 'R';
       }
       else if(Last_L_speed > Last_R_speed)
       {
            *direction = 'R';
       }
       else if(Last_L_speed < Last_R_speed)
       {
            *direction = 'L';
       }
    }
    else if( Status_A == 1 || Status_B == 1 || Status_C == 1 )
    {
        *d1 = 0 ;
        *d2 = 0 ;

       if(Last_L_speed == Last_R_speed )
       {
            *direction = 'R';
       }
       else if(Last_L_speed > Last_R_speed)
       {
            *direction = 'R';
       }
       else if(Last_L_speed < Last_R_speed)
       {
            *direction = 'L';
       }

    }
    else if(Status_C>1 )
    {

        //printf("block C have ob\n");
        if(Status_C==1){

            *d1=40;
            *d2=67;
            *direction = 'R';
//
//            *d1=28;
//            *d2=65;
//            *direction = 'R';


        }
        if(Status_C==2){

            *d1=-9;
            *d2=67;
            *direction = 'L';

//            *d1=-8.5;
//            *d2=53;
//            *direction = 'L';
        }
        if(Status_C==3){

            *d1=11;
            *d2=67;
            *direction = 'R';

//            *d1=8;
//            *d2=53;
//            *direction = 'R';
        }
        if(Status_C==4){

            *d1=11;
            *d2=67;
            *direction = 'L';

//            *d1=8;
//            *d2=53;
//            *direction = 'L';


        }

        if(Status_C==5){

            *d1=0;
            *d2=67;
            *direction = 'R';

//            *d1=0;
//            *d2=53;
//            *direction = 'R';
        }

        if(Status_C==6){

            *d1=-9;
            *d2=67;
            *direction = 'R';

//            *d1=-8.5;
//            *d2=67;
//            *direction = 'R';
        }
    }
    else if(Status_B>1 )
    {
        /*---B Block ST---*/
        if(Status_B==1){

            *d1=40;
            *d2=76;
            *direction = 'R';

//            *d1=26;
//            *d2=57.3;
//            *direction = 'R';
        }
        if(Status_B==2){

            *d1=-11;
            *d2=76;
            *direction = 'L';

//            *d1=-9;
//            *d2=57.3;
//            *direction = 'L';
        }
        if(Status_B==3){

            *d1=13;
            *d2=76;
            *direction = 'R';

//            *d1=9;
//            *d2=57.3;
//            *direction = 'R';
        }
        if(Status_B==4){

            *d1=13;
            *d2=76;
            *direction = 'L';

//            *d1=9;
//            *d2=57.3;
//            *direction = 'L';
        }

        if(Status_B==5){

            *d1=0;
            *d2=76;
            *direction = 'R';

//            *d1=0;
//            *d2=57.3;
//            *direction = 'R';
        }

        if(Status_B==6){

            *d1=-11;
            *d2=76;
            *direction = 'R';

//            *d1=-9;
//            *d2=57.3;
//            *direction = 'R';
        }
    }
    else if(Status_A>1 )
    {
       /*---A Block ST---*/

        if(Status_A==1){

            *d1=40;
            *d2=80;
            *direction = 'R';

//            *d1=28;
//            *d2=65;
//            *direction = 'R';
        }
        if(Status_A==2){

            *d1=-12;
            *d2=80;
            *direction = 'L';

//            *d1=-11;
//            *d2=65;
//            *direction = 'L';
        }
        if(Status_A==3){

            *d1=15;
            *d2=80;
            *direction = 'R';

//            *d1=10;
//            *d2=65;
//            *direction = 'R';
        }
        if(Status_A==4){

            *d1=13;
            *d2=80;
            *direction = 'L';

//            *d1=9;
//            *d2=65;
//            *direction = 'L';
        }

        if(Status_A==5){

            *d1=0;
            *d2=80;
            *direction = 'R';

//            *d1=0;
//            *d2=65;
//            *direction = 'R';
        }

        if(Status_A==6){

            *d1=-12;
            *d2=80;
            *direction = 'R';

//            *d1=-11;
//            *d2=65;
//            *direction = 'R';
        }
    }


}

void Avoidance_speed_Control(char direction,double d1,double d2,double *car_vl,double *car_vr,double *rlim)
{
    /*---Tracked robot data---*/
    int W = 54;
    int L = 60; //57
    double car_speed = 600; //Vc
    //double Car_straight_speed = 800;
    /*---radius---*/
    double r_lim = 0;
    double r_eq = 0;

    /*---Encodeer---*/
    //time_t t1 = time(NULL);


    if(direction == NULL)
    {
        *car_vl = car_speed;
        *car_vr = car_speed;

        return;
    }
    else if(direction == 'S')
    {
        *car_vl = 0;
        *car_vr = 0;

        return;
    }
    else if(direction == 'R')
    {
        if(d1==0 && d2==0)
        {
            d1=L/2;
            d2=W/2;
        }

        if( (L/2 + d1) > 0 )
        {
            r_lim = 0.5 * ( d1 - L/2 + (pow(d2,2) - pow(W/2,2))/(L/2 + d1) );



            printf("r_lim = %f \n",r_lim);

                if(r_lim > 0) //correct sol
                {
                    r_eq = 0.4 * r_lim;

                    *rlim = r_eq ;
                }
                else if(r_lim == 0)
                {
                    *car_vl = car_speed;
                    *car_vr = -car_speed;

                    return;
                }
                else //error sol
                {
                    *car_vl=0;
                    *car_vr=0;

                    printf("r_lim(right) < 0\n");
                    return;
                }

        }
        else if( (L/2 + d1) == 0 )
        {
            r_eq = 0.1 * (L/2);

            *rlim = r_eq;

            printf("(L/2 + d1) == 0");
        }
        else if( (L/2 + d1) < 0 )
        {
            *car_vl = car_speed;
            *car_vr = car_speed;
            return;
        }

    }
    else if(direction == 'L')
    {
        if(d1==0 && d2==0)
        {
            d1 = -L/2;
            d2 = W/2;
        }

        int d1_contrary = -d1;

        if( (L/2 + d1_contrary) > 0 )
        {
            r_lim = 0.5 * ( d1_contrary - L/2 + (pow(d2,2) - pow(W/2,2))/(L/2 + d1_contrary) );



            printf("r_lim = %f \n",r_lim);

                if(r_lim > 0) //correct sol
                {
                    r_eq = -0.4 * r_lim;
                    *rlim = r_eq;
                }
                else if(r_lim == 0)
                {
                    *car_vl = -car_speed;
                    *car_vr = car_speed;
                    printf("r_lim = 0\n");
                    return;
                }
                else //error sol
                {
                    *car_vl=0;
                    *car_vr=0;
                    printf("r_lim(left) < 0\n");
                    return;
                }

        }
        else if( (L/2 + d1_contrary) == 0 )
        {
            r_eq = -0.1 * (L/2);

            *rlim = r_eq;

            printf("(L/2 + d1) == 0");
        }
        else if( (L/2 + d1_contrary) < 0 )
        {
            *car_vl = car_speed;
            *car_vr = car_speed;
            return;
        }

    }

    *car_vl = ( (r_eq + (L/2)) / r_eq ) * car_speed;
    *car_vr = ( (r_eq - (L/2)) / r_eq ) * car_speed;

    //usleep(10000);
    *car_vl = (abs(*car_vl) > 2500)?(abs(*car_vl)/(*car_vl)*2500):(*car_vl);
    *car_vr = (abs(*car_vr) > 2500)?(abs(*car_vr)/(*car_vr)*2500):(*car_vr);


}


/*---For r test---*/
void Avoidance_MotorControl(double r_eq,double *car_vl,double *car_vr)
{
    /*---Tracked robot data---*/
    //int W = 54;
    double L = 58; //57
    double car_speed = 500; //Vc

    //printf("r=%f\n",r_eq);

    if(r_eq==0)
    {
        *car_vl = car_speed;
        *car_vr = -car_speed;
    }
    else
    {
        *car_vl = ( (r_eq + (L/2)) / r_eq ) * car_speed;
        *car_vr = ( (r_eq - (L/2)) / r_eq ) * car_speed;
        //usleep(10000);

        /*---4 out 5 in---*/
        *car_vl = (abs(*car_vl) > 2500)?(abs(*car_vl)/(*car_vl)*2500):(*car_vl);
        *car_vr = (abs(*car_vr) > 2500)?(abs(*car_vr)/(*car_vr)*2500):(*car_vr);
    }

}


