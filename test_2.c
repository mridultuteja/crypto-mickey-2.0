#include<stdio.h>
#include<string.h>
int xorr(int a,int b)                                                     //xor operation
{
  if(a==b)
  return 0;
  else
  return 1;
}
int andd(int a, int b)                                                   //and operation
{
  if(a==1 && b==1)
  return 1;
  else
  return 0;

}
int clock_r(int r[], int input_bit_r, int control_bit_r)
{ int tap[] ={0,1,3,4,5,6,9,12,13,16,19,20,21,22,25,28,37,38,41,42,45,46,50,52,54,56,58,60,61,63,64,65,66,67,71,72,79,80,81,82,87,88,89,90,91,92,94,95,96,97};
  int r_clocked[100];
  int feedback_bit,k;
  k=0;                                                                                          //tap counter
  feedback_bit = xorr(r[99],input_bit_r);
  for(int i=0;i<100;i++)
  { if(i==0)
    r_clocked[i]=0;
    else{
      r_clocked[i]= r[i-1];
    }
  if(i==tap[k])
  {
    r_clocked[i]=xorr(r_clocked[i],feedback_bit);
    k++;
  }
  if(control_bit_r==1)
  r_clocked[i]=xorr(r_clocked[i],r[i]);
  }

  r=r_clocked;
}
int clock_s(int s[],int input_bit_s,int control_bit_s)
{
int comp0[]={'\0',0,0,0,1,1,0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,1,1,1,1,0,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,0,0,0,0,0,1,1,'\0'};
int comp1[]={'\0',1,0,1,1,0,0,1,0,1,1,1,1,0,0,1,0,1,0,0,0,1,1,0,1,0,1,1,1,0,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,0,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,0,0,1,0,0,0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,'\0'};
int fb0[]={1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,0,0,1,1,0,0,0};
int fb1[]={1,1,1,0,1,1,1,0,0,0,0,1,1,1,0,1,0,0,1,1,0,0,0,1,0,0,1,1,0,0,1,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,1,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,1,0,1,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1};
int s_i[100],s_clocked[100];
int feedback_bit=xorr(s[99],input_bit_s);
s_i[0]=0;
s_i[99]=s[98];
for (int i=1;i<99;i++)
{
s_i[i]=xorr(s[i-1],andd(xorr(s[i],comp0[i]),xorr(s[i+1],comp1[i])));
}
if(control_bit_s==0)
{
  for (int i=0;i<100;i++)
  {
    s_clocked[i]=xorr(s_i[i],andd(fb0[i],feedback_bit));
  }
}
else{

    for (int i=0;i<100;i++)
    {
      s_clocked[i]=xorr(s_i[i],andd(fb1[i],feedback_bit));
}

}
s=s_clocked;
}
void clock_kg(int r[], int s[],int mixing, int input_bit)
{ int input_bit_r;
  int control_bit_r=xorr(s[34], r[67]);
  int control_bit_s=xorr(s[67], r[33]);
  if (mixing==1)
    input_bit_r=xorr(input_bit,s[50]);
  else
    input_bit_r=input_bit;
  int input_bit_s=input_bit;
  int r_cl[100],s_cl[100];
clock_r(r,input_bit_r,control_bit_r);
clock_s(s,input_bit_s,control_bit_s);

}

void main()
{
  int key[80], iv[80], z[100], i, j, l, r[100],s[100];

  printf("Enter length of keystream to be generated \n" );
	scanf("%d", &l );
	printf("Enter The 80-bit key \n" );

  for (j = 0; j< 80; j++)
		scanf("%d \n", &key[j]);

  printf("Enter the value for iv (40-bit)\n" );
  for (j=0; j < 40; j++)
		scanf("%d \n", &iv[j] );          //initialising register R and S value as 0

  for(i = 0; i < 100; i++)
	{
  		r[i]=0;
  		s[i]=0;
	}

	for (i=0;i<40;i++)                                         //loading in IV
		clock_kg(r,s,1,iv[i]);

	for (i = 0; i < 80; i++)                                           //loading in key
		clock_kg(r,s,1,key[i]);

	for (i=0;i<100;i++)                                               //prelock
		clock_kg(r,s,1,0);

	for(i=0;i<l;i++)                                        //Generating keystream
	{
		z[i]= xorr(r[0],s[0]);
  		clock_kg(r,s,0,0);
	}

  printf("The generated keystream is");
  for(i = 0; i < l; i++)
    printf("%d \n",z[i]);

}
