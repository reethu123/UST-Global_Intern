/** 

	Application to Create, Update, Delete and View Reminders in C using file.
	dev by,
	Reethu Das,
	reethudas@gmail.com.

 **/




#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


int Create_Function();   	//Function Definition To Create Task. 
int Edit_Function();		//Function Definition To Update Task. 
int Delete_Function();		//Function Definition To Delete Task. 
int View_Function();		//Function Definition To View Task List. 

#define MAX 100

//Main Function Call
int main()
{
	int while_loop = 1,opt;

	clrscr();

	printf("\nWelcome User!!!\n");

	while(while_loop == 1)
	{
		printf("\nSelect an option from the following:");
		printf("\n1. Create Task");
		printf("\n2. Edit Task");
		printf("\n3. Delete Task");
		printf("\n4. View Tasks");
		printf("\n5. Exit");
		printf("\nYour option : ");
		scanf("%d", &opt);

		switch(opt)
		{
			case 1: Create_Function();     //Function Call To Create Task. 
					break;
			case 2: Edit_Function();		//Function Call To Update Task. 
					break;
			case 3: Delete_Function();		//Function Call To Delete Task. 
					break;
			case 4: View_Function();		//Function Call To View Task. 
					getch();
					break;
			case 5: printf("\nExiting....");  
					while_loop= 0 ;			//Exit the while loop
					break;
			default:printf("\nInvaild Input!!\nEnter agian");
		}
	};

	getch();
	return 0;
}



//Function To Create Task. 
int Create_Function()
{
	int hour,minute,day,month,year;
	char task[MAX];

	FILE *fptr;			//File pointer

	printf("\nName of the task: ");
	scanf("%s" , task);
	//fgets(task, MAX, stdin);

	printf("\n\nInput the Time in HH:MM : ");
	scanf("%d:%d", &hour, &minute);

	printf("\nInput the Date of the task DD/MM/YYYY : ");
	scanf("%d/%d/%d", &day, &month, &year);

	fptr = fopen("program.txt","a+");       //Open File
	//Write to file
	fprintf(fptr,"%s $@$ %d $@$ %d $@$ %d $@$ %d $@$ %d\n",task, hour, minute, day, month, year);
	fclose(fptr);		//Close File

	printf("\nYour task is %s" , task);
	printf("\nTime is %d:%d" , hour, minute);
	printf("\nDate is %d/%d/%d\n\n" , day, month, year);

	getch();
	return(0);
}

//Function To View Task List. 
int View_Function()
{
	int i,temp_count,hour[MAX],minute[MAX],day[MAX],month[MAX],year[MAX],counter;
	char text_by_line[MAX][MAX],words_array[MAX],*ch,text[MAX],name[MAX][MAX];

	FILE *fptr;     //File Pointer
	//clrscr();

	if ((fptr = fopen("program.txt","r")) == NULL)
	{
       printf("No Tasks created!!");
       exit(1);
	}

	counter = 0;   //Count of number of lines in file.

	while ( fgets ( text_by_line[counter], sizeof text_by_line[counter], fptr ) != NULL ) /* Read a line */
	{
		counter++;
	}

	fclose(fptr);    //Close File

	//Spliting data from file.
	for( i = 0 ; i < counter ; i++ )
	{
		temp_count = 0;
		strcpy(words_array,text_by_line[i]);

		ch = strtok(words_array, " $@$ ");
		while (ch != NULL)
		{
			if( temp_count == 0 )
				strcpy(name[i],ch);
			if(temp_count == 1)
				hour[i] = atoi(ch);
			if(temp_count == 2)
				minute[i] = atoi(ch);
			if(temp_count == 3)
				day[i] = atoi(ch);
			if(temp_count == 4)
				month[i] = atoi(ch);
			if(temp_count == 5)
				year[i] = atoi(ch);

			ch = strtok(NULL, " $@$ ");
			temp_count++;
		}
	}

	if( counter != 0 )
		printf("\nTask List:\n\nSL.No \tName \tTime \tDate");
	else
		printf("\nNo Task Created.");

	for (i = 0; i < counter; i++)
	{
		printf("\n%d \t%s \t%d:%d \t%d/%d/%d",i+1,name[i],hour[i],minute[i],day[i],month[i],year[i]);
	}
	printf("\n\n");

	//getch();
	return 0;
}


