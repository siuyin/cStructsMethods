#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include <string.h>

typedef struct {
	size_t len;
	size_t cap;
	char* buf;
} MyString;

#define INITIAL_MYSTRING_SIZE 40
MyString* MyStringSet(MyString* s, char* str) {
	size_t n = strlen(str);
	if (n==0) {
		s->cap = INITIAL_MYSTRING_SIZE;
		s->buf = calloc(1,s->cap);
		s->len = 0;
		return s;
	}

	if (n+1 > s->cap) {
		if(s->cap > 0) free(s->buf);
		s->cap = 2*n;
		s->buf = calloc(1,s->cap);
	}

	strcpy(s->buf,str);
	s->len=n;
	return s;
}

MyString* NewMyString(char* str) {
	MyString *s = calloc(1,sizeof(MyString)); 
	s = MyStringSet(s,str);
	return s;
}

char* MyStringStr(MyString* s) {
	return s->buf;
}


#define BUFLEN 33
typedef struct {
	uint8_t a;
	uint8_t b;
	MyString *s;
} MyStruct;

void MyStructIncr(MyStruct *m){
	m->a++;
	m->b++;
}

void MyStructPrint(MyStruct *m) {
	printf("a=%d, b=%d, s=%s\n",m->a,m->b,MyStringStr(m->s));
}

MyStruct* NewMyStruct() {
	MyStruct* m = calloc(1, sizeof(MyStruct));
	return m;
}


int main() {
	MyStruct* s = NewMyStruct();
	s->a=254;
	s->b=255;
	s->s=NewMyString("Brown Fox");
	MyStructIncr(s);
	MyStructPrint(s);
	free(s);

	MyString* ms = NewMyString("The quick brown fox.");
	printf("%s: %lu\n",MyStringStr(ms),ms->len);

	MyStringSet(ms,"The lazy dog was jumped over by the quick brown fox.");
	printf("%s: %lu\n",MyStringStr(ms),ms->len);

	return 0;
}
