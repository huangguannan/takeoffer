1��stdio.h
(1)�ļ�������
FILE *fopen(const char *filename,const char* mode);
	//fopen������filenameָ�����ļ���������һ����֮���������������򿪲���ʧ�ܣ��򷵻�NULL��
int fflush(FILE *stream)
	//���������˵��fflush��������д������������δд���ļ�����������д���ļ��С�����������˵��������δ����ġ�
		//�����д�Ĺ����з��������򷵻�EOF�����򷵻�0.fflush��NULL������ϴ���е��������
int fclose(FILE *stream)
	//	fclose����������δд�������д��stream�У������������е�����δ���������ݣ����ͷ��Զ������ȫ�������������ر�����
		//���������򷵻�EOF�����򷵻�0
���������ӣ�
��2����ʽ�����
int fprintf(FILE *stream,const char* format,...);
int printf(const char* format,...);
int sprintf(char* s,const char* format,...);

int vfprintf(FILE *stream,const char* format,va_list arg);
int vprintf(const char* format,va_list arg);
int vsprintf(char* s,const char* format,va_list arg);
vfprintf,vprintf,vsprintf���Ӧ��printf�����ȼۣ���������arg�����˿ɱ�������ϡ�
(3)��ʽ������
int fscanf(FILE *stream,const char* format,...);
int scanf(const char* format,...);
int sscanf(const char* s,const char* format,...);
(4)�ַ�����/�������
int fgetc(FILE *stream)
	fgetc��������stream������һ���ַ�����������Ϊunsigned char(��ת��Ϊint����)����������ļ�ĩβ���������򷵻�EOF��
char* fgets(char *s,int n,FILE *stream)
	fgets������ཫ��n-1���ַ����뵽����s�С����������з�ʱ���ѻ��з����뵽����s�У���ȡ������ֹ������s�ԡ�\0����β��fgets������������s��
	��������ļ���ĩβ���������򷵻�NULL��
int fputc(int c,FILE *stream)
	fputs�������ַ�c��ת��Ϊunsigned char���ͣ��������stream�С�������д����ַ����������򷵻�EOF��
int fputs(const char *s,FILE *stream)
	fputs�������ַ���s���������ַ���\n�����������stream�У�������һ���Ǹ�ֵ���������򷵻�EOF��
int getc(FILE *stream)
	getc�����ȼ���fgetc��
int getchar(void)
	getchar�����ȼ���getc(stdin)
char* gets(char *s)
	gets��������һ�������ж��뵽����s�У�����ĩβ�Ļ��з��滻Ϊ�ַ���\0��������������s����������ļ���ĩβ���������򷵻�NULL��
int putc(int c,FILE* stream)
	putc�ȼ���fputc.
int putchar(int c)
	putchar(c)�ȼ���putc(c,stdout)
int puts(const char* s)
	puts�������ַ���s��һ�����з������stdout�С�������������򷵻�EOF;���򣬷���һ���Ǹ�ֵ��
��5��ֱ������/�������
size_t fread(void* ptr,size_t size,size_t nobj,FILE* stream)
	fread��������stream�ж�ȡ���nobj������Ϊsize�Ķ��󣬲����浽ptrָ��������С������ض�ȡ�Ķ�����Ŀ���˷���ֵ����С��nobj������ͨ������feof��ferror��ý��ִ��״̬��
size_t fwrite(const void *ptr,size_t size,size_t nobj,FILE* stream)
	fwrite������ptrָ��������ж�ȡnobj������Ϊsize�Ķ��󣬲��������stream�С�����������Ķ�����Ŀ������������󣬷���ֵ��С��nobj��
