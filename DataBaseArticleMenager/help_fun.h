

int fun()
{
	fstream pl,pl1;
	int i,i1,i2;
	char naz[1000],naz1[1000];
	bool bl=true;

	i1=0;
	i2=0;
	pl1.open("kraje.txt",ios_base::out | ios_base::trunc);
	pl.open("krajepl.txt",ios_base::in);
	while(!pl.eof())
	{
		i2++;
		memset(naz,0,1000);
		memset(naz1,0,1000);
		pl.getline(naz,1000);
		i1++;
		
		naz1[0]='"';
		for(i=0;naz[i]!=0;i++)
		{
			naz1[i+1]=naz[i];
		}
		naz1[i+1]='"';
		naz1[i+2]=',';
		pl1.write(naz1,strlen(naz1));
		if(i1==20)
		{
			pl1.put(10);
			pl1.put(13);
			i1=0;
		}
	}
	pl.close();
	pl1.close();
	return i2;
}
