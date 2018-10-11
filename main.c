#include <stdio.h>
#include <string.h>

typedef struct charStack{
	char *base,*top;
	size_t length;
}charStack;

void readFileGetContent(char *filenam,char **content);
int theStringValid(charStack *cs,char *content);

int main(int argc,char *argv[]){
	char *content = NULL;

	readFileGetCotent("testChar.txt", &content);
	if( content ){
		charStack curSt = {NULL,NULL,0};
		//判断字符序列的正确性
		int result = theStringValid(&curSt, content);

		printf("the format %s is", content);
		if( result ){
			printf(" ok!\n");
		}else{
			printf(" wrong!\n");
		}
	}

	return 0;
}

void readFileGetContent(char *filename,char **content){
	FILE *fp = fopen(filename,"r");

	if( fp ){
		size_t sizeGet = 0;

		if( getline(content, &sizeGet, fp) != -1 ){
			size_t clen = strlen(*content);
			(*content)[clen-1] = '\0';
		}else{
			*content = NULL;
		}
	}else{
		*content = NULL;
	}
}

int theStringValid(charStack *cs,char *content){
	int result = 0;
	size_t clen = strlen(content);

	cs->base = (char*)malloc(clen * sizeof(char));
	if( cs->base ){
		cs->top = cs->base;
		cs->length = clen;

		//遍历字符串并检测
		size_t pos = 1;//字符检测的序号
		*cs->top = content[0];
		cs->top++;

		while( cs->base!=cs->top && pos<clen ){
			if( content[pos]==')' || content[pos]==']' ){
				--cs->top;
			}else if( content[pos]=='(' || content[pos]=='[' ){
				*cs->top = content[pos];
			}

			pos++;
		}

		if( cs->base==cs->top ){
			result = 1;
		}
	}

	return result;
}