��6���ļ���λ����
int fseek(FILE* stream,long offset,int origin)
	fseek����������stream���ļ�λ�ã������Ķ�д���������µ�λ�ÿ�ʼ�����ڶ������ļ�����λ�ñ�����Ϊ��origin��ʼ�ĵ�offset���ַ�����origin��ֵ����ΪSEEK_SET(�ļ���ʼ��)�������������е�����δ���������ݣ����ͷ��Զ������ȫ�������������ر�����
	SEEK_CUR����ǰλ�ã���SEEK_END���ļ����������������ı�����offset��������Ϊ0������˵��ftell���ص�ֵ����ʱorigin��ֵ������SEEK_SET����fseek��������ʱ������һ���Ǹ�ֵ��
long ftell(FILE *stream)
	ftell��������stream���ĵ�ǰ�ļ�λ�á�����ʱ���ú�������-1L
void rewind(FILE* stream)
	rewind(fp)�ȼ������fseek(fp,0L,SEEK_SET);clearerr(fp)��ִ�н����
int fgetpos��FILE* stream��fpos_t *ptr��
	fgetpos������stream���ĵ�ǰλ�ü�¼��*ptr�У�������fsetpos��������ʹ�á��������򷵻�һ����0ֵ��
int fsetpos��FILE* stream,const fpot_t *ptr��
	fsetpos��������stream�ĵ�ǰλ������Ϊfgetpos��¼��*ptr�е�λ�á��������򷵻�һ����0ֵ��
��7����������
void clearerr(FILE* stream)
	

int feof(FIEL* stream)
	�����������stream����ص��ļ���������feof������һ����0ֵ��
int ferror(FIEL* stream)
	�����������stream����صĴ���ָʾ����ferror������һ����0ֵ��	
void perror(const char* s)
	perror(s)������ӡ�ַ���s�Լ�errno������ֵ��Ӧ�Ĵ�����Ϣ���ú����Ĺ���������ִ��������䣺
fprintf(stderr,"%s:%s\n",s,"error message");