//Function To Update Task. 
int Edit_Function()
{
	FILE *fptr1, *fptr2,*fptr3;
    int lno = 0, linectr = 0,choice,new_hour,new_minute,new_day,new_month,new_year,old_line_number;
	char str[MAX],fname[MAX],new_name[MAX],temp_buff[MAX];
	char newln[MAX], temp_fname[20];
	int i,temp,hour[MAX],minute[MAX],day[MAX],month[MAX],year[MAX],count;
	char text_by_line[MAX][MAX],words_array[MAX],*chr,name[MAX][MAX],text[MAX];

	if ((fptr3 = fopen("program.txt","r")) == NULL)
	{
       printf("No Tasks created!!");
       exit(1);
	}

	count = 0;

	while ( fgets ( text_by_line[count], sizeof text_by_line[count], fptr3 ) != NULL ) /* Read a line */
	{
		count++;
	}


	fclose(fptr3);

	//Getting Data from File.
	for( i = 0 ; i < count ; i++ )
	{
		temp = 0;
		strcpy(words_array,text_by_line[i]);

		chr = strtok(words_array, " $@$ ");
		while (chr != NULL)
		{
			//printf("%s %d \n", ch,temp);
			if( temp == 0 )
				strcpy(name[i],chr);
			if(temp == 1)
				hour[i] = atoi(chr);
			if(temp == 2)
				minute[i] = atoi(chr);
			if(temp == 3)
				day[i] = atoi(chr);
			if(temp == 4)
				month[i] = atoi(chr);
			if(temp == 5)
				year[i] = atoi(chr);
			chr = strtok(NULL, " $@$ ");
			temp++;

		}
	}

	View_Function(); 		//Print the List of Tasks

	printf("Enter the Sl.No of the task to Update : ");
	scanf("%d",&lno);

	old_line_number = lno-1;

	strcpy(temp_fname,"temp.txt");   //Temporary File to Copy.
	strcpy(fname,"program.txt");	 //Reminder File.
	fptr1 = fopen(fname, "r");
	if (!fptr1)
	{
		printf("No Tasks to Edit\n");
		return 0;
	}
	fptr2 = fopen(temp_fname, "w");
	if (!fptr2)
	{
		printf("Unable to open a temporary file to write!!\n");
		fclose(fptr1);
		return 0;
	}

	printf("\nSelect any of the following to Update:\n");
	printf("1. Name of the Task\n2. Time \n3. Date\n\nChoice: ");
	scanf("%d",&choice);

	switch(choice)
	{
	    case 1: printf("\nEnter New Name :");
		    scanf("%s" , new_name);     //Input New Name

		    //Rewrite New Line with New data
		    strcpy(newln,new_name);
		    strcat(newln," $@$ ");
	    	itoa(hour[old_line_number],temp_buff,10);
		    strcat(newln,temp_buff);
		    strcat(newln," $@$ ");
	    	itoa(minute[old_line_number],temp_buff,10);
		    strcat(newln,temp_buff);
		    strcat(newln," $@$ ");
	    	itoa(day[old_line_number],temp_buff,10);
		    strcat(newln,temp_buff);
		    strcat(newln," $@$ ");
	    	itoa(month[old_line_number],temp_buff,10);
		    strcat(newln,temp_buff);
		    strcat(newln," $@$ ");
	    	itoa(year[old_line_number],temp_buff,10);
		    strcat(newln,temp_buff);

		    break;
	    case 2: printf("\nEnter New Time in HH:MM format :");
		    scanf("%d:%d" , &new_hour,&new_minute);

		    //Rewrite New Line with New data
		    strcpy(newln,name[old_line_number]);
		    strcat(newln," $@$ ");
	    	itoa(new_hour,temp_buff,10);
		    strcat(newln,temp_buff);
		    strcat(newln," $@$ ");
	    	itoa(new_minute,temp_buff,10);
		    strcat(newln,temp_buff);
		    strcat(newln," $@$ ");
	    	itoa(day[old_line_number],temp_buff,10);		    
		    strcat(newln,temp_buff);
		    strcat(newln," $@$ ");
	    	itoa(month[old_line_number],temp_buff,10);		
		    strcat(newln,temp_buff);
		    strcat(newln," $@$ ");
	    	itoa(year[old_line_number],temp_buff,10);
		    strcat(newln,temp_buff);
		    break;

	    case 3: printf("\nEnter New Date in DD/MM/YYYY format :");
		    scanf("%d/%d/%d" , &new_day, &new_month, &new_year);

		    //Rewrite New Line with New data
		    strcpy(newln,name[old_line_number]);
		    strcat(newln," $@$ ");
	    	itoa(hour[old_line_number],temp_buff,10);
		    strcat(newln,temp_buff);
		    strcat(newln," $@$ ");
	    	itoa(minute[old_line_number],temp_buff,10);
		    strcat(newln,temp_buff);
		    strcat(newln," $@$ ");
	    	itoa(new_day,temp_buff,10);
		    strcat(newln,temp_buff);
		    strcat(newln," $@$ ");
	    	itoa(new_month,temp_buff,10);
		    strcat(newln,temp_buff);
		    strcat(newln," $@$ ");
	    	itoa(new_year,temp_buff,10);
		    strcat(newln,temp_buff);
		    break;

	    default:printf("Error!!Try again\n");
		    break;
	}

	// Copy all contents to the temporary file other except specific line
	while (!feof(fptr1))
	{
	    strcpy(str, "\0");
	    fgets(str, MAX, fptr1);
	    if (!feof(fptr1))
	    {
			linectr++;
			if(linectr != lno)
		    {
				fprintf(fptr2, "%s", str);
		    }
		    if(linectr == lno)
		    {
				fprintf(fptr2, "%s", newln);	//New Line write to file
		    }
		}
	}
	fclose(fptr1);
	fclose(fptr2);
	remove(fname);   //Delete File
	rename(temp_fname, fname);  //Rename File
	printf(" Updatation is successfully..!! \n");
	View_Function();
	getch();
	return 0;
}




