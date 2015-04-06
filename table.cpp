#include <iostream>
#include <fstream>
#include <string>
#define main_memory 512
using namespace std;

typedef struct
{
	int page;
	int frame;
	int max_page_size;
	int valid_bit;
	int reference_bit;
	int modify_bit;
	int clock_bit;
	
}table_str;

typedef struct 
{
	int table_count;
	int limit;
	table_str tableStr[520];

}process_table;

typedef struct 
{
	int process_no;
	int page_no;


}frame_table;

int check( frame_table F_table[],int frame_count,int page_no, int process_no)
{
	int chk=0;
	for (int i = 0; i < frame_count; i++)
	{	
		//cout<<"F_table[i].page_no: "<<F_table[i].page_no<<"---page_no: "<<page_no<<"F_table[i].process_no: "<<F_table[i].process_no<<"---process_no: "<< process_no<<endl;
		if(F_table[i].page_no == page_no && F_table[i].process_no == process_no)
		{
			chk=1;
			return chk;
		}
		else
		{
			chk=0;	
		}
			
	}

	return chk;
}

void update_table(process_table process[], int page, int frame,int valid_bit,int reference_bit, int modify_bit, int clock_bit,int proc_index, int table_index)
{
	process[proc_index].tableStr[table_index].page = page;
	process[proc_index].tableStr[table_index].frame = frame;
	process[proc_index].tableStr[table_index].valid_bit = valid_bit;
	process[proc_index].tableStr[table_index].reference_bit = reference_bit;
	process[proc_index].tableStr[table_index].modify_bit = modify_bit;
	process[proc_index].tableStr[table_index].clock_bit =clock_bit;
}

int main()
{
	string line;
	int page_size,frame_count;
	int a,b,i,j;


	process_table process[10];

	ifstream myReadFile;
	myReadFile.open("progAddrLimits.txt");
	i=0;
	if (myReadFile.is_open()) 
	{
		while (!myReadFile.eof() && i<10) 
		{	
			myReadFile >> a >> b;
			//cout<<a<<" "<<b<<endl;
			process[i].limit = b;
			i++;
		}
		
	}

	/*----------------------initially Filling table---------------------------*/
	
	for (int i = 0; i < 10; i++){
		process[i].table_count=0;
		for (int j = 0; j < 520; j++)
		{
			process[i].tableStr[j].page = j;
			process[i].tableStr[j].frame = j;
			process[i].tableStr[j].valid_bit = 0;
			process[i].tableStr[j].reference_bit = 0;
			process[i].tableStr[j].modify_bit = 0;
			process[i].tableStr[j].clock_bit =0;


		}
	}
/*-------------------------print table--------------------------- */
	// for (int i = 0; i < 1; i++){
		
	// 	for (int j = 0; j < process[i].limit; j++)
	// 	{
	// 		cout<<process[i].tableStr[j].page<<' '<<process[i].tableStr[j].frame<<' '<<process[i].tableStr[j].valid_bit<<' '<<process[i].tableStr[j].reference_bit<<' '<<process[i].tableStr[j].modify_bit<<' '<<process[i].tableStr[j].clock_bit<<endl ;
			

	// 	}
	// }

/*--------------------------GET NUMBER OF FRAMES----------------------------------*/

	cout<<"please enter page size: ";
	cin>>page_size;
	frame_count = main_memory/page_size;
	cout<<"total number of frames: "<< frame_count<<endl;
 	
	frame_table F_table[frame_count];  //create frame table
//	frame_table Input_ref_table[]

	ifstream referFile;
	referFile.open("progMemoryref.txt");
	i=0;int c,d,time=0;
	

/*------------------------Algorithms--------------------------*/
	//int choice=0;

	// cout<<"enter you choice:"<<endl;
	// cout<<"1. FIFO"<<endl<<"2. LRU"<<endl <<"3. Clock"<<"4. Exit."<<endl;

	// while(true)
	// {
		// switch(choice)
		// {
		// 	case 1:
		// 		do
		// 		{	
					ofstream answerfile;
  					answerfile.open ("FIFO.txt");
					i=0;j=0;
					int t=0;
					if (referFile.is_open()) 
						{
							while (!referFile.eof()) 
							{	
								referFile >> c >> d;
								cout<<c<<" "<<d<<endl;
								int chk = check(F_table,frame_count,d,c);
								if(chk==0)
								{
									answerfile<<"page fault----"<<" ----added page: "<<d<<" in main memory"<<endl;
									answerfile<<"page at frame: "<< i%frame_count<<" has been replaced"<<endl;
									F_table[i%frame_count].process_no = c;
									F_table[i%frame_count].page_no = d;
									//cout<<"till here is fine.-------------"<<endl;
									update_table(process,d,i%frame_count,1,1,1,t,c,process[c].table_count%frame_count);
									//cout<<"till here is fine.0000000000-------------"<<endl;
									i++;
									t++;
									process[c].table_count++;
								}
								else
								{	
									
									answerfile<<"this is already loaded."<<endl;

								}
								


								
							}
							
						}




		// 		}
		// 	case 4:
		// 		break;
		// 		false;

		// }myfile.close()


	//}






	answerfile.close();

	
	return 0;
}