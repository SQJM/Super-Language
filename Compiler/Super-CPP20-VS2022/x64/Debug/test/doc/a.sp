import ":std"

int int1
int jkk
int* intp
int** intpp

; type sy name
; type sy name =
; type sy name = {}
; type sy name ()
; type sy name () {}
; type name ()
; err

typedef long int big_int

#message "fdsg"
#message "f"

#import "[.]/dd.sdef"
#import ":std/dd.sdef"

int a = 1
#asm
	ADD eax, 1, %a
	MOV %a, eax
#end

class string
{
	public:
		operator void =(char str[])
		operator void [](int index)

	private:
		char* str[] = nullptr
}

void string::=(char str[])
{
	this->str = str
}

class myObj
{
	public:
		virtual void vv()
		virtual void vvg()!
		void hi()
		void hi2()
		{
			std::print("hi2")
		}
}

void myObj::hi()
{

}

struct myStruct
{

}

enum myEnum
{

}

union myUnio
{

}

string dfhg = "gg" + "ds"
+ "fd"

#define am 23 4352\
e2

; 取消 am
#undef am

#define a

#ifdef am
string ddaaaa = "gf"
#endif

#ifndef am
string ddaaaan = "gf"
#endif

#ifdef a
string ddaa = "gf"
#endif
;void hell速度发对o)"
;[[分分]]]
void hello();

int& kk()
{
	int a = 1
	return &a
}

void hello()
{
	std::print("hello")
}

void hello(string str)

void hello(string str)
{
	std::print("hello" + str)
}

char ccc = 'g'
int main()
{
	bool bool_var_1 = null ; false
	int d = a;
	int ffff = 1

	async int fn()
	{
		return 1 + 1
	}

	int sdf = await fn()

	char dd[] = "d\"a1;fd2;"
	char dd1[] = "d\"a1;f中文d2;"
	char* ddp[] = new("sdsf")
	ddp = nullptr
	delete ddp[]

	static const int d

	const char sttt = 'f'

	result fn()
	match_ok()
	{
	}

	char ccc = 'g'

	int 中文 = 1

	hello()

	int k1=1
	int k2 =2
	int k3= 3

	int apl = (1 + 1) + (2 + 3 )

	switch()
	{
		case 0:
		{
			break
		}
	}

	bool* ptr_bool_var_1 = nullptr
	;-
	- 这个
	- 注释 -\;
	-;
	int sss = 2
	return 0
}