int Delete_Function()
{
	FILE *fptr1, *fptr2;
    int lno, linectr = 0,choice,new_hour,new_minute,new_day,new_month,new_year;
	char str[MAX],fname[MAX],new_name[MAX],temp_buff[MAX];
	char newln[MAX], temp_file[20];


	View_Function();
	printf("Enter the Sl.No of the task to Delete : ");
	scanf("%d",&lno);

	strcpy(temp_file,"temp.txt"); //Open temporary file to copy
	strcpy(fname,"program.txt");
	fptr1 = fopen(fname, "r");

	if (!fptr1)
	{
		printf("No Tasks to Delete\n");
		return 0;
	}
	fptr2 = fopen(temp_file, "w");
	if (!fptr2)
	{
		printf("Unable to open a temporary file to write!!\n");
		fclose(fptr1);
		return 0;
	}

	// Copy all contents to the temporary file other except specific line
	while (!feof(fptr1))
	{
	    strcpy(str, "\0");
	    fgets(str, MAX, fptr1);
	    if (!feof(fptr1))
	    {
		linectr++;
		if (linectr != lno)
		    {
				fprintf(fptr2, "%s", str);
		    }
		}
	}
	fclose(fptr1);
	fclose(fptr2);
	remove(fname);		//Delete old File
	rename(temp_file, fname);		//Rename File
	printf(" Deletion is successfull..!! \n");
	View_Function();
	getch();
	return 0;

}