B.2�ַ�������<ctype.h>  //ÿ�������Ĳ�����Ϊint���ͣ�������ֵ������EOF�����unsigned char ���ͱ�ʾ���ַ��������ķ���ֵΪint���͡�
isalnum(c) //����isalpha(c)��isdigit(c)Ϊ��
isalpha(c)//����isupper(c)��islower(c)Ϊ��
iscntrl(c)// cΪ�����ַ�
isdigit(c)//cΪʮ��������
isgraph(c)//c�ǳ��ո���Ŀɴ�ӡ�ַ�
islower(c)//c��Сд��ĸ
isprint(c//c�ǰ����ո�Ŀɴ�ӡ�ַ�
ispunct��c��//c�ǳ��ո���ĸ��������Ŀɴ�ӡ�ַ�
isspace(c)//c�ǿո񡢻�ҳ�������з����س����������Ʊ�����������Ʊ��
isupper(c)//c�Ǵ�д��ĸ
isxdigit(c)//c��ʮ����������
��7λASCII�ַ����У��ɴ�ӡ�ַ��Ǵ�0x20(' ')��0x7E('~')֮����ַ��������ַ��Ǵ�0(NUL)��0x1F(US)֮����ַ��Լ��ַ�0x7F(DEL)
int tolower(c)//���c�Ǵ�д��ĸ����tolower(c)������Ӧ��Сд��ĸ�����򷵻�c��
int toupper(c)//���c��Сд��ĸ����toupper��c��������Ӧ�Ĵ�д��ĸ�����򷵻�c��


B.3�ַ�������<string.h>
//�����������ַ�����������һ����str��ͷ���ڶ�����mem��ͷ��������memmove�⣬����������û�ж�������ĸ�����Ϊ��
//�ȽϺ����Ѳ�����Ϊunsigned char���͵����鿴����
//���±��У�����s��t������Ϊchar *,cs��ct������Ϊconst char* ��n������Ϊsize_t��c������Ϊint������ת��Ϊchar���ͣ�
char *strcpy(s,ct)//���ַ���ct������'\0'�����Ƶ��ַ���s�У�������s.//����s�Ƿ�Խ�磬���ǽ�ct�а���'\0'��֮ǰ�����ݸ��Ƶ�s��
char *strncpy(s,ct,n)//���ַ���ct�����n���ַ����Ƶ��ַ���s�У�������s.���ct������n���ַ������á�\0����䡣���ct�ж���n��Ԫ�أ�����n��Ԫ�أ���������\0�������Ƶ�s��
char *strcat(s,ct)//���ַ���ct���ӵ�s��β����������s//����s�Ƿ�Խ�磬���ǽ�ct�а���'\0'��֮ǰ�����ݸ��Ƶ�sβ��
char *strncat(s,ct,n)//���ַ���ct�����ǰn���ַ����ӵ�s��β��������'\0'����������s��/����s�Ƿ�Խ�磬���ǽ�ct��n��Ԫ�ظ��Ƶ�sβ����Ȼ������n��Ԫ��֮�����һ��'\0'��
					//���ct������n���ַ������á�\0����䡣
int strcmp(cs,ct)//
int strncmp(cs,ct,n)
char *strchr(cs,c)//����ָ���ַ�c���ַ���cs�е�һ�γ��ֵ�λ�õ�ָ�룻���cs�в�����c���򷵻�NULL
char* strrchr(cs,c)//���һ�γ��ֵ�λ�õ�ָ��
char* strpbrk(cs,ct)//����һ��ָ�룬���μ����ַ���s1�е��ַ������������ַ����ַ���s2��Ҳ����ʱ����ֹͣ���飬�����ظ��ַ�λ�ã����ַ�null���������ڡ�
char* strstr(cs,ct)//����һ��ָ�룬��ָ���ַ���ct��һ�γ������ַ���cs�е�λ�ã�����ַ���ct�в������ַ���ct���򷵻�NULL��
size_t strlen(cs)//�����ַ����ĳ���
char* strerror(n)//����һ��ָ�룬��ָ���������n��Ӧ�Ĵ�����Ϣ�ַ���
char* strtok(s,ct)//��s��������ct�е��ַ��綨�ļǺš�
//��strtok(s,ct)����һϵ�е��ã����԰��ַ���s�ֳ����Ǻţ���Щ�Ǻ���ct�е��ַ�Ϊ�ֽ������һ�ε���ʱ��sΪ�ǿա�������s���ҵ�������ct���ַ��ĵ�һ���Ǻţ�
//��s�е���һ���ַ��滻Ϊ��\0����������ָ��Ǻŵ�ָ�롣���ÿ�ε���strtok����ʱ����s��ֵ�Ƿ�ΪNULLָʾ������������һ��������ct���ַ��ļǺš���s��û�������Ǻ�ʱ��������NULL��
//ÿ�ε���ʱ�ַ���ct���Բ�ͬ��

//��mem��ͷ�ĺ��������ַ�����ķ�ʽ������������ҪĿ�����ṩһ����Ч�ĺ����ӿڡ�
���±��г��ĺ����У�s��t�����;�Ϊvoid*,cs��ct�����;�Ϊconst void *,n������Ϊsize_t,c������Ϊint��
void* memcpy(s,ct,n)//���ַ���ct�е�n���ַ�������s�У�������s
void* memmove(s,ct,n)//�ú����Ĺ�����memcpy���ƣ�����ͬ���ǣ��������ص�ʱ���ú���������ȷִ�С�
int memcmp(s,ct,n)//��cs��ǰn���ַ���ct���бȽϡ�
void* memset(s,c,n)//��s�е�ǰn���ַ�����Ϊc
void* memchr(cs,c,n)//����һ��ָ�룬��ָ��c��cs�е�һ�γ��ֵ�λ�á������cs��ǰn���ַ����Ҳ���ƥ�䣬�򷵻�NULL

B.4��ѧ����<math.h>
���±��У�x,y������Ϊdouble,n������Ϊint�����к����ķ���ֵ�����;�Ϊdouble�����Ǻ����ĽǶ��û��ȱ�ʾ��
sin(x),cos(x),tan(x),asin(x),acos(x),atan(x),atan2(y,x),sinh(x),cosh(x),tanh(x),
exp(x)//�ݺ���e��x�η�
log(x)//��Ȼ����ln(x)
log10(x)//��10Ϊ�׵Ķ���
pow(x,y)//x��y�η�
sqrt(x)//ƽ����
ceil(x)//��С��x����С����
floor(x)//������x���������
fabs��x��//x�ľ���ֵ
ldexp(x,n)//����x*2��n�η�
modf(x,double* ip)//��x�ֳ��������ֺ�С�������֣������ֵ������ž���x��ͬ���ú�������С�����֣��������ֱ�����*ip��
fmod(x,y)//��x/y�ĸ���������������x��ͬ�����yΪ0������������ʵ����ء�


B.5  ʹ�ú���<stdlib.h>
double atof(const char* s)//���ַ���sת��Ϊdouble���ͣ��ú����ȼ���strtod(s,(char**)NULL);
int aoti(const char* s)//���ַ���sת��Ϊint���ͣ��ú����ȼ���(int)strtod(s,(char**)NULL,10);
long atol(const char* s)//���ַ���sת��Ϊlong���ͣ��ú����ȼ���strtod(s,(char**)NULL,10);
double strtod(const char *s,char **endp);//�ú������ַ���s��ǰ׺ת��Ϊdouble���ͣ�����ת��ʱ����s��ǰ���հ׷�������endpΪNULL,����ú�������ָ��s��δת�����֣�s�ĺ�׺���֣�
//��ָ�뱣������*endp�С����������磬�������ش����ʵ����ŵ�HUGE_VAL�����������磬�򷵻�0.������������£�errno����������ΪERANGE��
long strtol��const char *s,char **endp��int base��//�ú������ַ���s��ǰ׺ת��Ϊlong���ͣ�����ת��ʱ����s��ǰ���հ׷�������endpΪNULL,����ú�������ָ��s��δת�����֣�s�ĺ�׺���֣�
//��ָ�뱣������*endp�С����base��ȡֵ��2~36֮�䣬��ٶ��������Ը���Ϊ���׵ģ����base��ȡֵΪ0�������Ϊ�˽��ơ�ʮ���ƻ�ʮ�����ơ���0Ϊǰ׺���ǰ˽��ƣ���0x��0XΪǰ׺
//����ʮ�����ƣ����������磬�������ݽ���ķ��ŷ���LONG_MAX��LONG_MIN,ͬʱ��errno��ֵ����ΪERANGE��
unsigned long strtoul��const char *s,char **endp��int base��//����ͬstrtol��ֻ�ǽ��Ϊunsigned long
int rand(void)//����һ��0~RAND_MAX֮���α�����
void srand(unsigned int seed)//srand������seed��Ϊ�����µ�α��������е���������������seed�ĳ�ֵΪ1.
void *calloc(size_t nobj,size_t size)//calloc����Ϊ��nobj������Ϊsize�Ķ�����ɵ���������ڴ棬������ָ����������ָ�룻���޷�����Ҫ���򷵻�NULL��
void *malloc(size_t size)//�ú���Ϊ����Ϊsize�Ķ�������ڴ棬������ָ����������ָ�룬���޷�����Ҫ���򷵻�NULL���ú������Է����������г�ʼ����
void *realloc(void*p,size_t size)//realloc������pָ��Ķ���ĳ����޸�Ϊsize���ֽڡ�����·�����ڴ��ԭ�ڴ����ԭ�ڴ�����ݱ��ֲ��䣬���ӵĿռ䲻���г�ʼ��������·����
//�ڴ��ԭ�ڴ�С�����·����ڴ浥Ԫ������ʼ�������޷�����Ҫ���򷵻�NULL������������£�ԭָ��pָ��ĵ�Ԫ���ݱ��ֲ��䡣
void free(void *p);//�ͷ�pָ����ڴ�ռ䡣��p��ֵΪNULLʱ���ú�����ִ���κβ�����p����ָ����ǰʹ�ö�̬���亯������Ŀռ䡣
void abort(void)//abort����ʹ�����������ֹ���书����raise��SIGABRT�����ơ�
void exit(int status)//exit����ʹ����������ֹ��atexit�����ĵ���˳����Ǽǵ�˳���෴����������£������Ѵ򿪵��ļ�������������ϴ�������Ѵ򿪵��������رգ�����Ҳ�����ظ�������
//0ֵ��ʾ��ֹ�ɹ���Ҳ����ʹ��EXIT_SUCCESS����EXIT_FAILURE��Ϊ����ֵ��
int atexit(void (*fcn)())//atexit�����ǼǺ���fcn���ú������ڳ���������ֹʱ�����á�����Ǽ�ʧ�ܣ��򷵻ط�0ֵ��
int system(const char* s)//system�������ַ���s���ݸ�ִ�л��������s��ֵΪNULL,����������������ú������ط�0ֵ�����s��ֵ����NULL���򷵻�ֵ������ʵ���йء�
char* getenv(const char* name)//������name�йصĻ����ַ�����������ַ��������ڣ��򷵻�NULL��

void* bsearch��const void *key,const void *base,size_t n,size_t size,int (*cmp)(const void*keyval,const void *datum)��
//bsearch������base[0]...base[n-1]֮�������*keyƥ�����ں���cmp�У������һ�����������ҹؼ��֣�С�ڵڶ�������������������뷵��һ����ֵ��
//�����һ���������ڵڶ��������������뷵��0�������һ���������ڵڶ��������������뷵��һ����ֵ������base�е�����밴�������С�bsearch��������һ��ָ�룬��ָ��һ��ƥ���
//���������ƥ����򷵻�NULL��
void qsort(void *base,size_t n,size_t size,int (*cmp)(const void*,const void *))
//qsort������base[0]...base[n-1]�����еĶ��������������������ÿ������ĳ���Ϊsize���ȽϺ���cmp��bsearch�����е�������ͬ��
int abs(int n)
//abs����int���Ͳ���n�ľ���ֵ
long labs(long n)
//labs����long���Ͳ���n�ľ���ֵ

div_t div(int num,int denom)
//div��������num/denom���̺����������ѽ���ֱ𱣴��ڽṹ����div_t������int���͵ĳ�Աquot��rem��
ldiv_t div(long num,long denom)
//div��������num/denom���̺����������ѽ���ֱ𱣴��ڽṹ����div_t������long���͵ĳ�Աquot��rem��


B.6 ���<assert.h>
void assert(int ���ʽ)
//���ִ��assert(���ʽ)�������ʽ��ֵΪ0����assert�꽫��stderr�д�ӡһ����Ϣ
//��������NDEBUG,ͬʱ�ְ�����ͷ�ļ�<assert.h>����assert�꽫�����ԡ�     

B.9 �ź�<sighal.h>
void (*signal(int sig,void ��*handler��(int)))(int)
signal��������δ���������źš����handler��ֵ��SIG_DFL���������ʵ�ֶ����Ĭ����Ϊ�����handler��ֵ��SIG_IGN,����Ը��źţ����򣬵���handlerָ��ĺ��������ź���Ϊ������
�����ض����źţ�signal������handler��ǰһ��ֵ��������ִ����򷵻�ֵSIG_ERR

int raise(int sig)//��������ź�sig��������Ͳ��ɹ����򷵻�һ����0ֵ

B.10
clock_t clock(void)//�������س���ʼִ�к�ռ�õĴ�����ʱ�䡣����޷���ȡ������ʱ�䣬�򷵻�ֵΪ-1.clock()/CLOCKS_PER_SEC������Ϊ��λ��ʾ��ʱ�䡣










































































































