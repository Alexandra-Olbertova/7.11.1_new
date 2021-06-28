#include <stdio.h>
#include <stdlib.h>

unsigned long valid_date(int r, char l, char d, char h, char m, char s){
	
	int valid = 0, prestup = 0;
	
	if((r % 4 == 0 && r % 100 != 0) || (r % 400 == 0))
		prestup = 1;
	
	if(l >= 1 && l <= 12)
	{
		if(l == 2)
		{
			if (prestup == 1 && d == 29)
				valid = 0;
			else if(d > 28)
				return 1;
		}
		else if((l == 4 || l == 6 || l == 9  || l == 11) && (d > 30))
				return 1;
	}
	

	if(d <= 0 || d >= 31)
		return 1;
	if(h > 23 && m != 0 && s != 0)
		return 1;
	if(h < 0)
		return 1;
	if(m > 59 || m < 0)
		return 1;
	if(s > 59 || s < 0)
		return 1;

	return valid;		
}

unsigned long casovy_usek(int r1, char l1, char d1, char h1, char m1, char s1, int r2, char l2, char d2, char h2, char m2, char s2){

	unsigned long sum = 0;
	int prestup = 0;
	int R1,R2;
	
	R1=r1; R2=r2;

	if(l1 > 2)
		R1++;
	if(l2 < 2)
		R2--;
	
	while(R1 <= R2){
	
		if((R1 % 4 == 0 && R1 % 100 != 0) || (R1 % 400 == 0))
			prestup++;
	
		R1++;	
	}

	
	if(r1 == r2 && l1 == l2)
	{
		if(d1 == d2)
		{
			if(h1 != h2 && h1 != 0)
			{	
				if(h1 < h2)
					sum += (h2-h1)*3600;
				else
					sum += (h1-h2)*3600;
			}	
			if(m1 != m2 && m1 != 0)
			{
				if(m1 < m2)
					sum += (m2-m1)*60;
				else
					sum += (m1-m2)*60;
			}	
			if(s1 != s2 && s1 != 0)
			{
				if(s1 < s2)
					sum += s2-s1;
				else
					sum += s1-s2;
			}
		return sum;	
		}	
		
		while(d1 != d2)
		{
		sum += (23-h1)*3600 + (59-m1)*60 + (60-s1);
		h1 = 0; m1 = 0; s1 = 0;
		d1++;	
		}
		sum += h2*3600 + m2*60 + s2;
		
		return sum;		
	}	
	
	sum += (23-h1)*3600 + (59-m1)*60 + (60-s1);
	
	d1++;
	
	if(l1 == 2 && d1 == 29){
		l1++;
		d1 = 1;
	}
 	if(d1 == 31 && (l1 == 4 || l1 == 6 || l1 == 9  || l1 == 11)){
 		l1++;
		d1 = 1;
	}
 	if(d1 == 32){
 		l1++;
		d1 = 1;
	}
	if(l1 == 13){
		l1 = 1;
		r1++;
	}			
		
	do
	{
		while(l1 != l2)
		{
			if(l1 == 2)
				sum += (28-d1)*86400;
			else if(l1 == 4 || l1 == 6 || l1 == 9  || l1 == 11)
				sum += (30-d1)*86400;
			else 
				sum += (31-d1)*86400;	
			
			l1++;
			d1 = 0;
			if(l1 == 13){
				r1++;
				l1 = 1;	
				sum += 31*86400;
			}	
		}
		l1++;
	}
	while(r1 != r2);
	
	if(l2 == 1)
		sum -= 31*86400;
				
	sum += d2*86400;
	sum += h2*3600 + m2*60 + s2;
	sum += prestup*86400;

	return sum;
}

main(){
	
	int r1, r2;
	char l1, d1, h1, m1, s1, l2, d2, h2, m2, s2;
	int L1, D1, H1, M1, S1, L2, D2, H2, M2, S2;
	
	printf("Pocet sekund uplynutych medzi dvoma casovymi okamzikmi\n");
	
	printf("1. casovy usek\n");
	printf("rok mesiac den hodina minuta sekunda:");
		scanf("%d %d %d %d %d %d",&r1,&L1,&D1,&H1,&M1,&S1);

	l1 = (char) L1;
	d1 = (char)	D1;
	h1 = (char) H1;
	m1 = (char) M1;
	s1 = (char) S1;
		
	if(valid_date(r1,l1,d1,h1,m1,s1) != 0){
		printf("Nespravny datum");
		exit(0);
	}
	
	printf("2. casovy usek\n");
	printf("rok mesiac den hodina minuta sekunda:");
		scanf("%d %d %d %d %d %d",&r2,&L2,&D2,&H2,&M2,&S2);
		
	l2 = (char) L2;
	d2 = (char)	D2;
	h2 = (char) H2;
	m2 = (char) M2;
	s2 = (char) S2;
			
	if(valid_date(r2,l2,d2,h2,m2,s2) != 0){
		printf("Nespravny datum");
		exit(0);
	}
			
	if(r1 == r2)
	{
		if((l1 == l2 && d1 < d2) || (l1 < l2))
			printf("Pocet sekund = %lu",casovy_usek(r1,l1,d1,h1,m1,s1,r2,l2,d2,h2,m2,s2));
		else
			printf("Pocet sekund = %lu",casovy_usek(r2,l2,d2,h2,m2,s2,r1,l1,d1,h1,m1,s1));
	}
	
	else if(r1 < r2)
		printf("Pocet sekund = %lu",casovy_usek(r1,l1,d1,h1,m1,s1,r2,l2,d2,h2,m2,s2));
	else
		printf("Pocet sekund = %lu",casovy_usek(r2,l2,d2,h2,m2,s2,r1,l1,d1,h1,m1,s1));
}
