void getDate(char out[]);
struct tm *getDateRaw();
struct tm *toDateStruct(char input[]);
bool isDateToday(char date[]);
int getYear();
int getMonth();
int getDay();

void getDate(char out[]){
	time_t    rawtime;
	struct tm *info;

	time(&rawtime);
	info = localtime(&rawtime);

	char *outdate = "";
	strftime(outdate, 100, "%d:%m:%Y", info);
	strcpy(out, outdate);
}

struct tm *getDateStruct(){
	time_t    rawtime;
	struct tm *t = malloc(sizeof(struct tm));

	time(&rawtime);
	t = localtime(&rawtime);
	return(t);
}

struct tm *toDateStruct(char input[]){
	int day, month, year;

	static struct tm w =
	{
		0
	};

	sscanf(input, "%2d:%2d:%4d", &day, &month, &year);

	w.tm_year = year;
	w.tm_mon  = month;
	w.tm_mday = day;

	return(&w);
}

bool isDateToday(char date[]){
	struct tm *datet = toDateStruct(date);
	struct tm *today = getDateStruct();

	if(today->tm_year == datet->tm_year){
		if(today->tm_mon == datet->tm_mon){
			if(today->tm_mday == datet->tm_mday){
				return(true);
			}
		}
	}

	return(false);
}

int getYear(){
	char o[100];

	getDate(o);
	int y, m, d;
	sscanf(o, "%2d:%2d:%4d", &d, &m, &y);
	return(y);
}

int getMonth(){
	char o[100];

	getDate(o);
	int y, m, d;
	sscanf(o, "%2d:%2d:%4d", &d, &m, &y);
	return(m);
}

int getDay(){
	char o[100];

	getDate(o);
	int y, m, d;
	sscanf(o, "%2d:%2d:%4d", &d, &m, &y);
	return(d);
}
